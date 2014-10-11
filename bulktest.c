
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jtqueue.h"

int main(int argc, char *argv[]) {
    printf("INITIATING JTQUEUE BULK TESTER\n");
    srand(time(NULL));

    int max_capacity = (argc > 1) ? atoi(argv[1]) : 5;

    JTQueue *queue = jtq_create(max_capacity);

    for (int i = 0; i < 100; i++) {
        int r = rand() % 10;
        if (r > 3) {
            if (jtq_isfull(queue)) 
                printf("Full Queue. (%d)\n", i);
            else {
                jtq_enqueue(queue, i);
                printf("E: %d\n", i);
            }
        }
        else if (jtq_size(queue) > 0) {
            printf("D: %d\n", jtq_dequeue(queue));
        }
    }

    jtq_dispose(queue);
    printf("All done!\n");
}
