template <class KeyType,class SDType>
struct AVLNode
{
	AVLNode<KeyType,SDType>();
	~AVLNode<KeyType,SDType>();
	KeyType Key;//the key that this node stands for
	SDType SD;//satellite data coresponding to this key
	char BF;//BalanceFactor of this node in the tree
	AVLNode<KeyType,SDType> * Parent;//Parent node of this node and 0 if this node is root of the tree
	AVLNode<KeyType,SDType> * LC;//left child node of this node and 0 if this has not left child
	AVLNode<KeyType,SDType> * RC;//right child node of this node and  0 if this node has not right child
};

template <class KeyType,class SDType>
AVLNode<KeyType,SDType>::AVLNode()
{
	BF = 0;
	Parent = 0;
	LC = 0;
	RC = 0;
}

template <class KeyType,class SDType>
AVLNode<KeyType,SDType>::~AVLNode()
{
	delete LC;
	delete RC;
}

template <class KeyType,class SDType>
class AVL
{
public:
	AVL(){root = 0;};
	~AVL(){delete root;};
	AVLNode<KeyType,SDType> * Search(const KeyType&);
	int insert(const KeyType &,const SDType &);
	int Delete(KeyType&);
protected:
	AVLNode<KeyType,SDType> *root;
};

template <class T>
char compare(const T &x, const T &y);


template <class KeyType,class SDType>
AVLNode<KeyType,SDType> * AVL<KeyType,SDType>::Search(const KeyType &key)
{
	AVLNode<KeyType,SDType> *q = root;
	char c;
	while(q)
	{
		c = compare<KeyType>(key, q->Key);
		if(c == 1)//key > q->key
		{
			q = q->RC;
		}
		else if(c == -1)//key < q->key
		{
			q = q->LC;
		}
		else if (c == 0)//key = q->key
		{
			return q;
		}
	}
	return 0;
}

template <class KeyType , class SDType>
int AVL<KeyType,SDType>::insert(const KeyType & key, const SDType & sd)
{
	AVLNode<KeyType,SDType> *q = new AVLNode<KeyType,SDType>();
	q->Key = key;
	q->SD = sd;
	q->BF = 0;
	q->LC = 0;
	q->RC = 0;
	q->Parent = 0;
	AVLNode<KeyType,SDType> *p;
	p = root;
	char c;
	int icase;
	if (!p)//we have an empty tree 
	{
		//just add the node and finish
		q->Parent = 0;
		root = q;
		icase = 1; 
		return icase;
	}
	while(p)
	{
		c = compare<KeyType>(key,p->Key);
		if (c ==1)
		{
			if(p->RC)
				p = p->RC;
			else
			{
				p->RC = q;
				q->Parent = p;
				break;
			}
		}
		else if (c == -1)
		{
			if(p->LC)
				p = p->LC;
			else
			{
				p->LC = q;
				q->Parent = p;
				break;
			}
		}
		else if (c == 0)
		{
			delete q;
			icase = 0;
			return icase;
		}
	}//end of while
	AVLNode<KeyType,SDType> *r;
	AVLNode<KeyType,SDType>** handle;

	icase = 3;
	while(p)
	{//we check ancestors for unbalance or change in balance factor
		if(root)if(root->Parent) return 99999;
		if(q == p->LC)//the height of left subtree has increased
		{
			if( p->BF == 1)
			{//first case:it doesnt need balance and the height of the subtree does not change 
				//only change in balance factor is needed and the operation will finish
				p->BF = 0;
				icase = 2010;
				break;
			}
			else if (p->BF == 0)
			{//second case : change in balance factor and the height of subtree we must check more ancestors
				p->BF = -1;
				q = p;
				p = p->Parent;
				continue;
			}
			else if (p->BF == -1)
			{//third case : needs balance in two cases and in each case the height of subtree does not change
				//and so the operation will finish
				if (!(p->Parent))
				{
					handle = &root;
				}
				else
				{
					if (p == p->Parent->LC)
					{
						handle = &(p->Parent->LC);
					}
					else if (p == p->Parent->RC)
					{
						handle = &(p->Parent->RC);
					}
					else
					{
						return 9999;
					}
				}
				if (q->BF == -1)
				{//case 3-1
					p->LC = q->RC;
					q->RC = p;
					q->BF = 0;
					p->BF = 0;
					q->Parent = p->Parent;
					p->Parent = q;
					if(p->LC)
						p->LC->Parent = p;
					*handle = q;

					icase = 2031;
					break;
				}
				else if (q->BF == 1)
				{//case 3-2
					r = q->RC;
					p->LC = r->RC;
					q->RC = r->LC;
					r->LC = q;
					r->RC = p;
					r->Parent = p->Parent;
					q->Parent = p->Parent = r;
					if(p->LC)
						p->LC ->Parent = p;
					if(q->RC)
						q->RC->Parent = q;
					if (r->BF ==1)
					{
						p->BF = 0;
						q->BF = -1;
						r->BF = 0;
					}
					else if (r->BF == -1)
					{
						p->BF = 1;
						q->BF  = 0;
						r->BF = 0;
					}
					else if (r->BF ==0)
					{
						p->BF = 0;
						q->BF = 0;
					}
					*handle = r;
					icase = 2032;
					break;
				}
			}//end of third case
		}//end of left subtree height increse
		else if(q == p->RC)//the height of right subtree has increased
		{			
			if( p->BF == -1)
			{//first case:it doesnt need balance and the height of the subtree does not change 
				//only change in balance factor is needed and the operation will finish
				p->BF = 0;
				icase = 2110;
				break;
			}
			else if (p->BF == 0)
			{//second case : change in balance factor and the height of subtree we must check more ancestors
				p->BF = 1;
				q = p;
				p = p->Parent;
				continue;
			}
			else if (p->BF == 1)
			{//third case : needs balance in two cases and in each case the height of subtree does not change
				//and so the operation will finish
				if (!(p->Parent))
				{
					handle = &root;
				}

				else
				{
					if (p == p->Parent->LC)
					{
						handle = &(p->Parent->LC);
					}
					else if (p == p->Parent->RC)
					{
						handle = &(p->Parent->RC);
					}
					else return 9999;
				}
				if (q->BF == 1)
				{//case 3-1
					p->RC = q->LC;
					q->LC = p;
					q->BF = 0;
					p->BF = 0;
					q->Parent = p->Parent;
					p->Parent = q;
					if (p->RC)
						p->RC->Parent = p;
					*handle = q;

					icase = 2131;
					break;
				}//end of case 3-1
				else if (q->BF == -1)
				{//case 3-2
					r = q->LC;
					p->RC = r->LC;
					q->LC = r->RC;
					r->RC = q;
					r->LC = p;
					r->Parent = p->Parent;
					q->Parent = p->Parent = r;
					if (p->RC)
						p->RC ->Parent = p;
					if (q->LC)
						q->LC->Parent = q;
					if (r->BF ==-1)
					{
						p->BF = 0;
						q->BF = 1;
						r->BF = 0;
					}
					else if (r->BF == 1)
					{
						p->BF = -1;
						q->BF  = 0;
						r->BF = 0;
					}
					else if (r->BF ==0)
					{
						p->BF = 0;
						q->BF = 0;
					}
					*handle = r;

					icase = 2132;
					break;
				}//end of case 3-2
			}//end of third case

		}
	}//end of while 
	return icase;
}

