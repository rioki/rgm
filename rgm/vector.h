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

#ifndef _RGM_VECTOR_H_
#define _RGM_VECTOR_H_

#include <cassert>
#include <cmath>
#include <iostream>

#undef min
#undef max

namespace rgm
{
    template <typename T, unsigned int N>
    class vector
    {
    public:

        vector() {}

        explicit vector(T v) 
        {
            for (unsigned int i = 0; i < N; i++)
            {
                data[i] = v;
            }
        }

        vector(const vector<T, N>& v) 
        {
            // use assignement, since vector could be complex
            for (unsigned int i = 0; i < N; i++)
            {
                data[i] = v.data[i];
            }
        }

        template <typename T2>
        explicit vector(const vector<T2, N>& v) 
        {
            for (unsigned int i = 0; i < N; i++)
            {
                data[i] = static_cast<T>(v[i]);
            }
        }

        vector<T, N>& operator = (const vector<T, N>& v)
        {
            for (unsigned int i = 0; i < N; i++)
            {
                data[i] = v.data[i];
            }
            return *this;
        }

        vector<T, N>& operator += (const vector<T, N>& v)
        {
            for (unsigned int i = 0; i < N; i++)
            {
                data[i] += v.data[i];
            }
            return *this;
        }

        vector<T, N>& operator -= (const vector<T, N>& v)
        {
            for (unsigned int i = 0; i < N; i++)
            {
                data[i] -= v.data[i];
            }
            return *this;
        }

        T& operator [] (unsigned int i)
        {
            assert(i < N);
            return data[i];
        }

        const T& operator [] (unsigned int i) const
        {
            assert(i < N);
            return data[i];
        }

        const T* c_array() const 
        {
            return data;
        }

    protected:
        T data[N];
    };

    template <typename T>
    class vector2 : public vector<T, 2>
    {
    public:
        
        vector2() {}

        explicit vector2(T v) 
        : vector<T, 2>(v) {}          

        vector2(T x, T y)
        {
            data[0] = x;
            data[1] = y;
        }

        explicit vector2(const vector<T, 3>& v)
        {
            data[0] = v[0];
            data[1] = v[1];
        }

        explicit vector2(const vector<T, 4>& v)
        {
            data[0] = v[0];
            data[1] = v[1];
        }

        vector2(const vector<T, 2>& v)
        : vector<T, 2>(v) {}       
        
        template <typename T2>
        explicit vector2(const vector<T2, 2>& v) 
        : vector<T, 2>(v) {} 

    protected:
        using vector<T, 2>::data;
    };

    template <typename T>
    class vector3 : public vector<T, 3>
    {
    public:
        
        vector3() {}

        explicit vector3(T v) 
        : vector<T, 3>(v) {}          

        explicit vector3(T x, T y, T z)
        {
            data[0] = x;
            data[1] = y;
            data[2] = z;
        }
        
        explicit vector3(const vector<T, 2>& v, T z = (T)0)
        {
            data[0] = v[0];
            data[1] = v[1];
            data[2] = z;
        }

        explicit vector3(const vector<T, 4>& v)
        {
            data[0] = v[0];
            data[1] = v[1];
            data[2] = v[2];
        }

        vector3(const vector<T, 3>& v)
        : vector<T, 3>(v) {}

        template <typename T2>
        explicit vector3(const vector<T2, 3>& v) 
        : vector<T, 3>(v) {}

    protected:
        using vector<T, 3>::data;
    };

    template <typename T>
    class vector4 : public vector<T, 4>
    {
    public:
        
        vector4() {}

        explicit vector4(T v) 
        : vector<T, 4>(v) {}          

        vector4(T x, T y, T z, T w)
        {
            data[0] = x;
            data[1] = y;
            data[2] = z;
            data[3] = w;
        }

        explicit vector4(const vector<T, 2>& v, T z = (T)0, T w = (T)0)
        {
            data[0] = v[0];
            data[1] = v[1];
            data[2] = z;
            data[3] = w;
        }

        explicit vector4(const vector<T, 3>& v, T w = (T)0)
        {
            data[0] = v[0];
            data[1] = v[1];
            data[2] = v[2];
            data[3] = w;
        }

        vector4(const vector<T, 4>& v)
        : vector<T, 4>(v) {}

        template <typename T2>
        explicit vector4(const vector<T2, 4>& v) 
        : vector<T, 4>(v) {}

    protected:
        using vector<T, 4>::data;
    };

    template <typename T, unsigned int N>
    bool operator == (const vector<T, N>& a, const vector<T, N>& b)
    {
        for (unsigned int i = 0; i < N; i++)
        {                
            if (a[i] != b[i])
            {
                return false;
            }
        }        
        return true;
    }

