mod tests{
    #[test]
    fn test_queue(){

    }
}

mod queue{
    pub struct Queue<T>{
        vec: NonNull<T>,
        cap: usize,
        front: usize,
        end: usize,
    }
    use std::ptr::NonNull;
    use std::alloc::{self, Layout};
    


    impl<T> Queue<T>{
        
        pub fn new() -> Self{
            assert!(std::mem::size_of::<T>() != 0, "We're not ready to handle ZSTs");
            Queue{
                vec: NonNull::dangling(),
                cap: 0,
                front: 0,
                end: usize::MAX,
            }
        }
    }
}