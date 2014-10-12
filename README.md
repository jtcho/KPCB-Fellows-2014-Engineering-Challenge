KPCB Fellows Fall 2014 Engineering Challenge Problem
======================

PREFACE
-------

Hello!

I'm JT, and thanks for checking out my submission for the KPCB Fellows challenge question. :)

It was a lot of fun working on this, since I got to practice unit-testing for the first time ever!

RUNNING THE CODE
----------------
Simply run "make"!

This code was built on a 64-bit Linux system, but I tested it on OSX (Mavericks) as well. (y)

IMPLEMENTATION DETAILS
---------------

I wrote this implementation of a bounded integer queue in C. I *really* learned C in detail at Stanford this summer, so I figured that I could use it to demonstrate an innate understanding of efficiency and robustness. My queue uses an internal "circular" array of ints, to conserve memory. I also made certain design choices in terms of error handling, writing to stderr and also including asserts for certain crucial parts of the code. I haven't had much experience writing production
code so I did what I could to make everything top quality. All of my test code runs clean under valgrind, as well!

All the code is well documented, and you can run two test files.

    ./alltests - Unit Tests from CuTest framework

    ./bulktest *[number operations]* - Naive series of enqueue/dequeue operations, used for affirming basic functionality


