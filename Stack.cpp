//
// Created by Devon Mack on 4/4/2017.
//

#include "Stack.h"

using namespace std;

Stack::Stack() {
	head = NULL;
    size = 0;
}

Block* Stack::pop() {
    Block* ret;
    if (head != NULL) {
    	ret = head->data;
    	
		Node* temp = head->next;
		delete head;
		head = temp;
		
    } else {
        cout << "[Warning] Popping from empty stack!" << endl;
        return ret;
    }
    
	size--;
    return ret;
}

void Stack::push(Block* n) {
    nn = new Node;
    nn->data = n;
    nn->next = head;
    
	head = nn;
	size++;
}

int Stack::getSize() {
	return size;
}

/*Stack::~Stack() {
	cout << "destroy";
}*/

