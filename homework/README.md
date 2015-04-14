Requirements 
------------
- minimize stack -> use loops instead of recursion
- no malloc/free -> use static allocation(from stack) and my own object pool
- only include stdef.h and stdio.h, but assert.h is included for testing only.

main.c contains unit test cases to exercise the library.

Compile and Run
---------------
`gcc main.c llist.c; ./a.out`

Test Cases
----------
Test cases are created by building up an ordered linked list with
llistInsert(), then a new value = 5 is inserted.
Final linked list is printed, and results are verified with assert().

