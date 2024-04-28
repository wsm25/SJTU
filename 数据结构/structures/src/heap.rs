//! # Heaps
//! Include binary heap, pairing heap, and leftist tree
//! 
//! We implement higher priority root heap

use std::{mem::{ManuallyDrop, MaybeUninit}, ops::DerefMut};
use core::num::NonZeroUsize;

use crate::utils::Share;

/// f(x) returns i that i=2^x wile i <= x< 2*i
pub fn half2(x: usize)->usize{
    1<<(63-x.leading_zeros())
}

/// # Binary Tree
/// Implement with sequent storage.
/// 
/// As all nodes are stored in Vec, we cannot provide safe
/// reference for a pushed value, as it may move after any
/// another push and pop operation.
/// 
/// # Todo:
/// implement HeapVec with interfaces
/// - unchecked indexing, from 1
/// - drop and new
/// - mem allocation in pop
/// - unchecked swap
pub struct Binary<T: PartialOrd>{
    heap: Vec<T> // use vector 
}

impl<T: PartialOrd> Binary<T>{
    pub fn new()->Self{
        Self{heap: Vec::new()}
    }
    fn up(&mut self, mut index: usize)->usize{
        let h=&mut self.heap;
        while index>0 && h[index]>h[(index-1)/2]{
            h.swap(index, (index-1)/2);
            index=(index-1)/2;
        }
        index
    }
    fn down(&mut self, mut index: usize)->usize{
        let maxindex=self.heap.len();
        let h=&mut self.heap;
        let mut t=index*2+1;
        while t<maxindex {
            if t+1<maxindex && h[t+1]>h[t] {t+=1;} // select bigger
            if h[index]>=h[t] {break;} // stop when bigger
            h.swap(index, t);
            index=t;
            t=index*2+1;
        }
        index
    }
    /// pop root node
    pub fn pop(&mut self)->Option<T>{
        let h=&mut self.heap;
        let len=h.len();
        if len==0 {return None;}
        // len>0
        h.swap(0, len-1);
        let tail=h.pop().unwrap();
        self.down(0);
        Some(tail)
    }
    /// push a node
    pub fn push(&mut self, x: T){
        let h=&mut self.heap;
        let end=h.len();
        h.push(x);
        self.up(end);
    }
    /// flush all content, i.e. ordered sequence of content
    pub fn flush(&mut self)->Vec<T>{
        std::iter::from_fn(||self.pop()).collect()
    }
}

impl<T: PartialOrd> From<Vec<T>> for Binary<T>{
    fn from(v: Vec<T>) -> Self {
        let tail=v.len();
        let mut ret=Self{heap: v};
        for i in (0..half2(tail)).rev() {
            ret.down(i);
        }
        ret
    }
}

#[cfg(test)] #[test]
fn test_binary(){
    use rand::random;
    let mut heap=Binary::new();
    let mut x=i32::MAX;
    for _ in 0..N { match random::<bool>(){
        true=>{
            let v=random::<i32>();
            if v>x {x=v;}
            heap.push(v);
        },
        false=>{
            if let Some(v)=heap.pop(){
                assert!(x>=v);
                x=v;
            }
        }
    }};
}

struct LeftistNode<T: PartialOrd>{
    left: usize, // 0 if null
    right: usize,
    dist: isize, // -1 if null
    value: ManuallyDrop<T>,
}

struct LeftistPool<T: PartialOrd>{
    buf: Vec<LeftistNode<T>>,
    pool: Vec<NonZeroUsize> // will reuse node
}

