//! # Heaps
//! Include binary heap, pairing heap, and leftist tree
//! 
//! We implement higher priority root heap

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

/// Normal Binary Tree Node with extra information.  
/// We suppose store generic value in `value` field and
/// algorithm-related thing in `extra` field.
pub struct RawNode<T, E=()>{
    value: T,
    left: Option<NodeBox<T, E>>,
    right: Option<NodeBox<T, E>>,
    extra: E,
}

/// boxed wrapper of Node, used inside module
struct NodeBox<T, E=()>(Box<RawNode<T,E>>);

impl<T,E> NodeBox<T,E>{
    fn take_right(&mut self)->Option<Self>{
        take(&mut self.right)
    }
    fn take_left(&mut self)->Option<Self>{
        take(&mut self.left)
    }
}

impl<T, E> Deref for NodeBox<T, E>{
    type Target = RawNode<T, E>;
    fn deref(&self) -> &Self::Target {
        &self.0
    }
}
impl<T, E> DerefMut for NodeBox<T, E>{
    fn deref_mut(&mut self) -> &mut Self::Target {
        &mut self.0
    }
}
impl<T, E> Into<Node<T,E>> for NodeBox<T,E>{
    fn into(self) -> Node<T,E> {
        Node(self.0)
    }
}
impl<T, E> From<Node<T,E>> for NodeBox<T,E>{
    fn from(value: Node<T,E>) -> Self {
        Self(value.0)
    }
}

/// boxed wrapper of Node, used inside module
pub struct Node<T, E=()>(Box<RawNode<T,E>>);

impl<T, E> Deref for Node<T, E>{
    type Target = T;
    fn deref(&self) -> &Self::Target {
        &self.0.value
    }
}
impl<T, E> DerefMut for Node<T, E>{
    fn deref_mut(&mut self) -> &mut Self::Target {
        &mut self.0.value
    }
}


/// Pairing Heap
/// 
/// Known issue:
/// - [x] Stack Overflow caused by recursive implement
/// - [ ] expensive malloc and free call each push and pop
pub struct Pairing<T: PartialOrd>{
    root: Option<NodeBox<T>>
}

impl <T: PartialOrd> Pairing<T>{
    pub fn new()->Self{
        Self{root: None}
    }
    /// will raplace self.root with None
    #[inline(always)]
    fn take_root(&mut self)->Option<NodeBox<T>>{
        take(&mut self.root)
    }
    /// treat nodebox as pairing heap root
    fn meld_node(mut x: NodeBox<T>, mut y: NodeBox<T>)->NodeBox<T>{
        if x.value<y.value {(x,y)=(y,x);} // x greater, as root
        y.right=take(&mut x.left); // x son as y peer
        x.left=Some(y);
        x
    }
    /// meld two pairing tree
    pub fn meld(self, y: Self)->Self{
        if let None=self.root {return y;}
        if let None=y.root {return self;}
        // SAFETY: both x and y are not none
        Self::meld_node(self.into(), y.into()).into()
    }
    pub fn push(self, value: T)->Self{
        let y=NodeBox(Box::new(RawNode{
            value, left:None, right:None, extra:()
        }));
        self.meld(y.into())
    }
    /// legacy recursive implement of pop, may stack overflow if
    /// too many nodes are pushed without pop
    pub fn pop_legacy(&mut self)->Option<Node<T,()>>{
        if let None=self.root {return None;}
        let mut root=self.take_root().unwrap();
        self.root=match root.take_left(){
            None=>None,
            Some(left)=>Some(Self::merge_legacy(left))
        };
        Some(root.into())
    }

    /// merge all siblings into one tree
    fn merge_legacy(mut node: NodeBox<T>)->NodeBox<T>{
        match node.take_right(){
        None=>node, // already a valid root node
        Some(mut sib)=>{
            match sib.take_right(){
            None=>Self::meld_node(node, sib),
            Some(sibr)=>Self::meld_node(
                Self::merge_legacy(sibr),
                Self::meld_node(node, sib)
            )
            }
        }}
    }

    pub fn pop(&mut self)->Option<Node<T,()>>{
        if let None=self.root {return None;}
        let mut root=self.take_root().unwrap();
        if let Some(left)=root.take_left(){
            self.root=Some(Self::merge(left));
        }
        Some(root.into())
    }

    // merge from left to right
    fn merge(mut node: NodeBox<T>)->NodeBox<T>{
        while let Some(mut right)=node.take_right(){ match right.take_right(){
            None=>{ // finish!
                node=Self::meld(node.into(), right.into()).into();
            },
            Some(mut rr)=>{ // pair right and rr
                let rrr=rr.take_right();
                node=Self::meld(rr.into(), right.into()).into();
                node.right=rrr;
            }
        }}
        node
    }
}

impl <T: PartialOrd> From<NodeBox<T>> for Pairing<T>{
    fn from(value: NodeBox<T>) -> Self {
        unsafe{std::mem::transmute(value)}
    }
}

impl <T: PartialOrd> Into<NodeBox<T>> for Pairing<T>{
    fn into(self) -> NodeBox<T> {
        unsafe{std::mem::transmute(self)}
    }
}

#[cfg(test)] #[test]
fn test_pairing_legacy(){
    use rand::random;
    let mut heap=Pairing::new();
    let mut x=i32::MAX;
    for _ in 0..N { match random::<bool>(){
        true=>{
            let v=random::<i32>();
            if v>x {x=v;}
            heap=heap.push(v);
        },
        false=>{
            if let Some(v)=heap.pop_legacy(){
                let v=*v;
                assert!(x>=v);
                x=v;
            }
        }
    }};
}

#[cfg(test)] #[test]
fn test_pairing(){
    use rand::random;
    let mut heap=Pairing::new();
    let mut x=i32::MAX;
    for _ in 0..N { match random::<bool>(){
        true=>{
            let v=random::<i32>();
            if v>x {x=v;}
            heap=heap.push(v);
        },
        false=>{
            if let Some(v)=heap.pop(){
                let v=*v;
                assert!(x>=v);
                x=v;
            }
        }
    }};
}

use std::{mem::take, ops::{Deref, DerefMut}};

#[cfg(test)]
const N:usize=100000;