#include <stdio.h>
#include "CuTest.h"

/*
 * File: alltests.c
 * Author: JT Cho
 * [jonathan.t.cho@gmail.com | joncho@seas.upenn.edu]
 * -----------------
 * Runs all tests defined in the unittests.c file.
 */

CuSuite* CuGetSuite();

void RunAllTests(void) {
    CuString *output = CuStringNew();
    CuSuite *suite = CuGetSuite();

    //Run the tests!
    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
    
    //Clean up.
    CuStringDelete(output);
    CuSuiteDelete(suite);
}

int main(void) {
    RunAllTests();
}
