
#ifndef _RGM_QUATERNION_H_
#define _RGM_QUATERNION_H_

#include "vector.h"
#include "matrix.h"

namespace rgm
{
    template <typename T>
    class quaterion : public vector4<T>
    {
    public:
        quaterion() {}

        explicit quaterion(T v) 
        : vector4<T>(v) {}          

        quaterion(T x, T y, T z, T m)
        {
            data[0] = x;
            data[1] = y;
            data[2] = z;
            data[3] = m;
        }

        quaterion(const vector<T, 3>& v, T w)
        {
            data[0] = v[0];
            data[1] = v[1];
            data[2] = v[2];
            data[3] = w;
        }

        quaterion(const vector<T, 4>& v)
        : vector4<T>(v) {}

        quaterion(const vector4<T>& v)
        : vector4<T>(v) {}

        template <typename T2>
        explicit quaterion(const vector<T2, 4>& v) 
        : vector4<T>(v) {}

        operator vector3<T> () 
        {
            return vector3<T>(data[0], data[1], data[2]);
        }
    };

    template <typename T>
    quaterion<T> operator * (const quaterion<T>& a, const quaterion<T>& b)
    {
        T          wa = a[3];
        vector3<T> va = vector3<T>(a);
        T          wb = b[3];
        vector3<T> vb = vector3<T>(b);

        T          w = wa * wb - dot(va, vb);
        vector3<T> v = wa * vb + wb * va + cross(va, vb);

        return quaterion<T>(v, w);
    }

    
    template <typename T>
    quaterion<T> conjugate(const quaterion<T>& q)
    {
        return quaterion<T>(-vector3<T>(q), q[3]);
    }
     
    template <typename T>
    quaterion<T> inverse(const quaterion<T>& q)
    {
        return conjugate(q);
    }

    template <typename T>
    matrix<T, 4> quat2mat4(const quaterion<T>& q)
    {
        T xx = q[0] * q[0];
        T xy = q[0] * q[1];
        T xz = q[0] * q[2];
        T xw = q[0] * q[3];
        T yy = q[1] * q[1];
        T yz = q[1] * q[2];
        T yw = q[1] * q[3];
        T zz = q[2] * q[2];
        T zw = q[2] * q[3];

        matrix<T, 4> mat = matrix<T, 4>(1);
        mat[0][0] = 1 - 2 * (yy + zz);
        mat[1][0] = 2 * (xy - zw);
        mat[2][0] = 2 * (xz + yw);
        mat[0][1] = 2 * (xy + zw);
        mat[1][1] = 1 - 2 * (xx + zz);
        mat[2][1] = 2 * (yz - xw);
        mat[0][2] = 2 * (xz - yw);
        mat[1][2] = 2 * (yz + xw);
        mat[2][2] = 1 - 2 * (xx + yy);
        
        return mat;        
    }

    template <typename T>
    quaterion<T> quatfromvectors(vector<T, 3> u, vector<T, 3> v)
    {
        vec3 w = cross(u, v);
        quaterion<T> q = quaterion<T>(dot(u, v), w[0], w[1], w[2]);
        return normalize(q);
    }

    typedef quaterion<float>  quat;
    typedef quaterion<double> dquat;
}

#endif
