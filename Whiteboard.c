//
// Created by wj on 12/30/19.
//

#include "Whiteboard.h"


void initWhiteboard(Whiteboard * whiteboard, int maxTopics, int maxUsers ) {
	whiteboard->maxTopics = maxTopics;
	whiteboard->maxUsers = maxUsers;
	whiteboard->topicList = malloc(sizeof(Topic*)*maxTopics);
	whiteboard->userList = malloc(sizeof(*whiteboard->userList)*maxUsers);
	whiteboard->currentTopics=0;
	whiteboard->currentUsers=0;
}

int addUser(Whiteboard * whiteboard, char* username, char* password) {
	if (whiteboard->currentUsers < whiteboard->maxUsers) {
		whiteboard->userList[whiteboard->currentUsers] = malloc(sizeof(User));//->username, username);
		strcpy(whiteboard->userList[whiteboard->currentUsers]->username, username);
		strcpy(whiteboard->userList[whiteboard->currentUsers]->password, password);
		whiteboard->currentUsers++;
		return 0;
	}
	else {
		return -1;
	}
}

User* authenticate(Whiteboard* whiteboard, char * username, char* password) {
	for(int i=0; i<whiteboard->maxUsers; i++){
		if(!strcmp(whiteboard->userList[i]->username, username) && !strcmp(whiteboard->userList[i]->password, password)){
			return whiteboard->userList[i];
		}
	}
	return NULL;
}

int addTopic(Whiteboard * whiteboard, char* topicName, User * owner) {
	if (whiteboard->currentTopics < whiteboard->maxTopics) {
		whiteboard->topicList[whiteboard->currentTopics] = initTopic(owner, topicName, 10, 10);
		whiteboard->currentTopics++;
		return 0;
	}
	else {
		return -1;
	}
}