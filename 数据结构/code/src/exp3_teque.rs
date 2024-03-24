use std::marker::PhantomData;
use std::alloc::{alloc, dealloc, Layout};
struct Node<T>{
    left: *mut Self, // never null when inside dlist, no need to check null
    right: *mut Self,
    value: T,
}
/// ## Triple-ended queue
pub struct Teque<T>{
    head: *mut Node<T>,
    tail: *mut Node<T>,
    middle: *mut Node<T>,
    len: usize,
    _phantom: PhantomData<T>,
}

impl<T> Node<T>{
    unsafe fn new()->*mut Self{
        alloc(Layout::new::<Self>()) as *mut Self
    }
    unsafe fn with_beside(left: *mut Self, right: *mut Self)->*mut Self{
        let p = Self::new();
        Self::connect(left, p);
        Self::connect(p,right);
        p
    }
    fn from(value:T, left: *mut Self, right: *mut Self)->*mut Self{
        unsafe{
            let p = Self::with_beside(left, right);
            (*p).value=value;
            p
        }
    }

    unsafe fn read_value(p: *mut Self)->T{
        unsafe{(&(*p).value as *const T).read()}
    }

    unsafe fn connect(left: *mut Self, right: *mut Self){
        (*left).right=right;
        (*right).left=left;
    }

    unsafe fn delete(p: *mut Self){
        dealloc(p as *mut u8, Layout::new::<Self>());
    }
}

impl<T> Teque<T>{
    pub fn new()->Self{unsafe{
        let head = Node::new();
        let tail = Node::new();
        Node::connect(head, tail);
        let middle = head; // head when empty, is not compatible with push_front
        #[cfg(debug_assertions)] // debug with SIGSEGV
        {
            (*head).left=0 as *mut Node<T>;
            (*tail).right=0 as *mut Node<T>;
        }
        Teque{
            head, tail, middle, len:0, _phantom:PhantomData
        }
    }}

    pub fn push_front(&mut self, x:T){unsafe{
        let p = Node::from(x, 
            self.head, 
            (*self.head).right
        );
        if self.len==0{ // empty
            self.middle=p;
            self.len=1;
            return;
        }
        if (self.len&1)!=0{
            self.middle=(*self.middle).left;
        }
        self.len+=1;
        
    }}

    pub fn push_back(&mut self, x:T){unsafe{
        let _p = Node::from(x, (*self.tail).left, self.tail);
        if (self.len&1)==0{
            self.middle=(*self.middle).right;
        }
        self.len+=1;
    }}

    pub fn push_middle(&mut self, x:T){unsafe{
        self.middle = 
            if (self.len&1)==0{ // insert right of middle
                Node::from(x, 
                    self.middle, 
                    (*self.middle).right
                )
            } else { // left
                Node::from(x,
                    (*self.middle).left, 
                    self.middle
                )
            };
        self.len+=1;
    }}

    pub fn pop_front(&mut self)->Option<T>{unsafe{
        if self.len==0 {
            return None;
        }
        self.len-=1;
        if self.len==0 { // empty
            self.middle=self.head;
        }
        // non-empty
        if (self.len&1)!=0{
            self.middle=(*self.middle).right;
        }
        let p = (*self.head).right;
        let x = Node::read_value(p);
        Node::connect(self.head, (*p).right);
        Node::delete(p);
        
        Some(x)
    }}

    pub fn pop_back(&mut self)->Option<T>{unsafe{
        if self.len==0 {
            return None;
        }
        self.len-=1;
        // non-empty
        if (self.len&1)==0{
            self.middle=(*self.middle).left;
        }
        let p = (*self.tail).left;
        let x = Node::read_value(p);
        Node::connect((*p).left, self.tail);
        Node::delete(p);
        Some(x)
    }}

    pub fn pop_middle(&mut self)->Option<T>{unsafe{
        if self.len==0 {
            return None;
        }
        self.len-=1;
        let p = self.middle;
        let x = Node::read_value(p);
        self.middle = 
            if (self.len&1)==0{ 
                (*p).left
            } else {
                (*p).right
            };
        Node::connect((*p).left, (*p).right);
        Node::delete(p);
        Some(x)
    }}

    pub fn into_vec(&self)->Vec<T>{
        let mut v=Vec::new();
        unsafe{
            let mut p=(*self.head).right;
            while p!=self.tail{
                v.push(Node::read_value(p));
                p=(*p).right;
            }
        }
        v
    }
}

impl<T> Drop for Teque<T>{
    fn drop(&mut self) {unsafe{
        let mut p=(*self.head).right;
        while p!=self.tail{
            let x = (*p).right;
            Node::delete(p);
            p=x;
        }
        Node::delete(self.head);
        Node::delete(self.tail);
    }}
}

use std::collections::VecDeque;
#[repr(transparent)]
pub struct TriQueueBad<T>{
    vec: VecDeque<T>
}

impl<T> TriQueueBad<T>{
    pub fn new()->Self{
        Self{vec:VecDeque::new()}
    }
    pub fn push_front(&mut self, x:T){
        self.vec.push_front(x)
    }
    pub fn push_back(&mut self, x:T){
        self.vec.push_back(x)
    }
    pub fn push_middle(&mut self, x:T){
        self.vec.insert(self.vec.len()/2,x)
    }
    pub fn pop_front(&mut self)->Option<T>{
        self.vec.pop_front()
    }
    pub fn pop_back(&mut self)->Option<T>{
        self.vec.pop_back()
    }
    pub fn pop_middle(&mut self)->Option<T>{
        self.vec.remove((self.vec.len()-1)/2)
    }
    pub fn into_vec(&self)->Vec<&T>{
        self.vec.iter().collect()
    }
}
