/**
 * @author VaL Doroshchuk
 * @license GNU GPL v2
 */

#include <stdlib.h>
#include <kernel/chm/Chm.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <string>

using namespace NMphf;

TEST(Chm, testFixedList) 
{
    Chm chm;
    const unsigned len = 50;
    const char* list[] = {"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49"};
    bool generaged = chm.generate(list, len);
    EXPECT_TRUE(generaged);

    unsigned ids[len];
    for (unsigned i = 0; i < len; ++i) 
    {
        EXPECT_TRUE(chm.search(list[i], ids[i]));
    }
    
    for (unsigned i = 0; i < len; ++i) 
    {
        for (unsigned j = i + 1; j < len; ++j) 
        {
            if (ids[i] == ids[j]) 
            {
                FAIL();
            }
        }
    }
}

TEST(Chm, testRandomList) 
{
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";    

    Chm chm;
    const unsigned len = 8800;
    char* list[len];

    for (unsigned i = 0; i < len; ++i) 
    {
        unsigned ll = (rand() % 11) + 4;
        list[i] = new char[ll];
        for (unsigned j = 0; j < ll - 1; ++j) 
        {
            list[i][j] = alphanum[rand() % (sizeof(alphanum) - 1)];
        }
        list[i][ll-1] = '\0';
    }

    bool generaged = chm.generate(const_cast<const char**>(list), len);
    EXPECT_TRUE(generaged);

    unsigned ids[len];
    for (unsigned i = 0; i < len; ++i) 
    {
        EXPECT_TRUE(chm.search(list[i], ids[i]));
    }
    
    for (unsigned i = 0; i < len; ++i) 
    {
        for (unsigned j = i + 1; j < len; ++j) 
        {
            if (ids[i] == ids[j]) 
            {
                FAIL();
            }
        }
    }
}
