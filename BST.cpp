#include "BST.h"
#include <queue>
#include <sstream>
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
	if(sizeOfTree == 0 && root->getData() == data){
		delete root;
		root=NULL;
		return true;
	}
	Node *parent = root;
	Node *grandParent = parent;
	while(parent!=NULL || parent->getData() !=data){
		cout<<"in while loop. parent val "<<parent->getData()<<endl;
				if(parent->getData() == data){	//we have found what we need to remove
					cout<<"found the node! "<<parent->getData()<<" == "<<data<<endl;
					cout<<grandParent->getData()<<endl;
					if(parent->getRightChild() == NULL && parent->getLeftChild() == NULL){	//if we are removing a leaf
						cout<<"we are removing a leaf\n";
						if(grandParent->getRightChild() != NULL && grandParent->getRightChild()->getData() == parent->getData()){
							cout<<"setting: "<<grandParent->rightChild->getData()<<" to NULL\n";
							grandParent->rightChild = NULL;
						}else if(grandParent->getLeftChild() != NULL && grandParent->getLeftChild()->getData() == parent->getData()){
							cout<<"setting: "<<grandParent->leftChild->getData()<<" to NULL\n";
							grandParent->leftChild = NULL;
						}
						delete parent;
						//cout<<BSTtoString(this);
						sizeOfTree--;
						return true;
					}else if(!(parent->getRightChild() == NULL) != !(parent->getLeftChild() == NULL)){ //if parent only has one child
						cout<<"we are removing a node with only one child\ngrandParent is "<<grandParent->getData()<<endl;
						if(parent->getRightChild() == NULL){				//left subtree moves up
							cout<<"there is no right child for "<<parent->getData()<<endl;
							if(grandParent->getRightChild() == parent){
								cout<<"R, R\n";
								cout<<"replacing "<<grandParent->getRightChild()->getData() <<" with "<<parent->getLeftChild()->getData()<<endl;
								grandParent->rightChild = parent->getLeftChild();
							}else if(grandParent->getLeftChild() == parent){
								cout<<"L,R\n1\n";
								cout<<"replacing "<<grandParent->getLeftChild()->getData() <<" with "<<parent->getLeftChild()->getData()<<endl;
								grandParent->leftChild = parent->getLeftChild();
							}
							delete parent;
							sizeOfTree--;
							return true;
						}else if(parent->getLeftChild() == NULL){			//right subtree moves up
							cout<<"there is no left subtree for "<<parent->getData()<<endl;
							if(grandParent->getRightChild() == parent){
								cout<<"R,L\n";
								cout<<"replacing "<<grandParent->getRightChild()->getData() <<" with "<<parent->getRightChild()->getData()<<endl;
								grandParent->rightChild = parent->getRightChild();
							}else if(grandParent->getLeftChild() == parent){
								cout<<"L,R\n2\n";
								cout<<"replacing "<<grandParent->getLeftChild()->getData() <<" with "<<parent->getRightChild()->getData()<<endl;
								grandParent->leftChild = parent->getRightChild();
							}else if(grandParent == parent){
                                cout<<"replacing root "<<parent->getData()<<" with "<<grandParent->getRightChild()->getData()<<endl;
                                root = parent->getRightChild();
                            }
							cout<<";(\n";
							//cout<<BSTtoString(this);
							delete parent;
							sizeOfTree--;
							return true;
						}
						cout<<"Hmmm... Something went wrong in the remove function, with only one child.\n";
					}else{
                        cout<<"there should be two children\n";
						//if there are two children you can get the largest value of the left sub tree to replace it. (lab implimentation)
						if(parent->getLeftChild()->getLeftChild() == NULL && parent->getLeftChild()->getRightChild() == NULL && parent != root){
                            cout<<"no grandchildren on the left side\n";
                            //if there is no grandchildren on the left subtree,
                            if(grandParent->getLeftChild() == parent){
                                grandParent->leftChild = parent->getLeftChild();
                                parent->getLeftChild()->rightChild = parent->getRightChild();
                            }else{
                                grandParent->rightChild = parent->getLeftChild();
                                parent->getLeftChild()->rightChild = parent->getRightChild();
                            }
                            sizeOfTree--;
                            delete parent;
                            return true;
                        }
						cout<<"parent: "<<parent->getData()<<endl;
						//Under Construction

						Node* temp = parent->getLeftChild();
						Node* tempParent = parent;
						Node* tempGrandParent=parent;
						while(temp->getRightChild() != NULL){
							tempGrandParent = tempParent;
							tempParent=temp;
							temp=temp->getRightChild();	
						}
						//parent is the node we are replacing
						//temp is the node we are replacing it with
                        cout<<"temp parent value: "<<tempParent->getData()<<endl;
						//if(tempParent->getRightChild() != temp){
							//taking care of tempParent's new right child to replace temp as he goes on to do bigger things *snif*
                            //this produces an error when removing 6 in file 5, easier to detect and fix later than now....
                        Node* backup = root->getRightChild();
                            cout<<"taking care of temp's children\n";
                        cout<<"parent->rightChild: "<<parent->getRightChild()->getData()<<endl;
                        if(tempParent != root)
							tempParent->rightChild = temp->getLeftChild();
                        else{
                            temp->rightChild = root->getRightChild();
                            root = temp;
                            delete parent;
                            sizeOfTree--;
                            return true;
                        }
                        cout<<"1\n";
						//}
						if(grandParent->getRightChild() == parent){
							grandParent->rightChild = temp;
						}else if(grandParent->getLeftChild() == parent){
                            cout<<"replacing left child\n";
                            grandParent->leftChild = temp;
						}else if(grandParent == parent && parent == root) {
                            //this is the case of removing root
                            //parent->getLeftChild();
                            cout<<"2\n";
                            cout<<"parent: "<<parent->getData()<<" temp: "<<temp->getData()<<endl;
                            temp->rightChild = parent->getRightChild();
                            cout<<"temp->rightChild "<<temp->getRightChild()->getData()<<endl;
                            cout<<"2.1\n";
                            cout<<"parent val: "<<parent->getData()<<" right child "<<parent->getRightChild()->getData()<<endl;//" left child "<<parent->getLeftChild()->getData()<<endl;
                            if(parent->getLeftChild() == temp){
                            }else
                                temp->leftChild = parent->getLeftChild();
                            if(temp->getRightChild() == temp->getLeftChild()){//fixing my mistake in line 202
                                cout<<"fixing my mistake from line 202 temp->rightChild is "<<temp->getRightChild()->getData()<<" and now will be "<<backup->getData()<<endl;
                                temp->rightChild = backup;
                            }
                            sizeOfTree--;
                            root = temp;
                            cout<<"root: "<<root->getData()<<" left "<<root->getLeftChild()->getData()<<" right "<<root->getRightChild()->getData()<<endl;
                            delete parent;
                            return true;
                        }else if(grandParent == parent){
                            cout<<"I don't know what is going on, I sincerely hope I never see this\n";
                        }
						if(parent->leftChild == temp)
							temp->leftChild = NULL;	//so temp->left doesn't point to itself
						else
							temp->leftChild = parent->getLeftChild();//shouldn't have lost data, thanks to line 204
						temp->rightChild = parent->getRightChild();

						//^^under construction

						sizeOfTree--;
						delete parent;
						cout<<"temp val: "<<temp->getData()<<endl;
						if(temp->getLeftChild() !=NULL)
							cout<<"temp left child "<<temp->getLeftChild()->getData()<<endl;
						else
							cout<<"temp left child == NULL\n";
						if(temp->getRightChild() != NULL)
							cout<<"temp right child "<<temp->getRightChild()->getData()<<endl;
						else
							cout<<"temp right child == NULL\n";
						cout<<"returning true\n";
						cout<<BSTtoString(this);
						return true;
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
string BST::BSTtoString(BST* bst) {
	queue<NodeInterface*> readQ; // used to read in the levels of the tree, contains Node*
	stringstream nodeReader_ss; // used to store the values of the nodes and the level-order sequence
	int depth = 0; // the depth of a node on the tree

	if (bst->getRootNode() == NULL) {
		return "BST is empty";
	}

	readQ.push(bst->getRootNode()); // push the root node of the tree into the queue
	int x=0;
	while (!readQ.empty()) { // as long as the queue has a remaining node:
		cout<<x++<<endl;
		int i = readQ.size(); // store the number of nodes on this level of the tree
		nodeReader_ss << depth << ":  ";
		for (; i > 0; i--) { // for each node on this level,
			NodeInterface* nextNode = readQ.front(); // store the next node in the queue
			nodeReader_ss << nextNode->getData() << " "; // store the data from the node into the ss
			cout<<nextNode->getData()<<endl;
			if (nextNode->getLeftChild() != NULL) { // if there is a left child, push the left child into the queue
				readQ.push(nextNode->getLeftChild());
			}
			if (nextNode->getRightChild() != NULL) { // if there is a right child, push the left child into the queue
				readQ.push(nextNode->getRightChild());
			}
			readQ.pop(); // pop the node off of the queue, leaving its children in the queue
		}
		nodeReader_ss << "\n"; // push an endl into the ss to distinguish levels
		depth++;
	}
	cout<<"hello!\n";
	return nodeReader_ss.str();
}
void BST::recursiveDelete(Node* N){
	if(N == NULL)
		return;
	recursiveDelete(N->getRightChild());
	recursiveDelete(N->getLeftChild());
	delete N;
}
void BST::clear(){
	//I'm going to put the BST into an array, then iteratively delete the array
	recursiveDelete(root);
	root=NULL;
	
/*
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
	}*/
}
