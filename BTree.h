#include"Interfaces04.h"
#include"BTreeNode.h"

class BTree:public IBTree
{
	IBTreeNode * root;
	//int min_deg;

public:
	BTree()
	{
		root = NULL;
	}
	~BTree(){}
	void insert(int key, int num_keys);
	void remove(int key, int num_keys);
	int kthMin(int k);
	IBTreeNode * getRoot();
	void traverse_tree(IBTreeNode* root);
	void insert_nonfull_root(int key, IBTreeNode* rt, int num_keys);
	void splitchild(int index, IBTreeNode * child_y, IBTreeNode*rt);
	IBTreeNode * search_key(int key, IBTreeNode*root);
	int findkey(int k, IBTreeNode*rt);
	void removekey(int key, IBTreeNode * rt);
	void removeFromLeaf(int index, IBTreeNode*rt);
	void removeFromNonleaf(int index, IBTreeNode*rt);
	void fillnode(int index, IBTreeNode*rt);
	int getPrev(int index, IBTreeNode*rt);
	int getPost(int index, IBTreeNode* rt);
	void getFromPrev(int index, IBTreeNode*rt);
	void getFromNext(int index, IBTreeNode*rt);
	void combine(int index, IBTreeNode*rt);
	void inorderBTreeTraverse(IBTreeNode * curr, std::vector<int>& temp_vec);

};