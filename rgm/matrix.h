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

#ifndef _RGM_MATRIX_H_
#define _RGM_MATRIX_H_

#include <cassert>
#include <iostream>
#include <cstring>

#include "vector.h"

namespace rgm
{
    template <typename T, unsigned int N>
    class row
    {
    public:

        row(T* d)
        : data(d) {}

        row(const row<T, N>& r)
        : data(r.data) {}

        const row<T, N>& operator = (const vector<T, N>& v)
        {
            for (unsigned int j = 0; j < N; j++)
            {
                data[j] = v[j];
            }

            return *this;
        }

        const row<T, N>& operator = (const row<T, N>& v)
        {
            for (unsigned int j = 0; j < N; j++)
            {
                data[j] = v[j];
            }

            return *this;
        }

        T& operator [] (unsigned int j)
        {
            assert(j < N);
            return data[j];
        }

        T operator [] (unsigned int j) const
        {
            assert(j < N);
            return data[j];
        }

        operator vector<T, N>()
        {
            vector<T, N> r;

            for (unsigned int j = 0; j < N; j++)
            {
                r[j] = data[j];
            }

            return r;
        }

        const T* c_array() const
        {
            return data;
        }

    private:
        T* data;
    };

    template <typename T, unsigned int N>
    class matrix
    {
    public:

        matrix() {}

        explicit matrix(T v)
        {
            for (unsigned int i = 0; i < N; i++)
            {
                for (unsigned int j = 0; j < N; j++)
                {
                    if (i == j)
                    {
                        data[i * N + j] = v;
                    }
                    else
                    {
                        data[i * N + j] = 0;
                    }
                }
            }
        }

        matrix(const matrix<T, N>& m)
        {
            for (unsigned int i = 0; i < N*N; i++)
            {
                data[i] = m.data[i];
            }
        }

        const matrix<T, N>& operator = (const matrix<T, N>& m)
        {
            for (unsigned int i = 0; i < N*N; i++)
            {
                data[i] = m.data[i];
            }
            return *this;
        }

        row<T, N> operator [] (unsigned int i)
        {
            assert(i < N);
            return row<T, N>(&data[i * N]);
        }

        vector<T, N> operator [] (unsigned int i) const
        {
            assert(i < N);
            vector<T, N> r;

            for (unsigned int j = 0; j < N; j++)
            {
                r[j] = data[i * N + j];
            }

            return r;
        }

        const T* c_array() const
        {
            return data;
        }

    protected:
        T data[N*N];
    };

    template <typename T>
    class matrix2 : public matrix < T, 2 >
    {
    public:

        matrix2() {}

        explicit matrix2(T v)
        : matrix<T, 2>(v) {}

        matrix2(T v0, T v2,
                T v1, T v3)
        {
            data[0] = v0;
            data[1] = v1;
            data[2] = v2;
            data[3] = v3;
        }

        matrix2(const vector<T, 2>& x, const vector<T, 2>& y)
        {
            data[0] = x[0];
            data[1] = x[1];
            data[2] = y[0];
            data[3] = y[1];
        }

        matrix2(const matrix<T, 2>& v)
        : matrix<T, 2>(v) {}

    protected:
        using matrix<T, 2>::data;
    };

    template <typename T>
    class matrix3 : public matrix < T, 3 >
    {
    public:

        matrix3() {}

        explicit matrix3(T v)
        : matrix<T, 3>(v) {}

        matrix3(T v0, T v3, T v6,
                T v1, T v4, T v7,
                T v2, T v5, T v8)
        {
            data[0] = v0;
            data[1] = v1;
            data[2] = v2;
            data[3] = v3;
            data[4] = v4;
            data[5] = v5;
            data[6] = v6;
            data[7] = v7;
            data[8] = v8;
        }

        matrix3(const vector<T, 3>& x, const vector<T, 3>& y, const vector<T, 3>& z)
        {
            data[0] = x[0];
            data[1] = x[1];
            data[2] = x[2];
            data[3] = y[0];
            data[4] = y[1];
            data[5] = y[2];
            data[6] = z[0];
            data[7] = z[1];
            data[8] = z[2];
        }

        matrix3(const matrix<T, 3>& v)
        : matrix<T, 3>(v) {}

        matrix3(const matrix<T, 4>& v)
        {
            data[0] = v[0][0];
            data[1] = v[0][1];
            data[2] = v[0][2];

            data[3] = v[1][0];
            data[4] = v[1][1];
            data[5] = v[1][2];

            data[6] = v[2][0];
            data[7] = v[2][1];
            data[8] = v[0][2];
        }  
        
    protected:
        using matrix<T, 3>::data;
    };

