
; the finite set of states
#Q = {q0,q1,q2,q3,r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,s0,s1,s2,f0,halt_accept,halt_reject}

; the finite set of input symbols
#S = {a,b}

; the complete set of tape symbols
#G = {a,b,_,c,I,l,e,g,n,p,u,t}

; the start state
#q0 = q0

; the blank symbol
#B = _

; the set of final states
#F = {halt_accept}

; the number of tapes
#N = 2

; the transition functions

; State q0: start state
q0 a_ a_ r* q1
q0 b_ b_ ** r0 ; Illegal input
q0 __ __ ** r0 ; empty input


q1 a_ a_ r* q1
q1 b_ b_ r* q2
q1 __ __ l* r0

q2 a_ a_ ** r0
q2 b_ b_ r* q2
q2 __ __ l* q3

q3 a_ a_ l* q3
q3 b_ b_ l* q3
q3 __ __ r* s0

s0 a_ __ r* s1
s0 b_ b_ *l f0

s1 a_ a_ r* s1
s1 b_ bc rr s1
s1 __ __ l* s2

s2 a_ a_ l* s2
s2 b_ b_ l* s2
s2 __ __ r* s0

; accept stage
f0 bc cc rl f0
f0 _c cc rl f0
f0 __ __ ** halt_accept

; handle illegal input
r0 a_ a_ l* r0
r0 b_ b_ l* r0
r0 __ __ r* r1
r1 *_ I_ r* r2
r1 __ I_ r* r2
r2 *_ l_ r* r3
r2 __ l_ r* r3
r3 *_ l_ r* r4
r3 __ l_ r* r4
r4 *_ e_ r* r5
r4 __ e_ r* r5
r5 *_ g_ r* r6
r5 __ g_ r* r6
r6 *_ a_ r* r7
r6 __ a_ r* r7
r7 *_ l_ r* r8
r7 __ l_ r* r8
r8 *_ __ r* r9
r8 __ __ r* r9
r9 *_ I_ r* r10
r9 __ I_ r* r10
r10 *_ n_ r* r11
r10 __ n_ r* r11
r11 *_ p_ r* r12
r11 __ p_ r* r12
r12 *_ u_ r* r13
r12 __ u_ r* r13
r13 *_ t_ r* r14
r13 __ t_ r* r14
r14 *_ __ r* r14
r14 __ __ ** halt_reject

