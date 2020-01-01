//
// Created by wj on 12/30/19.
//

#ifndef WHITEBOARD_MESSAGE_H
#define WHITEBOARD_MESSAGE_H

#include "User.c"

static int currentMessage = 0;
typedef struct{
	int messageId;
	char messageText[1024];
	char status[16];
	User * owner;
}Message;


#endif //WHITEBOARD_MESSAGE_H
