use criterion::{criterion_group, criterion_main, Criterion};

use rand::random;

fn bench_heap(c: &mut Criterion) {
    use structures::heap::*;
    use std::time::Instant;
    c.bench_function("binary heap", |b| b.iter_custom(|batch|{
        let mut heap=Binary::new();
        let start = Instant::now();
        for _ in 0..batch{match random::<bool>(){ // 2ns
            true=>{heap.push(random::<i32>());},
            false=>{heap.pop();}
        }}
        start.elapsed()
    }));
    
    c.bench_function("pairing heap", |b| b.iter_custom(|batch|{
        let mut heap=Pairing::new();
        let start = Instant::now();
        for _ in 0..batch{
            match random::<bool>(){ // 2ns
                true=>{heap=heap.push(random::<i32>());},
                false=>{heap.pop();}
            }
        }
        start.elapsed()
    }));
    c.bench_function("binary heap sequent", |b| b.iter_custom(|batch|{
        let mut heap=Binary::new();
        let start = Instant::now();
        for _ in 0..batch{
            heap.push(random::<i32>());
        }
        for _ in 0..batch{
            heap.pop();
        }
        start.elapsed()
    }));
    c.bench_function("pairing heap sequent", |b| b.iter_custom(|batch|{
        let mut heap=Pairing::new();
        let start = Instant::now();
        for _ in 0..batch{
            heap=heap.push(random::<i32>());
        }
        for _ in 0..batch{
            heap.pop();
        }
        start.elapsed()
    }));
}

criterion_group!(benches, bench_heap);
criterion_main!(benches);