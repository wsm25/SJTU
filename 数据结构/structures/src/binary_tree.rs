/// # Binary Tree
///
/// Implement with link structure.
/// 

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
}

pub struct PreIter<'a, T>{
    stack: Vec<(Box<Node<T>>, usize)>,
    life: PhantomData<&'a mut T>,
}
impl<'a, T> Iterator for PreIter<'a, T>{
    type Item = &'a mut T;
    fn next(&mut self) -> Option<Self::Item> {
        if let Some((node, count))=self.stack.last_mut(){
            let mut p = Some(node);
            while let Some(node) = p{
                
            }
        } else {
            None
        }
    }
}