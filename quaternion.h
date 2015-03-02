
#ifndef _RGM_QUATERNION_H_
#define _RGM_QUATERNION_H_

#include "vector.h"

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

    typedef quaterion<float>  quat;
    typedef quaterion<double> dquat;
}

#endif
