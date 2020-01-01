//
// Created by wj on 12/30/19.
//

#include "Topic.h"
#include "stdlib.h"
#include "string.h"



Topic * initTopic(User * owner, char* topicName, int maxMessages, int maxSubscribers ) {
	Topic * topic = malloc(sizeof(Topic));
	topic->owner = owner;
	strcpy(topic->topicName,topicName);
	topic->maxMessages = maxMessages;
	topic->maxSubscribers = maxSubscribers;

	topic->messageList = malloc(sizeof(Message*)*maxMessages);
	topic->subscriberList =  malloc(sizeof(User*)*maxSubscribers);

	topic->currentSubscribers=0;
	topic->currentMessages=0;
	return topic;
}

int subscribeUser(Topic* topic,User* user) {
	if (topic->currentSubscribers < topic->maxSubscribers) {
		topic->subscriberList[topic->currentSubscribers] = user;
		return 0;
	}
	else {
		return -1;
	}
}

int isSubscribed(Topic* topic,User* user) {
	for(int i=0; i<topic->maxSubscribers; i++){
		if(topic->subscriberList[i] == user ){
			return 1;
		}
	}
	return -1;
}
int addMessage(Topic* topic, char* message, User* user) {
	if (topic->currentMessages < topic->maxMessages) {
		Message* mssg = malloc(sizeof(Message));
		mssg->owner = user;
		mssg->messageId=currentMessage++;
		strcpy(mssg->status,"Published");
		strcpy(mssg->messageText, message);
		topic->messageList[topic->currentMessages] = mssg;
		return 0;
	}
	else {
		return -1;
	}
}
Message* getMessage(Topic* topic, int messageId) {
	for (int i = 0; i < topic->currentMessages; i++) {
		if (messageId == topic->messageList[i]->messageId) {
			return topic->messageList[i];
		}
	}
	return NULL;

}
void deleteTopicDetails(Topic * topic) {
	for (int i = 0; i < topic->currentMessages; i++) {
		free(topic->messageList[i]);
	}
	free(topic->messageList);
	free(topic->subscriberList);
}

//int addMessage(struct )