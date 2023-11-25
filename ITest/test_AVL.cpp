#include "AVL_tree.h"

#include <gtest.h>

//TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
//{
//  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
//}

AVLtree<int> createTestTree()
{
	AVLtree<int> t;
	int i;
	t.insert(1);
	t.insert(2);
	t.insert(3);
	t.insert(4);
	t.insert(5);
	t.insert(6);
	t.insert(7);
	t.insert(8);
	t.insert(9);
	t.insert(10);
	t.insert(11);
	t.insert(12);
	t.insert(13);
	t.insert(14);
	t.insert(15);
	t.insert(16);
	t.insert(17);
	t.insert(18);
	t.insert(19);
	t.insert(20);
	t.insert(21);
	t.insert(22);
	t.insert(23);
	t.insert(24);
	t.insert(25);
	t.insert(26);
	t.insert(27);
	t.insert(28);
	t.insert(29);
	t.insert(30);
	t.insert(31);

	return t;
}

TEST(AVLtree, insert_brr)
{
	AVLtree<int> t;
	t.insert(8);
	t.insert(4);
	t.insert(10);
	t.insert(2);
	t.insert(6);
	t.insert(7);
	ASSERT_NO_THROW(t.insert(3));
}

TEST(AVLtree, insert_blr)
{
	AVLtree<int> t;
	t.insert(8);
	t.insert(12);
	t.insert(4);
	t.insert(15);
	t.insert(10);
	t.insert(9);
	ASSERT_NO_THROW(t.insert(14));
}

TEST(AVLtree, remove_1)
{
	AVLtree<int> t = createTestTree();
	ASSERT_NO_THROW(t.remove(16));
}

TEST(AVLtree, remove_2)
{
	AVLtree<int> t = createTestTree();
	t.remove(6);
	t.remove(5);
	ASSERT_NO_THROW(t.remove(7));
}

TEST(AVLtree, remove_3)
{
	AVLtree<int> t = createTestTree();
	t.remove(6);
	t.remove(5);
	ASSERT_NO_THROW(t.remove(7));
}

TEST(AVLtree, remove_4)
{
	AVLtree<int> t = createTestTree();
	t.remove(1);
	t.remove(2);
	ASSERT_NO_THROW(t.remove(3));
}

TEST(AVLtree, remove_5)
{
	AVLtree<int> t = createTestTree();
	t.insert(0);
	t.remove(7);
	ASSERT_NO_THROW(t.remove(4));
}

TEST(AVLtree, remove_6)
{
	AVLtree<int> t = createTestTree();
	t.remove(17);
	t.remove(18);
	t.remove(22);
	t.remove(21);
	t.remove(19);
	ASSERT_NO_THROW(t.remove(16));
}

//TEST(AVLtree, remove_2a)
//{
//	AVLtree<int> t = createTestTree();
//	ASSERT_NO_THROW(t.remove(8));
//}