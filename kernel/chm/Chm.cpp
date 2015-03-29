/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Mar 2015
 * @copyright Zbigniew Czech, George Havas, Bohdan S. Majewski, VaL Doroshchuk
 * @license GNU GPL v2
 * @package Mphf
 */

#include "Chm.hpp"
#include <common/hashes/jenkins.hpp>
#include <math.h> // ceil()
#include <cstring> // strlen()
#include <cstdlib> // rand()

namespace NMphf
{

Chm::Chm(double sizeFactor) throw()
    : mNodesCountFactor(sizeFactor)
    , mGraph(0)
{
    mHashSeeds[0] = mHashSeeds[1] = 0;
}

Chm::~Chm()
{
    delete mGraph;
}

bool Chm::reset(unsigned len)
{
    if (mNodesCountFactor < 2)
    {
        mNodesCountFactor = 2.09;
    }

    delete mGraph;
    mGraph = new Graph(ceil(mNodesCountFactor * len));

    return mGraph != 0;
}

void Chm::getNodeIndices(
    const char* key,
    unsigned& firstNodeIndex,
    unsigned& secondNodeIndex) const
{
    unsigned len = strlen(key);
    firstNodeIndex = NHash::jenkins(mHashSeeds[0], key, len) % mGraph->getNodesCount();
    secondNodeIndex = NHash::jenkins(mHashSeeds[1], key, len) % mGraph->getNodesCount();

    if (firstNodeIndex == secondNodeIndex &&
        ++secondNodeIndex >= mGraph->getNodesCount())
    {
        secondNodeIndex = 0;
    }
}

bool Chm::generate(const char* keys[], unsigned len)
{
    bool result = false;
    for (unsigned attempts = 0; !result && reset(len) && attempts < 20; ++attempts)
    {
        mHashSeeds[0] = rand() % mGraph->getNodesCount();
        mHashSeeds[1] = rand() % mGraph->getNodesCount();
        for (unsigned i = 0; i < len; ++i)
        {
            unsigned firstNodeIndex, secondNodeIndex;
            getNodeIndices(keys[i], firstNodeIndex, secondNodeIndex);
            mGraph->connect(firstNodeIndex, secondNodeIndex);
        }

        result = !mGraph->isCyclic();
    }

    if (result)
    {
        mGraph->calculateNodeValues();
    }

    return result;
}

bool Chm::search(const char* key, unsigned& result) const
{
    unsigned firstNodeIndex, secondNodeIndex;
    getNodeIndices(key, firstNodeIndex, secondNodeIndex);

    return mGraph->getEdgeId(firstNodeIndex, secondNodeIndex, result);
}

} // namespace NMphf
