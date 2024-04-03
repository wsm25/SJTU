//! # Binary Tree
//! Implement with link structure.

use std::{boxed::Box, marker::PhantomData};
pub struct Node<T>{
    left:  Option<Box<Node<T>>>,
    right: Option<Box<Node<T>>>,
    value: T,
}

impl<T> Node<T>{
    pub fn new(value: T)->Box<Node<T>>{
        Box::new(Node { left: None, right: None, value })
    }

    pub fn with_children(value: T, left: Box<Node<T>>, right: Box<Node<T>>)
    ->Box<Node<T>>{
        Box::new(Node { left: Some(left), right: Some(right), value })
    }

    pub fn into_preiter<'a>(&'a mut self)->PreIter<'a, T>{
        let mut stack=Vec::with_capacity(4);
        stack.push((self as *mut Self, PreIterStatus::Pre));
        PreIter{stack, phantom: PhantomData}
    }
}

enum PreIterStatus{Pre, Post, End}
pub struct PreIter<'a, T>{
    stack: Vec<(*mut Node<T>, PreIterStatus)>,
    phantom: PhantomData<&'a mut T>
}
impl<'a, T> Iterator for PreIter<'a, T>{
    type Item = &'a mut T;
    fn next(&mut self) -> Option<Self::Item> {unsafe{
        use PreIterStatus::*;
        match self.stack.pop(){
        None=>None,
        Some((node, status))=>{
            match status{
            Pre=>{
                self.stack.push((node, Post));
                match &mut (*node).left{
                    Some(n)=>self.stack.push((&mut **n, Pre)),
                    None=>()
                }
                Some(&mut (*node).value)
            },
            Post=>{
                match &mut (*node).right{
                    Some(n)=>{
                        self.stack.push((node, End));
                        self.stack.push((&mut **n, Pre));
                        self.next()
                    },
                    None=>self.next()
                }
            },
            End=>self.next()
            }
        }}
    }}
}