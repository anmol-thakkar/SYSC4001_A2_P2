#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int counter = 0;
    int cycle = 0;

    while (1){
        if (cycle % 3 == 0){
            printf("Cycle number: %d – %d is a multiple of 3\n", cycle, counter);
        } else {
            printf ("cycle number: %d\n", cycle);
        }
        counter++;
        cycle++;
        sleep(1);
    }
    return 0;
}