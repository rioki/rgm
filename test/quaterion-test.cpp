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

SUITE(quat)
{
    TEST(init)
    {
        rgm::quat q(1, 2, 3, 4);

        CHECK_EQUAL(1, q[0]);
        CHECK_EQUAL(2, q[1]);
        CHECK_EQUAL(3, q[2]);
        CHECK_EQUAL(4, q[3]);
    }

    TEST(transform) 
    {
        rgm::quat q = rgm::axis_angle<float>(rgm::vec3(0, 0, 1), 20.0f);
        rgm::mat4 m = rgm::mat4(1);
        m = rgm::rotate<float>(m, rgm::vec3(0, 0, 1), 20.0f);

        rgm::vec3 src(1, 1, 1);
        rgm::vec3 v1 = rgm::transform(m, src);
        rgm::vec3 v2 = rgm::transform(q, src);

        CHECK_EQUAL(v1, v2);
    }

    TEST(quat2mat4)
    {
        rgm::quat q = rgm::axis_angle<float>(rgm::vec3(0, 0, 1), 45.0f);
        rgm::mat4 m = rgm::mat4(1);
        m = rgm::rotate<float>(m, rgm::vec3(0, 0, 1), 45.0f);

        rgm::mat4 qm = rgm::quat2mat4(q);
        CHECK_EQUAL(m, qm);
    }
}
