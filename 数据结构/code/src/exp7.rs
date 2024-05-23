// 实验x

mod tests {
    #[test]
    fn test_qsort() {
        use super::*;
        let mut v=vec![1,1,4,5,1,4,1,9,1,9,8,1,0];
        let (h, t)=slice_raw(&mut v);
        qsort(h, t);
        assert_eq!(v, vec![0,1,1,1,1,1,1,4,4,5,8,9,9]);
    }
    #[test]
    fn test_isort() {
        use super::*;
        let mut v=vec![1,1,4,5,1,4,1,9,1,9,8,1,0];
        let (h, t)=slice_raw(&mut v);
        isort(h, t);
        assert_eq!(v, vec![0,1,1,1,1,1,1,4,4,5,8,9,9]);
    }
}

pub fn slice_raw<T>(s: &mut[T])->(*mut T, *mut T){
    let h=s.as_mut_ptr();
    let t=unsafe{h.add(s.len())};
    (h, t)
}

// insert sort
pub fn isort<T: Ord>(vec: *mut T, end: *mut T){unsafe{
    use std::ptr::*;
    let mut sorted=vec.add(1);
    while sorted<end{
        let mut p=sorted;
        while p>vec{
            let prep=p.sub(1);
            if *prep<=*p {break;}
            swap(p, prep);
            p=prep;
        }
        sorted=sorted.add(1);
    }
}}

pub fn qsort<T: Ord>(mut vec: *mut T, end: *mut T){unsafe{
    use std::ptr::*;
    while vec<end{
        // should be two recursion, but llvm doesn't provide good enough 
        // tail call optimization, we have to manually write a loop
        if end.offset_from(vec)<=7 {
            isort(vec, end);
            break;
        }
        let lst=end.sub(1);
        let mid=vec.add(lst.offset_from(vec) as usize/2);
        // pop sort
        if *mid<*vec {swap(mid, vec);}
        if *lst<*mid {swap(mid, lst);}
        if *vec<*mid {swap(mid, vec);}
        // begin
        let (mut left, mut right)=(vec, lst);
        loop{
            // pivot is on left
            while left<right && *left<=*right {right=right.sub(1);}
            if left==right {break;}
            swap(left, right);
            // pivot is on right
            while left<right && *left<=*right {left=left.add(1);}
            if left==right {break;}
            swap(left, right);
        }
        qsort(vec, left);
        vec=left.add(1);
    }
}}
