use std::{cell::UnsafeCell, ops::{Deref, DerefMut}, rc::Rc};

/// Share: single-thread shared element

/// really UNSAFE. only use when reallocation only happens inside a
/// method, and all method return will not point to some memory inside
/// the structure.
pub struct Share<T>(Rc<UnsafeCell<T>>);

impl<T> Share<T>{
    pub fn new(value: T)->Self{
        Self(Rc::new(UnsafeCell::new(value)))
    }
}

impl<T> Deref for Share<T>{
    type Target = T;
    fn deref(&self) -> &Self::Target {
        unsafe{&*self.0.get()}
    }
}

impl<T> DerefMut for Share<T>{
    fn deref_mut(&mut self) -> &mut Self::Target {
        unsafe{&mut *self.0.get()}
    }
}

impl<T> Clone for Share<T>{
    fn clone(&self) -> Self {
        Self(self.0.clone())
    }
}

impl<T> PartialEq for Share<T>{
    fn eq(&self, other: &Self) -> bool {
        Rc::ptr_eq(&self.0, &other.0)
    }
}