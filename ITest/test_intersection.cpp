#include "line.h"

#include <gtest.h>

TEST(intersection, regular)
{
	line l1(0, 5, 5, 0);
	line l2(5, 5, 0, 0);
	EXPECT_EQ(l1.intersect(l2), true);
}

TEST(intersection, regular_false)
{
	line l1(0, 5, 5, 0);
	line l2(-5, -5, 0, 0);
	EXPECT_EQ(l1.intersect(l2), false);
}

TEST(intersection, shared_point)
{
	line l1(0, 5, 5, 0);
	line l2(0, 0, 0, 5);
	EXPECT_EQ(l1.intersect(l2), true);
}

TEST(intersection, equal_points)
{
	line l1(0, 5, 5, 0);
	line l2(5, 0, 0, 5);
	EXPECT_EQ(l1.intersect(l2), true);
}

TEST(intersection, parallel)
{
	line l1(0, 5, 5, 0);
	line l2(0, 0, 5, -5);
	EXPECT_EQ(l1.intersect(l2), false);
}

TEST(intersection, on_same_line_not_intersecting)
{
	line l1(0, 0, 5, 5);
	line l2(6, 6, 15, 15);
	EXPECT_EQ(l1.intersect(l2), false);
}

TEST(intersection, on_same_line_intersecting)
{
	line l1(0, 0, 5, 5);
	line l2(4, 4, 15, 15);
	EXPECT_EQ(l1.intersect(l2), true);
}

TEST(intersection, one_on_other)
{
	line l1(0, 0, 5, 5);
	line l2(-1, -1, 15, 15);
	EXPECT_EQ(l1.intersect(l2), true);
}