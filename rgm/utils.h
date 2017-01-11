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

#ifndef _RGM_UTILS_H_
#define _RGM_UTILS_H_

#include <cassert>
#include <algorithm>

namespace rgm
{
    template <typename T>
    T step(T edge, T x)
    {
        if (x < edge)
        {
            return 0.0;
        }
        else 
        {
            return 1.0;
        }
    }

    template <typename T>
    T clamp(T a, float minVal, float maxVal)
    {
        return std::min<T>(std::max<T>(a, minVal), maxVal);
    }

    template <typename T>
    T smoothstep(T edge0, T edge1, T x)
    {
        T t = clamp<T>((x - edge0) / (edge1 - edge0), 0.0, 1.0);
        return t * t * (3.0 - 2.0 * t);
    }

    template <typename T>
    T lerp(T factor, T min, T max)
    {
        assert(min <= max);

        T f = clamp(factor, (T)0, (T)1);
        T d = max - min;
        return min + d * f;
    }

    template <typename T>
    T map(T factor, T imin, T imax, T omin, T omax)
    {
        assert(imin <= imax);
        assert(omin <= omax);

        T f = clamp(factor, imin, imax);

        T id = imax - imin;
        T od = omax - omin;
        T co = od / id;

        T f1 = f - imin;

        return omin + f1 * co;
    }
}

#endif
