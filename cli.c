#include <netinet/in.h> // Structure for storing address information
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <sys/socket.h> // For socket APIs
#include <sys/types.h>

#define PORT 9001
#define MAX_COMMAND_LINE_LEN 1024

char* getCommandLine(char *command_line) {
    do { 
        // Read input from stdin and store it in command_line. If there's an error, exit immediately.
        if ((fgets(command_line, MAX_COMMAND_LINE_LEN, stdin) == NULL) && ferror(stdin)) {
            fprintf(stderr, "Error: Unable to read input\n");
            exit(EXIT_FAILURE);
        }
    } while (command_line[0] == '\n'); // Handle case where only ENTER is pressed

    command_line[strlen(command_line) - 1] = '\0'; // Remove trailing newline character
    return command_line;
}

int main(int argc, char const* argv[]) { 
    int sockID = socket(AF_INET, SOCK_STREAM, 0); 
    char *token, *cp;
    char buf[MAX_COMMAND_LINE_LEN];
    char responseData[MAX_COMMAND_LINE_LEN];

    struct sockaddr_in servAddr; 
  
    servAddr.sin_family = AF_INET; 
    servAddr.sin_port = htons(PORT); 
    servAddr.sin_addr.s_addr = INADDR_ANY; 
  
    int connectStatus = connect(sockID, (struct sockaddr*)&servAddr, sizeof(servAddr)); 
  
    if (connectStatus == -1) { 
        printf("Connection failed. Please check server status.\n"); 
        return EXIT_FAILURE;
    } else { 
        printf("Connected to the server successfully.\n");

        while (1) {
            printf("Enter Command (or type 'menu' for options): ");
            getCommandLine(buf);

            send(sockID, buf, strlen(buf), 0);  // Send command and arguments to server

            cp = buf;
            token = strtok(cp, " ");

            if (strcmp(token, "exit") == 0) {
                printf("Exiting client. Goodbye!\n");
                break;
            } else if (strcmp(token, "menu") == 0) {
                printf("\nCOMMANDS LIST:\n");
                printf("1. print - Display all elements in the list\n");
                printf("2. get_length - Get the current size of the list\n");
                printf("3. add_back <value> - Add a value to the end of the list\n");
                printf("4. add_front <value> - Add a value to the start of the list\n");
                printf("5. add_position <index> <value> - Add a value at a specific index\n");
                printf("6. remove_back - Remove the last element\n");
                printf("7. remove_front - Remove the first element\n");
                printf("8. remove_position <index> - Remove an element at a specific index\n");
                printf("9. get <index> - Get the element at a given index\n");
                printf("10. exit - Terminate the client\n");
                continue;
            }

            recv(sockID, responseData, sizeof(responseData), 0); // Receive response from server
            printf("\nSERVER RESPONSE: %s\n", responseData);
            memset(buf, '\0', MAX_COMMAND_LINE_LEN);
        }
    }
    close(sockID); // Close the client socket
    return 0;
}
