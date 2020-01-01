//
// Created by wj on 12/30/19.
//

#ifndef WHITEBOARD_MESSAGE_H
#define WHITEBOARD_MESSAGE_H

#include "User.c"

static int currentMessage = 0;
typedef struct{
	int messageId;
	char * messageText;
	User * owner;
	char * status;
}Message;


#endif //WHITEBOARD_MESSAGE_H
