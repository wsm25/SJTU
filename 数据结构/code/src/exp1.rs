// 实验1 类与对象

mod tests {
    fn assert_eqf(x: f64, y:f64){
        if (x-y).abs()>1e-4 {
            assert_eq!(x, y);
        }
    }
    #[test]
    fn test_line() {
        use super::line;
        let l1 = line::new(3.,4.,6.,8.);
        let l2 = line::new(10., 8., 6., 5.);
        assert_eq!(l1.length(), l2.length());
        let l1 = line::new(-53.626,73.532, -51.943, -50.613);
        let l2 = line::new(-59.646, -59.994, 8., -51.253);
        assert!(l1.length()>l2.length())
    }

    #[test]
    fn test_point() {
        use super::point::*;
        // triangle
        let t=triangle::new(0., 0., 0., 1., 1., 0.);
        assert_eqf(t.girth(),3.41421);
        assert_eqf(t.area(), 0.5);
        let t = triangle::new(1.52, -0.38, 4.44, 3.09, -2.56, -2.39);
        assert_eqf(t.girth(), 17.9733);
        assert_eqf(t.area(), 4.1442);
        
        // circle
        let c=circle::new(0.,0.,0.,1.);
        assert_eqf(c.girth(),6.28);
        assert_eqf(c.area(),3.14);
        let c=circle::new(1.52, -0.38, 4.44, 3.09);
        assert_eqf(c.girth(),28.4805);
        assert_eqf(c.area(),64.5813);
    }
}

// Problem 1: Line
mod line {
    use super::sqr;
    pub struct Line {
        x1: f64,
        x2: f64,
        y1: f64,
        y2: f64,
    }

    pub fn new(x1: f64, y1: f64, x2: f64, y2: f64) -> Line{
        Line{x1, x2, y1, y2}
    }

    impl Line {
        pub fn length(&self) ->f64 {
            return (sqr(self.x1-self.x2)+sqr(self.y1-self.y2)).sqrt()
        }
    }
}

// Problem2 point
mod point{
    use super::sqr;
    pub struct Point{x:f64, y:f64}
    fn dist(p1: &Point, p2: &Point)->f64{
        (sqr(p1.x-p2.x)+sqr(p1.y-p2.y)).sqrt()
    }

    pub mod triangle {
        use super::Point;
        use super::dist;
        pub struct Triangle{
            p1:Point,
            p2:Point,
            p3:Point,
        }
        
        pub fn new(x1:f64,y1:f64,x2: f64,y2: f64,x3: f64,y3: f64)->Triangle{
            Triangle{
                p1: Point{x:x1,y:y1},
                p2: Point{x:x2, y:y2},
                p3: Point{x:x3, y:y3},
            }
        }

        impl Triangle{
            pub fn girth(&self)->f64{
                dist(&self.p1, &self.p2)
              + dist(&self.p2, &self.p3)
              + dist(&self.p3, &self.p1)
            }

            pub fn area(&self)->f64{
                0.5*(
                    self.p1.x*self.p2.y
                  + self.p2.x*self.p3.y
                  + self.p3.x*self.p1.y
                  - self.p2.x*self.p1.y
                  - self.p3.x*self.p2.y
                  - self.p1.x*self.p3.y
                ).abs()
            }
        }
    }

    // as inherit is only supported on trait,
    // i just implement circle with struct
    pub mod circle {
        const PI:f64 = 3.14;
        use super::Point;
        use super::dist;
        use super::sqr;
        pub struct Circle {
            c: Point, // center
            p: Point, // one point on circle
        }
        pub fn new(x1: f64, y1: f64, x2: f64, y2: f64)->Circle{
            Circle { 
                c: Point{x:x1, y:y1}, 
                p: Point { x:x2, y:y2 },
            }
        }
        impl Circle {
            pub fn girth(&self)->f64{
                2.*PI*dist(&self.c, &self.p)
            }

            pub fn area(&self)->f64{
                PI*(sqr(self.c.x-self.p.x)+sqr(self.c.y-self.p.y))
            }
        }
    }
}
// utils
fn sqr(x: f64)->f64{x*x}