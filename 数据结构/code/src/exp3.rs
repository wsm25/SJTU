#[cfg(test)]
mod test{
    #[test]
    fn teque(){
        use super::super::exp3_teque::*;
        // my test
        let mut q = Teque::new();
        q.push_front(1);
        q.push_back(2);
        q.push_middle(3);
        q.push_middle(4);
        assert_eq!(q.into_vec(), vec![1,4,3,2]);
        assert_eq!(q.pop_back().unwrap(), 2);
        assert_eq!(q.pop_middle().unwrap(), 4);
        assert_eq!(q.pop_middle().unwrap(), 1);
        assert_eq!(q.pop_front().unwrap(), 3);
        assert_eq!(q.pop_back(), None);
        q.push_middle(1);
        assert_eq!(q.pop_back().unwrap(), 1);
        // test 1
        let mut q = Teque::new();
        q.push_front(13);
        q.push_back(21);
        q.push_middle(5);
        q.pop_back();
        q.pop_middle();
        assert_eq!(q.into_vec(), vec![5]);
        // test 2
        q.pop_middle();
        assert_eq!(q.into_vec(), vec![]);
    }

    #[test]
    fn lunch(){
        use super::lunch::*;
        assert_eq!(unsatisfy(
            &[1, 2, 3, 0, 0, 1, 2, 2, 2], 
            &[1, 0, 1, 2, 0, 2, 2, 3, 2, 3, 1]
        ), 0);

        assert_eq!(unsatisfy(
            &[0,2,3,0,2,3,1,3,2,3,3,3,1,0,1,0,2,2,3,1], 
            &[1,1,3,0,2,2,0,0,1,3,0,3,2,3,2,2,3,0,3,3]
        ), 3);

    }

    #[test]
    fn stack_queue(){
        use super::stack_queue::*;
        use Type::*;
        use Operation::*;

        assert_eq!(type_of(&[
            Push(1), Push(2), Push(3),
            Pop(3),  Pop(2),  Pop(1),
        ]), Stack);

        assert_eq!(type_of(&[
            Push(1), Push(2), Pop(1), Pop(2),
        ]), Queue);

        assert_eq!(type_of(&[
            Push(5), Push(7), Push(7), Push(3),
            Pop(3),  Pop(5),  Pop(7),  Pop(7),
        ]), Error);
    }
}

// Problem 1: 吃不到的午餐
pub mod lunch{
    pub fn unsatisfy(students: &[u8], lunch: &[u8])->usize{
        let mut count=[0;10];
        for i in students{
            let i = *i as usize;
            if i>=10 {panic!("type should < 10, got {i}")}
            count[i]+=1;
        }
        for i in lunch{
            let i = *i as usize;
            if i>=10 {panic!("type should < 10, got {i}")}
            if count[i]==0 {break;}
            count[i]-=1;
        }
        let mut u=0;
        for i in count {u+=i;}
        u
    }
}

/// Problem 2: Distinguish stack and queue
pub mod stack_queue{
    pub enum Operation{
        Push(i32),
        Pop(i32),
    }
    use Operation::*;

    use std::collections::VecDeque;
    fn is_queue(l: &[Operation])->bool{
        let mut q=VecDeque::new();
        for op in l{
            match *op{
            Push(x)=>q.push_back(x),
            Pop(x) =>{
                match q.pop_front(){
                Some(y) => if x!=y {return false},
                None => return false
                }
            }}
        }
        true
    }
    
    fn is_stack(l: &[Operation])->bool{
        let mut q=VecDeque::new();
        for op in l{
            match *op{
            Push(x)=>q.push_back(x),
            Pop(x) =>{
                match q.pop_back(){
                Some(y) => if x!=y {return false},
                None => return false
                }
            }}
        }
        true
    }
    #[derive(PartialEq, Debug)]
    pub enum Type{Both, Stack, Queue, Error}
    use Type::*;
    pub fn type_of(l: &[Operation])->Type{
        match (is_queue(l), is_stack(l)){
            (true,  true) =>Both,
            (true,  false)=>Queue,
            (false, true) =>Stack,
            (false, false)=>Error,
        }
    }
}
