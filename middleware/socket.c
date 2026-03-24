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
#define BUFFERSIZE 1024 // TEN-TWENTY FOURRRR

extern int all_lists(FILE *);

int main(int port) {
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

  struct sockaddr_in client_addr;
  int client_addrlen = sizeof(client_addr);
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

  char buffer[BUFFERSIZE];
  FILE *filePointer;

  // Accept!
  for (;;) {
    int newsockfd = accept(sockfd, (struct sockaddr *)&host_addr,
                           (socklen_t *)&host_addr_len);
    if (newsockfd < 0) {
      perror("webserver accept failed");
      continue;
    }
    printf("connection accepted!\n");

    int sockn = getsockname(newsockfd, (struct sockaddr *)&client_addr,
                            (socklen_t *)&client_addrlen);
    if (sockn < 0) {
      perror("webserver could not getsockname");
      continue;
    }

    // Read incoming requests
    int valread = read(newsockfd, buffer, BUFFERSIZE);
    if (valread < 0) {
      perror("webserver read failed");
      continue;
    }

    char method[BUFFERSIZE];
    char uri[BUFFERSIZE];
    char version[BUFFERSIZE];
    sscanf(buffer, "%s %s %s", method, uri, version);

    // GET METHODS
    if (strcmp(method, "GET") == 0) {

      // GET /index.html
      if (strcmp(uri, "/index.html") == 0) {
        filePointer = fopen("./frontend/pages/index.html", "r");
        if (filePointer == NULL) {
          perror("Failed to load index.html");
          char *resp = "HTTP/1.0 404 NOT FOUND\r\n"
                       "Server: webserver-c\r\n"
                       "Content-type: text/html\r\n\r\n"
                       "<html>error</html>\r\n";

          int valwrite = write(newsockfd, resp, strlen(resp));
          if (valwrite < 0) {
            perror("webserver write failed");
            break;
          }
          continue;
        }

        char header[] = "HTTP/1.0 200 OK\r\n"
                        "Server: webserver-c\r\n"
                        "Content-type: text/html\r\n\r\n";

        int valwrite = write(newsockfd, header, sizeof(header));
        if (valwrite < 0) {
          perror("webserver write failed");
          break;
        }
        char file_buffer[1024];
        size_t bytes_read;
        while ((bytes_read = fread(file_buffer, 1, sizeof(file_buffer),
                                   filePointer)) > 0) {

          int valwrite = write(newsockfd, file_buffer, bytes_read);
          if (valwrite < 0) {
            perror("webserver write failed");
            break;
          }
        }
        fclose(filePointer);
        continue;
      } else if (strcmp(uri, "/lists") == 0) {
        // GET /lists

        FILE *temp = tmpfile();
        if (temp == NULL) {
          perror("Failed to create temporary file for lists");
          char *resp = "HTTP/1.0 500 INTERNAL SERVER ERROR\r\n"
                       "Server: webserver-c\r\n"
                       "Content-type: application/json\r\n\r\n"
                        "{\"error\": \"Temporary file unable to build\"}\r\n";
                        
          int valwrite = write(newsockfd, resp, strlen(resp));
          if (valwrite < 0) {
            perror("webserver write failed");
          }
          continue;
        }

        int res = all_lists(temp);
        printf("lists returned: %d\n", res);
        long file_pos = ftell(temp);
        printf("File Pos: %ld\n",file_pos);
        if (file_pos == 0){
          printf("all_lists has 0 lists");
        }

        if (res != 0) {

          perror("Failed to load all lists");
          char *resp = "HTTP/1.0 404 NOT FOUND\r\n"
                       "Server: webserver-c\r\n"
                       "Content-type: application/json\r\n\r\n"
                        "{\"error\": Lists not found\"}\r\n";
          int valwrite = write(newsockfd, resp, strlen(resp));
          if (valwrite < 0) {
            perror("webserver write failed");
            break;
          }
          continue;
        }

        rewind(temp);
        char header[] = "HTTP/1.0 200 OK\r\n"
                        "Server: webserver-c\r\n"
                       "Content-type: application/json\r\n\r\n";

        int valwrite = write(newsockfd, header, sizeof(header));
        if (valwrite < 0) {
          perror("webserver write failed");
          break;
        }
        char file_buffer[1024];
        size_t bytes_read;
        while ((bytes_read = fread(file_buffer, 1, sizeof(file_buffer), temp)) >
               0) {

          int valwrite = write(newsockfd, file_buffer, bytes_read);
          if (valwrite < 0) {
            perror("webserver write failed");
            break;
          }
        }
        fclose(temp);
        close(newsockfd);
        continue;
      } else {
        char *resp = "HTTP/1.0 404 NOT FOUND\r\n"
                     "Server: webserver-c\r\n"
                     "Content-type: text/html\r\n\r\n"
                     "<html>error</html>\r\n";
        int valwrite = write(newsockfd, resp, strlen(resp));
        if (valwrite < 0) {
          perror("webserver write failed");
          continue;
        }
      }

      // Write to the socket

      close(newsockfd);
    }
  }
  return 0;
}
#endif
