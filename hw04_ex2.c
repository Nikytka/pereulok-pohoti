#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main () {
    
    int n = 0, i;

    scanf ( "%d", &n );

    printf ( "Parent process was created: pid: %d\n", getpid () );

    for ( i = 0; i < n; i++ ) {
	
	pid_t pid = fork;
	
	if ( pid < 0 ) {
            printf ( "Cannot fork child!\n" );
	    exit ( 1 );
	}
        
        else if ( pid == 0 ) 
	    
	    printf ( "Child process %d was created: pid: %d, ppid: %d\n", i, getpid (), getppid () );
	else {
	    
            int stat = 0;
	    wait ( &stat );

	    printf ( "Child process %d exited: pid: %d. Now exit from the current process: pid: %d.\n", i, pid, getpid );
            exit ( 0 );
	}
    }
    //return 0;
}    
