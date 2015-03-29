/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Mar 2015
 * @copyright Zbigniew Czech, George Havas, Bohdan S. Majewski, VaL Doroshchuk, Bob Jenkins
 * @license GNU GPL v2
 */

#ifndef MPHF_HASHES_JENKINS
#define MPHF_HASHES_JENKINS

namespace NMphf {
namespace NHash {

/**
 * Hashes a variable-length key into a 32-bit value.
 * Every bit of the key affects every bit of the return value.  
 * Every 1-bit and 2-bit delta achieves avalanche.
 * About 6*len+35 instructions.
 *
 * The best hash table sizes are powers of 2.  There is no need to do
 * mod a prime (mod is sooo slow!).  If you need less than 32 bits,
 * use a bitmask.  For example, if you need only 10 bits, do
 * h = (h & hashmask(10));
 * In which case, the hash table should have hashsize(10) elements.
 *
 * If you are hashing n strings (uint8 **)k, do it like this:
 * for (i=0, h=0; i<n; ++i) h = hash( k[i], len[i], h);
 *
 * By Bob Jenkins, 1996.  bob_jenkins@burtleburtle.net.  You may use this
 * code any way you wish, private, educational, or commercial.  It's free.
 *
 * See http://burtleburtle.net/bob/hash/evahash.html
 * Use for hash table lookup, or anything where one collision in 2^^32 is
 * acceptable.  Do NOT use for cryptographic purposes.
 *
 * @param Random seed.
 * @param Requested key.
 * @param Length of the key.
 * @return Hashed value.
 */
unsigned jenkins(unsigned seed, const char* key, unsigned len);

} // namespace NHash
} // namespace NMphf

#endif // MPHF_HASHES_JENKINS