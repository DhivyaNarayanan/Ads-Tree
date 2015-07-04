#include"Interfaces04.h"

class AVLTreeNode : public IAVLTreeNode
{
	int key;
	IAVLTreeNode * lc;
	IAVLTreeNode * rc;
	int ht;

public:
	AVLTreeNode() { }
	~AVLTreeNode() { }
	void setLeft(IAVLTreeNode * left);
	void setRight(IAVLTreeNode * right);
	void setKey(int key);
	IAVLTreeNode * getLeft();
	IAVLTreeNode * getRight();
	int getKey();

};