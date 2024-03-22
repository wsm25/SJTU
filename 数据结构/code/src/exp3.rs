#[cfg(test)]
mod test{
    #[test]
    fn test_triqueue(){
        use super::triqueue::*;
        let mut q = TriQueue::new();
        q.push_front(1);
        q.push_front(2);
        assert_eq!(q.into_vec(), vec![2,1]);
    }
}

mod triqueue{
    use std::marker::PhantomData;
    use std::alloc::{alloc, dealloc, Layout};
    struct Node<T>{
        left: *mut Self, // never null when inside dlist
        right: *mut Self,
        value: T,
    }
    pub struct TriQueue<T>{
        head: *mut Node<T>,
        tail: *mut Node<T>,
        middle: *mut Node<T>,
        len: usize,
        _phantom: PhantomData<T>,
    }
    impl<T> Node<T>{
        const LAYOUT:Layout = Layout::new::<Self>();
        unsafe fn new()->*mut Self{
            alloc(Self::LAYOUT) as *mut Self
        }
        unsafe fn with_beside(left: *mut Self, right: *mut Self)->*mut Self{
            let p = Self::new();
            (*p).left=left;
            (*p).right=right;
            (*left).right=p;
            (*right).left=p;
            p
        }
        fn from(value:T, left: *mut Self, right: *mut Self)->*mut Self{
            unsafe{
                let p = Self::with_beside(left, right);
                (*p).value=value;
                p
            }
        }

        unsafe fn delete(&mut self){
            dealloc(self as *mut Self as *mut u8, Self::LAYOUT);
        }
    }

    impl<T: Clone> TriQueue<T>{
        pub fn new()->Self{unsafe{
            let head = Node::new();
            let tail = Node::new();
            (*head).left=0 as *mut Node<T>;
            (*head).right=tail;
            (*tail).left=head;
            (*head).right=0 as *mut Node<T>;
            let middle = head; // head when empty, compatative to push_back and push_middle
            TriQueue{
                head, tail, middle, len:0, _phantom:PhantomData
            }
        }}

        pub fn push_front(&mut self, x:T){unsafe{
            let l = self.head;
            let r = (*l).right;
            let p = Node::from(x, l, r);
            if self.len==0{
                self.middle=p;
                self.len=1;
                return;
            }
            self.len+=1;
            if (self.len&1)==0{
                self.middle=(*self.middle).left;
            }
        }}

        pub fn push_back(&mut self, x:T){unsafe{
            let r = self.tail;
            let l = (*r).left;
            let _p = Node::from(x, l, r);
            self.len+=1;
            if (self.len&1)!=0{
                self.middle=(*self.middle).right;
            }
        }}

        pub fn push_middle(&mut self, x:T){unsafe{
            let l = self.middle; // insert right of middle
            let r =(*l).right;
            let p = Node::from(x, l, r);
            if (self.len&1)==0{ 
                self.middle=p;
            }
            self.len+=1;
        }}


        pub fn into_vec(&self)->Vec<T>{
            let mut v=Vec::new();
            unsafe{
                let mut p=(*self.head).right;
                while p!=self.tail{
                    v.push((*p).value.clone());
                    p=(*p).right;
                }
            }
            v
        }

    }
}