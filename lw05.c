#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int a = 0;

void *mythread ( void *dummy ) {

    pthread_t mythid;

    mythid = pthread_self ();

    a++;

    printf ( "Thread %ld, Calculation result = %d\n", mythid, a );

    return NULL;

}

int main () {

    pthread_t thid, mythid;
    int res;

    res = pthread_create ( &thid, ( pthread_attr_t * ) NULL, mythread, NULL );

    if ( res != 0 ) {

	printf ( "Error on thread create, return value = %d\n", res );
	exit ( -1 );

    }

    printf ( "Thread created, thid = %ld\n", thid );

    mythid = pthread_self();

    a++;

    printf ( "Thread %ld, Calculation result = %d\n", mythid, a );

    pthread_join ( thid, ( void ** ) NULL );

    return 0;

}
