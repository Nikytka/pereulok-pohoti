#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define MAX_SIZE 1000

struct info {

    char* name;

};

void* Read ( void* a ) {

    struct info* dummy = ( struct info* ) a;

    int fd;

    if ( ( fd = open ( dummy->name, O_RDONLY ) ) < 0) {

        printf ( "Can't open FIFO for reading\n" );
	exit ( -1 );

    }

    char string [ MAX_SIZE + 5 ] = {};

    while ( 1 ) {

        int size = read ( fd, string, MAX_SIZE );
	printf ( "%s",  string );
	memset ( string, '\0', MAX_SIZE );

    }

    return NULL;

}

void *Write ( void* a ) {

    struct info* dummy = ( struct info* ) a;
    int fd;

    if ( ( fd = open ( dummy->name, O_WRONLY ) ) < 0 ) {

        printf ( "Can't open FIFO for writting\n" );
	exit ( -1 );

    }

    char string [ MAX_SIZE + 5 ] = {};

    while ( 1 ) {

        fgets ( string, MAX_SIZE, stdin );
	write ( fd, string, MAX_SIZE );
	memset ( string, '\0', MAX_SIZE );

    }

    return NULL;
}

int main ( char argc, char* argv[] ) {

    int f1, f2, res, n;
    size_t size;
    pthread_t thid1, thid2, mythid;
    //printf("k\n");
    n = atoi ( argv [1] );

    ( void ) umask ( 0 );
    //printf("k\n");
    mknod ( "0", S_IFIFO | 0666, 0 );

    mknod ( "1", S_IFIFO | 0666, 0 );

    char num_read [ 2 ] = {};
    char num_write [ 2 ] = {};

    if ( n == 0 ) {

        num_read[0] = '1';
	num_write[0] = '0';

    }

    else {

        num_read[0] = '0';
	num_write[0] = '1';

    }

    pthread_t read_id, write_id;

    struct info info_read, info_write;

    info_read.name = num_read;
    info_write.name = num_write;

    pthread_create ( &thid1, NULL, Read, &info_read);
    pthread_create ( &thid2, NULL, Write, &info_write);

    pthread_join ( thid1, NULL);

    /*struct info* str = ( struct info* ) calloc ( 1, sizeof ( struct info ) );

    str->string = ( char* ) calloc ( MAX_SIZE + 5, sizeof ( char ) );

    if ( n == 1 ) {

        if ( ( f1 = open ( file1, O_WRONLY ) ) < 0 ) {

            printf ( "Can't open FIFO for writing!\n" );
            exit ( -1 );

        }

        else {

            str->fd1 = f1;
            pthread_create ( &thid1, ( pthread_attr_t * ) NULL, Read, str );

        }

        if ( ( f2 = open ( file2, O_RDONLY ) ) < 0 ) {

                printf ( "Can't open FIFO for writing!\n" );
                exit ( -1 );

        }

        else {

            str->fd1 = f2;
            pthread_create ( &thid2, ( pthread_attr_t * ) NULL, Write, str );

        }

    }

    if ( n == 2 ) {

        if ( ( f1 = open ( file2, O_WRONLY ) ) < 0 ) {

            printf ( "Can't open FIFO for writing!\n" );
            exit ( -1 );

        }

        else {

            str->fd1 = f1;
            pthread_create ( &thid1, ( pthread_attr_t * ) NULL, Write, str );

        }

        if ( ( f2 = open ( file1, O_RDONLY ) ) < 0 ) {

                printf ( "Can't open FIFO for writing!\n" );
                exit ( -1 );

        }

        else {

            str->fd1 = f2;
            pthread_create ( &thid2, ( pthread_attr_t * ) NULL, Read, str );

        }

    }

    pthread_join ( thid2, NULL );*/

    return 0;

}