    template <typename T, unsigned int N>
    bool operator != (const vector<T, N>& a, const vector<T, N>& b)
    {
        return !(a == b);
    }

    template <typename T, unsigned int N>
    vector<T, N> operator + (const vector<T, N>& v)
    {
        return v;
    }
    
    template <typename T, unsigned int N>
    vector<T, N> operator - (const vector<T, N>& v)
    {
        vector<T, N> r;
        for (unsigned int i = 0; i < N; i++)
        {                
            r[i] = -v[i];
        }        
        return r;
    }

    template <typename T, unsigned int N>
    vector<T, N> operator + (const vector<T, N>& a, const vector<T, N>& b)
    {
        vector<T, N> r;
        for (unsigned int i = 0; i < N; i++)
        {                
            r[i] = a[i] + b[i];
        }        
        return r;
    }
    
    template <typename T, unsigned int N>
    vector<T, N> operator - (const vector<T, N>& a, const vector<T, N>& b)
    {
        vector<T, N> r;
        for (unsigned int i = 0; i < N; i++)
        {                
            r[i] = a[i] - b[i];
        }        
        return r;
    }

    template <typename T, unsigned int N, typename S>
    vector<T, N> operator * (const vector<T, N>& v, S s)
    {
        vector<T, N> r;
        for (unsigned int i = 0; i < N; i++)
        {                
            r[i] = v[i] * s;
        }        
        return r;
    }

    template <typename T, unsigned int N, typename S>
    vector<T, N> operator / (const vector<T, N>& v, S s)
    {
        vector<T, N> r;
        for (unsigned int i = 0; i < N; i++)
        {                
            r[i] = v[i] / s;
        }        
        return r;
    }

    template <typename T, unsigned int N>
    vector<T, N> operator * (const vector<T, N>& a, const vector<T, N>& b)
    {
        vector<T, N> r;
        for (unsigned int i = 0; i < N; i++)
        {                
            r[i] = a[i] * b[i];
        }        
        return r;
    }

    template <typename T, unsigned int N>
    vector<T, N> operator / (const vector<T, N>& a, const vector<T, N>& b)
    {
        vector<T, N> r;
        for (unsigned int i = 0; i < N; i++)
        {                
            r[i] = a[i] / b[i];
        }        
        return r;
    }

    template <typename T, unsigned int N>
    vector<T, N> operator % (const vector<T, N>& a, const vector<T, N>& b)
    {
        vector<T, N> r;
        for (unsigned int i = 0; i < N; i++)
        {                
            r[i] = a[i] % b[i];
        }        
        return r;
    }

    template <typename T, unsigned int N>
    T dot(const vector<T, N>& a, const vector<T, N>& b)
    {
        T r = 0;
        
        for (unsigned int i = 0; i < N; i++)
        {                
            r += a[i] * b[i];
        } 
        
        return r;
    }
    
    template <typename T>
    vector<T, 3> cross(const vector<T, 3>& a, const vector<T, 3>& b)
    {
        return vector3<T>  ((a[1] * b[2]) - (a[2] * b[1]),
                            (a[2] * b[0]) - (a[0] * b[2]),
                            (a[0] * b[1]) - (a[1] * b[0]));
    }
    
    template <typename T, unsigned int N>
    T length(const vector<T, N>& v)
    {
        return std::sqrt(dot(v, v));
    }

    template <typename T, unsigned int N>
    T distance(const vector<T, N>& a, const vector<T, N>& b)
    {
        return length(a - b);
    }
    
    template <typename T, unsigned int N>
    vector<T, N> normalize(const vector<T, N>& v)
    {
        return v / length(v);
    }

    template <typename T, unsigned int N>
    vector<T, N> min(const vector<T, N>& a, const vector<T, N>& b)
    {
        vector<T, N> r;

        for (unsigned int i = 0; i < N; i++)
        {                
            r[i] = std::min(a[i], b[i]);
        } 
        
        return r;
    }
    
    template <typename T, unsigned int N>
    vector<T, N> min(const vector<T, N>& a, T b)
    {
        vector<T, N> r;

        for (unsigned int i = 0; i < N; i++)
        {                
            r[i] = std::min(a[i], b);
        } 
        
        return r;
    }

    template <typename T, unsigned int N>
    T min(const vector<T, N>& v)
    {
        T r = v[0];

        for (unsigned int i = 1; i < N; i++)
        {                
            r = std::min(v[i], r);
        } 
        
        return r;
    }
    
    template <typename T, unsigned int N>
    vector<T, N> max(const vector<T, N>& a, const vector<T, N>& b)
    {
        vector<T, N> r;

        for (unsigned int i = 0; i < N; i++)
        {                
            r[i] = std::max(a[i], b[i]);
        } 
        
        return r;
    }
    
