#include "jtqueue.h"
#include "CuTest.h"
#include <stdio.h>

/*
 * File: unittests.c
 * Author: JT Cho
 * [jonathan.t.cho@gmail.com | joncho@seas.upenn.edu]
 * -----------------
 * Defines all the unit tests for the
 * JT Queue using the CuTest testing 
 * framework.
 */

//Test enqueuing and dequeueing one element.
void TestJTQEnqDeqOne(CuTest *tc) {
    JTQueue *queue = jtq_create(1);
    
    jtq_enqueue(queue, 0);

    CuAssertIntEquals(tc, jtq_peek(queue), 0);
    CuAssertTrue(tc, jtq_isfull(queue));
    CuAssertIntEquals(tc, jtq_dequeue(queue), 0);

    jtq_dispose(queue);
}

//Test multiple enqueues/dequeues of a single
//element at a time.
void TestJTQEnqDeqMany(CuTest *tc) {
    JTQueue *queue = jtq_create(1);
    
    for (int i = 0; i < 10; i++) {
        jtq_enqueue(queue, i);
        CuAssertIntEquals(tc, jtq_peek(queue), i);
        CuAssertIntEquals(tc, jtq_dequeue(queue), i);
    }

    jtq_dispose(queue);
}

//Test a bulk number of enqueues.
void TestJTQEnqMany(CuTest *tc) {
    JTQueue *queue = jtq_create(1000);

    for (int i = 0; i < 1000; i++) {
        jtq_enqueue(queue, i);
        CuAssertIntEquals(tc, jtq_peek(queue), 0);
        CuAssertIntEquals(tc, jtq_peekback(queue), i);
    }

    jtq_dispose(queue);
}

//Test a bulk number of dequeues.
void TestJTQDeqMany(CuTest *tc) {
    JTQueue *queue = jtq_create(1000);

    for (int i = 0; i < 1000; i++) {
        jtq_enqueue(queue, i);
    }

    for (int i = 0; i < 1000; i++) {
        CuAssertIntEquals(tc, jtq_dequeue(queue), i);
    }

    jtq_dispose(queue);
}

//Tests a specific case with the queue, where
//the "back" of the queue is actually at the
//internal starting pointer of the array.
void TestJTQCircular(CuTest *tc) {
    JTQueue *queue = jtq_create(5);
    for (int i = 0; i < 5; i++) {
        jtq_enqueue(queue, i);
    }

    jtq_dequeue(queue);

    jtq_enqueue(queue, 1337);
    CuAssertIntEquals(tc, jtq_size(queue), 5);
    CuAssertIntEquals(tc, jtq_peek(queue), 1);
    CuAssertIntEquals(tc, jtq_peekback(queue), 1337);

    while (jtq_size(queue) > 1) {
        jtq_dequeue(queue);
    }

    CuAssertIntEquals(tc, jtq_peek(queue), jtq_peekback(queue));
    while (! jtq_isfull(queue))
        jtq_enqueue(queue, 0);

    CuAssertIntEquals(tc, jtq_dequeue(queue), 1337);

    while (jtq_size(queue))
        jtq_dequeue(queue);

    CuAssertIntEquals(tc, jtq_size(queue), 0);

    jtq_dispose(queue);
}

//Tests the internal circular array.
void TestJTQCircularMany(CuTest *tc) {
    JTQueue *queue = jtq_create(3);

    for (int i = 1; i < 4; i++)
        jtq_enqueue(queue, i);

    for (int i = 4; i < 1000; i++) {
        int peek = jtq_peek(queue);
        int dequeued = jtq_dequeue(queue);
        CuAssertIntEquals(tc, peek, dequeued);
        //In the internal array, the value enqueued
        //in each array index will be the index itself [1-3].
        int val = (i%3) ? i%3 : 3;
        CuAssertIntEquals(tc, dequeued, val);
        jtq_enqueue(queue, val);
    }

    jtq_dispose(queue);
}

//Tests for a failure code upon trying to
//enqueue to an already full queue.
void TestJTQEnqFull(CuTest *tc) {
    JTQueue *queue = jtq_create(1);
    jtq_enqueue(queue, 0);
    CuAssertTrue(tc, jtq_isfull(queue));
    CuAssertIntEquals(tc, jtq_enqueue(queue, 1), 0);
    jtq_dispose(queue);
}

/*
 * Function: CuGetSuite
 * --------------------
 * Creates a test suite for the JTQueue.
 */
CuSuite *CuGetSuite(void) {
    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, TestJTQEnqDeqOne);
    SUITE_ADD_TEST(suite, TestJTQEnqDeqMany);
    SUITE_ADD_TEST(suite, TestJTQEnqMany);
    SUITE_ADD_TEST(suite, TestJTQDeqMany);
    SUITE_ADD_TEST(suite, TestJTQCircular);
    SUITE_ADD_TEST(suite, TestJTQCircularMany);
    SUITE_ADD_TEST(suite, TestJTQEnqFull);

    return suite;
}
