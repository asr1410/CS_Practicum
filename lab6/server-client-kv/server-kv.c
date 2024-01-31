/* server-kv.c
 * By: Abhishek Singh Rawat
 * Date: 04-10-1999
 * Derived from: server-kv-redacted.c
 *
 * Note: lines with "?????" need to be completed with code.
 *       See server.c for example.
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int keyVal[100];  /* The key-value store */
char msg[256];    // Temp string buffer
char buffer[256]; // I/O buffer

void error(char *msg)
{
  perror(msg);
  exit(1);
}

void DoPut(int newsockfd)
{ // put
  /*printf("request: %s\n",token);*/
  int n;
  int key = atoi(strtok(NULL, " \n"));
  int value = atoi(strtok(NULL, " \n"));

  if (key >= 0 && key < 100)
  {
    if (keyVal[key] == -1)
    {
      keyVal[key] = value;
      /* send reply "OK" to the client */
      strcpy(msg, "OK");
      n = write(newsockfd, msg, strlen(msg) + 1);
    }
    else
    {
      /* send reply "Key already exists" to the client */
      strcpy(msg, "Key already exists");
      n = write(newsockfd, msg, strlen(msg) + 1);
    }
  }
  else
  {
    /* send reply "Key should be within 0-99" */
    strcpy(msg, "Key should be within 0-99");
    n = write(newsockfd, msg, strlen(msg) + 1);
  }
} /* End DoPut */

void DoGet(int newsockfd)
{ // get
  int n;
  int key = atoi(strtok(NULL, " \n"));
  if (key >= 0 && key < 100)
  {
    if (keyVal[key] != -1)
    {
      /* send the value keyVal[key] to the client */
      sprintf(msg, "%d", keyVal[key]);
      n = write(newsockfd, msg, strlen(msg) + 1);
    }
    else
    {
      /* send "Key not found" to the client */
      strcpy(msg, "Key not found");
      n = write(newsockfd, msg, strlen(msg) + 1);
    }
  }
  else
  {
    /* send reply "Key should be within 0-99" */
    strcpy(msg, "Key should be within 0-99");
    n = write(newsockfd, msg, strlen(msg) + 1);
  }
} /* End DoGet */

void DoDelete(int newsockfd)
{ // delete
  int n;
  int key = atoi(strtok(NULL, " \n"));
  if (key >= 0 && key < 100)
  {
    if (keyVal[key] != -1)
    {
      keyVal[key] = -1;
      /* send reply OK to the client */
      strcpy(msg, "OK");
      n = write(newsockfd, msg, strlen(msg) + 1);
    }
    else
    {
      /* send "Key not found" to the client */
      strcpy(msg, "Key not found");
      n = write(newsockfd, msg, strlen(msg) + 1);
    }
  }
  else
  {
    /* send reply "Key should be within 0-99" */
    strcpy(msg, "Key should be within 0-99");
    n = write(newsockfd, msg, strlen(msg) + 1);
  }
} /* End DoDelete */

void DoBye(int newsockfd)
{
  /* Send reply Goodbye, close the connection and exit */
  strcpy(msg, "Goodbye");
  int n = write(newsockfd, msg, strlen(msg) + 1);
  printf("Server exiting on client Bye\n");
  close(newsockfd);
  exit(0);
}

int main(int argc, char *argv[])
{
  /* Initialise empty keyVal store.  -1 is an empty slot */
  for (int i = 0; i < 100; i++)
  {
    keyVal[i] = -1;
  }

  int sockfd;
  /* Create a socket and store the returned file descriptor in sockfd */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    error("ERROR opening socket");
  }

  struct sockaddr_in serv_addr;
  /* Construct sockaddr_in struct. Fill in a port number to listen on, with the address family. The port number
      should be unique and should not clash with well-known ports. IP address can be anything (INADDR_ANY) */
  bzero((char *)&serv_addr, sizeof(serv_addr));
  int portno = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  /* bind socket to this port number on this machine */
  if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
    error("ERROR on binding");
  }

  /* listen for incoming connection requests */
  listen(sockfd, 5);

  int newsockfd;
  /* accept a new request and store the returned file descriptor in newsockfd */
  int clilen;
  clilen = sizeof(serv_addr);
  newsockfd = accept(sockfd, (struct sockaddr *)&serv_addr, &clilen);
  if (newsockfd < 0)
  {
    error("ERROR on accept");
  }

  while (1)
  {
    bzero(buffer, 256);
    /* read message from client into the buffer */
    int n = read(newsockfd, buffer, 255);
    if (n < 0)
      error("ERROR reading from socket");

    char *token = strtok(buffer, " \n");

    if (strcmp(token, "put") == 0)
      DoPut(newsockfd);
    else if (strcmp(token, "get") == 0)
      DoGet(newsockfd);
    else if (strcmp(token, "del") == 0)
      DoDelete(newsockfd);
    else if (strcmp(token, "bye") == 0)
      DoBye(newsockfd);
    else
    {
      sprintf(msg, "Invalid request: %s: only get/put/delete/bye supported", token);
      n = write(newsockfd, msg, strlen(msg) + 1);
    }
  } /* End while(1) */

  return 0;
}
