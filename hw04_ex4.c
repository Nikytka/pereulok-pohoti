#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main () {

    if ( fork() == 0 )
	    execlp ( "gcc", "gcc", "hw04_ex4_test.c", "-o", "hi", NULL );
    
    int stat = 0;

    wait ( &stat );

    execlp ( "./hi", "./hi", NULL );

} 
