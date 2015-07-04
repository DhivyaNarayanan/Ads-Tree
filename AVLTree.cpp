#include"AVLTree.h"

std::vector<int>temp_vec;
void AVLTree::insert(int key)
{
	root = insert_key(key, root);
}
void AVLTree::remove(int key)
{
	root = delete_key(key, root);
}
int AVLTree::kthMin(int k)
{
	in_order(root, 0, k);
	/*for (int i = 0; i < temp_vec.size(); i++)
		std::cout << temp_vec[i] << "\t";
	std::cout << "\n\n";*/

	int kmin = temp_vec[k];
	/*for (int i = 0; i <= temp_vec.size(); i++)
	{
		temp_vec.pop_back();
	}*/
	temp_vec.clear();
	return kmin;

	//return 0;
}
IAVLTreeNode * AVLTree::getRoot()
{
	return this->root;
}
IAVLTreeNode * AVLTree::insert_key(int key, IAVLTreeNode* rt)
{
	if (rt == NULL)
	{
		rt = new AVLTreeNode();
		rt->setKey(key);
		rt->setLeft(NULL);
		rt->setRight(NULL);
		ht = getht(rt);
	}

	else if (key < rt->getKey())
	{
		rt->setLeft(insert_key(key, rt->getLeft()));
		if (getht(rt->getLeft()) - getht(rt->getRight()) == 2)
		{
			if (key < rt->getLeft()->getKey())
				rt = SingleRotate_right(rt);
			else
				rt = DoubleRotate_LeftRight(rt);
		}
	}
	else if (key > rt->getKey())
	{
		rt->setRight(insert_key(key, rt->getRight()));
		if (getht(rt->getRight()) - getht(rt->getLeft()) == 2)
		{
			if (key > rt->getRight()->getKey())
				rt = SingleRotate_left(rt);
			else
				rt = DoubleRotate_RightLeft(rt);
		}
	}

	ht = getht(rt);
	return rt;
}
IAVLTreeNode *AVLTree::SingleRotate_left(IAVLTreeNode * k2)
{
	IAVLTreeNode * k1;
	k1 = k2->getRight();
	k2->setRight(k1->getLeft());
	k1->setLeft(k2);

	return k1;

}
IAVLTreeNode * AVLTree::SingleRotate_right(IAVLTreeNode * k2)
{
	IAVLTreeNode * k1;
	k1 = k2->getLeft();
	k2->setLeft(k1->getRight());
	k1->setRight(k2);

	return k1;
}
IAVLTreeNode *AVLTree::DoubleRotate_LeftRight(IAVLTreeNode * k3)
{
	IAVLTreeNode * k2;
	k3->setLeft(SingleRotate_left(k3->getLeft()));
	k2 = SingleRotate_right(k3);

	return k2;

}
IAVLTreeNode * AVLTree::DoubleRotate_RightLeft(IAVLTreeNode* k3)
{
	IAVLTreeNode * k2;
	k3->setRight(SingleRotate_right(k3->getRight()));
	k2 = SingleRotate_left(k3);
	return k2;
}
int AVLTree::getht(IAVLTreeNode * root)
{
	if (root == NULL)
		return 0;
	int h1 = getht(root->getLeft());
	int h2 = getht(root->getRight());
	return max(h1, h2) + 1;
}

int AVLTree::max(int h1, int h2)
{
	int m = h1;
	if (m < h2)
		m = h2;
	return m;
}
IAVLTreeNode * AVLTree::find_min(IAVLTreeNode * rt)
{
	if (rt == NULL)
		return NULL;
	else if (rt->getLeft() == NULL)
		return rt;
	else
		return find_min(rt->getLeft());
}
IAVLTreeNode * AVLTree::delete_key(int key, IAVLTreeNode * rt)
{
	IAVLTreeNode * temp = new AVLTreeNode();

	if (rt == NULL)
		return NULL;
	else if (key < rt->getKey())
		rt->setLeft(delete_key(key, rt->getLeft()));
	else if (key > rt->getKey())
		rt->setRight(delete_key(key, rt->getRight()));
	else if ((rt->getLeft() && rt->getRight()) != 0)
	{
		temp = find_min(rt->getRight());
		rt->setKey(temp->getKey());
		rt->setRight(delete_key(temp->getKey(), rt->getRight()));
	}
	else
	{
		temp = rt;
		if (rt->getLeft() == NULL)
			rt = rt->getRight();
		else if (rt->getRight() == NULL)
			rt = rt->getLeft();
	}
	//free(temp);
	return rt;
}
void AVLTree::in_order(IAVLTreeNode*rt, int i, int k)
{
	if (rt == NULL)
		return;
	else
	{
		in_order(rt->getLeft(), i, k);
		temp_vec.push_back(rt->getKey());
		if (i == k)
			return;
		i++;
		//std::cout << rt->getKey() << "\t";
		in_order(rt->getRight(), i, k);
	}
}