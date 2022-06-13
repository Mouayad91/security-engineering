#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

extern int errno;

int main(int argc, char *argv[]) {
    // Überprüfen ob argumente größer als 1 sind, 
    // d.h. ob eine Datei oder Ordner mitgegeben
    if (!fopen(argv[1], "r")) {
        perror("Error: Datei oder Ordner muss angegeben werden");
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return 1;
    }

    // For schleife das über die einzelnen Argumente iteriert.
    for (int i = 1; i < argc; i++) {
        // Struct of file/dir statistics
        struct stat statStruct;

        // Ausführen von stat und mitgabe des statStruct
        stat(argv[i], &statStruct);

        // Nutzung von Bitwise AND operator zur Rückgabe des file mode in symbolic name
        switch (statStruct.st_mode & S_IFMT) {
            // Überprüfen der einzelnen Eingabetypen und ausgabe
            case S_IFDIR: printf("Eingabetyp = Ordner\n"); break;
            case S_IFREG: printf("Eingabetyp = Regulaer\n"); break;
            case S_IFIFO: printf("Eingabetyp = Pipe\n"); break;
            case S_IFSOCK: printf("Eingabetyp = Socket\n"); break;
            case S_IFCHR: printf("Eingabetyp = Char\n"); break;
            case S_IFLNK: printf("Eingabetyp = Symbolic Link\n"); break;
        }

        // Ausgabe der stat struct properties
        printf("User-ID = %d\n", statStruct.st_uid);
        printf("Gruppen-ID =  %d\n", statStruct.st_gid);
        printf("Zugriffsbits im Oktalsystem = %o \n", statStruct.st_mode & 0b111111111);
        printf("Zeit des letzten Zugriffs = %s", ctime(&statStruct.st_atime));
        printf("Zeit der letzten Inode-Änderung = %s", ctime(&statStruct.st_ctime));
        printf("Zeit der letzten Dateiänderung = %s\n", ctime(&statStruct.st_mtime));
    }
    
    return 0;
}