impl<T: PartialOrd> LeftistPool<T>{
    pub fn merge(&mut self, mut x: usize, mut y: usize)->usize{
        if x==0 || y==0 {return x|y;}
        let b=&mut self.buf; // buffer alias
        // x as greater
        if b[x].value < b[y].value {(x,y)=(y,x);}
        // merge x.right and y
        let newx=b[x].right;
        self.buf[x].right=self.merge(b[x].right, y);
        let b=&mut self.buf; // buffer alias
        // leftist
        if b[b[x].right].dist > b[b[x].left].dist{
            (b[x].right, b[x].left)=(b[x].left, b[x].right);
        }
        // maintain dist
        b[x].dist=b[b[x].right].dist+1;
        x
    }
    /// for alias usage
    fn fields(&mut self)->(&mut Vec<LeftistNode<T>>, &mut Vec<NonZeroUsize>){
        (&mut self.buf, &mut self.pool)
    }
}
impl<T: PartialOrd> Drop for LeftistPool<T>{
    fn drop(&mut self) {
        let b=&mut self.buf;
        for i in b{
            if i.dist!=-1{
                unsafe{std::ptr::drop_in_place(
                    (i.value.deref_mut()) as *mut T
                )}
            }
        }
    }
}

/// Leftist forest, can generate new leftist tree, mergeable
/// with other trees in the forest.
/// 
/// # Example
/// ```
/// use structures::heap::LeftistForest;
/// let mut forest=LeftistForest::new();
/// let mut heap1=forest.new_tree();
/// let mut heap2=forest.new_tree();
/// for i in [1,1,4,5,1,4]{
///     heap1.push(i)
/// }
/// for i in [1,9,1,9,8,1,0]{
///     heap2.push(i)
/// }
/// heap1.merge(heap2);
/// for i in [9,9,8,5,4,4,1,1,1,1,1,1,0]{
///     assert_eq!(i, heap1.pop().unwrap());
/// }
/// ```
pub struct LeftistForest<T: PartialOrd>(Share<LeftistPool<T>>);
impl<T: PartialOrd> LeftistForest<T>{
    pub fn new()->Self{
        Self(Share::new(LeftistPool{
        // SAFETY: value won't drop
        buf: vec![LeftistNode{
            left:0, right:0, dist:-1,
            value: unsafe{MaybeUninit::uninit().assume_init()}
        }],
        pool: Vec::new()
        }))
    }
    pub fn new_tree(&self)->LeftistTree<T>{
        LeftistTree{ root: 0, forest: self.0.clone() }
    }
}

pub struct LeftistTree<T: PartialOrd>{
    root: usize,
    forest: Share<LeftistPool<T>>,
}

impl <T: PartialOrd> LeftistTree<T>{
    pub fn new(rc: &LeftistForest<T>)->Self{
        rc.new_tree()
    }
    pub fn push(&mut self, value: T){
        let new_node=LeftistNode{
            left:0, right:0, dist:0, 
            value: ManuallyDrop::new(value)
        };
        let (buf, pool)=self.forest.fields();
        let x=match pool.pop(){
        Some(i)=>{
            let i=i.get();
            buf[i]=new_node;
            i
        },
        None=>{
            buf.push(new_node);
            buf.len()-1
        }};
        self.root=self.forest.merge(self.root, x);
    }

    pub fn pop(&mut self)->Option<T>{
        if self.root==0 {return None;}
        let (buf, pool)=self.forest.fields();
        let root=&mut buf[self.root];
        let output=unsafe{ManuallyDrop::take(&mut root.value)};
        root.dist=-1;
        // safety: root!=0
        pool.push(unsafe{NonZeroUsize::new_unchecked(self.root)});
        // FUCKING rust ownership
        let (left, right)=(buf[self.root].left, buf[self.root].right);
        self.root=self.forest.merge(left, right);
        Some(output)
    }

    pub fn merge(&mut self, other: Self){
        if self.forest!=other.forest {
            panic!("merge leftist tree from different forest!");
        }
        self.root=self.forest.merge(self.root, other.root)
    }
}



#[cfg(test)] #[test]
fn test_leftist(){
    use rand::random;
    let forest=LeftistForest::new();
    let mut heap=LeftistTree::new(&forest);
    let mut x=i32::MAX;
    for _ in 0..N { match random::<bool>(){
        true=>{
            let v=random::<i32>();
            if v>x {x=v;}
            heap.push(v);
        },
        false=>{
            if let Some(v)=heap.pop(){
                assert!(x>=v);
                x=v;
            }
        }
    }};
}

#[cfg(test)]
const N:usize=10000;