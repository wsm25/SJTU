
mod tests{
    #[test]
    fn test_nodelist(){
        use super::nodelist::NodeList;
        let mut l1=NodeList::from_vec(vec![1, 3, 5, 7, 9]);
        l1.insert(0,2);
        l1.erase(4,7);
        assert_eq!(l1.vector(), vec![2, 1, 3, 9]);

    }
    
    #[test]
    fn test_calculator() {
        fn assert_eqf(x: f64, y:f64){
            if (x-y).abs()>1e-4 {
                assert_eq!(x, y);
            }
        }
        use super::calculator::calculate;
        // testcase 1
        assert_eqf(7.5, calculate(
            "5 7 2 3 * - * 10 4 / +".to_string()
        ).unwrap());
        // testcase1 enhanced
        assert_eqf(7.5, calculate(
            "5 7 2 3*-*10 4/+".to_string()
        ).unwrap());
        // testcase 2
        assert_eq!(Err(()), calculate(
            "1 2 + +".to_string()
        ));
    }
}


/// Problem 1: 链表
pub mod nodelist {
    type Link = Option<Box<Node>>;
    struct Node {
        value: i32,
        next: Link
    }
    
    // TODO iterator and drop implement with
    // ```rust
    // type Link = Cell<Option<Box<Node>>>;
    // ```
    pub struct NodeList{
        head: Box<Node>
    }

    use std::mem;
    impl Node {
        fn new(value: i32) ->Box<Self>{
            Box::new(Node{value, next:None})
        }

        fn insert(&mut self, value: i32){
            match &self.next { // &mut 外部可变，as_mut 内部可变
                None => {
                    self.next=Some(Node::new(value));
                }
                Some(_) => {
                    let next = mem::replace(&mut self.next, Some(Node::new(value)));
                    self.next.as_mut().unwrap().next=next;
                }
            }
        }

        fn remove_next(&mut self){
            let mut next1;
            match self.next {
                None => return,
                Some(_) => next1=self.next.take().unwrap(),
            }
            match next1.next{
                None => {
                    drop(self.next.take());
                }
                Some(_) => {
                    self.next=next1.next.take();
                    drop(next1);
                }
            }
        }
    }
    
    
    impl NodeList{
        pub fn new() -> Self{
            NodeList{head: Node::new(0)}
        }

        pub fn iter(&mut self){
            
        }

        pub fn from_vec(v: Vec<i32>) -> NodeList{
            let mut l = NodeList::new();
            let mut p =l.head.as_mut();
            for i in v {
                p.insert(i);
                p=p.next.as_mut().unwrap();
            }
            return l;
        }

        pub fn insert(&mut self, mut i: usize, n: i32){
            let mut p =self.head.as_mut();
            while i>0 {
                if let None = p.next{
                    return;
                }
                p=p.next.as_mut().unwrap();
                i-=1;
            }
            p.insert(n);
        }

        pub fn erase(&mut self, a: i32, b: i32){
            let mut p =self.head.as_mut();
            loop {
                let value;
                match &p.next {
                    None => break,
                    Some(next) => value=next.value,
                }
                if value>=a && value<=b {
                    p.remove_next();
                } else {
                    p=p.next.as_mut().unwrap();
                }
            }
        }

        pub fn vector(&self)->Vec<i32>{
            let mut l=Vec::new();
            let mut p =self.head.as_ref();
            loop {
                match &p.next {
                    None => break,
                    Some(next) => l.push(next.value),
                }
                p=p.next.as_ref().unwrap();
            }
            return l;
        }
    }
}


/// Problem 2: 四则计算器
pub mod calculator {
    pub fn calculate(s: String)->Result<f64, ()>{
        let mut st=Vec::new();
        let mut input = s.chars().into_iter();
        let mut chn=input.next();
        while let Some(ch)=chn {
            match ch {
            '+' | '-' | '*' | '/' => {
                if st.len()<2{
                    return Err(());
                }
                let b=st.pop().unwrap();
                let mut a=st.pop().unwrap();
                match ch {
                    '+'=> a+=b,
                    '-'=> a-=b,
                    '*'=> a*=b,
                    '/'=> a/=b,
                    _=>()
                }
                st.push(a);
                chn=input.next();
            },
            '0'..='9' => {
                let mut n = (ch as i32)-('0' as i32);
                chn=input.next();
                while let Some(ch)=chn{
                    if ch<'0' || ch>'9' {
                        break;
                    }
                    n=n*10+(ch as i32)-('0' as i32);
                    chn=input.next();
                }
                st.push(n as f64);
            },
            _ => chn=input.next(),
            }
        }
        if st.len()!=1{
            Err(())
        } else {
            Ok(st.pop().unwrap())
        }
    }
}
