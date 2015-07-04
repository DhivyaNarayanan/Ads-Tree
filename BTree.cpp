#include"BTree.h"
#include<iostream>

void BTree::insert(int key, int num_keys)
{
	if (root == NULL)
	{
		root = new BTreeNode(num_keys, true);
		root->setKey(0, key);
		root->setKeySize(1);
		root->setChildSize(0);
	}
	else
	{
		if (root->getKeySize() == num_keys)
		{
			IBTreeNode *nn = new BTreeNode(num_keys, false);
			nn->setChild(0, root);
			nn->setChildSize(1);
			splitchild(0, root, nn);
			int i = 0;
			if (nn->getKey(0) < key)
				i++;
			insert_nonfull_root(key, nn->getChild(i), num_keys);
			root = nn;
			//root->setChildSize(2);
		}
		else
			insert_nonfull_root(key, root, num_keys);
	}

}
void BTree::remove(int key, int num_keys)
{
	if (root==NULL)
	{
		//std::cout << "Tree is empty\n";
		return;
	}
	removekey(key, root);

	if (root->getKeySize() == 0)
	{
		IBTreeNode* tmp = root;
		if (root->isLeaf())
			root = NULL;
		else
			root = root->getChild(0);

		delete tmp;

	}
	return;
}
int BTree::kthMin(int k)
{
	std::vector<int> temp_vec;
	inorderBTreeTraverse(root, temp_vec);
	return temp_vec[k];
	
}

void BTree::inorderBTreeTraverse(IBTreeNode * curr, std::vector<int>& temp_vec)
{
	int i;
	for (i = 0; i < curr->getKeySize(); i++)
	{
		if (curr->isLeaf() == false)
			inorderBTreeTraverse(curr->getChild(i), temp_vec);
		temp_vec.push_back(curr->getKey(i));
	}
	if (curr->isLeaf() == false)
		inorderBTreeTraverse(curr->getChild(i), temp_vec);
	
}

IBTreeNode * BTree::getRoot()
{
	return this->root;
}

void  BTree::traverse_tree(IBTreeNode* rt)
{
	if (rt != NULL)
	{
		int i;
		for (i = 0; i < rt->getKeySize(); i++)
		{
			if (rt->isLeaf() == false)
			{
				traverse_tree(rt->getChild(i));
			}
			std::cout << " " << rt->getKey(i);
		}
		if (rt->isLeaf() == false)
			traverse_tree(rt->getChild(i));
	}

}

IBTreeNode * BTree::search_key(int key, IBTreeNode * rt)
{
	if (rt != NULL)
	{
		int i = 0;
		while (i < rt->getKeySize() && key > rt->getKey(i))
			i++;
		if (rt->getKey(i) == key)
			return rt;
		if (rt->isLeaf() == true)
			return NULL;
		return search_key(key, rt->getChild(i));
	}
	else
		return NULL;
}

void BTree::insert_nonfull_root(int key, IBTreeNode* rt, int num_keys)
{
	int i = rt->getKeySize() - 1;
	if (rt->isLeaf() == true)
	{
		while (i >= 0 && rt->getKey(i) > key)
		{
			rt->setKey(i + 1, rt->getKey(i));
			i--;
		}
		rt->setKey(i + 1, key);
		rt->setKeySize(rt->getKeySize() + 1);
	}
	else
	{
		while (i >= 0 && rt->getKey(i) > key)
			i--;
		if (rt->getChild(i + 1)->getKeySize() == num_keys)
		{
			splitchild(i + 1, rt->getChild(i + 1), rt);
			if (rt->getKey(i + 1) < key)
				i++;
		}
		insert_nonfull_root(key, rt->getChild(i + 1), num_keys);
	}
}

void BTree::splitchild(int index, IBTreeNode * child_y, IBTreeNode*rt)
{
	int min_deg = 3;
	IBTreeNode * nn = new BTreeNode(5, child_y->isLeaf());
	nn->setKeySize(min_deg - 1);
	for (int j = 0; j < min_deg - 1; j++)
		nn->setKey(j, child_y->getKey(j + min_deg));
	if (child_y->isLeaf() == false)
	{
		for (int j = 0; j < min_deg; j++)
		{
			nn->setChild(j, child_y->getChild(j + min_deg));
			//nn->setChildSize(min_deg);
			//child_y->setChildSize(child_y->getChildSize() - min_deg);
		}
		nn->setChildSize(min_deg);
		child_y->setChildSize(child_y->getChildSize() - min_deg);
		//nn->setChildSize(nn->getChildSize() + 1);
	}
	//nn->setChildSize(nn->getChildSize() + 1);
	child_y->setKeySize(child_y->getKeySize()-(min_deg -1));
	for (int j = rt->getKeySize(); j >= index + 1; j--)
		rt->setChild(j + 1, rt->getChild(j));
	rt->setChild(index + 1, nn);
	rt->setChildSize(rt->getChildSize() + 1);
	for (int j = rt->getKeySize() - 1; j >= index; j--)
	{
		rt->setKey(j + 1, rt->getKey(j));
	}
	rt->setKey(index, child_y->getKey(min_deg - 1));
	rt->setKeySize(rt->getKeySize() + 1);
	child_y->setKeySize(child_y->getKeySize() - 1);

}

int BTree::findkey(int k, IBTreeNode*rt)
{
	int index = 0;
	while (index < rt->getKeySize() && rt->getKey(index) < k)
		++index;
	return index;
}

