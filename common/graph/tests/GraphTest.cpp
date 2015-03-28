/**
 * @author VaL Doroshchuk
 * @license GNU GPL v2
 */

#include <common/graph/Graph.hpp>
#include <gtest/gtest.h>

using namespace NMphf;

TEST(Graph, nodesCount) 
{
    Graph g(10);
    EXPECT_EQ(10, g.getNodesCount());
}

TEST(Graph, addNegativeNode) 
{
    Graph g(1);

    EXPECT_EQ(1, g.getNodesCount());
    EXPECT_EQ(false, g.connect(10, 0));
    EXPECT_EQ(false, g.connect(0, 10));
}

TEST(Graph, connect) 
{
    Graph g(5);

    EXPECT_EQ(true, g.connect(0, 4));
    EXPECT_EQ(true, g.connect(1, 4));
    EXPECT_TRUE(g.getNode(0) != 0);
    EXPECT_TRUE(g.getNode(1) != 0);
    EXPECT_TRUE(g.getNode(2) == 0);
    EXPECT_TRUE(g.getNode(3) == 0);
    EXPECT_TRUE(g.getNode(4) != 0);

    EXPECT_EQ(true, g.connect(0, 2));
    EXPECT_TRUE(g.getNode(0) != 0);
    EXPECT_TRUE(g.getNode(2) != 0);
    EXPECT_TRUE(g.getNode(3) == 0);
}
