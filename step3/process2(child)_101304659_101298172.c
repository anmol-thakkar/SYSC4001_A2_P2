#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int counter = 0;
    int cycle = 0;

    while (counter > -500) {
        if (counter % 3 == 0)
            printf("P2 - Cycle number: %d – %d is a multiple of 3\n", cycle, counter);
        else
            printf("P2 - Cycle number: %d\n", cycle);

        counter--;
        cycle++;
        usleep(100000);
    }

    printf("P2 finished as counter reached -500\n");
    return 0;
}