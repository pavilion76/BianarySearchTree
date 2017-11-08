#ifndef NODE_H_
#define NODE_H_
#include <cstddef>
#include "NodeInterface.h"
using namespace std;

class Node:public NodeInterface{
public:
	int data;
	Node *leftChild;
	Node *rightChild;
	Node(int value){
		data=value;
		leftChild = NULL;
		rightChild = NULL;
	}
	int getData() const{
		return data;
	}
	Node* getLeftChild() const{
		return leftChild;
	}
	Node* getRightChild() const{
		return rightChild;
	}
	~Node(){}
	Node(){}

};
#endif
