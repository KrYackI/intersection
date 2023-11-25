#pragma once

template <class T>
class tree_23
{
public:
    struct Node
    {
        int size = 0;
        T value[3];
        Node* nodes[4] = { nullptr, nullptr, nullptr, nullptr };
        int height = 1;
        Node() {};
        Node(T _val) : size(1) { value[0] = _val; }
        Node(const Node& node)
        {
            size = node.size;
            height = node.height;
            for (int i = 0; i < size; ++i)
                value[i] = node.value[i];
            for (int i = 0; i < size + 1; ++i)
            {
                if (node.nodes[i])
                    nodes[i] = new Node{ *node.nodes[i] };
            }
        }
        Node& operator=(const Node& node)
        {
            if (this == &node)
                return *this;
            for (int i = 0; i < size + 1; ++i)
                delete nodes[i];
            size = node.size;
            height = node.height;
            for (int i = 0; i < size; ++i)
                value[i] = node.value[i];
            for (int i = 0; i < size + 1; ++i)
                if (node.nodes[i])
                    nodes[i] = new Node{ *node.nodes[i] }
                else
                    nodes[i] = nullptr;
            return *this;
        }

        int getHeight(Node* cur)
        {
            return cur == nullptr ? 0 : cur->height;
        }

        void balanse()
        {
            height = (getHeight(nodes[1]) < getHeight(nodes[0]) ? getHeight(nodes[0]) : getHeight(nodes[1]));
            height = 1 + (height < getHeight(nodes[2]) ? getHeight(nodes[2]) : height);
        }

        bool is_leaf() {
            return (nodes[0] == nullptr) && (nodes[1] == nullptr) && (nodes[2] == nullptr);
        }

        ~Node()
        {
            for (int i = 0; i < size + 1; ++i)
                delete nodes[i];
        }
    };

private:
    //t == 2

	Node* root;

    Node* search_rec(Node* cur, int& j, T& k)
    {
        j = 0;
        while (j < cur->size && k > cur->value[j])
            ++j;
        if (j < cur->size && k == cur->value[j])
            return cur;
        if (cur->is_leaf())
            return nullptr;
        return search_rec(cur->nodes[j], j, k);
    }

    Node* getNextInternal(Node* root, int& i, T k)
    {
        Node* cur = root;
        Node* closestRight = nullptr;
        while (cur != nullptr)
        {
            int j = 0;
            while (j < cur->size && k >= cur->value[j])
                ++j;
            if (j < cur->size)
            {
                closestRight = cur;
                i = j;
            }
            cur = cur->nodes[j];
        }
        return closestRight;
    }

    Node* getPrevInternal(Node* root, int& i, T k)
    {
        Node* cur = root;
        Node* closestLeft = nullptr;
        while (cur != nullptr)
        {
            int j = 0;
            while (j < cur->size && k > cur->value[j])
                ++j;
            if (j > 0)
            {
                closestLeft = cur;
                i = j - 1;
            }
            cur = cur->nodes[j];
        }

        return closestLeft;
    }

    void split_child(Node* par, int i, Node* cut)
    {
        Node* t = new Node;
        t->size = 1;
        t->value[0] = cut->value[2];
        if (!cut->is_leaf())
        {
            t->nodes[0] = cut->nodes[2];
            t->nodes[1] = cut->nodes[3];
            cut->nodes[2] = nullptr;
            cut->nodes[3] = nullptr;
        }
        cut->size = 1;
        for (int j = par->size; j >= i; --j)
            par->nodes[j + 1] = par->nodes[j];
        par->nodes[i + 1] = t;
        for (int j = par->size - 1; j >= i - 1; --j)
            par->value[j + 1] = par->value[j];
        par->value[i] = cut->value[1];
        par->size++;
    }

    void incert_notfull(Node* par, T& k)
    {
        int i = par->size - 1;
        if (par->is_leaf())
        {
            while (i >= 0 && k < par->value[i])
            {
                par->value[i + 1] = par->value[i];
                --i;
            }
            par->value[i + 1] = k;
            par->size++;
        }
        else
        {
            while (i >= 0 && k < par->value[i])
                --i;
            ++i;
            incert_notfull(par->nodes[i], k);
            if (par->nodes[i]->size == 3)
                split_child(par, i, par->nodes[i]);
            par->balanse();
        }
    }

