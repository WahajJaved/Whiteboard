//
// Created by wj on 12/30/19.
//

#ifndef WHITEBOARD_WHITEBOARD_H
#define WHITEBOARD_WHITEBOARD_H


#include "Topic.c"

typedef struct {
	Topic ** topicList;
	User ** userList;
	int currentTopics;
	int currentUsers;
	int maxTopics;
	int maxUsers;
} Whiteboard;


#endif //WHITEBOARD_WHITEBOARD_H
