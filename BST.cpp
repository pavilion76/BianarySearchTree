#include "BST.h"
using namespace std;

BST::BST(){
	cout<<"I innitialized BST object\n";
}
BST::~BST(){
	clear();
}
bool BST::add(int data){
	//cout<<"adding "<<data<<endl;
	if(root==NULL){
		root = new Node(data);
		return true;
	}
	Node *parent = root;
	Node *grandParent = parent;
	while(true){
		//cout<<"in add function loop adding "<<data<<endl;
		if(parent !=NULL)
			grandParent = parent;
		if(parent == NULL){						//this is where we insert the data 
			//cout<<"found where to insert the data\n";
			//cout<<"gradnparent "<<grandParent->getData()<<endl;
			if(grandParent->getData() >data)
				grandParent->leftChild = new Node(data);
			if(grandParent->getData() <data)
				grandParent->rightChild = new Node(data);
			//cout<<"just incrimenting the size\n";
			sizeOfTree++;
			return true;
		}
		if(parent->getData() == data)			//not allowed to have duplicates
			return false;	
		else if(parent->getData() >data)
			parent = parent->getLeftChild();
		else if(parent->getData() <data)
			parent = parent->getRightChild();
		
	}
}
NodeInterface* BST::recurseTo(int data,NodeInterface* tree){
	if(tree->getData()==data)
		return NULL;
	if(tree->getData() == data)
		return tree;
	if(tree->getData() >= data)
		return recurseTo(data,tree->getRightChild());
	if(tree->getData() <=data)
		return recurseTo(data,tree->getLeftChild());
}
//this is the same thing as add, but you pass in a node (and therefore the entire tree behind it)
bool BST::add(NodeInterface* tree){
	/*if(root==NULL){
		//root = tree;
		return true;
	}
	NodeInterface *parent = root;
	NodeInterface *grandParent = parent;
	while(true){
		grandParent = parent;
		if(parent->getData() == tree->getData())			//not allowed to have duplicates
			return false;	
		else if(parent->getData() >tree->getData())
			parent = parent->getLeftChild();
		else if(parent->getData() <tree->getData())
			parent = parent->getRightChild();
		if(parent == NULL){						//this is where we insert the data 
			if(grandParent->getData() >tree->getData())
				parent->leftChild = tree;
			if(grandParent->getData() <tree->getData())
				parent->rightChild = tree;
			return true;
		}
	}*/
}
/*bool BST::remove(int data){
	if(root==NULL){
		return true;
	}
	NodeInterface *parent = root;
	NodeInterface *grandParent = parent
	while(true){
		grandParent = parent;
		if(parent->getData() == data){						//Found what needs to be deleted
			if(grandParent->getData() >data)
				//parent->leftChild = Node(data);
			if(grandParent->getData() <data)
				//parent->rightChild = Node(data);
			sizeOfTree--;
			return true;
		}
		else if(parent->getData() >data)
			parent = parent->getLeftChild();
		else if(parent->getData() <data)
			parent = parent->getRightChild();
		if(parent == NULL){									//Crap....
			return false;
		}
	}
}*/
bool BST::remove(int data){
	cout<<"\nremoving "<<data<<endl;
	if(root==NULL)
		return false;
	Node *parent = root;
	Node *grandParent = parent;
	while(parent!=NULL || parent->getData() !=data){
		cout<<"in while loop. parent val "<<parent->getData()<<endl;
				if(parent->getData() == data){	//we have found what we need to remove
					cout<<"found the node! "<<parent->getData()<<" == "<<data<<endl;
					if(parent->getRightChild() == NULL && parent->getLeftChild() == NULL){	//if we are removing a leaf
						cout<<"we are removing a leaf\n";
						if(grandParent->getRightChild() == parent)
							grandParent->rightChild == NULL;
						else if(grandParent->getLeftChild() == parent)
							grandParent->leftChild == NULL;
						delete parent;
						return true;
					}else if(!(parent->getRightChild() == NULL) != !(parent->getLeftChild() == NULL)){ //if parent only has one child
						cout<<"we are removing a node with only one child\ngrandParent is "<<grandParent->getData()<<endl;
						if(parent->getRightChild() == NULL){				//left subtree moves up
							cout<<"there is no right child for "<<parent->getData()<<endl;
							if(grandParent->getRightChild()->getData() == parent->getData()){
								cout<<"R, R\n";
								cout<<"replacing "<<grandParent->getRightChild()->getData() <<" with "<<parent->getLeftChild()->getData()<<endl;
								grandParent->rightChild = parent->getLeftChild();
							}else if(grandParent->getLeftChild()->getData() == parent->getData()){
								cout<<"L,R\n";
								cout<<"replacing "<<grandParent->getLeftChild()->getData() <<" with "<<parent->getLeftChild()->getData()<<endl;
								grandParent->leftChild = parent->getLeftChild();
							}
							delete parent;
							return true;
						}else if(parent->getLeftChild() == NULL){			//right subtree moves up
							cout<<"there is no left subtree for "<<parent->getData()<<endl;
							if(grandParent->getRightChild() == parent){
								cout<<"R,L\n";
								cout<<"replacing "<<grandParent->getRightChild()->getData() <<" with "<<parent->getRightChild()->getData()<<endl;
								grandParent->rightChild = parent->getRightChild();
							}else if(grandParent->getLeftChild() == parent){
								cout<<"L,R\n";
								cout<<"replacing "<<grandParent->getLeftChild()->getData() <<" with "<<parent->getRightChild()->getData()<<endl;
								grandParent->leftChild = parent->getRightChild();
							}
							cout<<";(\n";
							delete parent;
							return true;
						}
						cout<<"Hmmm... Something went wrong in the remove function, with only one child.\n";
					}else{																		//if there are two children
						//if there are two children you can get the largest value of the left sub tree to replace it. (lab implimentation)
						cout<<"there should be two children\n";
						Node* temp = parent->getLeftChild();
						while(temp->getRightChild() != NULL)
							temp=temp->getRightChild();
						//temp is now the value we will be replacing parent with AKA, the largest value (and which by deffinition is a leaf)
						if(grandParent->getRightChild() == parent){
							grandParent->rightChild = temp;
						}else if(grandParent->getLeftChild() == parent){
							grandParent->leftChild = temp;
						}
					}	
				}
		grandParent = parent;
		if(parent->getData() > data){
			parent = parent->getLeftChild();
		}else{
			parent = parent->getRightChild();
		}
		if(parent == NULL)
			return false;
	}
	return false; // clearly didn't find the node, because it doesn't exist, or this isn't a true BST
}
void BST::clear(){
	NodeInterface *parent = root;
	while(root != NULL){
		NodeInterface *grandParent = parent;	
		while(parent->getLeftChild() != NULL && parent->getRightChild() != NULL){//going through left children
			if(parent->getLeftChild() !=NULL){
				grandParent = parent;
				parent = parent->getLeftChild();
			}
			if(parent->getRightChild() !=NULL){
				grandParent = parent;
				parent = parent->getRightChild();
			}
		}//now that the Left child is null
	}
}
