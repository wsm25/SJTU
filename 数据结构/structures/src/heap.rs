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

struct LeftistNode<T: PartialOrd>{
    left: LeftPtr<T>, // 0 if null
    right: LeftPtr<T>,
    dist: isize, // -1 if null
    value: T,
}
type LeftPtr<T>=Option<Box<LeftistNode<T>>>;

impl<T: PartialOrd> LeftistNode<T>{
    fn swap(&mut self){
        std::mem::swap(&mut self.left, &mut self.right);}
    fn take_right(&mut self)->LeftPtr<T>{
        std::mem::take(&mut self.right)}
    fn take_left(&mut self)->LeftPtr<T>{
        std::mem::take(&mut self.left)}
}

/// Leftist tree, mergeable with other leftist tree.
/// 
/// # Example
/// ```
/// use structures::heap::Leftist;
/// let mut heap1=Leftist::new();
/// let mut heap2=Leftist::new();
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
pub struct Leftist<T: PartialOrd>{
    root: LeftPtr<T>
}

impl<T: PartialOrd> Leftist<T>{
    fn merge_ptr(x: LeftPtr<T>, y: LeftPtr<T>)->LeftPtr<T>{
        if let None=x {return y;}
        if let None=y {return x;}
        // safety: nonnull
        let mut x=unsafe{x.unwrap_unchecked()};
        let mut y=unsafe{y.unwrap_unchecked()};
        // x as greater
        if x.value < y.value {(x,y)=(y,x);}
        // merge x.right and y
        x.right=Self::merge_ptr(x.take_right(), Some(y));
        // leftist
        fn dist<T: PartialOrd>(x: &LeftPtr<T>)->isize{match x{
            None=>-1,
            Some(x)=>x.dist
        }}
        if dist(&x.right) > dist(&x.left){
            x.swap();
        }
        // maintain dist
        x.dist=dist(&x.right)+1;
        Some(x)
    }
    fn take_root(&mut self)->LeftPtr<T>{
        std::mem::take(&mut self.root)
    }
    pub fn new()->Self{
        Self{root:None}
    }
    pub fn push(&mut self, value:T){
        let newnode=Box::new(LeftistNode{
            left:None, right:None, dist:0,
            value
        });
        self.root=Self::merge_ptr(
            self.take_root(), Some(newnode));
    }
    pub fn pop(&mut self)->Option<T>{
        if let None=self.root{return None;}
        let mut root=unsafe{self.take_root().unwrap_unchecked()};
        self.root=Self::merge_ptr(root.take_left(), root.take_right());
        Some(root.value)
    }
    pub fn merge(&mut self, other: Self){
        self.root=Self::merge_ptr(
            self.take_root(), other.root);
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