/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Mar 2015
 * @copyright VaL Doroshchuk
 * @license GNU GPL v2
 * @package Mphf
 */

#ifndef MPHF_COMMON_GRAPH
#define MPHF_COMMON_GRAPH

#include "Node.hpp"

namespace NMphf
{

/**
 * Graph implementation with fixed size of nodes.
 */
class Graph
{
public:

    /**
     * Default constructor.
     * @param Fixed size of current graph.
     */
    Graph(unsigned nodesCount) throw();
    ~Graph();

    /**
     * Connects nodes by their indecies.
     *
     * @param Index of first node.
     * @param Index of second node.
     * @return false In case of an error.
     */
    bool connect(unsigned firstNodeIndex, unsigned secondNodeIndex);

    /**
     * Returns provided total nodes count.
     */
    unsigned getNodesCount() const;

    /**
     * Returns submitted edges count.
     */
    unsigned getEdgesCount() const;

    /**
     * Returns stored node by index.
     *
     * @param Index of requested node.
     * @see getNodesCount() to check how many nodes stored.
     */
    Node* getNode(unsigned index);

    /**
     * @copydoc getNode()
     */
    const Node* getNode(unsigned index) const;

    /**
     * Returns true if current graph is cyclic.
     */
    bool isCyclic() const;

    /**
     * Traverses the graph and calculates values of the nodes
     * to provide an ability to translate keys to unique ids.
     */
    void calculateNodeValues();

    /**
     * Returns unique edge id between node
     * from \a firstNodeIndex and \a secondNodeIndex.
     *
     * @param Index of a first node.
     * @param Index of a second node.
     * @return false In case of errors.
     */
    bool getEdgeId(
        unsigned firstNodeIndex,
        unsigned secondNodeIndex,
        unsigned& result
        );

private:

    /**
     * Prevents copying.
     */
    Graph(const Graph&);
    Graph& operator=(const Graph&);

    /**
     * The size of graph. Total count of requested nodes.
     */
    unsigned mNodesCount;

    /**
     * Count of instantiated nodes.
     */
    unsigned mCreatedNodesCount;

    /**
     * Count of submitted edges.
     */
    unsigned mEdgesCount;

    /**
     * Array of pointers to nodes.
     */
    Node** mNodes;

    /**
     * Traverses the graph and assignes a value to each node.
     *
     * @param Index of a node.
     * @param Checks which node has been visited.
     * @param Unique edge id.
     */
    void traverse(unsigned index, std::vector<bool>& visitedNodes, unsigned& edgeId);

    /**
     * To check for cycles in graph tries to delete a node with degree 1.
     *
     * @param Index of a node.
     * @param Checks which node has been visited.
     * @param Calculates how many nodes with degree 1 have been removed.
     */
    bool deleteLeafNodes(
        unsigned index,
        std::vector<bool>& visitedNodes,
        unsigned& deletedNodesCount
        ) const;
};

} // namespace NMphf

#endif // MPHF_COMMON_GRAPH