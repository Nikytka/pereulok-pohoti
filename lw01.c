#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd, N;
    size_t size;
    (void)umask(0);

    scanf ( "%d", &N );
    
    if ( ( fd = open ( "my.txt", O_RDONLY, 0666 ) ) < 0 ) {
        printf ( "Can\'t open file\n" );
	exit ( -1 );
    }

    char* string = (char*) malloc ( N * sizeof(char) );

    do {
        size = read ( fd, string, N );
        write ( 1, string, size );
	printf ("\n");
    }
    while ( size != 0);
    
    close ( fd );
    return 0;
}

    
