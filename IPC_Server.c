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
#include <sys/ipc.h>
#include <sys/shm.h>
#include "Whiteboard.c"

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

void WriteInShm(int shm_id, Whiteboard* whiteboard){
    // shmat to attach to shared memory
    //printf("Starting to Write");
    Whiteboard* str =  (Whiteboard*) shmat(shm_id, (void *) 0, 0);

    str->maxUsers = whiteboard->maxUsers;
    //detaching shm
    shmdt(str);
}
Whiteboard* gettShm(int shm_id){
    //shmat to attach to shared memory
    //printf("Starting to Retreive");
    Whiteboard * str = (Whiteboard*) shmat(shm_id, (void *) 0, 0);
    //printf("From inside the hell : %d\n", str->maxUsers);
    return str;
}

int main(void)
{
    //voters = getVoterList("Voters_List.txt");
    int maxTopics = 5;
    int maxUsers = 3;
    int socket_desc, client_sock, client_size, accept_fd;
    struct sockaddr_in server_addr, client_addr;         //SERVER ADDR will have all the server address
    char server_message[2000], client_message[2000];
    char * str;
    char clientUserName[2000];

    Whiteboard* whiteboard = malloc(sizeof(Whiteboard));
    initWhiteboard(whiteboard,maxTopics,maxUsers);
    printf("maxUsers : %d \n",whiteboard->maxUsers);
    if(addUser(whiteboard, "abc","123") < 0){
        printf("User not added \n");
        return -1;
    }
    addUser(whiteboard, "abd","124");
    addUser(whiteboard, "cba","321");
    printf("stage 0");

    // shmget returns an identifier in shmid
    int shm_id = shmget(IPC_PRIVATE,1024,0666|IPC_CREAT);

    WriteInShm(shm_id,whiteboard);
    initWhiteboard(gettShm(shm_id),maxUsers,maxTopics);

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
    server_addr.sin_port = htons(2700);               // Set port number, using htons function to use proper byte order */
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
    pid_t child_pid;
    int i=0;
    while (i<1) {
        i++;
        if ((accept_fd = accept(socket_desc, (struct sockaddr *) &server_addr, &addr_size)) < 0) {
            printf("Accept Command Failed. Error!!!!!\n");
            return -1;
        }
        printf("Connection Accepted\n");
        if (fork()== 0) {
            //child process
            User* currentUser;
            //memset(client_message,'\0',sizeof(client_message));
            if (recv(accept_fd, client_message, sizeof(client_message), 0) < 0) {
                printf("LogIn userName not received. Error!!!!!\n");
                return -1;
            }

           // memset(clientUserName, '\0', sizeof(clientUserName));
            strcpy(clientUserName,client_message);
            printf("client username : %s\n",clientUserName);
            //WriteInShm(shm_id);
            memset(client_message,'\0',sizeof(client_message));
            if (recv(accept_fd, client_message, sizeof(client_message), 0) < 0) {
                printf("LogIn password not received. Error!!!!!\n");
                return -1;
            }
            printf("client password : %s\n", client_message);

            memset(server_message, '\0', sizeof(server_message));
            if((currentUser = authenticate(whiteboard,clientUserName,client_message))==NULL){
                printf("Incorrect Credentails \n");
                memset(server_message, '\0', sizeof(server_message));
                strcpy(server_message, "Incorrect Credentials");
            }
            else{
                printf("User Is logged In\n");
                memset(server_message, '\0', sizeof(server_message));
                strcpy(server_message, "Logged In");
            }
            if (send(accept_fd, server_message, strlen(server_message), 0) < 0) {
                printf("Authentication not Sent. Error!!!!\n");
                return -1;
            }
            printf("Session Information Sent to client \n");


            int signal = 0; // 0-not yet decided, 1-Add topic , 2-Exit, 4-delete topic
            while (signal != 2){

                //Ask for signal id from user
                memset(client_message,'\0',sizeof(client_message));
                if (recv(accept_fd, client_message, sizeof(client_message), 0) < 0) {
                    printf("Option not received. Error!!!!!\n");
                    return -1;
                }
                signal = atoi(client_message);
                printf("client choose option no : %d\n",signal);
                if(signal == 1){
                    //adding a topic
                    Whiteboard * upd_wb = gettShm(shm_id);
                    memset(client_message,'\0',sizeof(client_message));
                    memset(server_message,'\0',sizeof(server_message));
                    if (recv(accept_fd, client_message, sizeof(client_message), 0) < 0) {
                        printf("Topic Name not received. Error!!!!!\n");
                        return -1;
                    }
                    if(addTopic(upd_wb,client_message,currentUser) < 0){
                        printf("Failed to add Topic");
                        return -1;
                    }
                    strcpy(server_message,"Topic Added");
                    if (send(accept_fd, server_message, strlen(server_message), 0) < 0) {
                        printf("Authentication not Sent. Error!!!!\n");
                        return -1;
                    }
                    // detaching shm
                    shmdt(upd_wb);
                    WriteInShm(shm_id,upd_wb);
                }
                else if(signal == 4){
                    //delete topic
                    Whiteboard * upd_wb = gettShm(shm_id);
                    memset(client_message,'\0',sizeof(client_message));
                    memset(server_message,'\0',sizeof(server_message));
                    if (recv(accept_fd, client_message, sizeof(client_message), 0) < 0) {
                        printf("Topic Name not received. Error!!!!!\n");
                        return -1;
                    }
                    if(deleteTopic(upd_wb, client_message,currentUser) < 0){
                        strcpy(server_message,"Topic Deleted");

                    }
                    else {
                        strcpy(server_message,"Topic Deleted");
                    }
                    if (send(accept_fd, server_message, strlen(server_message), 0) < 0) {
                        printf("Authentication not Sent. Error!!!!\n");
                        return -1;
                    }

                    // detaching shm
                    shmdt(upd_wb);
                    WriteInShm(shm_id,upd_wb);
                }
                else if (signal == 5){
                    //subscribe for a topic

                    Whiteboard * upd_wb = gettShm(shm_id);
                    memset(client_message,'\0',sizeof(client_message));
                    memset(server_message,'\0',sizeof(server_message));
                    if (recv(accept_fd, client_message, sizeof(client_message), 0) < 0) {
                        printf("Topic Name not received. Error!!!!!\n");
                        return -1;
                    }
                    Topic* topic_name = getTopic(upd_wb,client_message);
                    if(subscribeUser(topic_name,currentUser)<0){
                        strcpy(server_message,"Not Subscribed");
                    }
                    else{
                        strcpy(server_message,"Subscribed");
                    }
                    if (send(accept_fd, server_message, strlen(server_message), 0) < 0) {
                        printf("Authentication not Sent. Error!!!!\n");
                        return -1;
                    }

                    // detaching shm
                    shmdt(upd_wb);
                    WriteInShm(shm_id,upd_wb);
                }

                else if(signal == 6){
                    //reply to a messageId
                    Whiteboard * upd_wb = gettShm(shm_id);
                    memset(client_message,'\0',sizeof(client_message));
                    memset(server_message,'\0',sizeof(server_message));
                    if (recv(accept_fd, client_message, sizeof(client_message), 0) < 0) {
                        printf("Message ID not received. Error!!!!!\n");
                        return -1;
                    }
                    int messageId = atoi(client_message);
                    memset(client_message,'\0',sizeof(client_message));
                    if (recv(accept_fd, client_message, sizeof(client_message), 0) < 0) {
                        printf("Message not received. Error!!!!!\n");
                        return -1;
                    }
                    int checker = replyMessage(whiteboard,client_message,currentUser,messageId);
                    if(checker<0){
                        strcpy(server_message,"Not replied");
                    }
                    else{
                        strcpy(server_message,"reply successfull");
                    }
                    if (send(accept_fd, server_message, strlen(server_message), 0) < 0) {
                        printf("Authentication not Sent. Error!!!!\n");
                        return -1;
                    }

                    // detaching shm
                    shmdt(upd_wb);
                    WriteInShm(shm_id,upd_wb);
                }
                else if(signal == 7){
                    //reply to a topic
                    Whiteboard * upd_wb = gettShm(shm_id);

                    memset(client_message,'\0',sizeof(client_message));
                    if (recv(accept_fd, client_message, sizeof(client_message), 0) < 0) {
                        printf("Topic not received. Error!!!!!\n");
                        return -1;
                    }
                    //printf("%s\n",client_message);
                    Topic* topic_name = getTopic(upd_wb,client_message);
                    printf("total msges %d \n",topic_name->currentMessages);

                    //printf("%s\n",topic_name->topicName);
                    memset(client_message,'\0',sizeof(client_message));
                    if (recv(accept_fd, client_message, sizeof(client_message), 0) < 0) {
                        printf("Message not received. Error!!!!!\n");
                        return -1;
                    }
                    //printf("%s\n",client_message);
                    int checker = addMessage(topic_name,client_message,currentUser);
                    if(checker<0){
                        strcpy(server_message,"Not replied");
                    }
                    else{
                        strcpy(server_message,"reply successfull");
                    }
                    if (send(accept_fd, server_message, strlen(server_message), 0) < 0) {
                        printf("Authentication not Sent. Error!!!!\n");
                        return -1;
                    }
                    // detaching shm
                    shmdt(upd_wb);
                    WriteInShm(shm_id,upd_wb);
                }else if (signal == 8){
                    //get message from id
                    Whiteboard * upd_wb = gettShm(shm_id);
                    memset(client_message,'\0',sizeof(client_message));
                    if (recv(accept_fd, client_message, sizeof(client_message), 0) < 0) {
                        printf("MessageId not received. Error!!!!!\n");
                        return -1;
                    }
                    int mesId = atoi(client_message);
                    Message* outMess = getMessageTopic(whiteboard,mesId,currentUser );
                    if(outMess == NULL){
                        strcpy(server_message,"Not Retreived");
                    }
                    else{
                        strcpy(server_message,outMess->messageText);
                    }
                    if (send(accept_fd, server_message, strlen(server_message), 0) < 0) {
                        printf("Authentication not Sent. Error!!!!\n");
                        return -1;
                    }

                    // detaching shm
                    shmdt(upd_wb);
                    WriteInShm(shm_id,upd_wb);
                }
                else if (signal == 9){
                    //get message status from id
                    Whiteboard * upd_wb = gettShm(shm_id);
                    memset(client_message,'\0',sizeof(client_message));
                    if (recv(accept_fd, client_message, sizeof(client_message), 0) < 0) {
                        printf("MessageId not received. Error!!!!!\n");
                        return -1;
                    }
                    int mesId = atoi(client_message);
                    Message* outMess = getMessageTopic(whiteboard,mesId,currentUser );
                    if(outMess == NULL){
                        strcpy(server_message,"Status Not Retreived");
                    }
                    else{
                        strcpy(server_message,outMess->status);
                    }
                    if (send(accept_fd, server_message, strlen(server_message), 0) < 0) {
                        printf("Authentication not Sent. Error!!!!\n");
                        return -1;
                    }

                    // detaching shm
                    shmdt(upd_wb);
                    WriteInShm(shm_id,upd_wb);
                }
                else if(signal == 10){
                    //get message list
                    Whiteboard * upd_wb = gettShm(shm_id);
                    memset(client_message,'\0',sizeof(client_message));
                    if (recv(accept_fd, client_message, sizeof(client_message), 0) < 0) {
                        printf("Topic not received. Error!!!!!\n");
                        return -1;
                    }
                    Topic* topic_name = getTopic(upd_wb,client_message);

                    Message ** m_list = getMessageList(upd_wb, topic_name);
                    int total_iterations = topic_name->currentMessages;
                    printf("total iter %d\n",total_iterations);

                    memset(server_message,'\0',sizeof(server_message));
                    int count = 1;
                    while(count <= total_iterations){
                        //printf("to be added in all_mess %s\n",m_list[count]->messageText);
                        strcat(server_message,m_list[count]->messageText);
                        count++;
                    }
                    printf("message to send is : %s\n",server_message);
                    if (send(accept_fd, server_message, strlen(server_message), 0) < 0) {
                        printf("Message not Sent. Error!!!!\n");
                        return -1;
                    }

                    // detaching shm
                    shmdt(upd_wb);
                    WriteInShm(shm_id,upd_wb);

                }
                else if(signal == 11){
                    //get topic list
                    Whiteboard * upd_wb = gettShm(shm_id);
                    Topic ** t_list = getAvailableTopicList(upd_wb);

                    int total_iterations = upd_wb->currentTopics;
                    //printf("total iter %d\n",total_iterations);

                    memset(server_message,'\0',sizeof(server_message));
                    int count = 0;
                    while(count <= total_iterations){
                        printf("to be added in all topics %s\n",t_list[count]->topicName);
                        strcat(server_message,t_list[count]->topicName);
                        count++;
                    }
                    printf("message to send is : %s\n",server_message);
                    if (send(accept_fd, server_message, strlen(server_message), 0) < 0) {
                        printf("Message not Sent. Error!!!!\n");
                        return -1;
                    }

                    // detaching shm
                    shmdt(upd_wb);
                    WriteInShm(shm_id,upd_wb);

                }


            }




        }
        else {
            wait(NULL);
            //PrintShm(shm_id);
        }

    }



	memset(server_message,'\0',sizeof(server_message));
	memset(client_message,'\0',sizeof(client_message));
			
	//Closing the Socket
	close(client_sock);
	close(socket_desc);
	return 0;    
}
