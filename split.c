#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int Split ( char* string, const char* del, char** tokens );

int Split ( char* string, const char* del, char** tokens ) {

    int i = 0;

    tokens[0] = strtok ( string, del );

    while ( tokens [i] != NULL ) {
        i++;
        tokens[i] = strtok( NULL, del );
    }

    return i;
}

int main ( ) {

    FILE *in1, *in2;
    struct stat st1;
    struct stat st2;

    in1 = fopen ( "string.txt", "r" );
    in2 = fopen ( "delimiters.txt", "r" );

    fstat ( fileno ( in1 ), &st1 );
    fstat ( fileno ( in2 ), &st2 );

    char** token = ( char** ) malloc ( st1.st_size * sizeof ( char* ) );
    char* string = ( char* ) malloc ( st1.st_size * sizeof ( char ) );
    char* del = ( char* ) malloc ( st2.st_size * sizeof ( char ) );

    fgets ( string, st1.st_size, in1 );
    fgets ( del, st2.st_size, in2 );

    int num = 0;
    num = Split ( string, del, token );

    printf ( "%d\n", num );

    free ( token );
    free ( string );
    free ( del );

    fclose ( in1 );
    fclose ( in2 );

    return 0;
}
