
struct BSNode<T: PartialOrd, E>{
    left: BSPtr<T,E>,
    right: BSPtr<T,E>,
    count: usize,
    value: T,
    extra: E,
}
struct BSPtr<T: PartialOrd,E>(Option<Box<BSNode<T,E>>>);

impl<T:PartialOrd, E> BSPtr<T, E>{

}



pub trait BS{
    
}