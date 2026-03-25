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

#ifdef WEBSERVER
extern int all_lists(FILE *);
extern int appendTask(char *message, char *listname);
extern int pigeonshred(FILE *, char *);

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

        int valwrite = write(newsockfd, header, strlen(header));
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
          close(newsockfd);
          continue;
        }

        int res = all_lists(temp);

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

        int valwrite = write(newsockfd, header, strlen(header));
        if (valwrite < 0) {
          perror("webserver write failed");
          break;
        }
        char open_bracket = '[';
        write(newsockfd, &open_bracket, 1);
        char line[256];
        int first_item = 1;
        while (fgets(line, sizeof(line), temp) != NULL) {

          size_t line_length = strlen(line);
          if (line_length > 0 && line[line_length - 1] == '\n') {
            line[line_length - 1] = '\0';
            line_length--;
          }

          if (strlen(line) > 0) {
            if (!first_item) {
              write(newsockfd, ",", 1);
            }
            first_item = 0;

            write(newsockfd, "\"", 1);

            for (int i = 0; line[i] != '\0'; i++) {
              write(newsockfd, &line[i], 1);
            }
            write(newsockfd, "\"", 1);
          }
        }

        valwrite = write(newsockfd, "]", 1);
        if (valwrite < 0) {
          perror("webserver write failed");
          break;
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

    else if (strcmp(method, "POST") == 0) {

      if (strcmp(uri, "/fly") == 0) {

        char *body = NULL;

        for (char *p = buffer; p < buffer + valread - 3; p++) {
          if (p[0] == '\r' && p[1] == '\n' && p[2] == '\r' && p[3] == '\n') {
            body = p + 4;
            break;
          }
        }
        // null terminate input
        if (body) {
          char *end = memchr(body, '\r', valread - (body - buffer));
          if (!end) {
            end = memchr(body, '\n', valread - (body - buffer));
          }
          if (end) {
            *end = '\0';
          } else {
            body[valread - (body - buffer)] = '\0';
          }
          char listname[256] = {0};
          char task[256] = {0};
          sscanf(body, "%255[^~\r\n]~%255[^\r\n]", listname, task);
          appendTask(task, listname);
          char resp[] = "HTTP/1.0 200 OK\r\n"
                        "Server: webserver-c\r\n"
                        "Content-type: text/plain\r\n\r\n"
                        "OK\r\n";
          write(newsockfd, resp, strlen(resp));
        } else {
          char resp[] = "HTTP/1.0 404 NOT FOUND\r\n"
                        "Server: webserver-c\r\n"
                        "Content-type: text/plain\r\n\r\n"
                        "appendTask Failed\r\n";
        }
        close(newsockfd);
        continue;
      }
    } else if (strcmp(method, "DELETE") == 0) {
      if (strcmp(uri, "/shredlist") == 0) {

        char *body = NULL;

        printf("buffer: %s\n", buffer);
        for (char *p = buffer; p < buffer + valread - 3; p++) {
          if (p[0] == '\r' && p[1] == '\n' && p[2] == '\r' && p[3] == '\n') {
            body = p + 4;
            break;
          }
        }
        if (body) {
          char *end = memchr(body, '\r', valread - (body - buffer));
          if (!end) {
            end = memchr(body, '\n', valread - (body - buffer));
          }
          if (end) {
            *end = '\0';
          } else {
            body[valread - (body - buffer)] = '\0';
          }
          char listname[256] = {0};
          sscanf(body, "%255[^\r\n]", listname);
          printf("body: %s\n", body);
          printf("listname: %s\n", listname);

          pigeonshred(stdout, listname);
          char resp[] = "HTTP/1.0 200 OK\r\n"
                        "Server: webserver-c\r\n"
                        "Content-type: text/plain\r\n\r\n"
                        "OK\r\n";
          write(newsockfd, resp, strlen(resp));
        } else {
          char resp[] = "HTTP/1.0 404 NOT FOUND\r\n"
                        "Server: webserver-c\r\n"
                        "Content-type: text/plain\r\n\r\n"
                        "appendTask Failed\r\n";
        }
        close(newsockfd);
        continue;
      }
    }
  }
  return 0;
}

#endif
