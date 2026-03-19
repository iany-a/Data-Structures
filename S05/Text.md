S05-Stacks

LIFO - last in, first out; if the stack is full up to a point, the stack SP is at the top of the stack

PUSH > Stack > POP

BP is always at the base of the stack

n elements

    0 1 2 3 ...................... n-2, n-1

PUSH/POP is done either at the first index or last index
index = -1 PUSH index = 0 when end is SP 
index = size PUSH index = size - 1 when start is SP == STACK IS EMPTY (_stack underflow_ if you extract from an empty stack)

Today we will implement stacks with lists


PUSH/POP at the head of the stack (SP level)

(SP) __ -> __ -> __ -> _N (BP)




