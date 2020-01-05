/*
        TCP_Client. This Program will implement the Client Side for TCP_Socket Programming.
        It will get some data from user and will send to the server and as a reply from the
        server, it will get its data back.
*/

#include <stdio.h>
#include <string.h>
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr

int main(void)
{
        int socket_desc;
        struct sockaddr_in server_addr;
        char server_message[2020], client_message[2020];
        
        //Cleaning the Buffers
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        
        //Creating Socket
        
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);
        
        if(socket_desc < 0)
        {
                printf("Could Not Create Socket. Error!!!!!\n");
                return -1;
        }
        
        printf("Socket Created\n");
        
        //Specifying the IP and Port of the server to connect
        
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(2000);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        
        //Now connecting to the server accept() using connect() from client side
        
        if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
        {
                printf("Connection Failed. Error!!!!!");
                return -1;
        }
        
        printf("Connected\n");
        
        //Get Input from the User
        
        printf("Enter UserName: ");
        gets(client_message);                                     //One is that gets() will only get character string data. 
                                                       //		will get only one variable at a time.
																//  reads characters from stdin and loads them into str
        //Send the message to Server
        
        if(send(socket_desc, client_message, strlen(client_message),0) < 0)
        {
                printf("UserName not sent. Error!!!!\n");
                return -1;
        }

        memset(client_message,'\0',sizeof(client_message));
        printf("Enter Password: ");
        gets(client_message);
        if(send(socket_desc, client_message, strlen(client_message),0) < 0)
        {
            printf("Password not sent. Error!!!!\n");
            return -1;
        }

        //Receive the message back from the server
        
        if(recv(socket_desc, server_message, sizeof(server_message),0) < 0)
        {
                printf("Receive Failed. Error!!!!!\n");
                return -1;
        }
        
        printf("Server Message: %s\n",server_message);

        int signal = 0;
        while(signal != 2){
            printf("Enter no of any option you want to choose \n(0-nothing\n 1-Add New Topic\n 2-Exit\n 4-Delete Topic\n 5- Subscribe to a topic\n 6-Reply to a messageId\n 7-Reply to a topic\n 8-Get message from id\n 9-Get message status from id\n 10-Get message list\n 11- Get topic list\n");
            memset(client_message,'\0',sizeof(client_message));
            gets(client_message);
            signal = atoi(client_message);

            if(send(socket_desc, client_message, strlen(client_message),0) < 0)
            {
                printf("option not sent. Error!!!!\n");
                return -1;
            }

            if (signal == 1){
                //addTopic
                memset(client_message,'\0',sizeof(client_message));
                printf("type the name of new Topic : ");
                gets(client_message);
                if(send(socket_desc, client_message, strlen(client_message),0) < 0)
                {
                    printf("topic name not sent. Error!!!!\n");
                    return -1;
                }
                memset(server_message,'\0',sizeof(server_message));
                if(recv(socket_desc, server_message, sizeof(server_message),0) < 0)
                {
                    printf("Receive Failed. Error!!!!!\n");
                    return -1;
                }
                printf("server replied : %s\n",server_message);
            }
            else if(signal == 4){
                memset(client_message,'\0',sizeof(client_message));
                printf("Enter the name of topic you want to delete : ");
                gets(client_message);
                if(send(socket_desc, client_message, strlen(client_message),0) < 0)
                {
                    printf("topic name not sent. Error!!!!\n");
                    return -1;
                }
                memset(server_message,'\0',sizeof(server_message));
                if(recv(socket_desc, server_message, sizeof(server_message),0) < 0)
                {
                    printf("Receive Failed. Error!!!!!\n");
                    return -1;
                }
                printf("server replied : %s\n",server_message);
            }
            else if(signal == 5){
                memset(client_message,'\0',sizeof(client_message));
                printf("Enter the name of topic you want to subscribe : ");
                gets(client_message);
                if(send(socket_desc, client_message, strlen(client_message),0) < 0)
                {
                    printf("topic name not sent. Error!!!!\n");
                    return -1;
                }
                memset(server_message,'\0',sizeof(server_message));
                if(recv(socket_desc, server_message, sizeof(server_message),0) < 0)
                {
                    printf("Receive Failed. Error!!!!!\n");
                    return -1;
                }
                printf("server replied : %s\n",server_message);
            }
            else if(signal == 6){
                memset(client_message,'\0',sizeof(client_message));
                printf("Enter the Id of message you want to apply to : ");
                gets(client_message);
                if(send(socket_desc, client_message, strlen(client_message),0) < 0)
                {
                    printf("topic name not sent. Error!!!!\n");
                    return -1;
                }
                memset(client_message,'\0',sizeof(client_message));
                printf("Enter the message you want to reply : ");
                gets(client_message);
                if(send(socket_desc, client_message, strlen(client_message),0) < 0)
                {
                    printf("topic name not sent. Error!!!!\n");
                    return -1;
                }
                memset(server_message,'\0',sizeof(server_message));
                if(recv(socket_desc, server_message, sizeof(server_message),0) < 0)
                {
                    printf("Receive Failed. Error!!!!!\n");
                    return -1;
                }
                printf("server replied : %s\n",server_message);
            }
            else if(signal == 7){
                memset(client_message,'\0',sizeof(client_message));
                printf("Enter the Topic you want to reply to : ");
                gets(client_message);
                if(send(socket_desc, client_message, strlen(client_message),0) < 0)
                {
                    printf("topic name not sent. Error!!!!\n");
                    return -1;
                }
                memset(client_message,'\0',sizeof(client_message));
                printf("Enter the message you want to reply : ");
                gets(client_message);
                if(send(socket_desc, client_message, strlen(client_message),0) < 0)
                {
                    printf("message not sent. Error!!!!\n");
                    return -1;
                }
                memset(server_message,'\0',sizeof(server_message));
                if(recv(socket_desc, server_message, sizeof(server_message),0) < 0)
                {
                    printf("Receive Failed. Error!!!!!\n");
                    return -1;
                }
                printf("server replied : %s\n",server_message);
            }
            else if(signal == 8){
                memset(client_message,'\0',sizeof(client_message));
                printf("Enter the messageId you want to get : ");
                gets(client_message);
                if(send(socket_desc, client_message, strlen(client_message),0) < 0)
                {
                    printf("messageID not sent. Error!!!!\n");
                    return -1;
                }
                memset(server_message,'\0',sizeof(server_message));
                if(recv(socket_desc, server_message, sizeof(server_message),0) < 0)
                {
                    printf("Receive Failed. Error!!!!!\n");
                    return -1;
                }
                printf("server replied : %s\n",server_message);
            }

            else if(signal == 9){
                memset(client_message,'\0',sizeof(client_message));
                printf("Enter the messageId you want to get status of : ");
                gets(client_message);
                if(send(socket_desc, client_message, strlen(client_message),0) < 0)
                {
                    printf("messageID not sent. Error!!!!\n");
                    return -1;
                }
                memset(server_message,'\0',sizeof(server_message));
                if(recv(socket_desc, server_message, sizeof(server_message),0) < 0)
                {
                    printf("Receive Failed. Error!!!!!\n");
                    return -1;
                }
                printf("server replied : %s\n",server_message);
            }else if (signal == 10){
                memset(client_message,'\0',sizeof(client_message));
                printf("Enter the Topic you want to see messages off : ");
                gets(client_message);
                if(send(socket_desc, client_message, strlen(client_message),0) < 0)
                {
                    printf("topic name not sent. Error!!!!\n");
                    return -1;
                }
                char* all_messages[4000];
                memset(all_messages,'\0',sizeof(all_messages));
                if(recv(socket_desc, all_messages, sizeof(all_messages),0) < 0)
                {
                    printf("Receive Failed. Error!!!!!\n");
                    return -1;
                }
                printf("%s\n",all_messages);
            }
            else if (signal == 11){
	            memset(server_message,'\0',sizeof(server_message));
	            memset(server_message,'\0',sizeof(server_message));
	            if(recv(socket_desc, server_message, sizeof(server_message),0) < 0)
	            {
		            printf("Receive Failed. Error!!!!!\n");
		            return -1;
	            }
	            printf("%s\n",server_message);
            }


        }

        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        
        //Closing the Socket
        close(socket_desc);
        
        return 0;
}



