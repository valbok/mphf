/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Mar 2015
 * @copyright Zbigniew Czech, George Havas, Bohdan S. Majewski, VaL Doroshchuk
 * @license GNU GPL v2
 * @package Mphf
 */

#include "Node.hpp"

namespace NMphf
{

Node::Node() throw() : mValue(0)
{
}

void Node::connectTo(const unsigned index)
{
    mEdges.push_back(index);
}

unsigned Node::getEdgesCount() const
{
    return mEdges.size();
}

unsigned Node::getNodeIndex(const unsigned edgeIndex) const
{
    return mEdges[edgeIndex];
}

void Node::setValue(unsigned value)
{
    mValue = value;
}

unsigned Node::getValue() const
{
    return mValue;
}

} // namespace NMphf
