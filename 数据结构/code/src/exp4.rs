/// 实验4 树

mod tests {
    #[test]
    fn test_leaves() {
        use super::*;
        assert_eq!(3,count_leaves(
            &parse_to_vec("8 4 10 3 7 null 12 null null 6")
        ));
        assert_eq!(3,count_leaves(
            &parse_to_vec("1 1 2 null 1 2 1")
        ));
    }

    #[test]
    fn test_strip(){
        use super::*;
        assert_eq!(
            parse_to_vec("1 1 0 null 1 null 1"),
            strip(parse_to_vec("1 1 0 null 1 0 1"))
        );
        assert_eq!(
            parse_to_vec("1 0 null 1 1"),
            strip(parse_to_vec("1 0 0 1 1 0 0"))
        )
    }

    #[test]
    fn test_full(){
        use super::is_full;
        assert_eq!(true,  is_full("A B C @ @ D @ @ E F @ @ G @ @"));
        assert_eq!(false, is_full("A B C D @ E @ @ F @ @ @ G @ @"));
    }

    #[test]
    fn test_ancestor(){
        use super::*;
        let tree=parse_to_vecstr("a b d null c null f");
        assert_eq!(Some(&"a"), common_ancestor(&tree, 2, 7));
        assert_eq!(None, common_ancestor(&tree, 2, 6));
    }
}

/// Parses string like `"1 1 2 null 1 2 1"` to Vector like 
/// `[1,1,2,None,1,2,1]`
pub fn parse_to_vec(s: &str)->Vec<Option<i32>>{
    s.split(" ").map(|s|{
        match s{
            "null"=>None,
            _=>Some(s.parse().unwrap())
        }
    }).collect()
}


/// Parses string like `"a b null c"` to Vector like 
/// `["a", "b", None, "c"]`
pub fn parse_to_vecstr(s: &str)->Vec<Option<&str>>{
    s.split(" ").map(|s|{
        match s{
        "null" => None,
        _ => Some(s)
        }
    }).collect()
}

/// Problem 1: Count leaves
pub fn count_leaves(input: &[Option<i32>])->i32{
    let mut v=Vec::new();
    for i in input{
    match i{
        None=>v.push(0), // null
        Some(_)=>{
            v.push(1);
            let t=v.len()>>1;
            v[t]=0;
        }
    }
    };
    v.iter().sum()
}

/// Problem 2: Strip Tree
pub fn strip(input: Vec<Option<i32>>)->Vec<Option<i32>>{
    // closure isn't expressive enough, expecially for recursion
    struct Stripper(Vec<Option<i32>>);
    impl Stripper{
        /// true for stripped, false for not stripped
        fn strip(&mut self, index:usize)->bool{
            match self.0.get(index){
            None=>true, // out of bound, as if stripped
            Some(x)=>match x.clone(){ // clone derefs and copies the value
            None=>true, // empty, as if stripped
            Some(x)=>{
                // recursive strip
                let left=self.strip((index<<1)+1);
                let right=self.strip((index<<1)+2);
                match x{
                1=>false, // not strip
                _=>{ // may strip
                    if left&&right{ // strip
                        self.0[index]=None;
                        true
                    } else { // not strip
                        false
                    }
                }
            }}}}
        }
    }
    let mut v=Stripper(input);
    v.strip(0);
    while let Some(None)=v.0.last(){v.0.pop();} // pop ending None
    v.0
}

/// Problem 3: full binary tree
pub fn is_full(s: &str)->bool{
    // parse
    let input=s.split(" ")
        .map(|s|{match s{"@"=>false, _=>true}});

    // recursion
    enum BranchStatus{Empty, Full, NotFull}
    use BranchStatus::*;
    // preorder iterator
    struct PreorderTree<T>(T);
    impl<T: Iterator<Item = bool>> PreorderTree<T>{
        fn is_full(&mut self)->BranchStatus{
            match self.0.next(){
            None | Some(false) => Empty,
            Some(true)=>{ // non-null
                match (self.is_full(), self.is_full()){
                (Empty, Empty) | (Full, Full)=>Full,
                _=>NotFull
                }
            }}
        }
    }
    
    match PreorderTree(input).is_full(){
        NotFull=>false,
        _=>true
    }
}

/// Problem 4: Common ancestor
pub fn common_ancestor<T>(i: &Vec<Option<T>>, x:usize, mut y:usize)->Option<&T>{
    match (&i[x-1], &i[y-1]){
    (Some(_), Some(_))=>{
        y>>=x.leading_zeros()-y.leading_zeros();
        let index=(x>>(usize::BITS-(x^y).leading_zeros())) -1;
        i[index].as_ref()
    },
    _=>None
    }
}