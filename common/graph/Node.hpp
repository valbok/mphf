/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Mar 2015
 * @copyright Zbigniew Czech, George Havas, Bohdan S. Majewski, VaL Doroshchuk
 * @license GNU GPL v2
 * @package Mphf
 */

#ifndef MPHF_COMMON_NODE
#define MPHF_COMMON_NODE

#include <vector>

namespace NMphf
{

/**
 * Graph's node with possibility to assign a value.
 */
class Node
{
public:

    /**
     * Default constructor
     */
    Node() throw();

    /**
     * Connects or creates an edge with a node by its index.
     *
     * @param Index of a node where this node can be fetched from.
     */
    void connectTo(const unsigned index);

    /**
     * Returns count of connected nodes.
     */
    unsigned getEdgesCount() const;

    /**
     * Returns index of a node by internal edge index.
     *
     * @param Index of an edege.
     */
    unsigned getNodeIndex(const unsigned edgeIndex) const;

    /**
     * Sets value of the node.
     *
     * @param Value of the node.
     */
    void setValue(unsigned value);

    /**
     * Returns stored value.
     */
    unsigned getValue() const;

private:

    /**
     * Prevents copying.
     */
    Node(const Node&);
    Node& operator=(const Node&);

    /**
     * An array of edges. Stores index of nodes
     */
    std::vector<unsigned> mEdges;

    /**
     * Node's value.
     */
    unsigned mValue;
};

} // namespace NMphf

#endif // MPHF_COMMON_NODE