    template <typename T>
    class matrix4 : public matrix < T, 4 >
    {
    public:

        matrix4() {}

        explicit matrix4(T v)
        : matrix<T, 4>(v) {}

        matrix4(float v0, float v4, float v8, float v12,
                float v1, float v5, float v9, float v13,
                float v2, float v6, float v10, float v14,
                float v3, float v7, float v11, float v15)
        {
            data[0]  = v0;
            data[1]  = v1;
            data[2]  = v2;
            data[3]  = v3;
            data[4]  = v4;
            data[5]  = v5;
            data[6]  = v6;
            data[7]  = v7;
            data[8]  = v8;
            data[9]  = v9;
            data[10] = v10;
            data[11] = v11;
            data[12] = v12;
            data[13] = v13;
            data[14] = v14;
            data[15] = v15;
        }

        matrix4(const vector<T, 4>& x, const vector<T, 4>& y, const vector<T, 4>& z, const vector<T, 4>& p)
        {
            data[0]  = x[0];
            data[1]  = x[1];
            data[2]  = x[2];
            data[3]  = x[3];
            data[4]  = y[0];
            data[5]  = y[1];
            data[6]  = y[2];
            data[7]  = y[3];
            data[8]  = z[0];
            data[9]  = z[1];
            data[10] = z[2];
            data[11] = z[3];
            data[12] = p[0];
            data[13] = p[1];
            data[14] = p[2];
            data[15] = p[3];
        }

        matrix4(const matrix<T, 4>& v)
            : matrix<T, 4>(v) {}

    protected:
        using matrix<T, 4>::data;
    };

