#pragma once
#include <iostream>

//template <class T>
//struct Node
//{
//    int size = 0;
//    T value[3];
//    Node* nodes[4] = { nullptr, nullptr, nullptr, nullptr };
//
//    Node() {};
//    Node(T _val) : size(1) { value[0] = _val; }
//    Node(const Node& node)
//    {
//        for (int i = 0; i < size; ++i)
//            value[i] = node.value[i];
//        for (int i = 0; i < size + 1; ++i)
//            nodes[i] = node.nodes[i];
//    }
//    Node& operator=(const Node& node)
//    {
//        if (this == &node)
//            return *this;
//        for (int i = 0; i < size + 1; ++i)
//            delete nodes[i];
//        for (int i = 0; i < node.size + 1; ++i)
//            if (node.nodes[i])
//                nodes[i] = node.nodes[i];
//            else
//                nodes[i] = nullptr;
//        return *this;
//    }
//
//    bool is_leaf() {
//        return (nodes[0] == nullptr) && (nodes[1] == nullptr) && (nodes[2] == nullptr);
//    }
//
//    ~Node()
//    {
//        for (int i = 0; i < size + 1; ++i)
//            delete nodes[i];
//    }
//};

template <class T>
class tree_23
{
public:
    struct Node
    {
        int size = 0;
        T value[3];
        Node* nodes[4] = { nullptr, nullptr, nullptr, nullptr };

        Node() {};
        Node(T _val) : size(1) { value[0] = _val; }
        Node(const Node& node)
        {
            size = node.size;
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
            for (int i = 0; i < size; ++i)
                value[i] = node.value[i];
            for (int i = 0; i < size + 1; ++i)
                if (node.nodes[i])
                    nodes[i] = new Node{ *node.nodes[i] };
                else
                    nodes[i] = nullptr;
            return *this;
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
            //if (par->nodes[i]->size == 3)
            //{
            //    split_child(par, i, par->nodes[i]);
            //    if (k > par->value[i])
            //        ++i;
            //}
            incert_notfull(par->nodes[i], k);
            if (par->nodes[i]->size == 3)
                split_child(par, i, par->nodes[i]);
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
                        Node* r = getNext(i, k);
                        T t = r->value[i];
                        r->value[i] = cur->value[j];
                        cur->value[j] = t;
                        remove(r, k);
                    }
                else
                {
                    int i;
                    Node* l = getPrev(i, k);
                    T t = l->value[i];
                    l->value[i] = cur->value[j];
                    cur->value[j] = t;
                    remove(l, k);
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
    }


public:
    tree_23() {root = new Node; }
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

    T getNextItem(T k)
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
            }
            cur = cur->nodes[j];
        }
        return (closestRight->value[0] == k) ? closestRight->value[1]: closestRight->value[0];
    }

    Node* getPrev(int& i, T k)
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

    Node* getPrev(T k)
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
            }
            cur = cur->nodes[j];
        }

        return closestLeft;
    }

    T getPrevItem(T k)
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
            }
            cur = cur->nodes[j];
        }

        return (closestLeft->value[1] == k) ? closestLeft->value[0]: closestLeft->value[1];
    }

	void insert(T k) 
    {
        incert_notfull(root, k);
        if (root->size == 3)
        {
            Node* t = new Node;
            t->nodes[0] = root;
            
            
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

    void printt(int i)
    {
        for(int j = 0; j < i; ++j)
            std::cout << '\t';
    }

    void printr(Node* root, int i)
    {
        if (root != nullptr)
        {
            printt(i);
            for (int j = 0; j < root->size; ++j)
            {
                std::cout << root->value[j] << ' ';
            }
            std::cout << '\n';
            if (!root->is_leaf())
                for (int j = 0; j <= root->size; ++j)
                {
                    printr(root->nodes[j], i+1);
                }
        }
    }

    void print()
    {
        printr(root, 0);
    }

    ~tree_23()
    {
        delete root;
    }
};