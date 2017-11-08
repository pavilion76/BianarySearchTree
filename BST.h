#ifndef BST_H_
#define BST_H_
#include "BSTInterface.h"
#include "Node.h"
//set up recursive delete by adding a deconstructor on the Node and calling delete on root
//nevermind, that broke everything
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
	void recursiveDelete(Node* N);
	int size(){
		return sizeOfTree;
	}
	NodeInterface* recurseTo(int data,NodeInterface* tree);
};
#endif
