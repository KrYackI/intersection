#pragma once

//template <class T>
//struct Node
//{
//	T value;
//	Node* left = nullptr;
//	Node* right = nullptr;
//	int balance = 0;
//	Node(T _val) : value(_val) {};
//	Node(const Node& _node)
//	{
//		value = _node.value;
//		if (_node.left)
//			left = new Node(*_node.left);
//		if (_node.right)
//			right = new Node(*_node.right);
//		balance = _node.balance;
//	}
//	Node& operator=(const Node& _node)
//	{
//		if (&_node == this)
//			return *this;
//		delete left;
//		delete right;
//		value = _node.value;
//		balance = _node.balance;
//		if (_node.left)
//			left = new Node(*_node.left);
//		else
//			left = nullptr;
//		if (_node.right)
//			right = new Node(*_node.right);
//		else
//			right = nullptr;
//		return *this;
//	}
//
//	~Node()
//	{
//		delete left;
//		delete right;
//	}
//};

template <class T>
class AVLtree
{
public:

	struct Node
	{
		T value;
		Node* left = nullptr;
		Node* right = nullptr;
		int balance = 0;
		Node(T _val) : value(_val) {};
		Node(const Node& _node)
		{
			value = _node.value;
			if (_node.left)
				left = new Node(*_node.left);
			if (_node.right)
				right = new Node(*_node.right);
			balance = _node.balance;
		}
		Node& operator=(const Node& _node)
		{
			if (&_node == this)
				return *this;
			delete left;
			delete right;
			value = _node.value;
			balance = _node.balance;
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

		~Node()
		{
			delete left;
			delete right;
		}
	};

private:
	Node* root;
	Node* right_rot(Node* cur, bool p)
	{
		Node* l = cur->left;
		cur->left = l->right;
		l->right = cur;
		if (p)
		{
			cur->balance = 0;
			l->balance = 0;
		}
		else
		{
			int b = l->balance;
			if (!b)
			{
				cur->balance = -1;
				l->balance = 1;
			}
			else
			{
				cur->balance = 0;
				l->balance = -0;
			}
		}
		return l;
	}
	Node* left_rot(Node* cur, bool p)
	{
		Node* r = cur->right;
		cur->right = r->left;
		r->left = cur;
		if (p)
		{
			cur->balance = 0;
			r->balance = 0;
		}
		else
		{
			int b = r->balance;
			if (!b)
			{
				cur->balance = 1;
				r->balance = -1;
			}
			else
			{
				cur->balance = 0;
				r->balance = -0;
			}
		}
		return r;
	}
	Node* big_right_rot(Node* cur, bool p)
	{
		Node* p1 = cur->left;
		Node* p2 = p1->right;
		p1->right = p2->left;
		p2->left = p1;
		cur->left = p2->right;
		p2->right = cur;

		if (p2->balance == -1) cur->balance = 1;
		else cur->balance = 0;

		if (p2->balance == 1) p1->balance = -1;
		else p1->balance = 0;

		cur = p2;
		if (p) cur->balance = 0;
		else p2->balance = 0;

		return p2;
	}
	Node* big_left_rot(Node* cur, bool p)
	{
		Node* p1 = cur->right;
		Node* p2 = p1->left;
		p1->left = p2->right;
		p2->right = p1;
		cur->right = p2->left;
		p2->left = cur;

		if (p2->balance == 1) cur->balance = -1;
		else cur->balance = 0;

		if (p2->balance == -1) p1->balance = 1;
		else p1->balance = 0;

		cur = p2;
		if (p) cur->balance = 0;
		else p2->balance = 0;

		return p1;
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
				if (h)
					switch (par->balance)
					{
					case 1:
						par->balance = 0;
						h = false;
						break;
					case 0:
						par->balance = -1;
						break;
					case -1:
						if (par->left->balance == -1)
							par = right_rot(par, true);
						else
							par = big_right_rot(par, true);
						h = false;
						break;
					}

			}
			else
			{
				par->right = add(_val, par->right, h);
				if (h)
					switch (par->balance)
					{
					case -1:
						par->balance = 0;
						h = false;
						break;
					case 0:
						par->balance = 1;
						break;
					case 1:
						if (par->right->balance == 1)
							par = left_rot(par, true);
						else
							par = big_left_rot(par, true);
						h = false;
						break;
					}
			}
		return par;
	}

	Node* delThis(Node* cur, T& _val, bool& h)
	{
		if (cur->left != nullptr) cur->left = delThis(cur->left, _val, h);
		else
		{
			_val = cur->value;
			Node* t = cur->right;
			cur->right = nullptr;
			delete cur;
			h = true;
			return t;
		}
		if (h)
			switch (cur->balance)
			{
			case -1:
				cur->balance = 0;
				break;
			case 0:
				cur->balance = 1;
				h = false;
				break;
			case 1:
				if (cur->right->balance == 1)
					cur = left_rot(cur, true);
				else
					cur = big_left_rot(cur, true);
				h = false;
				break;
			}
		return cur;
	}

	Node* del(Node* cur, T& _val, bool& h)
	{
		if (cur == nullptr) return cur;


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
				cur->right = delThis(cur->right, cur->value, h);
				if (h)
					switch (cur->balance)
					{
					case 1:
						cur->balance = 0;
						break;
					case 0:
						cur->balance = -1;
						h = false;
						break;
					case -1:
						if (cur->left->balance == -1)
							cur = right_rot(cur, true);
						else
							cur = big_right_rot(cur, true);
						h = false;
						break;
					}
			}
			return cur;
		}
		if (cur->value > _val)
		{
			cur->left = del(cur->left, _val, h);
			if (h)
				switch (cur->balance)
				{
				case -1:
					cur->balance = 0;
					break;
				case 0:
					cur->balance = 1;
					h = false;
					break;
				case 1:
					if (cur->right->balance == 1)
						cur = left_rot(cur, true);
					else
						cur = big_left_rot(cur, true);
					h = false;
					break;
				}
		}
		if (cur->value < _val)
		{
			cur->right = del(cur->right, _val, h);
			if (h)
				switch (cur->balance)
				{
				case 1:
					cur->balance = 0;
					break;
				case 0:
					cur->balance = -1;
					h = false;
					break;
				case -1:
					if (cur->left->balance == -1)
						cur = right_rot(cur, true);
					else
						cur = big_right_rot(cur, true);
					h = false;
					break;
				}
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