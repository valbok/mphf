/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Mar 2015
 * @copyright Zbigniew Czech, George Havas, Bohdan S. Majewski, VaL Doroshchuk
 * @license GNU GPL v2
 */

#ifndef MPHF_HASHES_JENKINS
#define MPHF_HASHES_JENKINS

#include <stdint.h>

namespace NMphf {
namespace NHash {

unsigned jenkins(unsigned seed, const char *k, unsigned keylen);
int  siphash( uint8_t *out, const uint8_t *in, uint64_t inlen, const uint8_t *k );

} // namespace NHash
} // namespace NMphf

#endif // MPHF_HASHES_JENKINS