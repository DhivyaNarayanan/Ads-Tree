#include"AVLTreeNode.h"


void AVLTreeNode::setLeft(IAVLTreeNode * left)
{
	this->lc = left;
}
void AVLTreeNode::setRight(IAVLTreeNode * right)
{
	this->rc = right;
}
void AVLTreeNode::setKey(int key)
{
	this->key = key;
}
IAVLTreeNode * AVLTreeNode::getLeft()
{
	return this->lc;
}
IAVLTreeNode * AVLTreeNode::getRight()
{
	return this->rc;
}
int AVLTreeNode::getKey()
{
	return this->key;
}