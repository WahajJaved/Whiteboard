//
// Created by wj on 12/30/19.
//

#ifndef WHITEBOARD_TOPIC_H
#define WHITEBOARD_TOPIC_H

#include "User.c"

struct Topic {
	struct Message * messageList;
	struct User owner;
	struct User * subscriberList;
};


#endif //WHITEBOARD_TOPIC_H
