Requirements 
------------
- minimize stack -> use loops instead of recursion
- no malloc/free -> use stack allocation and my own object pool
- only include stdef.h and stdio.h

main.c is contains some unit test cases to exercise the library.
assert.h is included for testing only.

Compile and Run
---------------
`gcc main.c llist.c; ./a.out`
