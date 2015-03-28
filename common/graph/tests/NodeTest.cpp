/**
 * @author VaL Doroshchuk
 * @license GNU GPL v2
 */

#include <common/graph/Node.hpp>
#include <gtest/gtest.h>

using namespace NMphf;

TEST(Node, connectTo) 
{
    Node n1;
    Node n2;
    Node n3;
    EXPECT_EQ(0, n1.getEdgesCount());
    EXPECT_EQ(0, n2.getEdgesCount());
    EXPECT_EQ(0, n3.getEdgesCount());

    n1.connectTo(1);
    EXPECT_EQ(1, n1.getEdgesCount());
    EXPECT_EQ(1, n1.getNodeIndex(0));

    n1.connectTo(2);
    EXPECT_EQ(2, n1.getEdgesCount());
    EXPECT_EQ(2, n1.getNodeIndex(1));
}


