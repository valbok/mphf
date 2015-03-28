/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Mar 2015
 * @copyright Zbigniew Czech, George Havas, Bohdan S. Majewski, VaL Doroshchuk
 * @license GNU GPL v2
 * @package Mphf
 */

#include "Graph.hpp"
#include <vector>
#include <iostream>

namespace NMphf
{

Graph::Graph(const unsigned nodesCount) throw()
    : mNodesCount(nodesCount)
    , mCreatedNodesCount(0)
{
    mNodes = new Node*[nodesCount](); // () means create null pointers.
}

Graph::~Graph()
{
    for (unsigned i = 0; i < mNodesCount; ++i)
    {
        delete mNodes[i];
    }

    delete [] mNodes;
}

unsigned Graph::getNodesCount() const
{
    return mNodesCount;
}

unsigned Graph::getEdgesCount() const
{
    return mEdgesCount;
}

bool Graph::connect(
    const unsigned firstNodeIndex,
    const unsigned secondNodeIndex
    )
{
    if (firstNodeIndex >= mNodesCount ||
        secondNodeIndex >= mNodesCount)
    {
        return false;
    }

    Node* firstNode = mNodes[firstNodeIndex];
    Node* secondNode = mNodes[secondNodeIndex];
    if (firstNode == 0)
    {
        firstNode = new Node;
        mNodes[firstNodeIndex] = firstNode;
        ++mCreatedNodesCount;
    }
    if (secondNode == 0)
    {
        secondNode = new Node;
        mNodes[secondNodeIndex] = secondNode;
        ++mCreatedNodesCount;
    }

    firstNode->connectTo(secondNodeIndex);
    secondNode->connectTo(firstNodeIndex);

    ++mEdgesCount;

    return true;
}

Node* Graph::getNode(const unsigned index)
{
    return mNodes[index];
}

const Node* Graph::getNode(const unsigned index) const
{
    return mNodes[index];
}

bool Graph::isCyclic() const
{
    // If empty graph means it is acyclic.
    if (mCreatedNodesCount == 0)
    {
        return false;
    }

    std::vector<bool> visitedNodes;
    visitedNodes.reserve(getNodesCount());

    // Total deleted leaf nodes.
    unsigned deletedNodesCount = 0;
    for (unsigned i = 0; i < getNodesCount(); ++i)
    {
        if (visitedNodes.size() <= i)
        {
            visitedNodes.push_back(false);
        }
        deleteLeafNodes(i, visitedNodes, deletedNodesCount);
    }

    return mCreatedNodesCount > deletedNodesCount;
}

bool Graph::deleteLeafNodes(
    unsigned index,
    std::vector<bool>& visitedNodes,
    unsigned& deletedNodesCount
    ) const
{
    const Node* node = getNode(index);
    if (node == 0 || visitedNodes.at(index))
    {
        return false;
    }

    visitedNodes[index] = true;

    // Calculates how many related nodes have been removed.
    unsigned deletedEdgesCount = 0;
    for (unsigned i = 0; i < node->getEdgesCount(); ++i)
    {
        unsigned nextNodeIndex = node->getNodeIndex(i);
        while (visitedNodes.size() <= nextNodeIndex)
        {
            visitedNodes.push_back(false);
        }

        if (visitedNodes.at(nextNodeIndex))
        {
            continue;
        }

        const Node* nextNode = getNode(nextNodeIndex);
        if (nextNode == 0 ||
            deleteLeafNodes(nextNodeIndex, visitedNodes, deletedNodesCount))
        {
            ++deletedEdgesCount;
        }
    }

    // If at least one edge left need to remove the current node
    // because it is already a leaf.
    if (deletedEdgesCount + 1 >= node->getEdgesCount())
    {
        ++deletedNodesCount;

        return true;
    }

    return false;
}

void Graph::calculateNodeValues()
{
    std::vector<bool> visitedNodes;
    visitedNodes.reserve(getNodesCount());
    // Each edge will have an unigue id to avoid collisions.
    unsigned edgeId = 0;
    for (unsigned i = 0; i < getNodesCount(); ++i)
    {
        if (visitedNodes.size() <= i)
        {
            visitedNodes.push_back(false);
        }

        Node* node = getNode(i);
        if (node != 0 && !visitedNodes.at(i))
        {
            node->setValue(0);
            traverse(i, visitedNodes, edgeId);
        }
    }
}

void Graph::traverse(
    const unsigned index,
    std::vector<bool>& visitedNodes,
    unsigned& edgeId
    )
{
    visitedNodes[index] = true;

    Node* node = getNode(index);
    if (node == 0)
    {
        return;
    }

    for (unsigned i = 0; i < node->getEdgesCount(); ++i)
    {
        unsigned nextNodeIndex = node->getNodeIndex(i);
        while (visitedNodes.size() <= nextNodeIndex)
        {
            visitedNodes.push_back(false);
        }

        Node* nextNode = getNode(nextNodeIndex);
        if (nextNode == 0 || visitedNodes.at(nextNodeIndex))
        {
            continue;
        }

        nextNode->setValue(edgeId - node->getValue());
        ++edgeId;
        traverse(nextNodeIndex, visitedNodes, edgeId);
    }
}

unsigned Graph::getEdgeId(
    unsigned firstNodeIndex,
    unsigned secondNodeIndex,
    unsigned& result)
{
    Node* firstNode = firstNodeIndex < mNodesCount ? getNode(firstNodeIndex) : 0;
    Node* secondNode = secondNodeIndex < mNodesCount ? getNode(secondNodeIndex) : 0;
    if (firstNode == 0 || secondNode == 0)
    {
        return false;
    }

    result = (firstNode->getValue() + secondNode->getValue()) % mEdgesCount;

    return true;
}

} // namespace NMphf
