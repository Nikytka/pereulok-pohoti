#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main () {
    
    int fd1[2], fd2[2], num1[2], num2[2], result;
    size_t size;
    
    scanf ( "%d%d", num1, num1+1 );

    if ( pipe ( fd1 ) < 0 ) {
        printf ( "Can\'t create a pipe!\n" );
	exit ( -1 );
    }

    if ( pipe ( fd2 ) < 0 ) {
        printf ( "Can\'t create a pipe!\n" );
        exit ( -1 );
    }
    
    result = fork();

    if ( result < 0 ) {
       	printf ( "Can\'t fork child!\n" );
	exit ( -1 );
    }

    else if ( result > 0 ) {
	close ( fd1[0] );
	write ( fd1[1], num1, 2*sizeof(int) );
	close ( fd1[1] );
	read ( fd2[0], num2, sizeof(int) ); 
	printf ( "The composition is %d\n", num2[0] );
	exit ( -1 );
    }
    else {
	close ( fd1[1] );
	read ( fd1[0], num2, 2*sizeof(int) );
        num2[0]=num2[0]*num2[1];
        write ( fd2[1], num2, sizeof(int) );
	close ( fd2[0] );
	close ( fd2[1] );
	exit ( -1 );
    }

    return 0;
}
