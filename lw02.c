#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main () {
    
    int fd[2];
    int i = 1;
    size_t size;
    
    char string[] = "1";
    if ( pipe ( fd ) < 0 ) {
	printf ( "Can\'t create pipe\n" );
        exit ( -1 );
    }

    do {
        write ( fd[1], string, 1 );
        printf ( "%d\n", i );
	i++;
    }
    while ( 1 != 0 );
    
    return 0;
}
