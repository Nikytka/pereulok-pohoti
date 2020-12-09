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

    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons ( 0 );
    cliaddr.sin_addr.s_addr = INADDR_ANY;

    bzero ( cliaddr.sin_zero, 8 );

    if ( ( sockfd = socket ( AF_INET, SOCK_DGRAM, 0 ) ) < 0 ) {
        
        printf ( "Can't create socket!\n" );
        exit ( -1 );
    
    }

    if ( bind ( sockfd, ( struct sockaddr* ) &cliaddr, sizeof ( cliaddr ) ) < 0 ) {

        printf( "Can't bind!\n" );
        exit ( -1 );
    
    }

    servddr = cliaddr;

    int a = atoi ( argv[2] );

    servddr.sin_port = htons ( a );

    inet_aton ( argv[1], &servaddr.sin_addr );

    printf( "Success, sender started!\n" );

    for ( int i = 0; i < 10; i++ ) {

        char message[] = "Hayuhay s vami IOneGuy!\n";
        sendto ( sockfd, message, sizeof ( message ), 0, ( struct sockaddr* ) &servddr, sizeof ( servddr ) );
        printf( "Success, sended!\n" );

    }

    printf ( "Sender is over\n" );

    return 0;
}