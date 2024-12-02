import numpy as np
import subprocess
import sys
from io import StringIO

CASES = {
    "1": (4,6,6,5),
    "2": (50, 85, 85, 64),
    "3": (128, 256, 256, 512),
}

QEMU = ["./qemu-arm-static","-L", "/usr/arm-linux-gnueabi"]

def get_matrix(bt):
    matrix = []
    tmp = [i for i in bt.decode().split('\n') if i]
    for i in tmp:
        matrix.append([int(j) for j in i.split(' ') if j])
    return matrix

def gen_case_legacy(r1, c1, r2, c2):
    assert c1 == r2
    return (
        np.array([list(range(i, i+c1)) for i in range(1, 1+r1)]), 
        np.array([[i]*c2 for i in range(1, 1+r2)])
    )

def gen_case(r1, c1, r2, c2):
    assert c1 == r2
    rng = np.random.default_rng()
    return (
        rng.integers(0, 1024, (r1, c1)), 
        rng.integers(0, 1024, (r2, c2))
    )

def test_case(key):
    r1, c1, r2, c2 = CASES[key]
    m1, m2 = gen_case(r1, c1, r2, c2)
    result = np.dot(m1, m2)
    
    input_ = StringIO()
    input_.write(f"{r1} {c1}\n")
    for line in m1:
        input_.write((' '.join([str(i) for i in line])+'\n'))
    input_.write(f"{r2} {c2}\n")
    for line in m2:
        input_.write((' '.join([str(i) for i in line])+'\n'))
    p = subprocess.Popen([*QEMU, "main"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=sys.stdout)
    matrix = get_matrix(p.communicate(input_.getvalue().encode(), timeout=10)[0])
    return (result == matrix).all()

if __name__ == "__main__":
    score = 0
    for case in CASES:
        if test_case(case):
            print(f"\033[32m\033[1m[+] Test {case} pass\033[0m")
            score += 10
        else:
            print(f"\033[31m\033[1m[x] Test {case} fail\033[0m")
    print(f"\033[34m\033[1m[*] Final score is {score}.\033[0m\n")