void BTree::removekey(int key, IBTreeNode*rt)
{
	int index = findkey(key, rt);
	if (index < rt->getKeySize() && rt->getKey(index) == key)
	{
		if (rt->isLeaf())
			removeFromLeaf(index, rt);
		else
			removeFromNonleaf(index, rt);
	}
	else
	{
		if (rt->isLeaf())
			return;
		bool f = ((index == rt->getKeySize()) ? true : false);
		if (rt->getChild(index)->getKeySize() < 3)
			fillnode(index, rt);
		if (f && index > rt->getKeySize())
			removekey(key, rt->getChild(index - 1));
		else
			removekey(key, rt->getChild(index));
	}
	return;
}

void BTree::removeFromLeaf(int index, IBTreeNode*rt)
{
	for (int i = index + 1; i < rt->getKeySize(); ++i)
		rt->setKey(i - 1, rt->getKey(i));

	rt->setKeySize(rt->getKeySize() - 1);
	return;
}

void BTree::removeFromNonleaf(int index, IBTreeNode* rt)
{
	int k = rt->getKey(index);
	if (rt->getChild(index)->getKeySize() >= 3)
	{
		int pre = getPrev(index, rt);
		rt->setKey(index, pre);
		removekey(pre, rt->getChild(index));
	}
	else if (rt->getChild(index + 1)->getKeySize() >= 3)
	{
		int post = getPost(index, rt);
		rt->setKey(index, post);
		removekey(post, rt->getChild(index + 1));
	}
	else
	{
		combine(index, rt);
		removekey(k, rt->getChild(index));
	}
	return;
}

int BTree::getPrev(int index, IBTreeNode* rt)
{
	IBTreeNode * cur = rt->getChild(index);
	while (!cur->isLeaf())
		cur = cur->getChild(cur->getKeySize());
	return cur->getKey(cur->getKeySize() - 1);
}

int BTree::getPost(int index, IBTreeNode*rt)
{
	IBTreeNode * cur = rt->getChild(index + 1);
	while (!cur->isLeaf())
		cur = cur->getChild(0);

	return cur->getKey(0);
}

void BTree::fillnode(int index, IBTreeNode*rt)
{
	if (index != 0 && rt->getChild(index - 1)->getKeySize() >= 3)
		getFromPrev(index, rt);
	else if (index != rt->getKeySize() && rt->getChild(index + 1)->getKeySize() >= 3)
		getFromNext(index, rt);

	else
	{
		if (index != rt->getKeySize())
			combine(index, rt);
		else
			combine(index - 1, rt);
	}
	return;
}

void BTree::getFromPrev(int index, IBTreeNode * rt)
{
	IBTreeNode * ch = rt->getChild(index);
	IBTreeNode * sib = rt->getChild(index - 1);

	for (int i = ch->getKeySize() - 1; i >= 0; --i)
		ch->setKey(i + 1, ch->getKey(i));

	if (!ch->isLeaf())
	{
		for (int i = ch->getKeySize(); i >= 0; --i)
			ch->setChild(i + 1, ch->getChild(i));
	}

	ch->setKey(0, rt->getKey(index - 1));

	if (!sib->isLeaf())
	{
		ch->setChild(0, sib->getChild(sib->getKeySize()));
		ch->setChildSize(ch->getChildSize() + 1);
		sib->setChildSize(sib->getChildSize() - 1);
	}
		

	rt->setKey(index - 1, sib->getKey(sib->getKeySize() - 1));

	ch->setKeySize(ch->getKeySize() + 1);
	sib->setKeySize(sib->getKeySize() - 1);

	return;

}

void BTree::getFromNext(int index, IBTreeNode*rt)
{
	IBTreeNode * ch = rt->getChild(index);
	IBTreeNode * sib = rt->getChild(index + 1);

	ch->setKey(ch->getKeySize(), rt->getKey(index));

	if (!ch->isLeaf())
	{
		ch->setChild(ch->getKeySize() + 1, sib->getChild(0));
		ch->setChildSize(ch->getChildSize() + 1);
		sib->setChildSize(sib->getChildSize() - 1);
	}
		

	rt->setKey(index, sib->getKey(0));

	for (int i = 1; i < sib->getKeySize(); ++i)
		sib->setKey(i - 1, sib->getKey(i));

	if (!sib->isLeaf())
	{
		for (int i = 1; i <= sib->getKeySize(); ++i)
			sib->setChild(i - 1, sib->getChild(i));

		//sib->setChildSize(sib->getChildSize() - 1);
	}

	ch->setKeySize(ch->getKeySize() + 1);
	sib->setKeySize(sib->getKeySize() - 1);

	return;

}

void BTree::combine(int index, IBTreeNode*rt)
{
	IBTreeNode * ch = rt->getChild(index);
	IBTreeNode * sib = rt->getChild(index + 1);

	ch->setKey(2, rt->getKey(index));

	for (int i = 0; i < sib->getKeySize(); ++i)
		ch->setKey(i + 3, sib->getKey(i));

	if (!ch->isLeaf())
	{
		for (int i = 0; i <= sib->getKeySize(); ++i)
		{
			ch->setChild(i + 3, sib->getChild(i));
			ch->setChildSize(ch->getChildSize() + 1);
		}
			

		//ch->setChildSize(ch->getChildSize() + sib->getKeySize());
	}

	for (int i = index + 1; i < rt->getKeySize(); ++i)
		rt->setKey(i - 1, rt->getKey(i));

	for (int i = index + 2; i <= rt->getKeySize(); ++i)
		rt->setChild(i - 1, rt->getChild(i));

	rt->setChildSize(rt->getChildSize() - 1);

	ch->setKeySize(ch->getKeySize() + sib->getKeySize() + 1);
	rt->setKeySize(rt->getKeySize() - 1);
	//rt->setChildSize(rt->getChildSize() - 1);
	sib->setKeySize(0);
	sib->setChildSize(0);
	delete(sib);
	return;

}


