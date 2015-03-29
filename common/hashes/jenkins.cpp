/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Mar 2015
 * @copyright Zbigniew Czech, George Havas, Bohdan S. Majewski, VaL Doroshchuk
 * @license GNU GPL v2
 * @package Mphf
 */

#include "jenkins.hpp"

namespace NMphf {
namespace NHash {

/*
   --------------------------------------------------------------------
   mix -- mix 3 32-bit values reversibly.
   For every delta with one or two bits set, and the deltas of all three
   high bits or all three low bits, whether the original value of a,b,c
   is almost all zero or is uniformly distributed,
 * If mix() is run forward or backward, at least 32 bits in a,b,c
 have at least 1/4 probability of changing.
 * If mix() is run forward, every bit of c will change between 1/3 and
 2/3 of the time.  (Well, 22/100 and 78/100 for some 2-bit deltas.)
 mix() was built out of 36 single-cycle latency instructions in a
 structure that could supported 2x parallelism, like so:
 a -= b;
 a -= c; x = (c>>13);
 b -= c; a ^= x;
 b -= a; x = (a<<8);
 c -= a; b ^= x;
 c -= b; x = (b>>13);
 ...
 Unfortunately, superscalar Pentiums and Sparcs can't take advantage
 of that parallelism.  They've also turned some of those single-cycle
 latency instructions into multi-cycle latency instructions.  Still,
 this is the fastest good hash I could find.  There were about 2^^68
 to choose from.  I only looked at a billion or so.
 --------------------------------------------------------------------
 */
#define mix(a,b,c) { \
    a -= b; a -= c; a ^= (c>>13); \
    b -= c; b -= a; b ^= (a<<8);  \
    c -= a; c -= b; c ^= (b>>13); \
    a -= b; a -= c; a ^= (c>>12); \
    b -= c; b -= a; b ^= (a<<16); \
    c -= a; c -= b; c ^= (b>>5);  \
    a -= b; a -= c; a ^= (c>>3);  \
    b -= c; b -= a; b ^= (a<<10); \
    c -= a; c -= b; c ^= (b>>15); \
}

unsigned jenkins(unsigned seed, const char *k, unsigned keylen) {
    unsigned hashes[3];
    unsigned len, length;

    /* Set up the internal state */
    length = keylen;
    len = length;
    hashes[0] = hashes[1] = 0x9e3779b9;  /* the golden ratio; an arbitrary value */
    hashes[2] = seed;   /* the previous hash value - seed in our case */

    /*---------------------------------------- handle most of the key */
    while (len >= 12) {
        hashes[0] += ((unsigned)k[0] + ((unsigned)k[1]<<8) + ((unsigned)k[2]<<16) +((unsigned)k[3]<<24));
        hashes[1] += ((unsigned)k[4] + ((unsigned)k[5]<<8) + ((unsigned)k[6]<<16) +((unsigned)k[7]<<24));
        hashes[2] += ((unsigned)k[8] + ((unsigned)k[9]<<8) + ((unsigned)k[10]<<16) +((unsigned)k[11]<<24));
        mix(hashes[0], hashes[1], hashes[2]);
        k += 12; 
        len -= 12;
    }

    /*------------------------------------- handle the last 11 bytes */
    hashes[2] += length;
    switch(len) {              /* all the case statements fall through */
        case 11:
            hashes[2] +=((unsigned)k[10]<<24);
        case 10:
            hashes[2] +=((unsigned)k[9]<<16);
        case 9 :
            hashes[2] +=((unsigned)k[8]<<8);
            /* the first byte of hashes[2] is reserved for the length */
        case 8 :
            hashes[1] +=((unsigned)k[7]<<24);
        case 7 :
            hashes[1] +=((unsigned)k[6]<<16);
        case 6 :
            hashes[1] +=((unsigned)k[5]<<8);
        case 5 :
            hashes[1] +=(unsigned char) k[4];
        case 4 :
            hashes[0] +=((unsigned)k[3]<<24);
        case 3 :
            hashes[0] +=((unsigned)k[2]<<16);
        case 2 :
            hashes[0] +=((unsigned)k[1]<<8);
        case 1 :
            hashes[0] +=(unsigned char)k[0];
            /* case 0: nothing left to add */
    }

    mix(hashes[0], hashes[1], hashes[2]);

    return hashes[2];
}

} // namespace NHash
} // namespace NMphf
