#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
   int* array;
   int shmid;
   //int new = 1;
   char pathname[] = "lw08.c";
   key_t key;

   if((key = ftok(pathname,0)) < 0){
     printf("Can\'t generate key\n");
     exit(-1);
   }

    if ( ( shmid = shmget ( key, 3000 * sizeof ( char ), 0666|IPC_CREAT|IPC_EXCL ) ) < 0 ){

        if ( errno != EEXIST ){
            printf ( "Can\'t create shared memory\n" );
            exit ( -1 );
        } 
        else {
            if ( ( shmid = shmget ( key, 3000 * sizeof ( char ), 0 ) ) < 0 ){
                printf ( "Can\'t find shared memory\n" );
                exit ( -1 );
            }
        //new = 0;
        }
    }

   if ( ( array = ( int * ) shmat ( shmid, NULL, 0 ) ) == ( int * )( -1 ) ){
      printf("Can't attach shared memory\n");
      exit(-1);
   }

   FILE* file = fopen( "lw08.c" , "r" );
   fread ( array, sizeof ( char ), 3000, file );
   fclose( file );

   if ( shmdt ( array ) < 0 ){
      printf("Can't detach shared memory\n");
      exit(-1);
   }

   return 0;
}
