#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if(argc <= 1) {
        perror("Error: No arguments found");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        printf("%d: %s\n", i, argv[i]);
    }

    return 0;
}