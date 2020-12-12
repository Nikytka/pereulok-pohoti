#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int Max_words_num = 1000;

struct element {
    int lag;
    int words_num;
    char** command;
};

int Split ( char* string, const char* del, char** tokens ) {
    int i = 0;

    tokens[0] = strtok ( string, del );

    while ( tokens [i] != NULL ) {
        i++;
        tokens[i] = strtok( NULL, del );
    }

    return i;
}

int comparator ( const void* frst1, const void* scnd2 ) {

    struct element* frst = ( struct element* )frst1;
    struct element* scnd = ( struct element* )scnd2;
    return ( frst->lag - scnd->lag );

}

int main ( int argc, char** argv ) {

    FILE *in;
    struct stat st;

    in = fopen ( argv[1], "r" );
    fstat ( fileno ( in ), &st );
    size_t file_size = st.st_size;

    char* buff = ( char* ) malloc ( ( file_size + 1 ) * sizeof ( char ) );
    fread ( buff, sizeof ( char ), file_size, in );
    char** curr_command = ( char** ) malloc ( ( file_size + 1 ) * sizeof ( char* ) );

    size_t command_num = Split ( buff, "\n", curr_command );
    printf ( "%ld\n", command_num );
    struct element* commands = ( struct element* ) malloc ( command_num * sizeof ( struct element ) );

    size_t i = 0;

    for ( i = 0; i < command_num; i++ ) {

	char* com_start = curr_command[i];
        int j = 0;

        while ( isdigit ( curr_command[i][j] ) )

            j++;

	curr_command[i][j] = '\0';

        commands[i].lag = atoi ( com_start );
        commands[i].command = ( char** ) malloc ( ( Max_words_num ) * sizeof ( char* ) );
        commands[i].words_num = Split ( curr_command[i] + j + 1, " ", commands[i].command );

 }

    qsort ( commands, command_num, sizeof ( struct element ), comparator );

    for ( i = 0; i < command_num; i++ ) {

        if ( i == 0 )
		sleep ( commands[i].lag );
	else
        	sleep ( commands[i].lag - commands[i - 1].lag );

        pid_t pid = fork();
        if ( pid == 0 ) {

            execvp ( commands[i].command[0], commands[i].command );
            printf("\n");
            exit(1);

        }

        else {

          int status = 0;
            wait ( &status );

        }
    }

    free ( commands );
    free ( curr_command );
    free ( buff );

    return 0;
}
