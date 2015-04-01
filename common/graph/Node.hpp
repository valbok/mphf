/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Mar 2015
 * @copyright VaL Doroshchuk
 * @license GNU GPL v2
 * @package Mphf
 */

#ifndef MPHF_COMMON_NODE
#define MPHF_COMMON_NODE

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
    ~Node();

    /**
     * Connects or creates an edge with a node by its index.
     *
     * @param Index of a node where this node can be fetched from.
     */
    void connectTo(unsigned index);

    /**
     * Returns count of connected nodes.
     */
    unsigned getEdgesCount() const;

    /**
     * Returns index of a node by internal edge index.
     *
     * @param Index of an edege.
     */
    unsigned getNodeIndex(unsigned edgeIndex) const;

    /**
     * Sets value of the node.
     *
     * @param Value of the node.
     */
    void setValue(int value);

    /**
     * Returns stored value.
     */
    int getValue() const;

private:

    /**
     * Prevents copying.
     */
    Node(const Node&);
    Node& operator=(const Node&);

    /**
     * Resizes array of edges.
     */
    void resize();

    /**
     * An array of edges. Stores ids or indices of connected nodes.
     */
    unsigned* mEdges;
    
    /**
     * Count of stored edges.
     */
    unsigned mEdgesCount;

    /**
     * Node's value.
     */
    unsigned mValue;

    /**
     * Capacity of reserved items in an array.
     */
    unsigned mEdgesCapacity;
};

} // namespace NMphf

#endif // MPHF_COMMON_NODE