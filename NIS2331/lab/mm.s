.globl matrix_mul
// int matrix_mul(Matrix *results, const Matrix *source1, const Matrix *source2);
matrix_mul:
    // result: r12, src1: r1, src2: r2
    push    {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    ldr     r10, [r0]
    mov     r12, r0
    // check row > 0 && column > 0
    cmp     r10, #1
    ldrge   lr, [r12, #4]
    cmpge   lr, #1
    bge     .2
.fail:
    mov     r0, #1
    pop     {r4, r5, r6, r7, r8, r9, r10, r11, pc}
.2:
    ldr     r3, [r1]
    cmp     r3, #1
    ldrge   r8, [r1, #4]
    cmpge   r8, #1
    blt     .fail
    ldr     r5, [r2]
    cmp     r5, #1
    ldrge   r4, [r2, #4]
    cmpge   r4, #1
    blt     .fail
    // check s1.column == s2.row && r.column == s2.column && r.row == s1.row
    cmp     r8, r5
    bne     .fail
    cmp     r10, r3
    cmpeq   lr, r4
    bne     .fail
    // check passed
    sub     sp, sp, #12
    mov     r0, #0
    sub     r3, r0, r8, lsl #2
    sub     r5, r0, lr, lsl #2
    mul     r0, r8, r10
    ldr     r1, [r1, #8]
    // sp[2]: -4*r.col
    str     r3, [sp, #8]
    add     r0, r1, r0, lsl #2
    ldr     r1, [r2, #8]
    sub     r3, r0, #4
    mul     r0, r8, lr
    add     r0, r1, r0, lsl #2 
    sub     r0, r0, #4 
    // sp[1]: s2.data+4*s2.row*s2.col-4
    str     r0, [sp, #4]
    ldr     r0, [r12, #8]
    // sp[0]: r.data
    str     r0, [sp]
.loop1:
    sub     r10, r10, #1
    ldr     r1, [sp]
    ldr     r4, [sp, #4]
    mov     r7, lr
    mul     r0, r10, lr
    add     r6, r1, r0, lsl #2
.loop2:
    sub     r7, r7, #1
    mov     r0, #0
    mov     r1, r3
    mov     r2, r4
    mov     r11, r8
.loop3:
    ldr     r9, [r2], r5
    subs    r11, r11, #1
    ldr     r12, [r1], #-4
    mla     r0, r9, r12, r0
    bne     .loop3
    sub     r4, r4, #4
    cmp     r7, #0
    str     r0, [r6, r7, lsl #2]
    bne     .loop2
    ldr     r0, [sp, #8]
    cmp     r10, #0
    add     r3, r3, r0
    bne     .loop1
    mov     r0, #0
    add     sp, sp, #12
    pop     {r4, r5, r6, r7, r8, r9, r10, r11, pc}
