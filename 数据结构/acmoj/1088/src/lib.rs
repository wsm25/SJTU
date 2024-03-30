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

#[inline]
pub fn positive_mod(n: isize, mo: isize) -> isize {
    let r = n%mo;
    if r >= 0 {
        r
    } else {
        mo+r
    }
}

pub fn iter_index(mut index: isize, m: isize, n: isize, mut direction: isize)->(isize, isize){
    if direction!=0 {
        index+=m-1;
    } else{
        index-=m;
    }
    index=positive_mod(index, (n-1)<<1);
    if index>n-1 { // reverse
        index=((n-1)<<1)-index;
        direction^=1;
    }
    return (index, direction);
}