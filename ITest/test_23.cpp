#include "2,3-tree.h"

#include <gtest.h>


//				p
//		cg				tx
//a	de	 jk		   q    u	y	

tree_23<char> createTestTreeWOheight()
{
	tree_23<char> t;
	int i;
	t.insert('p');
	tree_23<char>::Node* k = t.search(i, 'p');
	tree_23<char>::Node* n = new tree_23<char>::Node;
	n->size = 2;
	n->value[0] = 'c';
	n->value[1] = 'g';
	k->nodes[0] = n;
	n = new tree_23<char>::Node;
	n->size = 1;
	n->value[0] = 'a';
	k->nodes[0]->nodes[0] = n;
	n = new tree_23<char>::Node;
	n->size = 2;
	n->value[0] = 'd';
	n->value[1] = 'e';
	k->nodes[0]->nodes[1] = n;
	n = new tree_23<char>::Node;
	n->size = 2;
	n->value[0] = 'j';
	n->value[1] = 'k';
	k->nodes[0]->nodes[2] = n;
	n = new tree_23<char>::Node;
	n->size = 2;
	n->value[0] = 't';
	n->value[1] = 'x';
	k->nodes[1] = n;
	n = new tree_23<char>::Node;
	n->size = 1;
	n->value[0] = 'q';
	k->nodes[1]->nodes[0] = n;
	n = new tree_23<char>::Node;
	n->size = 1;
	n->value[0] = 'u';
	k->nodes[1]->nodes[1] = n;
	n = new tree_23<char>::Node;
	n->size = 1;
	n->value[0] = 'y';
	n->value[1] = 'z';
	k->nodes[1]->nodes[2] = n;
	return t;
}

TEST(tree_23, can_create)
{
  ASSERT_NO_THROW(tree_23<int> v);
}

TEST(tree_23, search)
{
	tree_23<int> t;
	int i;
	t.insert(5);
	
	ASSERT_NO_THROW(tree_23<int>::Node * k = t.search(i, 5));
}

TEST(tree_23, search_p)
{
	tree_23<char> t;
	int i;
	t.insert('p');
	tree_23<char>::Node* k = t.search(i, 'p');
	EXPECT_NE(k, nullptr);
}

TEST(tree_23, remove_2a)
{
	tree_23<char> t = createTestTreeWOheight();
	ASSERT_NO_THROW(t.remove('d'));
}

TEST(tree_23, remove_2b)
{
	tree_23<char> t = createTestTreeWOheight();
	ASSERT_NO_THROW(t.remove('c'));
}

TEST(tree_23, remove_2c)
{
	tree_23<char> t = createTestTreeWOheight();
	ASSERT_NO_THROW(t.remove('x'));
}

TEST(tree_23, remove_3)
{
	tree_23<char> t = createTestTreeWOheight();
	ASSERT_NO_THROW(t.remove('p'));
}

TEST(tree_23, remove_3a)
{
	tree_23<char> t = createTestTreeWOheight();
	ASSERT_NO_THROW(t.remove('a'));
}

TEST(tree_23, remove_3b)
{
	tree_23<char> t = createTestTreeWOheight();
	ASSERT_NO_THROW(t.remove('u'));
}

TEST(tree_23, insert)
{
	tree_23<int> t;
	ASSERT_NO_THROW(t.insert(404));
}

TEST(tree_23, insert_split)
{
	tree_23<int> t;
	int i;
	t.insert(1);
	t.insert(2);
	t.insert(3);
	EXPECT_EQ(t.search(i, 2)->nodes[0], t.search(i, 1));
}

TEST(tree_23, getPrev)
{
	tree_23<char> t = createTestTreeWOheight();
	int i;
	tree_23<char>::Node* m = t.getPrev(i, 'h');
	EXPECT_EQ(m->value[i], 'g');
}

TEST(tree_23, getPrevEQ)
{
	tree_23<char> t = createTestTreeWOheight();
	int i;
	tree_23<char>::Node* m = t.getPrev(i, 'g');
	EXPECT_NE(m->value[i], 'g');
}

TEST(tree_23, getPrevNull)
{
	tree_23<char> t = createTestTreeWOheight();
	int i;
	tree_23<char>::Node* m = t.getPrev(i, 'a');
	EXPECT_EQ(m, nullptr);
}

TEST(tree_23, getNext)
{
	tree_23<char> t = createTestTreeWOheight();
	int i;
	tree_23<char>::Node* m = t.getNext(i, 'g');
	EXPECT_EQ(m->value[i], 'j');
}

TEST(tree_23, getNextEQ)
{
	tree_23<char> t = createTestTreeWOheight();
	int i;
	tree_23<char>::Node* m = t.getNext(i, 'g');
	EXPECT_NE(m->value[i], 'g');
}

TEST(tree_23, getNextNull)
{
	tree_23<char> t = createTestTreeWOheight();
	int i;
	tree_23<char>::Node* m = t.getNext(i, 'z');
	EXPECT_EQ(m, nullptr);
}

TEST(tree_23, height)
{
	tree_23<int> t;
	for (int i = 0; i < 100; i++)
		t.insert(i);
	EXPECT_LE(t.getHeight(), 7);
}