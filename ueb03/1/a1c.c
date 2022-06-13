#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

extern int errno;

int main(int argc, char *argv[])
{
    // Check if file was passed as input 
    if (!fopen(argv[1], "r"))
    {
        perror("Error: Datei muss angegeben werden");
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return 1;
    }

    int picture = open(argv[1], O_RDONLY);
    char buffer[100];

    /* -------------- Retrieve Camera Brand ----------------- */

    if ((lseek(picture, 0x9e, SEEK_SET) == -1) || (read(picture, buffer, 100) == -1))
    {
        perror("Error reading file");
        fprintf(stderr, "Error reading file: %s\n", strerror(errno));
    }

    printf("Name of device : %s\n", buffer);

    /* -------------- Retrieve Camera Model ----------------- */

    if ((lseek(picture, 0xb6, SEEK_SET) == -1) || (read(picture, buffer, 100) == -1))
    {
        perror("Error reading file");
        fprintf(stderr, "Error reading file: %s\n", strerror(errno));
    }

    printf("Camera Model: %s\n", buffer);

    /* -------------- Retrieve Date of shoot ----------------- */

    if ((lseek(picture, 0xe4, SEEK_SET) == -1) || (read(picture, buffer, 100) == -1))
    {
        perror("Error reading file");
        fprintf(stderr, "Error reading file: %s\n", strerror(errno));
    }

    printf("Date of shoot: %s\n", buffer);


    int closed = close(picture);
    if (closed == -1)
    {
        printf("File is closed\n");
    }

    return 0;
}
