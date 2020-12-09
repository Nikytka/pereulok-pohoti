#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main ( int argc, char* argv [] ) {

    struct sockaddr_in servaddr, cliaddr;
    struct sockaddr info;
    int sockfd;

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons ( atoi ( argv [2] ) );

    bzero ( servaddr.sin_zero, 8 );

    inet_aton( argv[1], &servaddr.sin_addr );

    if ( ( sockfd = socket ( AF_INET, SOCK_DGRAM, 0 ) ) < 0) {

        printf ( "Can't create socket!\n" );
        exit ( -1 );

    }

    if ( bind ( sockfd, ( struct sockaddr* ) &servaddr, sizeof ( servaddr ) ) < 0 ) {

        prinrf ( "Can't bind!\n" );
        exit ( -1 );

    }

    printf( "Success, reciever started!\n" );

    for ( int i = 0; i < 10; i++ ) {

        char message[25];
        socklen_t size;
        recvfrom ( sockfd, message, 25, 0, ( struct sockaddr* ) &cliaddr, &size );
        printf ( "Recieved message from %s:%hu: %s", inet_ntoa ( cliaddr.sin_addr ), ntohs ( cliaddr.sin_port ), message );

    }

    printf( "Reciever is over!\n" );
    
    return 0;
}