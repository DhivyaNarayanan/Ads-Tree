#include"BTreeNode.h"

int BTreeNode::getKey(int index)
{
	return this->keys[index];
}
void BTreeNode::setKey(int index, int key)
{
	this->keys[index] = key;
}
int BTreeNode::getKeySize()
{
	return this->no_of_keys;
}
void BTreeNode::setKeySize(int size)
{
	this->no_of_keys = size;
}
int BTreeNode::getChildSize()
{
	return this->no_of_child;
}
void BTreeNode::setChildSize(int size)
{
	this->no_of_child = size;
}
IBTreeNode * BTreeNode::getChild(int index)
{
	return this->children[index];
}
void BTreeNode::setChild(int index, IBTreeNode * child)
{
	this->children[index] = child;
}
bool BTreeNode::isLeaf()
{
	return this->leaf;
}
