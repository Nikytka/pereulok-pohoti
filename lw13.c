#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>

//Dead lock as example from presentation

int main() {

    int semid;
    int i = 0;
    struct sembuf mybuf;
    char pathname [] = "lw13.c";
    key_t key;

    key = ftok ( pathname, 0 );

    if ( ( semid = semget ( key, 2, 0666 | IPC_CREAT ) ) < 0 ) {
        printf("Can\'t create semaphore set\n");
        exit(-1);
    }

    mybuf.sem_num = 0;
    mybuf.sem_op  = 1;
    mybuf.sem_flg = 0;

    if(semop(semid, &mybuf, 1) < 0){
      printf("fuck Can\'t add 1 to semaphore\n");
      exit(-1);
    }

    mybuf.sem_num = 1;

    if(semop(semid, &mybuf, 1) < 0){
      printf("suck Can\'t add 1 to semaphore\n");
      exit(-1);
    }

    if ( fork() > 0 ) {

        printf ( "I'm inside parent)))\n" );

        while ( 1 ) {

            printf ( "Iteration a %d\n",  i);

            mybuf.sem_num = 0;
            mybuf.sem_op  = -1;
            semop(semid, &mybuf, 1);

            mybuf.sem_num = 1;
            semop(semid, &mybuf, 1);

            mybuf.sem_num = 0;
            mybuf.sem_op = 1;
            semop(semid, &mybuf, 1);

            mybuf.sem_num = 1;
            semop(semid, &mybuf, 1);

            i++;
        }
    }

    else {

        printf ( "I'm inside child)))\n" );

        while ( 1 ) {

            printf ( "Iteration b %d\n", i );

            mybuf.sem_num = 0;
            mybuf.sem_op  = -1;
            semop(semid, &mybuf, 1);

            mybuf.sem_num = 1;
            semop(semid, &mybuf, 1);

            mybuf.sem_num = 0;
            mybuf.sem_op = 1;
            semop(semid, &mybuf, 1);

            mybuf.sem_num = 1;
            semop(semid, &mybuf, 1);

            i++;
        }
    }

    return 0;
}
