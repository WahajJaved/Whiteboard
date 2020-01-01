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
	for(int i=0; i<whiteboard->currentUsers; i++){
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

Message* getMessageTopic(Whiteboard* whiteboard, int messageId) {
	for(int i=0; i<whiteboard->currentTopics; i++) {
		if(getMessage(whiteboard->topicList[i],messageId) != NULL) {
			return getMessage(whiteboard->topicList[i],messageId);
		}
	}
	return NULL;
}

int replyMessage(Whiteboard* whiteboard, char* reply, User* user, int messageId) {
	for(int i=0; i<whiteboard->currentTopics; i++) {
		if(getMessage(whiteboard->topicList[i],messageId) != NULL) {
			return addMessage(whiteboard->topicList[i], reply, user);
		}
	}
	return -1;
}

Topic* getTopic(Whiteboard* whiteboard, char* topicName) {
	for(int i=0; i<whiteboard->currentTopics; i++) {
		if(strcmp(topicName, whiteboard->topicList[i]->topicName)){
			return whiteboard->topicList[i];
		}
	}
	return NULL;
}

int deleteTopic(Whiteboard* whiteboard, char* topicName, User * user) {
	for(int i=0; i<whiteboard->currentTopics; i++) {
		if(strcmp(topicName, whiteboard->topicList[i]->topicName)){
			deleteTopicDetails(whiteboard->topicList[i]);
			free(whiteboard->topicList[i]);
			whiteboard->currentTopics--;
			for (int j=i; j<whiteboard->currentTopics; j++) {
				whiteboard->topicList[j] = whiteboard->topicList[j+1];
			}
			return 0;
		}
	}
	return -1;
}
Message** getMessageList(Whiteboard* whiteboard, Topic* topic) {
	return topic->messageList;
}
Topic** getAvailableTopicList(Whiteboard* whiteboard, Topic* topic) {
	return whiteboard->topicList;
}