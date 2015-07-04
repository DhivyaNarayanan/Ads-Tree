#include"Interfaces04.h"

class BTreeNode : public IBTreeNode
{
	int * keys;				//array of keys
	int max_keys;			// num_keys - max no_ of keys in the node - always 5
	int min_deg_t;			// minimum degree of the node
	IBTreeNode **children;  //array of child pointers
	int no_of_keys;			// no of keys in the node
	int no_of_child;		// no of children in the node
	bool leaf;				// is the node is leaf or not

public:
	BTreeNode(int num_keys, bool leaf1)
	{
		min_deg_t = ((num_keys)+1) / 2;
		max_keys = num_keys;
		leaf = leaf1;
		keys = new int[max_keys];
		children = new IBTreeNode *[max_keys + 1];
		no_of_keys = 0;
		no_of_child = 0;
	}
	~BTreeNode(){}
	int getKey(int index);
	void setKey(int index, int key);
	int getKeySize();
	void setKeySize(int size);
	int getChildSize();
	void setChildSize(int size);
	IBTreeNode * getChild(int index);
	void setChild(int index, IBTreeNode * child);
	bool isLeaf();


};
