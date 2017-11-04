#ifndef BST_H_
#define BST_H_
#include "BSTInterface.h"
#include "Node.h"

class BST: public BSTInterface {
public:
	Node* root = NULL;
	int sizeOfTree =0;
	BST();
	~BST();
	NodeInterface* getRootNode() const{
		return root;
	}
	string BSTtoString(BST* bst);
	virtual bool add(int data);
	bool add(NodeInterface* tree);
	virtual bool remove(int data);
	virtual void clear();
	int size(){
		return sizeOfTree;
	}
	NodeInterface* recurseTo(int data,NodeInterface* tree);
};
#endif
