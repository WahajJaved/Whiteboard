/*
        TCP_Server. This Program will will create the Server side for TCP_Socket Programming.
        It will receive the data from the client and then send the same data back to client.
*/

#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> //socket
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include "Whiteboard.c"

#define READ_SEM "./sem-read-key"
#define WRITE_SEM "./sem-write-key"

// Buffer data structures
#define MAX_READERS 10

struct arg_struct {
	int socket_desc;
	struct sockaddr_in client_addr;
};
int read_sem, write_sem;


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
	/* for semaphore */
	key_t s_key;
	union semun
	{
		int val;
		struct semid_ds *buf;
		ushort array [1];
	} sem_attr;

	//  mutual exclusion semaphore, mutex_sem with an initial value 1.
	/* generate a key for creating semaphore  */
	if ((s_key = ftok (READ_SEM, 'a')) == -1) {
		perror ("ftok"); exit (1);
	}
	if ((read_sem = semget (s_key, 1, 0660 | IPC_CREAT)) == -1) {
		perror ("semget"); exit (1);
	}
	// Giving initial value.
	sem_attr.val = MAX_READERS-1;        // unlocked
	if (semctl (read_sem, 0, SETVAL, sem_attr) == -1) {
		perror ("semctl SETVAL"); exit (1);
	}

	// counting semaphore, indicating the number of available buffers.
	/* generate a key for creating semaphore  */
	if ((s_key = ftok (WRITE_SEM, 'a')) == -1) {
		perror ("ftok"); exit (1);    /* for semaphore */

	}
	if ((write_sem = semget (s_key, 1, 0660 | IPC_CREAT)) == -1) {
		perror ("semget"); exit (1);
	}
	// giving initial values
	sem_attr.val = 1;    // MAX_BUFFERS are available
	if (semctl (write_sem, 0, SETVAL, sem_attr) == -1) {
		perror (" semctl SETVAL "); exit (1);
	}

	int maxTopics = 5;
    int maxUsers = 3;
    int socket_desc, client_sock, client_size, accept_fd;
    struct sockaddr_in server_addr, client_addr;         //SERVER ADDR will have all the server address
    char server_message[2000], client_message[2000];
    char * str;
    char clientUserName[2000];


    // shmget returns an identifier in shmid
    int shm_id = shmget(IPC_PRIVATE,1024,0666|IPC_CREAT);

	Whiteboard* whiteboard = gettShm(shm_id);
	initWhiteboard(whiteboard,maxTopics,maxUsers);
	printf("maxUsers : %d \n",whiteboard->maxUsers);

	addUser(whiteboard, "abd","124");
	addUser(whiteboard, "cba","321");
	printf("stage 0");


	WriteInShm(shm_id,whiteboard);

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
    server_addr.sin_port = htons(2030);               // Set port number, using htons function to use proper byte order */
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
    while (i<5) {
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
            whiteboard = gettShm(shm_id);

	        // READ Semaphore
	        struct sembuf asem [1];
	        asem [0].sem_op = -1;
	        if (semop (read_sem, asem, 1) == -1) {
		        perror ("semop: dec read_sem"); exit (1);
	        }

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
	        // After READ
	        asem[0].sem_op = 1;
	        if (semop (read_sem, asem, 1) == -1) {
		        perror ("semop: dec read_sem"); exit (1);
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
	                // WRITE
	                asem [0].sem_op = -MAX_READERS+1;
	                if (semop (read_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
	                }

	                asem [0].sem_op = -1;
	                if (semop (write_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
	                }

	                if(addTopic(upd_wb,client_message,currentUser) < 0){
                        printf("Failed to add Topic");
                        return -1;
                    }
	                // After Write
	                asem [0].sem_op = 1;
	                if (semop (write_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
	                }
	                asem [0].sem_op = MAX_READERS-1;
	                if (semop (read_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
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
	                // WRITE
	                asem [0].sem_op = -MAX_READERS+1;
	                if (semop (read_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
	                }

	                asem [0].sem_op = -1;
	                if (semop (write_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
	                }
                    if(deleteTopic(upd_wb, client_message,currentUser) < 0){
                        strcpy(server_message,"Topic Deleted");

                    }
	                // After Write
	                asem [0].sem_op = 1;
	                if (semop (write_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
	                }
	                asem [0].sem_op = MAX_READERS-1;
	                if (semop (read_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
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
	                // WRITE
	                asem [0].sem_op = -MAX_READERS+1;
	                if (semop (read_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
	                }

	                asem [0].sem_op = -1;
	                if (semop (write_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
	                }
                    Topic* topic_name = getTopic(upd_wb,client_message);
                    if(subscribeUser(topic_name,currentUser)<0){
                        strcpy(server_message,"Not Subscribed");
                    }
                    else{
                        strcpy(server_message,"Subscribed");
                    }
	                // After Write
	                asem [0].sem_op = 1;
	                if (semop (write_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
	                }
	                asem [0].sem_op = MAX_READERS-1;
	                if (semop (read_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
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
	                // WRITE
	                asem [0].sem_op = -MAX_READERS+1;
	                if (semop (read_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
	                }

	                asem [0].sem_op = -1;
	                if (semop (write_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
	                }
                    int checker = replyMessage(whiteboard,client_message,currentUser,messageId);
	                // After Write
	                asem [0].sem_op = 1;
	                if (semop (write_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
	                }
	                asem [0].sem_op = MAX_READERS-1;
	                if (semop (read_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
	                }
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
	                // WRITE
	                asem [0].sem_op = -MAX_READERS+1;
	                if (semop (read_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
	                }

	                asem [0].sem_op = -1;
	                if (semop (write_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
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
	                // After Write
	                asem [0].sem_op = 1;
	                if (semop (write_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
	                }
	                asem [0].sem_op = MAX_READERS-1;
	                if (semop (read_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
	                }
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
	                // READ
	                struct sembuf asem [1];
	                asem [0].sem_op = -1;
	                if (semop (read_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
	                }
                    Message* outMess = getMessageTopic(whiteboard,mesId,currentUser );
	                // After READ
	                asem[0].sem_op = 1;
	                if (semop (read_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
	                }
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
	                // READ
	                struct sembuf asem [1];
	                asem [0].sem_op = -1;
	                if (semop (read_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
	                }
                    Message* outMess = getMessageTopic(whiteboard,mesId,currentUser );
	                // After READ
	                asem[0].sem_op = 1;
	                if (semop (read_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
	                }
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
	                // READ
	                struct sembuf asem [1];
	                asem [0].sem_op = -1;
	                if (semop (read_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
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
	                // After READ
	                asem[0].sem_op = 1;
	                if (semop (read_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
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
                	//ret topics
                	Whiteboard * upd_wb = gettShm(shm_id);
	                // READ
	                struct sembuf asem [1];
	                asem [0].sem_op = -1;
	                if (semop (read_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
	                }
	                Topic ** t_list = getAvailableTopicList(upd_wb);

	                int total_iterations = upd_wb->currentTopics;
	                //printf("total iter : %d\n",total_iterations);

	                memset(server_message,'\0',sizeof(server_message));
	                int count = 0;
	                while(count < total_iterations){
		                printf("to be added in all topics %s\n",t_list[count]->topicName);
		                strcat(server_message,t_list[count]->topicName);
		                count++;
	                }
	                // After READ
	                asem[0].sem_op = 1;
	                if (semop (read_sem, asem, 1) == -1) {
		                perror ("semop: spool_signal_sem"); exit (1);
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
            //wait(NULL);
            //PrintShm(shm_id);
        }
    }



	memset(server_message,'\0',sizeof(server_message));
	memset(client_message,'\0',sizeof(client_message));

	// remove semaphores
	if (semctl (read_sem, 0, IPC_RMID) == -1) {
		perror ("semctl IPC_RMID"); exit (1);
	}
	if (semctl (write_sem, 0, IPC_RMID) == -1) {
		perror ("semctl IPC_RMID"); exit (1);
	}

	//Closing the Socket
	close(client_sock);
	close(socket_desc);
	return 0;    
}
