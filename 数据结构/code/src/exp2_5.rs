// 实验2 链表和栈

mod tests {
    fn assert_eqf(x: f64, y:f64){
        if (x-y).abs()>1e-4 {
            assert_eq!(x, y);
        }
    }
    #[test]
    fn test_calculator() {
        use super::calculator::calculate;
        // testcase 1
        assert_eqf(7.5, calculate(
            "5 7 2 3 * - * 10 4 / +".to_string()
        ).unwrap());
        // testcase 2
        assert_eq!(Err(()), calculate(
            "1 2 + +".to_string()
        ));
    }

}

// Problem 2: 四则计算器
mod calculator {
    pub fn calculate(s: String)->Result<f64, ()>{
        let mut st=Vec::new();
        let mut input = s.chars().into_iter();
        while let Some(ch)=input.next() {
            match ch {
            '+' | '-' | '*' | '/' => {
                if st.len()<2{
                    return Err(());
                }
                let b=st.pop().unwrap();
                let mut a=st.pop().unwrap();
                match ch {
                    '+'=> a+=b,
                    '-'=> a-=b,
                    '*'=> a*=b,
                    '/'=> a/=b,
                    _=>()
                }
                st.push(a);
            },
            '0'..='9' => {
                let mut n = (ch as i32)-('0' as i32);
                while let Some(ch)=input.next(){
                    if ch<'0' || ch>'9' {
                        break;
                    }
                    n=n*10+(ch as i32)-('0' as i32);
                }
                st.push(n as f64);
            },
            _=>()
            }
        }
        if st.len()!=1{
            Err(())
        } else {
            Ok(st.pop().unwrap())
        }
    }
}
