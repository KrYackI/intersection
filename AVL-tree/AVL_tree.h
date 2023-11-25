#pragma once

template <class T>
class AVLtree
{
public:

	struct Node
	{
		T value;
		Node* left = nullptr;
		Node* right = nullptr;
		int height = 1;
		Node(T _val) : value(_val) {};
		Node(const Node& _node)
		{
			value = _node.value;
			if (_node.left)
				left = new Node(*_node.left);
			if (_node.right)
				right = new Node(*_node.right);
			height = _node.height;
		}
		Node& operator=(const Node& _node)
		{
			if (&_node == this)
				return *this;
			delete left;
			delete right;
			value = _node.value;
			height = _node.height;
			if (_node.left)
				left = new Node(*_node.left);
			else
				left = nullptr;
			if (_node.right)
				right = new Node(*_node.right);
			else
				right = nullptr;
			return *this;
		}

		int getHeight(Node* cur)
		{
			return cur == nullptr ? 0 : cur->height;
		}

		void balanse()
		{
			height = 1 + (getHeight(right) < getHeight(left) ? getHeight(left) : getHeight(right));
		}

		int getBalanse()
		{
			return getHeight(right) - getHeight(left);
		}

		~Node()
		{
			delete left;
			delete right;
		}
	};

private:
	Node* root;
	Node* right_rot(Node* cur)
	{
		Node* l = cur->left;
		cur->left = l->right;
		l->right = cur;
		cur->balanse();
		l->balanse();
		return l;
	}
	Node* left_rot(Node* cur)
	{
		Node* r = cur->right;
		cur->right = r->left;
		r->left = cur;
		cur->balanse();
		r->balanse();
		return r;
	}
	Node* big_right_rot(Node* cur)
	{
		cur->left = left_rot(cur->left);
		return right_rot(cur);
	}
	Node* big_left_rot(Node* cur)
	{
		cur->right = right_rot(cur->right);
		return left_rot(cur);
	}

	Node* getNext(Node* root, T value)
	{
		Node* closestRight = nullptr;
		Node* t = root;
		while (t != nullptr)
		{
			if (t->value > value)
			{
				closestRight = t;
				t = t->left;
			}
			else if (t->value <= value) t = t->right;
		}
		return closestRight;
	}

	Node* add(T& _val, Node* par, bool& h)
	{
		if (par == nullptr)
		{
			h = true;
			return new Node(_val);
		}
		else
			if (_val < par->value)
			{
				par->left = add(_val, par->left, h);
			}
			else if (_val > par->value)
			{
				par->right = add(_val, par->right, h);
			}
			else return par;
		par->balanse();
		int b = par->getBalanse();
		if (b < -1)
		{
			if (_val < par->left->value)
				return right_rot(par);
			else if (_val > par->left->value)
				return big_right_rot(par);
		}
		if (b > 1)
		{
			if (_val < par->right->value)
				return big_left_rot(par);
			else if (_val > par->right->value)
				return left_rot(par);
		}
		return par;
	}

	Node* del(Node* cur, T& _val, bool& h)
	{
		if (cur == nullptr)
		{
			h = false;
			return cur;
		}

		if (cur->value > _val)
			cur->left = del(cur->left, _val, h);

		if (cur->value < _val)
			cur->right = del(cur->right, _val, h);

		if (cur->value == _val)
		{
			Node* t = cur;
			if (t->left == nullptr && t->right == nullptr)
			{
				h = true;
				delete cur;
				return nullptr;
			}
			else if (cur->left == nullptr)
			{
				h = true;
				t = cur->right;
				cur->right = nullptr;
				delete cur;
				return t;
			}
			else if (cur->right == nullptr)
			{
				h = true;
				t = cur->left;
				cur->left = nullptr;
				delete cur;
				return t;
			}
			else
			{
				Node* t = getNext(cur->right, _val);
				cur->value = t->value;
				t->value = _val;
				cur->right = del(cur->right, _val, h);
			}
		}

		if (cur == nullptr)
			return cur;

		cur->balanse();
		int b = cur->getBalanse();
		if (b < -1)
		{
			if (cur->left->getBalanse() <= 0)
				return right_rot(cur);
			else
				return big_right_rot(cur);
		}
		if (b > 1)
		{
			if (cur->right->getBalanse() == -1)
				return big_left_rot(cur);
			else
				return left_rot(cur);
		}
		return cur;
	}

public:
	AVLtree() { root = nullptr; }
	AVLtree(const AVLtree& _tree)
	{
		if (_tree.root)
			root = new Node{ *_tree.root };
	}
	AVLtree& operator=(const AVLtree& _tree)
	{
		if (&_tree == this)
			return *this;
		delete root;
		root = _tree.root;
		return *this;
	}

	int getHeight()
	{
		return root->height;
	}

	void insert(T _val)
	{
		bool h = false;
		root = add(_val, root, h);
	}

	void remove(T _val) {
		bool h = false;
		root = del(root, _val, h);
	}

	Node* search(T value)
	{
		Node* t = root;
		while (t != nullptr)
		{
			if (t->value > value) t = t->left;
			else if (t->value < value) t = t->right;
			else if (t->value == value) return t;
		}
		return nullptr;
	}

	Node* getNext(T value)
	{
		Node* closestRight = nullptr;
		Node* t = root;
		while (t != nullptr)
		{
			if (t->value > value)
			{
				closestRight = t;
				t = t->left;
			}
			else if (t->value <= value) t = t->right;
		}
		return closestRight;
	}

	T getNextItem(T value)
	{
		Node* closestRight = nullptr;
		Node* t = root;
		while (t != nullptr)
		{
			if (t->value > value)
			{
				closestRight = t;
				t = t->left;
			}
			else if (t->value <= value) t = t->right;
		}
		return closestRight->value;
	}

	Node* getPrev(T value)
	{
		Node* closestLeft = nullptr;
		Node* t = root;
		while (t != nullptr)
		{
			if (t->value >= value) t = t->left;
			else if (t->value < value)
			{
				closestLeft = t;
				t = t->right;
			}
		}
		return closestLeft;
	}

	T getPrevItem(T value)
	{
		Node* closestLeft = nullptr;
		Node* t = root;
		while (t != nullptr)
		{
			if (t->value >= value) t = t->left;
			else if (t->value < value)
			{
				closestLeft = t;
				t = t->right;
			}
		}
		return closestLeft->value;
	}

	~AVLtree()
	{
		delete root;
	}
};