    template <typename T, unsigned int N>
    vector<T, N> max(const vector<T, N>& a, float b)
    {
        vector<T, N> r;

        for (unsigned int i = 0; i < N; i++)
        {                
            r[i] = std::max(a[i], b);
        } 
        
        return r;
    }

    template <typename T, unsigned int N>
    T max(const vector<T, N>& v)
    {
        T r = v[0];

        for (unsigned int i = 1; i < N; i++)
        {                
            r = std::max(v[i], r);
        } 
        
        return r;
    }

    template <typename T, unsigned int N>
    vector<T, N> pow(const vector<T, N>& a, const vector<T, N>& b)
    {
        vector<T, N> r;

        for (unsigned int i = 0; i < N; i++)
        {                
            r[i] = std::pow(a[i], b[i]);
        } 
        
        return r;
    }
    
    template <typename T, unsigned int N>
    vector<T, N> clamp(const vector<T, N>& a, const vector<T, N>& minVal, const vector<T, N>& maxVal)
    {
        return min(max(a, minVal), maxVal);
    }
    
    template <typename T, unsigned int N>
    vector<T, N> clamp(const vector<T, N>& a, float minVal, float maxVal)
    {
        return min(max(a, minVal), maxVal);
    }
    
    template <typename T, unsigned int N>
    vector<T, N> mix(const vector<T, N>& a, const vector<T, N>& b, const vector<T, N>& wb)
    {
        return a * (vector<T, N>(1.0) - wb) + b * wb;
    }
    
    template <typename T, unsigned int N>
    vector<T, N> mix(const vector<T, N>& a, const vector<T, N>& b, float wb)
    {
        return a * vector<T, N>(1.0 - wb) + b * vector<T, N>(wb);
    }
    
    template <typename T, unsigned int N>
    vector<T, N> floor(const vector<T, N>& v)
    {
        vector<T, N> r;

        for (unsigned int i = 0; i < N; i++)
        {                
            r[i] = std::floor(v[i]);
        } 
        
        return r;
    }
    
    template <typename T, unsigned int N>
    vector<T, N> ceil(const vector<T, N>& v)
    {
        vector<T, N> r;

        for (unsigned int i = 0; i < N; i++)
        {                
            r[i] = std::ceil(v[i]);
        } 
        
        return r;
    }
    
    template <typename T>
    T limit(T v, T vmin, T vmax)
    {
        assert(vmin < vmax);
        
        T d = vmax - vmin;
        
        while (v > vmax)
        {
            v -= d;
        }
        while (v < vmin)
        {
            v += d;
        }
        
        return v;
    }
    
    template <typename T, unsigned int N>
    vector<T, N> limit(const vector<T, N>& v, T vmin, T vmax)
    {
        vector<T, N> r;

        for (unsigned int i = 0; i < N; i++)
        {                
            r[i] = limit(v[i], vmin, vmax);
        } 
        
        return r;
    }
    
    template <typename T, unsigned int N>
    vector<T, N> round(const vector<T, N>& v)
    {
        vector<T, N> r;

        for (unsigned int i = 0; i < N; i++)
        {             
            // WHY U NO std::round?!
            r[i] = ::round(v[i]);
        } 
        
        return r;
    }
    
    template <typename T, unsigned int N>
    vector<T, N> abs(const vector<T, N>& v)
    {
        vector<T, N> r;

        for (unsigned int i = 0; i < N; i++)
        {             
            r[i] = std::abs(v[i]);
        } 
        
        return r;
    }

    template <typename T, unsigned int N>
    bool close(const vector<T, N>& a, const vector<T, N>& b, T eps)
    {
        auto c = abs(a - b);
        for (size_t i = 0; i < N; ++i)
        {
            if (c[i] > eps)
            {
                 return false;
            }
        }
        return true;
    }

    template <typename T, unsigned int N>
    std::ostream& operator << (std::ostream& os, const vector<T, N>& v)
    {
        os << "(";
        for (unsigned int i = 0; i < N; i++)
        {                
            os << v[i];
            if (i != N-1)
            {
                os << ", ";
            }
        }
        os << ")";
        return os;
    }

    typedef vector2<bool> bvec2;
    typedef vector3<bool> bvec3;
    typedef vector4<bool> bvec4;

    typedef vector2<int> ivec2;
    typedef vector3<int> ivec3;
    typedef vector4<int> ivec4;

    typedef vector2<unsigned int> uvec2;
    typedef vector3<unsigned int> uvec3;
    typedef vector4<unsigned int> uvec4;

    typedef vector2<float> vec2;
    typedef vector3<float> vec3;
    typedef vector4<float> vec4;

    typedef vector2<double> dvec2;
    typedef vector3<double> dvec3;
    typedef vector4<double> dvec4;
}

#endif