    void remove(Node* cur, T& k)
    {
        int j = 0;
        while (j < cur->size && k > cur->value[j])
            ++j;
        if (j < cur->size && k == cur->value[j])
            if (cur->is_leaf())
            {
                for (int i = j; i < cur->size - 1; ++i)
                    cur->value[i] = cur->value[i + 1];
                cur->size--;
                return;
            }
            else
            {
                if (cur->nodes[j]->size == 1)
                    if (cur->nodes[j + 1]->size == 1)
                    {
                        Node* l = cur->nodes[j];
                        Node* r = cur->nodes[j + 1];
                        l->value[1] = cur->value[j];
                        l->value[2] = r->value[0];
                        l->nodes[2] = r->nodes[0];
                        l->nodes[3] = r->nodes[1];
                        r->nodes[0] = r->nodes[1] = nullptr;
                        l->size = 3;
                        delete r;
                        for (int i = j; i < cur->size - 1; ++i)
                            cur->value[i] = cur->value[i + 1];
                        for (int i = j + 1; i < cur->size; ++i)
                            cur->nodes[i] = cur->nodes[i + 1];
                        cur->nodes[cur->size] = nullptr;
                        cur->size--;
                        remove(l, k);
                    }
                    else
                    {
                        int i;
                        Node* r = getNextInternal(cur->nodes[j + 1], i, k);
                        T t = r->value[i];
                        r->value[i] = cur->value[j];
                        cur->value[j] = t;
                        remove(cur->nodes[j + 1], k);
                    }
                else
                {
                    int i;
                    Node* l = getPrevInternal(cur->nodes[j], i, k);
                    T t = l->value[i];
                    l->value[i] = cur->value[j];
                    cur->value[j] = t;
                    remove(cur->nodes[j], k);
                }
            }
        else
        {
            if (cur->is_leaf())
                return;
            if (cur->nodes[j]->size == 1)
            {
                Node* l = (j > 0) ? cur->nodes[j - 1] : nullptr;
                Node* c = cur->nodes[j];
                Node* r = (j < cur->size) ? cur->nodes[j + 1] : nullptr;

                if (l != nullptr && l->size == 2)
                {
                    //for (int i = c->size - 2; i >= 0; --i)
                    //    c->value[i + 1] = c->value[i];
                    c->value[1] = c->value[0];
                    c->value[0] = cur->value[j - 1];
                    cur->value[j - 1] = l->value[l->size - 1];
                    //for (int i = c->size - 1; i >= 0; --i)
                    //    c->nodes[i + 1] = c->nodes[i];
                    c->nodes[2] = c->nodes[1];
                    c->nodes[1] = c->nodes[0];
                    c->nodes[0] = l->nodes[l->size];
                    l->nodes[l->size] = nullptr; 
                    c->size++;
                    l->size--;
                    remove(c, k);
                }
                else if (r != nullptr && r->size == 2)
                {
                    c->value[c->size] = cur->value[j];
                    cur->value[j] = r->value[0];
                    //for (int i = 0; i < r->size - 1; ++i)
                    //    r->value[i] = r->value[i + 1];
                    r->value[0] = r->value[1];
                    c->nodes[c->size + 1] = r->nodes[0];
                    //for (int i = 0; i < r->size; ++i)
                    //    r->nodes[i] = r->nodes[i + 1];
                    r->nodes[0] = r->nodes[1];
                    r->nodes[1] = r->nodes[2];
                    r->nodes[r->size] = nullptr;
                    c->size++;
                    r->size--;
                    remove(c, k);
                }
                else if (l != nullptr && l->size == 1)
                {
                    l->value[1] = cur->value[j - 1];
                    l->value[2] = c->value[0];
                    l->nodes[2] = c->nodes[0];
                    l->nodes[3] = c->nodes[1];
                    c->nodes[0] = c->nodes[1] = nullptr;
                    l->size = 3;
                    delete c;
                    for (int i = j - 1; i < cur->size - 1; ++i)
                        cur->value[i] = cur->value[i + 1];
                    for (int i = j; i < cur->size; ++i)
                        cur->nodes[i] = cur->nodes[i + 1];
                    cur->nodes[cur->size] = nullptr;
                    cur->size--;
                    remove(l, k);
                    --j;
                }
                else if (r != nullptr && r->size == 1)
                {
                    c->value[1] = cur->value[j];
                    c->value[2] = r->value[0];
                    c->nodes[2] = r->nodes[0];
                    c->nodes[3] = r->nodes[1];
                    r->nodes[0] = r->nodes[1] = nullptr;
                    c->size = 3;
                    delete r;
                    for (int i = j; i < cur->size - 1; ++i)
                        cur->value[i] = cur->value[i + 1];
                    for (int i = j + 1; i < cur->size; ++i)
                        cur->nodes[i] = cur->nodes[i + 1];
                    cur->nodes[cur->size] = nullptr;
                    cur->size--;
                    remove(c, k);
                }
            }
            else remove(cur->nodes[j], k);
        }
        if (cur->nodes[j]->size == 3)
            split_child(cur, j, cur->nodes[j]);
        cur->balanse();
    }


public:
    tree_23() {root = nullptr; }
    tree_23(const tree_23& _tree) 
    {
        if (_tree.root)
            root = new Node{ *_tree.root };
    }

    tree_23& operator=(const tree_23& _tree)
    {
        if (this == &_tree)
            return *this;
        delete root;
        root = _tree.root;
        return *this;
    }

    int getHeight()
    {
        return root->height;
    }

    Node* search(int& i, T k)
    {
        return search_rec(root, i, k);
    }

    Node* search(T& k)
    {
        Node* cur = root;
        while (cur != nullptr)
        {
            int j = 0;
            while (j < cur->size && k > cur->value[j])
                ++j;
            if (j < cur->size && k == cur->value[j])
                return cur;
            if (cur->is_leaf())
                return nullptr;
            cur = cur->nodes[j];
        }
    }

    Node* getNext(int& i, T k)
    {
        return getNextInternal(root, i, k);
    }

    Node* getNext(T k)
    {
        int i;
        return getNextInternal(root, i, k);
    }

    T getNextItem(T k)
    {
        int i;
        return getNextInternal(root, i, k)->value[i];
    }

    Node* getPrev(int& i, T k)
    {
        return getPrevInternal(root, i, k);
    }

    Node* getPrev(T k)
    {
        int i;
        return getPrevInternal(root, i, k);
    }

    T getPrevItem(T k)
    {
        int i;
        return getPrevInternal(root, i, k)->value[i];
    }

	void insert(T k) 
    {
        if (root == nullptr)
        {
            root = new Node(k);
            return;
        }
        incert_notfull(root, k);
        if (root->size == 3)
        {
            Node* t = new Node;
            t->nodes[0] = root;
            t->height = 1 + root->height;
            
            split_child(t, 0, root);
            root = t;
        }
	}

    void remove(T k)
    {
        remove(root, k);
        if (root->size == 0)
        {
            Node* t = root;
            root = root->nodes[0];
            t->nodes[0] = nullptr;
            delete t;
        }
    }

    ~tree_23()
    {
        delete root;
    }
};