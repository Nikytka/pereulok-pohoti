#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LAST_MESSAGE 255

int main() {
    
    int msqid;
    char pathname [ ] = "lw14.c";
    key_t  key;
    int i,len;

    struct mymsgbuf {
       
       short sinfo;
       float finfo;
    
    } info;

    /* Create or attach message queue  */
    
    key = ftok(pathname, 0);
    
    if ( ( msqid = msgget ( key, 0666 | IPC_CREAT ) ) < 0 ) {

       printf ( "Can\'t get msqid\n" );
       exit ( -1 );

    }


    /* Send information */
    
    for ( i = 1; i <= 5; i++ ) {
       
       info.sinfo = 1;
       //strcpy(mybuf.mtext, "This is text message");
       len = sizeof ( short ) + sizeof ( float ) + 1;
       
       if ( msgsnd ( msqid, ( struct msgbuf * ) &info, len, 0 ) < 0 ) {

         printf ( "Can\'t send message to queue\n" );
         msgctl ( msqid, IPC_RMID, ( struct msqid_ds * ) NULL );
         exit ( -1 );

       }

    }    
       
    /* Send the last message */   
       
    info.sinfo = LAST_MESSAGE;   
    len = 0;   
       
    if ( msgsnd ( msqid, ( struct msgbuf * ) &info, len, 0 ) < 0 ) {

       printf( "Can\'t send message to queue\n" );
       msgctl( msqid, IPC_RMID, ( struct msqid_ds * ) NULL );
       exit( -1 );

    }

    return 0;    
}
