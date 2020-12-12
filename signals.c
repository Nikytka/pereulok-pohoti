#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int par_pid;

void sign1 ( int sign ) {

  printf ( "RT - " );
  sleep ( 1 );
  kill ( par_pid, SIGUSR2 );

}

void sign2 ( int sign ) {

  printf ( "champion!\n" );
  sleep ( 1 );
  kill ( par_pid, SIGUSR1 );

}

void start () {

  sign1 ( 0 );
  while ( 1 );

}


int main () {

  signal ( SIGUSR1, sign1 );
  signal ( SIGUSR2, sign2 );

  par_pid = getpid();

  start();

return 0;

}
