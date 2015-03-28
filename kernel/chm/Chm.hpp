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

namespace NMphf {

/**
 * An optimal algorithm for generating minimal perfect hash functions.
 */
class Chm 
{
public:

    /**
     *
     */
    explicit Chm(double factor = 2.09) throw();

    /**
     *
     */
    ~Chm();
    
    /**
     *
     */
    bool generate(const char* keys[], unsigned len);
    
    /**
     *
     */
    bool search(const char* key, unsigned& result) const;

private:
    
    /**
     *
     */
    bool reset(unsigned len);
    
    /**
     *
     */    
    unsigned hash(const char* key, unsigned len);

    /**
     *
     */
    void hashes(const char* key, unsigned& firstNodeIndex, unsigned& secondNodeIndex) const;


    double mNodesCountFactor;
    Graph* mGraph;

    unsigned mHashSeeds[2];

};

} // namespace NMphf

#endif // MPHF_CHM