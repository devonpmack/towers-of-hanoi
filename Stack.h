//
// Created by Devon Mack on 4/4/2017.
//

#ifndef RPN_STACK_H
#define RPN_STACK_H

#include "Block.h"
#include "Block.cpp"

#include <iostream>

class Stack {
    protected:
    	struct Node {
			Node* next;
			Block* data;
		};
        Node* head;
        Node* nn;
        int size;
    public:
        Stack();
        void push(Block* n);
        Block* pop();
        ~Stack() { std::cout << "Unloading stack." << std::endl;};
        int getSize();
};


#endif //RPN_STACK_H
