/*
        TCP_Server. This Program will will create the Server side for TCP_Socket Programming.
        It will receive the data from the client and then send the same data back to client.
*/

#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


struct arg_struct {
    int socket_desc;
    struct sockaddr_in client_addr;
};

struct Voter {
	char Name[30];
 	char CNIC[15];
	char Vote[10];
};


struct Voter* voters;



struct Voter* getVoterList(char* filename) {
	char line_buffer[100];
	FILE* fp = fopen("/tmp/test.txt", "r+");
	
	voters = malloc(10*sizeof(struct Voter));
	int voterCount = 0;
	while(fgets(line_buffer, 100, fp)) {
		for(int i=0; i<100; i++) {
            if (line_buffer[i] == '/') {
                line_buffer[i] = '\0';
                strcpy(voters[voterCount].Name, line_buffer);
                strcpy(voters[voterCount].CNIC, &(line_buffer[i+1]));
            }
        }
        voterCount++;
    }
}

void * cast_vote(void * message) {
    char client_message[200];

    struct arg_struct * args = (struct arg_struct*) message;
    int client_size = sizeof(args->client_addr);
    int client_sock = accept(args->socket_desc, (struct sockaddr*)&args->client_addr, &client_size);          // heree particular client k liye new socket create kr rhaa ha
    if (client_sock < 0){
        printf("Accept Failed. Error!!!!!!\n");
        return -1;
    }

    printf("Client Connected with IP: %s and Port No: %i\n",inet_ntoa(args->client_addr.sin_addr),ntohs(args->client_addr.sin_port));

    //Receive the name and CNIC from client (comma seperated)
    if (recv(client_sock, client_message, sizeof(client_message),0) < 0){
        printf("Receive Failed. Error!!!!!\n");
        return -1;
    }

    printf("Client Message: %s\n",client_message);


    char server_message[100];
    strcpy(server_message, "Enter your desired candidate's symbol");

    struct Voter current_voter;
    for(int i=0; i<100; i++) {
        if (client_message[i] == '/') {
            client_message[i] = '\0';
            strcpy(current_voter.Name, client_message);
            strcpy(current_voter.CNIC, &(client_message[i+1]));
        }
    }

    /* Authenticate User */
    int voter_index = -1;
    int authenticated = 0;
    for (int i=0; i<10; i++) {
        if (strcmp(voters[i].CNIC, current_voter.CNIC) == 0) {
            authenticated = 1;
            voter_index=i;
        }
    }
    //
    if (authenticated) {
        send(client_sock, server_message, sizeof(server_message), 0); // Sends Candidate Details
        recv(client_sock, client_message, sizeof(client_message), 0); // Recieves candidates vote
        strcpy(voters[voter_index].Vote, client_message);
    }
}
void updateFile(char * filename) {
    FILE * fp = fopen(filename, 'w+');
    for (int i=0; i<10; i++) {
        if (voters[i].Vote){
            fprintf(fp, "%s/%s/%s", voters[i].Name, voters[i].CNIC, voters[i].Vote);
        }
    }
}

int main(void)
{
    //voters = getVoterList("Voters_List.txt");

    int socket_desc, client_sock, client_size, accept_fd;
    struct sockaddr_in server_addr, client_addr;         //SERVER ADDR will have all the server address
    char server_message[2000], client_message[2000];                 // Sending values from the server and receive from the server we need this

    //Cleaning the Buffers

    memset(server_message,'\0',sizeof(server_message));
    memset(client_message,'\0',sizeof(client_message));     // Set all bits of the padding field//

    //Creating Socket

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_desc < 0)
    {
        printf("Could Not Create Socket. Error!!!!!\n");
        return -1;
    }

    printf("Socket Created\n");

    //Binding IP and Port to socket

    server_addr.sin_family = AF_INET;               /* Address family = Internet */
    server_addr.sin_port = htons(2020);               // Set port number, using htons function to use proper byte order */
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");    /* Set IP address to localhost */



    // BINDING FUNCTION

    if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0)    // Bind the address struct to the socket.  /
        //bind() passes file descriptor, the address structure,and the length of the address structure
    {
        printf("Bind Failed. Error!!!!!\n");
        return -1;
    }

    printf("Bind Done\n");

    //Put the socket into Listening State

    if(listen(socket_desc, 1) < 0)                               //This listen() call tells the socket to listen to the incoming connections.
        // The listen() function places all incoming connection into a "backlog queue" until accept() call accepts the connection.
    {
        printf("Listening Failed. Error!!!!!\n");
        return -1;
    }

    printf("Listening for Incoming Connections.....\n");

    //Accept the incoming Connections
    int addr_size = sizeof(struct sockaddr_in);
    int child_pid;
    while (1){
        if((accept_fd = accept(socket_desc, (struct sockaddr*)&server_addr, &addr_size))<0)
        {
            printf("Accept Command Failed. Error!!!!!\n");
            return -1;
        }
        if ((child_pid = fork()) == 0){
            //child process
            if(recv(accept_fd, client_message, sizeof(client_message),0) < 0)
            {
                printf("LogIn userName not received. Error!!!!!\n");
                return -1;
            }
            else{
                printf(" client username : ");
                printf("%s",client_message);

                if(recv(accept_fd, client_message, sizeof(client_message),0) < 0)
                {
                    printf("LogIn password not received. Error!!!!!\n");
                    return -1;
                }
                else{
                    printf(" client password : ");
                    printf("%s",client_message);

                    memset(server_message,'\0',sizeof(server_message));
                    strcpy(server_message,"Logged In");
                    if(send(accept_fd, server_message, strlen(server_message),0) < 0)
                    {
                        printf("Authentication not Sent. Error!!!!\n");
                        return -1;
                    }
                    else {
                        printf("client is logged in \n");
                    }
                }
            }
        }


    }

	memset(server_message,'\0',sizeof(server_message));
	memset(client_message,'\0',sizeof(client_message));
			
	//Closing the Socket
	close(client_sock);
	close(socket_desc);
	return 0;    
}
