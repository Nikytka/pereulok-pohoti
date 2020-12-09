#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

/*int getNum ( int n ) {

    return */

int main ( char argc, char* argv[] ) {
    
    int MAX_SIZE = 1000;
    char* string = ( char* ) calloc ( MAX_SIZE + 1, sizeof ( char ) );    
    int fd, res, n;
    size_t size;
    char file1[] = "1.fifo", file2[] = "2.fifo";

    n = atoi ( argv [1] );
    
    ( void ) umask ( 0 );

    mknod ( file1, S_IFIFO | 0666, 0 );

    /*if ( errno != EEXIST ) {

        printf ( "Can't create FIFO!\n" );
        exit ( -1 );

    }*/

    mknod ( file2, S_IFIFO | 0666, 0 );

    /*if ( errno != EEXIST ) {
	
        printf ( "Can't create FIFO!\n" );
        exit ( -1 );
    
    }*/

    if ( ( res = fork () ) < 0 ) {

	printf ( "Can't fork child!\n" );
	exit ( -1 );

    }
    
    if ( n == 1 ) {

        if ( res == 0 ) {
	
	    if ( ( fd = open ( file1, O_WRONLY ) ) < 0 ) {
	    
	        printf ( "Can't open FIFO for writing!\n" );
                exit ( -1 );

	    }
  
            else {

                while ( 1 ) {
	
                    fgets ( string, MAX_SIZE, stdin );
		    write ( fd, string, MAX_SIZE );
		}
	    }
	}
        else {
      
            if ( ( fd = open ( file2, O_RDONLY ) ) < 0 ) {

                printf ( "Can't open FIFO for writing!\n" );
                exit ( -1 );

            }
     
	    else {

		while ( 1 ) {

		    read ( fd, string, MAX_SIZE );
		    printf ( "%s\n", string );
		
		
		}

	    }

	}

    }
	        
    if ( n == 2 ) {
	        	    
	if ( res == 0 ) {

            if ( ( fd = open ( file2, O_WRONLY ) ) < 0 ) {

                printf ( "Can't open FIFO for writing!\n" );
                exit ( -1 );

            }

            else {

                while ( 1 ) {

                    fgets ( string, MAX_SIZE, stdin );
                    write ( fd, string, MAX_SIZE );
                }
            }

	}

	else {

            if ( ( fd = open ( file1, O_RDONLY ) ) < 0 ) {

                printf ( "Can't open FIFO for writing!\n" );
                exit ( -1 );

            }

            else {

                while ( 1 ) {

                    read ( fd, string, MAX_SIZE );
                    printf ( "%s\n", string );


                }

            }

        }

    }

    return 0;
    
}
