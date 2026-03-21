#include <errno.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 3666
int sockets(int port) {
  // Create socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    perror("webserver socket creation failed");
    return 1;
  }
  printf("socket creation successful\n");

  // Create addr
  struct sockaddr_in host_addr;
  int host_addr_len = sizeof(host_addr);

  host_addr.sin_family = AF_INET;
  host_addr.sin_port = htons(PORT);
  host_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  // Bind socket to address

  if (bind(sockfd, (struct sockaddr *)&host_addr, host_addr_len) != 0) {
    perror("webserver bind failed");
    return 1;
  }
  printf("socket bounded to address\n");

  // Listen
  if (listen(sockfd, SOMAXCONN) != 0) {
    perror("webserver listen failed");
    return 1;
  }
  printf("server listening for connections\n");

  // Accept!
  for (;;) {
    int newsockfd = accept(sockfd, (struct sockaddr *)&host_addr,
                           (socklen_t *)&host_addr_len);
    if (newsockfd < 0) {
      perror("webserver accept failed");
      continue;
    }
    printf("connection accepted!\n");
    close(newsockfd);
  }
  return 0;
}
