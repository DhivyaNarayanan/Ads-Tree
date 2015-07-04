#include"Interfaces04.h"
#include"AVLTreeNode.h"

class AVLTree : public IAVLTree
{
	IAVLTreeNode * root;
	int ht;
public:
	AVLTree()
	{
		root = NULL;
		ht = 0;
	}
	~AVLTree() { }
	void insert(int key);
	void remove(int key);
	int kthMin(int k);
	IAVLTreeNode * getRoot();
	IAVLTreeNode * insert_key(int key, IAVLTreeNode* rt);
	IAVLTreeNode * SingleRotate_left(IAVLTreeNode * k2);
	IAVLTreeNode * SingleRotate_right(IAVLTreeNode * k2);
	IAVLTreeNode * DoubleRotate_LeftRight(IAVLTreeNode * k3);
	IAVLTreeNode * DoubleRotate_RightLeft(IAVLTreeNode* k3);
	int getht(IAVLTreeNode * root);
	IAVLTreeNode * find_min(IAVLTreeNode * rt);
	IAVLTreeNode * delete_key(int key, IAVLTreeNode * rt);
	void in_order(IAVLTreeNode*rt, int i, int k);
	int max(int h1, int h2);
};