/*
rgm - Rioki's Graphic Math Library

Copyright (c) 2014-2017 Sean "rioki" Farrell

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

SUITE(vector)
{
     TEST(init2)
     {
        rgm::vec2 v(1, 2);
        CHECK_EQUAL(1, v[0]);
        CHECK_EQUAL(2, v[1]);
     }

     TEST(init3)
     {
         rgm::vec3 v(1, 2, 3);
         CHECK_EQUAL(1, v[0]);
         CHECK_EQUAL(2, v[1]);
         CHECK_EQUAL(3, v[2]);
     }

     TEST(init4)
     {
         rgm::vec4 v(1, 2, 3, 4);
         CHECK_EQUAL(1, v[0]);
         CHECK_EQUAL(2, v[1]);
         CHECK_EQUAL(3, v[2]);
         CHECK_EQUAL(4, v[3]);
     }
}