//! # Heaps
//! Include binary heap, pairing heap, and leftist tree
//! 
//! We implement higher priority root heap

use std::{mem::ManuallyDrop, ops::{Deref, DerefMut}};

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

/// Leftist tree
/// 
/// Known issue:
/// - memory leak caused by manually drop
pub struct Leftist<T: PartialOrd>{
    root: usize,
    buf: Vec<LeftistNode<T>>,
    pool: Vec<usize> // will reuse node
}

impl<T: PartialOrd> Leftist<T>{
    pub fn new()->Self{Self{
        root: 0,
        // SAFETY: value won't drop
        buf: vec![LeftistNode{
            left:0, right:0, dist:-1,
            value: unsafe{std::mem::zeroed()}
        }],
        pool: Vec::new()
    }}
    
    pub fn merge(&mut self, mut x: usize, mut y: usize)->usize{
        if x==0 || y==0 {return x|y;}
        let b=&mut self.buf; // buffer alias
        // x as greater
        if b[x].value < b[y].value {(x,y)=(y,x);}
        // merge x.right and y
        let newx=b[x].right;
        self.buf[x].right=self.merge(newx, y);
        let b=&mut self.buf; // buffer alias
        // leftist
        if b[b[x].right].dist > b[b[x].left].dist{
            (b[x].right, b[x].left)=(b[x].left, b[x].right);
        }
        // maintain dist
        b[x].dist=b[b[x].right].dist+1;
        x
    }

    pub fn push(&mut self, value: T){
        let new_node=LeftistNode{left:0, right:0, dist:0, value: ManuallyDrop::new(value)};
        let x=match self.pool.pop(){
        Some(i)=>{
            self.buf[i]=new_node;
            i
        },
        None=>{
            self.buf.push(new_node);
            self.buf.len()-1
        }};
        self.root=self.merge(self.root, x);
    }

    pub fn pop(&mut self)->Option<T>{
        if self.root==0 {return None;}
        let root=&mut self.buf[self.root];
        let output=unsafe{ManuallyDrop::take(&mut root.value)};
        root.dist=-1;
        self.pool.push(self.root);
        let root=&self.buf[self.root];
        self.root=self.merge(root.left, root.right);
        Some(output)
    }
}

impl<T: PartialOrd> Drop for Leftist<T>{
    fn drop(&mut self) {
        let b=&mut self.buf;
        for i in b{
            if i.dist!=-1{
                unsafe{std::ptr::drop_in_place(
                    i.value.deref_mut() as *mut T
                )}
            }
        }
    }
}

#[cfg(test)] #[test]
fn test_leftist(){
    use rand::random;
    let mut heap=Leftist::new();
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