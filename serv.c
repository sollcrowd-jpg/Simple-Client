#include <netinet/in.h> // structure for storing address information
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h> // for socket APIs
#include <sys/types.h>  // for socket APIs
#include "list.h"       // Your linked list implementation

#define PORT 9001
#define ACK "ACK"

int main(int argc, char const* argv[]) {
    int n, val, idx;
    
    // create server socket
    int servSockD = socket(AF_INET, SOCK_STREAM, 0);
    
    // string to store data to recv/send to/from client
    char buf[1024];
    char sbuf[1024];
    char* token;

    // define server address
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(PORT);
    servAddr.sin_addr.s_addr = INADDR_ANY;

    // bind socket to the specified IP and port
    bind(servSockD, (struct sockaddr*)&servAddr, sizeof(servAddr));
    
    // listen for connections
    listen(servSockD, 1);
    
    // integer to hold client socket
    int clientSocket = accept(servSockD, NULL, NULL);

    // create the list
    list_t* mylist = list_alloc();  

    while (1) {
        // receive messages from client socket
        n = recv(clientSocket, buf, sizeof(buf), 0);
        buf[n] = '\0';

        if (n > 0) {
            token = strtok(buf, " ");
            
            if (strcmp(token, "exit") == 0) {
                list_free(mylist); // free linked list
                exit(1);           // terminate server
            } else if (strcmp(token, "get_length") == 0) {
                val = list_length(mylist);
                sprintf(sbuf, "%s%d", "Length = ", val);
            } else if (strcmp(token, "add_front") == 0) {
                token = strtok(NULL, " ");
                val = atoi(token);
                list_add_to_front(mylist, val);
                sprintf(sbuf, "%s%d", ACK, val);
            } else if (strcmp(token, "add_back") == 0) {
                token = strtok(NULL, " ");
                val = atoi(token);
                list_add_to_back(mylist, val);
                sprintf(sbuf, "%s%d", ACK, val);
            } else if (strcmp(token, "add_position") == 0) {
                token = strtok(NULL, " ");
                idx = atoi(token);
                token = strtok(NULL, " ");
                val = atoi(token);
                list_add_at_index(mylist, idx, val);
                sprintf(sbuf, "%s%d", ACK, val);
            } else if (strcmp(token, "remove_front") == 0) {
                val = list_remove_from_front(mylist);
                sprintf(sbuf, "Removed front = %d", val);
            } else if (strcmp(token, "remove_back") == 0) {
                val = list_remove_from_back(mylist);
                sprintf(sbuf, "Removed back = %d", val);
            } else if (strcmp(token, "remove_position") == 0) {
                token = strtok(NULL, " ");
                idx = atoi(token);
                val = list_remove_at_index(mylist, idx);
                sprintf(sbuf, "Removed at %d = %d", idx, val);
            } else if (strcmp(token, "get") == 0) {
                token = strtok(NULL, " ");
                idx = atoi(token);
                val = list_get_elem_at(mylist, idx);
                sprintf(sbuf, "Element at %d = %d", idx, val);
            } else if (strcmp(token, "print") == 0) {
                sprintf(sbuf, "%s", listToString(mylist));
            }

            // send response to client
            send(clientSocket, sbuf, sizeof(sbuf), 0);
        }
        memset(buf, '\0', 1024);
    }

    return 0;
}
