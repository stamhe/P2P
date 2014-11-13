/*   LINUX:      gcc -o server2  server2.c -lnsl                         */


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>  /* define socket */
#include <netinet/in.h>  /* define internet socket */
#include <netdb.h>       /* define internet socket */

#define SERVER_PORT 7777        /* define a server port number */

int main()
{
    int sd, ns, k, pid;
    struct sockaddr_in server_addr = { AF_INET, htons( SERVER_PORT ) };
    struct sockaddr_in client_addr = { AF_INET };
    int client_len = sizeof( client_addr );
    char buf[1024], *host;

    /* create a stream socket */
    if( ( sd = socket( AF_INET, SOCK_STREAM, 0 ) ) == -1 )
    {
      perror( "server: socket failed" );
      exit( 1 );
    }
    
    /* bind the socket to an internet port */
    if( bind(sd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1 )
    {
      perror( "server: bind failed" );
      exit( 1 );
    }

    /* listen for clients */
    if( listen( sd, 1 ) == -1 )
    {
      perror( "server: listen failed" );
      exit( 1 );
    }

    printf("SERVER is listening for clients to establish a connection\n");

   if ( (pid=fork()) == 0 )
   {  /* child code begins */

      if( ( ns = accept( sd, (struct sockaddr*)&client_addr,
                         &client_len ) ) == -1 )
      {
          perror( "server: accept failed" );
          exit( 1 );
      }

      printf("Child accept() successful.. a client has connected to child ! waiting for a message\n");

      /* data transfer on connected socket ns */
      while( (k = read(ns, buf, sizeof(buf))) != 0)
      {    printf("SERVER(Child) RECEIVED: %s\n", buf);
           write(ns, buf, k);
      }
        close(ns);
        close(sd);
    }
    else
    {   /* Parent code */
      if( ( ns = accept( sd, (struct sockaddr*)&client_addr,
                         &client_len ) ) == -1 )
      {
          perror( "server: accept failed" );
          exit( 1 );
      }

      printf("Parent accept() successful.. a client has connected to Parent! waiting for a message\n");

      /* data transfer on connected socket ns */
      while( (k = read(ns, buf, sizeof(buf))) != 0)
      {    printf("SERVER(Parent) RECEIVED: %s\n", buf);
           write(ns, buf, k);
      }
      close(ns);
      close(sd);
    }


    unlink(server_addr.sin_addr);

    return(0);
}