// 实验x

mod tests {
    #[test]
    fn test_bs() {
        use super::*;
        let tree=bsptr::from_str("3 1 4 null 2");
        assert_eq!(true, bsptr::valid(&tree));
        assert_eq!(Some(&2), bsptr::rank(&tree, 2-1));
        let tree=bsptr::from_str("8 4 10 3 6 null 12 1 null 5");
        assert_eq!(true, bsptr::valid(&tree));
        assert_eq!(None, bsptr::rank(&tree, 9-1));
        let tree=bsptr::from_str("30 1 4 null 2");
        assert_eq!(false, bsptr::valid(&tree));
    }
    #[test]
    fn test_flush() {
        use super::*;
        let stree="3 1 4 null 2";
        let mut tree=bsptr::from_str(stree);
        println!("tree: {tree:?}");
        let v=bsptr::strip_le(&mut tree, &3);
        println!("removed: {v:?}");
        println!("tree: {tree:?}");
    }
}

// Binary Search Node

pub type BSPtr<T>=Option<Box<BSNode<T>>>;
pub struct BSNode<T>{
    left: BSPtr<T>,
    right: BSPtr<T>,
    value: T
}
impl<T> BSNode<T>{
    pub fn new(value: T)->Self{
        Self{left:None, right:None, value}
    }
}

use std::fmt::Debug;
impl<T: Debug> Debug for BSNode<T>{
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        use std::collections::VecDeque;
        let mut q=VecDeque::new();
        q.push_back(Some(self));
        let mut cur:usize=0;
        let mut max:usize=0;
        loop{
            let s=q.pop_front().unwrap();
            match s{
                None=>{
                    write!(f, "null")?;
                    q.push_back(None);
                    q.push_back(None);
                },
                Some(p)=>{
                    write!(f, "{:?}", p.value)?;
                    max = if let Some(_)=p.right {cur*2+2} 
                        else if let Some(_)=p.left {cur*2+1}
                        else {max};
                    q.push_back(p.left.as_deref());
                    q.push_back(p.right.as_deref());
                }
            };
            if cur!=max {
                write!(f, " ")?;
                cur+=1;
            } else {break;}
        }
        Ok(())
    }
} 

pub mod bsptr{
    use super::*;

    /// convert strings of level traversal into i32 binary tree
    pub fn from_str(s: &str)->BSPtr<i32>{
        use std::num::ParseIntError;
        fn opt_int(s: &str) -> Result<Option<i32>, ParseIntError> {
            match s{
                "null"=> Ok(None),
                _=>match s.parse(){
                Err(e)=>Err(e),
                Ok(x)=>Ok(Some(x))
            }}
        }
        // recursive closure
        struct P(Vec<Option<i32>>);
        impl P { fn parse(&self, i: usize)->BSPtr<i32>{
            if i>=self.0.len() {None}
            else {
                match self.0[i]{
                None=>None,
                Some(x)=>{
                    let mut t=Box::new(BSNode::new(x));
                    t.left=self.parse(i*2+1);
                    t.right=self.parse(i*2+2);
                    Some(t)
                }
            }}
        }}
        P(s.split(' ').map(|i|opt_int(i).unwrap()).collect())
            .parse(0)
    }
    
    /// returns whether a binary tree is a valid binary search tree
    pub fn valid(p: &BSPtr<i32>)->bool{
        struct BSInfo(i32, i32, bool); // min, max, valid
        fn bsinfo(p: &Box<BSNode<i32>>)->BSInfo{
            let mut info=BSInfo(p.value, p.value, true);
            if let Some(l)=&p.left{
                let i=bsinfo(l);
                if !i.2 || i.1>p.value {
                    info.2=false;
                    return info;
                }
                info.0=i.0;
            }
            if let Some(r)=&p.right{
                let i=bsinfo(r);
                if !i.2 || i.0<p.value {
                    info.2=false;
                }
                info.1=i.1;
            }
            info
        }
        match p{
            None=>true,
            Some(p)=>bsinfo(&p).2
        }
    }

    /// returns r-th object in inorder traversal
    pub fn rank<T>(p: &BSPtr<T>, r:usize)->Option<&T>{
        enum X<'a, T>{Found(&'a T), NotFound(usize)}
        fn iter<T>(p: &BSPtr<T>, r: usize)->X<T>{
            match p{
            None=>X::NotFound(r), // nullptr
            Some(p)=>{
                match iter(&p.left, r){
                X::Found(n)=>X::Found(n), // left
                X::NotFound(r)=>{  // mid and right
                    match r{
                    0=>X::Found(&p.value), // mid
                    _=>iter(&p.right, r-1) // right
                    }
                }}
            }}
        }
        match iter(p, r){
            X::Found(i)=>Some(i),
            X::NotFound(_)=>None
        }
    }
    
    /// strip object in binary search tree less than edge
    pub fn strip_le<T: Ord>(p: &mut BSPtr<T>, edge: &T)->Vec<T>{
        use std::mem::take;
        struct X<T: Ord>(Vec<T>);
        impl<T: Ord> X<T>{ fn strip(&mut self, p: &mut BSPtr<T>, edge: &T){
            while let Some(pp)=p{
                self.strip(&mut pp.left, edge);
                if pp.value<*edge{ // strip itself and left
                    let node=take(p).unwrap();
                    self.0.push(node.value);
                    *p=node.right;
                } else {break;}
            }
        }}
        let mut x=X(Vec::new());
        x.strip(p, edge);
        x.0
    }
}