/* client-kv.c
 * By: Abhishek Singh Rawat
 * Date: 04-10-1999
 * Derived from: client-kv-redacted.c
 *
 * Note: lines with "?????" need to be completed with code.
 *       See client.c for example.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

#define MAX_INPUT_SIZE 256

char msg[MAX_INPUT_SIZE]; // Temporary message

void error(char *msg)
{
  perror(msg);
  exit(1);
}

int main(int argc, char *argv[])
{
  int sockfd, portnum, n;
  struct sockaddr_in server_addr;
  struct hostent *server;

  char inputbuf[MAX_INPUT_SIZE];
  if (argc < 3)
  {
    sprintf(msg, "usage %s <server-ip-addr> <server-port>\n", argv[0]);
    error(msg);
  }

  /* create client socket, get sockfd handle */
  portnum = atoi(argv[2]);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    error("ERROR opening socket");
  }

  /* fill in server address in sockaddr_in datastructure */
  server = gethostbyname(argv[1]);
  if (server == NULL)
  { /* Server IP invalid */
    error("ERROR, no such host\n");
  }

  bzero((char *)&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr,
        (char *)&server_addr.sin_addr.s_addr,
        server->h_length);
  server_addr.sin_port = htons(portnum);

  /* Connect to server */
  if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
  {
    error("ERROR connecting\n");
  }
  printf("Connected to server\n");

  do
  {
    /* Ask user for message to send to the server */
    printf("Enter request: ");
    fgets(inputbuf, MAX_INPUT_SIZE - 1, stdin);

    /* Write to the server */
    n = write(sockfd, inputbuf, strlen(inputbuf));
    if (n < 0)
    {
      error("ERROR writing to socket");
    }

    /* Read reply */
    bzero(inputbuf, MAX_INPUT_SIZE);
    n = read(sockfd, inputbuf, MAX_INPUT_SIZE - 1);
    if (n < 0)
    {
      error("ERROR reading from socket");
    }
    printf("Server replied: %s\n", inputbuf);

  } while (memcmp(inputbuf, "Goodbye", strlen("Goodbye")));

  return 0;
}
