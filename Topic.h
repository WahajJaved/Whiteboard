//
// Created by wj on 12/30/19.
//

#ifndef WHITEBOARD_TOPIC_H
#define WHITEBOARD_TOPIC_H


#include "Message.c"
#include "User.c"

typedef struct {
	char* topicName;
	Message * messageList;
	User * owner;
	User ** subscriberList;
	int currentMessages, currentSubscribers;
	int maxMessages, maxSubscribers;
} Topic;


#endif //WHITEBOARD_TOPIC_H
