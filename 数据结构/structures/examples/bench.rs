
fn main(){
    use std::fs::File;
    use std::time::Instant;
    const N:usize=10_000_000;
    let guard = pprof::ProfilerGuardBuilder::default().frequency(1000).blocklist(&["libc", "libgcc", "pthread", "vdso"]).build().unwrap();
    println!("benchmark start!");
    let start = Instant::now();
    bench_heap(N);
    println!("benchmark end! {} ns/op", start.elapsed().as_nanos()/(N as u128));
    println!("writing report to flamegraph.svg...");
    if let Ok(report) = guard.report().build() {
        let file = File::create("flamegraph.svg").unwrap();
        report.flamegraph(file).unwrap();
    };
}

fn bench_heap(loops: usize){
    use structures::heap::*;
    use rand::random;

    let mut heap=Pairing::new();
    for _ in 0..loops{
        heap=heap.push(random::<i32>());
    }
    for _ in 0..loops{
        heap.pop();
    }
}