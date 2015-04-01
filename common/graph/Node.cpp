/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Mar 2015
 * @copyright VaL Doroshchuk
 * @license GNU GPL v2
 * @package Mphf
 */

#include "Node.hpp"
#include <algorithm>

namespace NMphf
{

Node::Node() throw()
    : mEdges(0)
    , mEdgesCount(0)
    , mValue(0)
    , mEdgesCapacity(6)
{
    mEdges = new unsigned[mEdgesCapacity];
}

void Node::resize()
{
    if (mEdgesCount < mEdgesCapacity)
    {
        return;
    }

    mEdgesCapacity *= mEdgesCapacity;
    unsigned* newEdges = new unsigned[mEdgesCapacity];
    if (newEdges != 0)
    {
        std::copy(mEdges, mEdges + mEdgesCount, newEdges);
        delete [] mEdges;
        mEdges = newEdges;
    }
}

Node::~Node()
{
    delete [] mEdges;
}

void Node::connectTo(unsigned index)
{
    resize();

    mEdges[mEdgesCount] = index;
    ++mEdgesCount;
}

unsigned Node::getEdgesCount() const
{
    return mEdgesCount;
}

unsigned Node::getNodeIndex(unsigned edgeIndex) const
{
    return mEdges[edgeIndex];
}

void Node::setValue(int value)
{
    mValue = value;
}

int Node::getValue() const
{
    return mValue;
}

} // namespace NMphf
