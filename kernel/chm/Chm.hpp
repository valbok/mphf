/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Mar 2015
 * @copyright Zbigniew Czech, George Havas, Bohdan S. Majewski, VaL Doroshchuk
 * @license GNU GPL v2
 * @package Mphf
 */

#ifndef MPHF_CHM
#define MPHF_CHM

#include <common/graph/Graph.hpp>

namespace NMphf
{

/**
 * An optimal algorithm for generating
 * minimal perfect hash functions based on graphs.
 *
 * The algorithm is probabilistic, involving generation of random graphs.
 * It uses expected linear time and requires a linear number of words
 * to represent the hash function, and thus is optimal up to constant factors.
 * It runs very fast in practice.
 */
class Chm
{
public:

    /**
     * @param Constant factor of hash function's size.
     *        Defines how many graph's nodes need to be created.
     */
    explicit Chm(double sizeFactor = 2.09) throw();
    ~Chm();

    /**
     * Generates hash functions.
     *
     * @param An array of keys.
     * @param Length of the array.
     * @return true in case of success.
     */
    bool generate(const char* keys[], unsigned len);

    /**
     * Queries the functions to find an unique identifier by a key.
     *
     * @param Key to search.
     * @param[out] Buffer for the result.
     * @return true In case of success.
     */
    bool search(const char* key, unsigned& result) const;

private:

    /**
     * Resets state of the object.
     *
     * @param New length of submitted array.
     * @return true In case of success.
     */
    bool reset(unsigned len);

    /**
     * Returns indices of nodes in a graph by a key.
     *
     * @param Requested key.
     * @param[out] Index of first node. To make a connection from this node.
     * @param[out] Index of second node. To make a connection to this node.
     */
    void getNodeIndices(
        const char* key,
        unsigned& firstNodeIndex,
        unsigned& secondNodeIndex) const;

    /**
     * Defines size factor of nodes. Must not be less than 2.0.
     */
    double mNodesCountFactor;

    /**
     * Random gprah.
     */
    Graph* mGraph;

    /**
     * Seeds for hash functions that used to calculate indices of nodes.
     */
    unsigned mHashSeeds[2];
};

} // namespace NMphf

#endif // MPHF_CHM