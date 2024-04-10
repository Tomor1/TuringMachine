
; the finite set of states
#Q = {q0,q1,q2,q3,q4,q5,q6,q9,accept,accept1,accept2,accept3,accept4,reject,reject1,reject2,reject3,reject4,reject5,halt_accept,halt_reject}

; the finite set of input symbols
#S = {a,b,c}

; the complete set of tape symbols
#G = {a,b,_,=,c,t,r,u,e,f,l,s}

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
q0 a_ a= rr q1
q0 b_ b= rr q4
q0 a= a= rr q0
q0 b= b= rr q0
q0 c_ c_ rr q6
q0 __ __ ** reject

q1 a_ a_ rr q1
q1 b_ b_ rr q1
q1 c_ c_ rr q2
q1 __ __ ll reject

q2 a_ a= rr q3
q2 a= a= rr q2
q2 b= b= rr q2
q2 b_ b_ ll reject
q2 c_ c_ ll reject
q2 __ __ ll reject

q3 a_ a_ ll q3
q3 b_ b_ ll q3
q3 a= a= ll q3
q3 b= b= ll q3
q3 c_ c_ ll q9
q3 __ __ ll q9

q9 a_ a_ ll q9
q9 b_ b_ ll q9
q9 a= a= ll q9
q9 b= b= ll q9
q9 c_ c_ ll q9
q9 __ __ rr q0

q4 a_ a_ rr q4
q4 b_ b_ rr q4
q4 c_ c_ rr q5
q4 __ __ ll reject

q5 b_ b= rr q3
q5 a= a= rr q5
q5 b= b= rr q5
q5 a_ a_ ll reject
q5 c_ c_ ll reject
q5 __ __ ll reject

q6 a= a= rr q6
q6 b= b= rr q6
q6 __ __ ll accept
q6 a_ a_ ll reject
q6 b_ b_ ll reject
q6 c_ c_ ll reject

; accept stage
accept a= __ ll accept
accept b= __ ll accept
accept c_ __ ll accept
accept __ t_ rr accept1
accept1 __ r_ rr accept2
accept1 *_ r_ rr accept2
accept2 __ u_ rr accept3
accept2 *_ u_ rr accept3
accept3 __ e_ rr accept4
accept3 *_ e_ rr accept4
accept4 *_ __ rr accept4
accept4 __ __ ** halt_accept

; reject stage
reject a_ a_ ll reject
reject b_ b_ ll reject
reject a= a= ll reject
reject b= b= ll reject
reject c_ c_ ll reject
reject __ f_ rr reject1
reject1 __ a_ rr reject2
reject1 *_ a_ rr reject2
reject1 *= a_ rr reject2
reject2 *_ l_ rr reject3
reject2 *= l_ rr reject3
reject2 __ l_ rr reject3
reject3 __ s_ rr reject4
reject3 *_ s_ rr reject4
reject3 *= s_ rr reject4
reject4 __ e_ rr reject5
reject4 *_ e_ rr reject5
reject4 *= e_ rr reject5
reject5 *_ __ rr reject5
reject5 *= __ rr reject5
reject5 __ __ ** halt_reject

