#[cfg(test)]
mod tests{
    use super::*;
    #[test]
    fn bigger(){
        assert_eq!(iter_index(0,3,9,1), (2, 1));
        assert_eq!(iter_index(2,9,4,1), (2,0));
        assert_eq!(iter_index(2,9,2,0), (1,0));
        assert_eq!(iter_index(4,3,9,0), (1,0));
    }

    #[test]
    fn test_mod(){
        assert_eq!(positive_mod(-10, 3), 2);
    }
}

fn positive_mod(n: isize, mo: isize) -> isize {
    if n >= 0 {
        n%mo
    } else {
        n-(n/mo-1)*mo
    }
}

fn iter_index(mut index: isize, M: isize, N: isize, mut direction: isize)->(isize, isize){
    if direction!=0 {
        index+=M-1;
    } else{
        index-=M;
    }
    index=positive_mod(index, (N-1)<<1);
    if index>N-1 { // reverse
        index=((N-1)<<1)-index;
        direction^=1;
    }
    return (index, direction);
}