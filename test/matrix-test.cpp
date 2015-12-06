/*
rgm - Rioki's Graphic Math Library

Copyright (c) 2014-2015 Sean "rioki" Farrell

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "rtest.h"
#include <rgm/rgm.h>

SUITE(matrix)
{
    TEST(init3)
    {
        rgm::mat3 m(1, 2, 3, 
                    4, 5, 6,
                    7, 8, 9);

        CHECK_EQUAL(rgm::vec3(1, 4, 7), (rgm::vec3)m[0]);
        CHECK_EQUAL(rgm::vec3(2, 5, 8), (rgm::vec3)m[1]);
        CHECK_EQUAL(rgm::vec3(3, 6, 9), (rgm::vec3)m[2]);
    }

    TEST(init4)
    {
        rgm::mat4 m( 1,  2,  3,  4, 
                     5,  6,  7,  8, 
                     9, 10, 11, 12,
                    13, 14, 15, 16);

        CHECK_EQUAL(rgm::vec4(1, 5,  9, 13), (rgm::vec4)m[0]);
        CHECK_EQUAL(rgm::vec4(2, 6, 10, 14), (rgm::vec4)m[1]);
        CHECK_EQUAL(rgm::vec4(3, 7, 11, 15), (rgm::vec4)m[2]);
        CHECK_EQUAL(rgm::vec4(4, 8, 12, 16), (rgm::vec4)m[3]);
    }
}