template <class KeyType,class SDType>
int AVL<KeyType,SDType>::Delete(KeyType& key)
{
	//find the Node if it exists
	AVLNode<KeyType,SDType> *q = Search(key);
	if(!q)
		return 1;
	AVLNode<KeyType,SDType> *p = q->Parent;
	if (q->LC && q->RC)
	{//find the successor of q and replace its data to data of q 
		AVLNode<KeyType,SDType> *s = q;
		p = q ;
		q = q->RC;
		while(q->LC)
		{
			p = q;
			q = q->LC;
		}
		//assign to data of s node , data of q node 
		//this may need some changes to be efficient 
		//it means that may be just swapping Node pointers is better

		s->Key = q->Key;
		s->SD = q->SD;
	}
	AVLNode<KeyType,SDType> *res = q;
	char c = 0;
	//splice out the node
	if(!p)//if q is the root 
	{
		if (!( q->LC ))
			root = q->RC;
		else
			root = q->LC;
	}
	else
	{
		if (p->RC == q)
		{
			if (!(q->RC))
				p->RC = q->LC;
			else
				p->RC = q->RC;
			c = 1;
		}
		else if (p->LC == q)
		{
			if (!(q->RC))
				p->LC = q->LC;
			else
				p->LC = q->RC;
			c = -1;
		}
	}//end of else
	res->LC = 0;
	res->RC = 0;
	delete res;
	//end of splice out the node 
	//in this point q points at the subtree that its height is decreased and p to current node 
	//we go up through the ancestors on p in a while loop and we got these as loop  constant at the end of loop also
	AVLNode<KeyType,SDType> ** handle;
	AVLNode<KeyType,SDType> *r, *t;
	while (p)
	{//we go up until we reach a node that reserves its height after changes 
		if(c == -1)
		{//height of left subtree has decreased 
			if (p->BF == -1)
			{//first case : the node remains balnced but the height of this 
				//subtree decreased by one . balance factor needs to change, then we go up further
				p->BF = 0;
				q = p;
				p = p->Parent;
				if (p)
				{
					if (q  == p->LC)
						c =-1;
					else if (q == p->RC)
						c = 1;
				}
				continue;
			}
			else if (p->BF == 0)
			{//second case : the node remains balanced and its height remains unchanged and 
				//only a change in balnce factor is needed. then we finish the operation
				p->BF = 1;
				return 0;
			}
			else if (p->BF == 1)
			{//third case: the node is unbalanced and we need change in subtree
				if (!(p->Parent))
					handle = &root;
				else 
				{
					if(p == p->Parent->LC)
						handle = &(p->Parent->LC);
					else if ( p == p->Parent ->RC)
						handle = &(p->Parent->RC);
				}
				r = p->RC;
				if (r->BF == 0)
				{//case 3-1 : after making changes the height of the subtree does not change
					//and so we finsish the operation after making this subtree avl.
					p->RC = r->LC ;
					r->LC = p;
					p->BF = -1;
					*handle = r;
					r->Parent = p->Parent;
					p->Parent = r;
					if(p->RC)
						p->RC->Parent = p;
					return 0;

				}
				else if (r->BF  == 1)
				{//case 3-2 : the  height of this subtree decreases by one and after making changes we go up further
					p->RC = r->LC ;
					r->LC = p;
					p->BF = 0;
					r->BF = 0;
					*handle = r;
					r->Parent = p->Parent ;
					p->Parent = r;
					if (p->RC)
						p->RC->Parent = p;
					q = r ;
					p = q->Parent;
					if (p)
					{
						if (q  == p->LC)
							c =-1;
						else if (q == p->RC)
							c = 1;
					}
					continue;
				}//end of case 3-2
				else if (r->BF == -1)
				{//case 3-3: height of this subtree after making changes will decrese y one and so 
					//we must go up further
					t = r->LC ;
					r->LC = t->RC;
					p->RC = t->LC;
					t->LC = p;
					t->RC = r;
					if (t->BF == -1)
					{
						p->BF = -1;
						r->BF = 0;
						t->BF = 0;
					}
					else if (t->BF == -1)
					{
						p->BF = 0;
						r->BF = 1;
						t->BF = 0;
					}
					else if (t->BF == 0)
					{
						p->BF =0;
						r->BF = 0;
					}
					t->Parent = p->Parent;
					p->Parent = t;
					r->Parent = t;
					if (p->RC)
						p->RC->Parent = p;
					if (r->LC)
						r->LC->Parent = r;
					q = t;
					p = q->Parent;
					if (p)
					{
						if (q  == p->LC)
							c =-1;
						else if (q == p->RC)
							c = 1;
					}
					continue;
				}//end of case 3-3
			}

		}
		else if (c == 1)//symmetric to previous case
		{//height of right subtree has decreased 
			if (p->BF == 1)
			{//first case : the node remains balnced but the height of this 
				//subtree decreased by one . balance factor needs to change, then we go up further
				p->BF = 0;
				q = p;
				p = p->Parent;
				if (p)
				{
					if (q  == p->LC)
						c =-1;
					else if (q == p->RC)
						c = 1;
				}
				continue;
			}
			else if (p->BF == 0)
			{//second case : the node remains balanced and its height remains unchanged and 
				//only a change in balnce factor is needed. then we finish the operation
				p->BF = -1;
				return 0;
			}
			else if (p->BF == -1)
			{//third case: the node is unbalanced and we need change in subtree
				if (!(p->Parent))
					handle = &root;
				else 
				{
					if(p == p->Parent->LC)
						handle = &(p->Parent->LC);
					else if ( p == p->Parent ->RC)
						handle = &(p->Parent->RC);
				}
				r = p->LC;
				if (r->BF == 0)
				{//case 3-1 : after making changes the height of the subtree does not change
					//and so we finsish the operation after making this subtree avl.
					p->LC = r->RC ;
					r->RC = p;
					p->BF = 1;
					r->BF = -1;
					*handle = r;
					r->Parent = p->Parent;
					p->Parent = r;
					if(p->RC)
						p->RC->Parent = p;
					return 0;
				}//end of case 3-1
				else if (r->BF  == 1)
				{//case 3-2 : the  height of this subtree decreases by one and after making changes we go up further
					p->LC = r->RC ;
					r->RC = p;
					p->BF = 0;
					r->BF = 0;
					*handle = r;
					r->Parent = p->Parent ;
					p->Parent = r;
					if (p->LC)
						p->LC->Parent = p;
					q = r ;
					p = q->Parent;
					if (p)
					{
						if (q  == p->LC)
							c =-1;
						else if (q == p->RC)
							c = 1;
					}
					continue;
				}//end of case 3-2
				else if (r->BF == 1)
				{//case 3-3: height of this subtree after making changes will decrese y one and so 
					//we must go up further
					t = r->RC ;
					r->RC = t->LC;
					p->LC = t->RC;
					t->LC = p;
					t->RC = r;
					if (t->BF == -1)
					{
						p->BF = 1;
						r->BF = 0;
						t->BF = 0;
					}
					else if (t->BF == -1)
					{
						p->BF = 0;
						r->BF = -1;
						t->BF = 0;
					}
					else if (t->BF == 0)
					{
						p->BF =0;
						r->BF = 0;
					}
					t->Parent = p->Parent;
					p->Parent = t;
					r->Parent = t;
					if (p->LC)
						p->LC->Parent = p;
					if (r->RC)
						r->RC->Parent = r;
					q = t;
					p = q->Parent;
					if (p)
					{
						if (q  == p->LC)
							c =-1;
						else if (q == p->RC)
							c = 1;
					}
					continue;
				}//end of case 3-3
			}//end of third case
		}//end of right subtree height decrease
	}
	return 0;
}