    template <typename T, unsigned int N>
    bool operator == (const matrix<T, N>& a, const matrix<T, N>& b)
    {
        for (unsigned int i = 0; i < N; i++)
        {
            for (unsigned int j = 0; j < N; j++)
            {
                if (a[i][j] != b[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }

    template <typename T, unsigned int N>
    bool operator != (const matrix<T, N>& a, const matrix<T, N>& b)
    {
        return !(a == b);
    }

    template <typename T, unsigned int N>
    matrix<T, N> operator + (const matrix<T, N>& a)
    {
        return a;
    }

    template <typename T, unsigned int N>
    matrix<T, N> operator - (const matrix<T, N>& a)
    {
        matrix<T, N> r;
        for (unsigned int i = 0; i < N; i++)
        {
            for (unsigned int j = 0; j < N; j++)
            {
                r[i][j] = -a[i][j];
            }
        }
        return r;
    }

    template <typename T, unsigned int N>
    matrix<T, N> operator + (const matrix<T, N>& a, const matrix<T, N>& b)
    {
        matrix<T, N> r;
        for (unsigned int i = 0; i < N; i++)
        {
            for (unsigned int j = 0; j < N; j++)
            {
                r[i][j] = a[i][j] + b[i][j];
            }
        }
        return r;
    }

    template <typename T, unsigned int N>
    matrix<T, N> operator - (const matrix<T, N>& a, const matrix<T, N>& b)
    {
        matrix<T, N> r;
        for (unsigned int i = 0; i < N; i++)
        {
            for (unsigned int j = 0; j < N; j++)
            {
                r[i][j] = a[i][j] - b[i][j];
            }
        }
        return r;
    }

    template <typename T, unsigned int N>
    matrix<T, N> operator * (const matrix<T, N>& a, const matrix<T, N>& b)
    {
        matrix<T, N> r((T)0);

        for (unsigned int i = 0; i < N; i++)
        {
            for (unsigned int j = 0; j < N; j++)
            {
                for (unsigned int k = 0; k < N; k++)
                {
                    r[i][j] += a[k][j] * b[i][k];
                }
            }
        }

        return r;
    }

    template <typename T, unsigned int N>
    vector<T, N> operator * (const matrix<T, N>& m, const vector<T, N>& v)
    {
        vector<T, N> r((T)0);

        for (unsigned int i = 0; i < N; i++)
        {
            for (unsigned int j = 0; j < N; j++)
            {
                r[i] += m[j][i] * v[j];
            }
        }

        return r;
    }

    template <typename T, unsigned int N>
    matrix<T, N> operator * (const matrix<T, N>& m, T s)
    {
        matrix<T, N> r;

        for (unsigned int i = 0; i < N; i++)
        {
            for (unsigned int j = 0; j < N; j++)
            {
                r[i][j] = m[j][i] * s;
            }
        }

        return r;
    }

    template <typename T, unsigned int N>
    matrix<T, N> operator * (T s, const matrix<T, N>& m)
    {
        return m * s;
    }

    template <typename T, unsigned int N>
    matrix<T, N> matrixCompMult(const matrix<T, N>& a, const matrix<T, N>& b)
    {
        matrix<T, N> r((T)0);

        for (unsigned int i = 0; i < N; i++)
        {
            for (unsigned int j = 0; j < N; j++)
            {
                r[i][j] = a[i][j] * b[i][j];
            }
        }

        return r;
    }

    template <typename T>
    T det(const matrix<T, 1>& a)
    {
        return a[0][0];;
    }

    template <typename T>
    T det(const matrix<T, 2>& a)
    {
        return a[0][0] * a[1][1] - a[1][0] * a[0][1];
    }

    template <typename T, unsigned int N>
    T det(const matrix<T, N>& a)
    {
        assert(N > 2);
        T d = 0;
        for (unsigned int j1 = 0; j1 < N; j1++)
        {
            matrix<T, N - 1> m;
            for (unsigned int i = 1; i < N; i++)
            {
                unsigned int j2 = 0;
                for (unsigned int j = 0; j < N; j++)
                {
                    if (j == j1)
                    {
                        continue;
                    }

                    m[i - 1][j2] = a[i][j];
                    j2++;
                }
            }
            d += (T)std::pow(-1.0, j1 + 2.0) * a[0][j1] * det(m);
        }
        return d;
    }

    template <typename T, unsigned int N>
    matrix<T, N> cofct(const matrix<T, N>& a)
    {
        matrix<T, N> b;
        matrix<T, N - 1> c;
        
        for (unsigned int j = 0; j < N; j++) 
        {
            for (unsigned int i = 0; i < N; i++) 
            {
                unsigned int i1 = 0;
                for (unsigned int ii = 0; ii < N; ii++) 
                {
                    if (ii == i)
                    {
                        continue;
                    }
                        
                    unsigned int j1 = 0;
                    for (unsigned int jj = 0; jj < N; jj++) 
                    {
                        if (jj == j)
                        {
                            continue;
                        }
                            
                        c[i1][j1] = a[ii][jj];
                        j1++;
                    }
                    i1++;
                }
                b[i][j] = (T)std::pow(-1.0, i + j + 2.0) * det(c);
            }
        }
        
        return b;
    }

    template <typename T, unsigned int N>
    matrix<T, N> transpose(const matrix<T, N>& m)
    {
        matrix<T, N> r((T)0);

        for (unsigned int i = 0; i < N; i++)
        {
            for (unsigned int j = 0; j < N; j++)
            {
                r[j][i] = m[i][j];
            }
        }

        return r;
    }
     
    template <typename T, unsigned int N>
    matrix<T, N> adj(const matrix<T, N>& m)
    {
        return trans(cofct(m));
    }

    template <typename T, unsigned int N>
    matrix<T, N> inv(const matrix<T, N>& m)
    {
        // WTF?! either the cofct is wrong or the adj 
        //return (1 / det(m)) * adj(m);
        return (1 / det(m)) * cofct(m);
    }

    template <typename T, unsigned int N>
    matrix<T, N> abs(const matrix<T, N>& m)
    {
        matrix<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            for (size_t j = 0; j < N; ++j)
            {
                result[i][j] = std::abs(m[i][j]);
            }
        }
        return result;
    }

    template <typename T, unsigned int N>
    bool close(const matrix<T, N>& a, const matrix<T, N>& b, T eps)
    {
        auto c = abs(a - b);
        for (size_t i = 0; i < N; ++i)
        {
            for (size_t j = 0; j < N; ++j)
            { 
                if (c[i][j] > eps)
                {
                    return false;
                }
            }
        }
        return true;
    }

    template <typename T, unsigned int N>
    std::ostream& operator << (std::ostream& os, const matrix<T, N>& m)
    {
        os << "{";
        for (unsigned int j = 0; j < N; j++)        
        {
            for (unsigned int i = 0; i < N; i++)
            {
                os << m[i][j];
                if (i != N - 1)
                {
                    os << ", ";
                }
                else if (j != N - 1)
                {
                    os << "; ";
                }
            }
        }
        os << "}";
        return os;
    }

    typedef matrix2<bool> bmat2;
    typedef matrix3<bool> bmat3;
    typedef matrix4<bool> bmat4;

    typedef matrix2<int> imat2;
    typedef matrix3<int> imat3;
    typedef matrix4<int> imat4;

    typedef matrix2<unsigned int> umat2;
    typedef matrix3<unsigned int> umat3;
    typedef matrix4<unsigned int> umat4;

    typedef matrix2<float> mat2;
    typedef matrix3<float> mat3;
    typedef matrix4<float> mat4;

    typedef matrix2<double> dmat2;
    typedef matrix3<double> dmat3;
    typedef matrix4<double> dmat4;
}

#endif
