# quine.c

###### Author: Joshua Malmberg	Date: October 17th, 2020

This program implements a quine in C. For more information about quines see:

https://en.wikipedia.org/wiki/Quine_(computing)

The program is named quine0.c and outputs a program quine[i].c, incrementing i. The function can be adapted to include an additional function that does some useful work.

The file **quine0.c** provides the implementation of the quine.

If you wish to change the work done by the function useful_fn() in quine0.c, the function q0() must be updated. The file **q0_gen.c** can be used to generate the new q0() function. Copy the specification of q() and useful_dn() into a file named **in.txt** in the same directory as **q0_gen.c** and a file **out.txt** containing the corresponding implementation of q0() will be produced by compiling and then running **q0_gen.c**.

