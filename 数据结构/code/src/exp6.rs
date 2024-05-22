// 实验x

mod tests {
    #[test]
    fn test_bs() {
        use super::*;
        let tree=parse_tree("3 1 4 null 2");
        assert_eq!(true, is_bs(&tree));
        assert_eq!(Some(&2), bs_rank(&tree, 2-1));
        let tree=parse_tree("8 4 10 3 6 null 12 1 null 5");
        assert_eq!(true, is_bs(&tree));
        assert_eq!(None, bs_rank(&tree, 9-1));
        let tree=parse_tree("30 1 4 null 2");
        assert_eq!(false, is_bs(&tree));
    }
    #[test]
    fn test_flush() {
        use super::*;
        let stree="3 1 4 null 2";
        let tree=parse_tree(stree);
        println!("{tree:?}");
    }
}
use std::{collections::VecDeque, fmt::Debug, str::FromStr};
pub type BSPtr<T>=Option<Box<BSNode<T>>>;
pub struct BSNode<T>{
    left: BSPtr<T>,
    right: BSPtr<T>,
    value: T
}
impl<T> BSNode<T>{
    pub fn new(v: T)->Self{
        Self{left: None, right:None, value: v}
    }
}
impl<T: Debug> Debug for BSNode<T>{
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let mut q=VecDeque::new();
        q.push_back(Some(self));
        let mut cur:usize=0;
        let mut max:usize=0;
        while cur<=max{
            let s=q.pop_front().unwrap();
            let r=match s{
                None=>{
                    q.push_back(None);
                    q.push_back(None);
                    write!(f, "null")
                },
                Some(p)=>{
                    max = if let Some(_)=p.right {cur*2+2} 
                        else if let Some(_)=p.left {cur*2+1}
                        else {max};
                    q.push_back(p.left.as_deref());
                    q.push_back(p.right.as_deref());
                    write!(f, "{:?}", p.value)
                }
            };
            if r.is_err() {return r;}
            if cur!=max {write!(f, " ")?;}
            cur+=1;
        }
        println!("max: {max}");
        Ok(())
    }
} 

pub fn parse_tree(s: &str)->BSPtr<i32>{
    fn opt_int(s: &str) -> Result<Option<i32>, ()> {
        if s=="null" {Ok(None)}
        else {i32::from_str(s).map_or(Err(()), |n|{Ok(Some(n))})}
    }
    // recursive closure
    struct P(Vec<Option<i32>>);
    impl P{ fn parse(&self, i: usize)->BSPtr<i32>{
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

pub fn is_bs(p: &BSPtr<i32>)->bool{
    struct BSInfo(i32, i32, bool); // min, max
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
pub fn bs_rank<T>(p: &BSPtr<T>, r:usize)->Option<&T>{
    enum X<'a, T>{Found(&'a T), NotFound(usize)}
    fn iter<'a, T>(p: &'a BSPtr<T>, r: usize)->X<'a, T>{
        match p{
            None=>X::NotFound(r),
            Some(p)=>{
                let x=iter(&p.left, r);
                match x{
                    X::Found(_)=>x,
                    X::NotFound(r)=>{ match r{
                        0=>X::Found(&p.value),
                        _=>iter(&p.right, r-1)
                    }}
                }
            }
        }
    }
    match iter(p, r){
        X::Found(i)=>Some(i),
        X::NotFound(_)=>None
    }
}

// Problem y: y
mod y {
}
