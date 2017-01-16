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

#ifndef _RGM_GL_H_
#define _RGM_GL_H_

#include "vector.h"
#include "matrix.h"
#include "quaternion.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

namespace rgm
{
    template <typename T>
    T radians(T degrees) 
    {
        return degrees * ((T)M_PI / (T)180.0);
    };

    template <typename T>
    T degrees(T radians) 
    {
        return radians * ((T)180.0 / (T)M_PI);
    };

    template <typename T>
    matrix4<T> frustum(T left, T right, T bottom, T top, T znear, T zfar)
    {
        T temp1 = (T)2 * znear;
        T temp2 = right - left;
        T temp3 = top - bottom;
        T temp4 = zfar - znear;

        return matrix4<T>  (temp1/temp2,        (T)0,  (right + left) / temp2,                    (T)0,
                                   (T)0, temp1/temp3,  (top + bottom) / temp3,                    (T)0,
                                   (T)0,        (T)0, (-zfar - znear) / temp4, (-temp1 * zfar) / temp4,
                                   (T)0,        (T)0,                      -1,                    (T)0);       
    }

    template <typename T>
    matrix4<T> perspective(T fov, T aspect, T znear, T zfar)
    {
        T ymax = znear * std::tan(fov * M_PI / 360.0f);
        T xmax = ymax * aspect;
        return frustum(-xmax, xmax, -ymax, ymax, znear, zfar);
    }

    template <typename T>
    matrix4<T> ortho(T l, T r, T b, T t, T n, T f)
    {
        return matrix4<T>(   2.0/(r-l),       0.0,        0.0, -(r+l)/(r-l),
                                   0.0, 2.0/(t-b),        0.0, -(t+b)/(t-b),
                                   0.0,       0.0, -2.0/(f-n), -(f+n)/(f-n),
                                   0.0,       0.0,        0.0,          1.0);     
    }

    template <typename T>
    matrix4<T> lookat(vector<T, 3> position, vector<T, 3> target, vector<T, 3> up)
    {
        vector<T, 3> forward = normalize(position - target);
        vector<T, 3> upn     = normalize(up);
        vector<T, 3> side    = normalize(cross(forward, upn));
        // correct up to be perfectly perpendicular
        vector<T, 3> up2     = cross(side, forward);

        matrix4<T>   r(    side[0],     side[1],     side[2], (T)0,
                             up[0],       up[1],       up[2], (T)0,
                        forward[0],  forward[1],  forward[2], (T)0,
                              (T)0,        (T)0,        (T)0, (T)1);
        r = translate(r, -position);
        return r;

    }

    template <typename T>
    matrix<T, 4> translate(const matrix<T, 4>& m, const vector<T, 3>& p)
    {
        matrix<T, 4> m2(m);
        
        m2[3][0] = m[0][0] * p[0] + m[1][0] * p[1] + m[2][0] * p[2] + m[3][0];
        m2[3][1] = m[0][1] * p[0] + m[1][1] * p[1] + m[2][1] * p[2] + m[3][1];
        m2[3][2] = m[0][2] * p[0] + m[1][2] * p[1] + m[2][2] * p[2] + m[3][2];
        m2[3][3] = m[0][3] * p[0] + m[1][3] * p[1] + m[2][3] * p[2] + m[3][3];

        return m2;
    }

    template <typename T>
    matrix<T, 4> rotate(const matrix<T, 4>& m, const vector<T, 3>& v, T angle)
    {
        T a = radians(angle);
        T c = std::cos(a);
        T s = std::sin(a);
        
        vector<T, 3> axis = normalize(v);

        vector<T, 3> t = axis * (1 - c);

        matrix<T, 3> d(1);
        d[0][0] = c + t[0] * axis[0];
        d[0][1] = 0 + t[0] * axis[1] + s * axis[2];
        d[0][2] = 0 + t[0] * axis[2] - s * axis[1];

        d[1][0] = 0 + t[1] * axis[0] - s * axis[2];
        d[1][1] = c + t[1] * axis[1];
        d[1][2] = 0 + t[1] * axis[2] + s * axis[0];

        d[2][0] = 0 + t[2] * axis[0] + s * axis[1];
        d[2][1] = 0 + t[2] * axis[1] - s * axis[0];
        d[2][2] = c + t[2] * axis[2];
        
        matrix<T, 4> r;
        r[0] = m[0] * d[0][0] + m[1] * d[0][1] + m[2] * d[0][2];
        r[1] = m[0] * d[1][0] + m[1] * d[1][1] + m[2] * d[1][2];
        r[2] = m[0] * d[2][0] + m[1] * d[2][1] + m[2] * d[2][2];
        r[3] = m[3];
        
        return r;
    }

    template <typename T>
    matrix<T, 4> rotate(const matrix<T, 4>& m, const quaterion<T>& q)
    {

        T x = q[0];
        T y = q[1];
        T z = q[2];
        T w = q[3];
        T xx = x * x;
        T xy = x * y;
        T xz = x * z;
        T xw = x * w;
        T yy = y * y;
        T yz = y * z;
        T yw = y * w;
        T zz = z * z;
        T zw = z * w;

        matrix4<T> r((T)1.0 - (T)2.0*(yy + zz),          (T)2.0*(xy + zw),          (T)2.0*(xz - yw), (T)0.0,
                              (T)2.0*(xy - zw), (T)1.0 - (T)2.0*(xx + zz),          (T)2.0*(yz + xw), (T)0.0,
                              (T)2.0*(xz + yw),          (T)2.0*(yz - xw), (T)1.0 - (T)2.0*(xx + yy), (T)0.0,
                                        (T)0.0,                    (T)0.0,                    (T)0.0, (T)1.0);
        r = transpose(r); // FIXME rewrite the above
        return m * r;
    }

    template <typename T>
    matrix<T, 4> scale(const matrix<T, 4>& m, const vector<T, 3>& v)
    {
        matrix<T, 4> r;
        r[0] = m[0] * v[0];
        r[1] = m[1] * v[1];
        r[2] = m[2] * v[2];
        r[3] = m[3];
        return r;    
    }

    template <typename T>
    vector<T, 3> transform(const matrix<T, 4>& m, const vector<T, 3>& v)
    {
        return vector3<T>(m * vector4<T>(v, 0.0f));
    }


    template <typename T>
    vector<T, 3> transform(const quaterion<T>& q, const vector<T, 3>& v)
    {
        return vector<T, 3>(q * quaterion<T>(v, 0) * inverse(q));
    }

    template <typename T>
    quaterion<T> axis_angle(const vector<T, 3>& axis, T angle)
    {
        /*vector<T, 3> axis_n    = normalize(axis);
        T            angle_rad = angle * PI / 180.0;

        T            wr = std::cos(angle_rad / static_cast<T>(2.0));
        vector<T, 3> vr = axis_n * std::sin(angle_rad / static_cast<T>(2.0));

        return quaterion<T>(vr, wr);*/

        vector<T, 3> an    = normalize(axis);

        T sin_a = std::sin(radians(angle/(T)2.0));
        T cos_a = std::cos(radians(angle/(T)2.0));

        T x = an[0] * sin_a;
        T y = an[1] * sin_a;
        T z = an[2] * sin_a;
        T w = cos_a;
        return quaterion<T>(x, y, z, w);
    }

    template <typename T>
    vector3<T> project(const vector<T, 3>& point, const matrix<T, 4>& projection, const matrix<T, 4>& modelview, const vector<T, 4>& viewport)
    {
        matrix<T, 4> temp = projection * modelview;

        vector<T, 4> v = temp * vector4<T>(point, 1);
        v = v / v[3];        

        return vector3<T>(viewport[0] + viewport[2] * (v[0] + 1) / 2, 
                          viewport[1] + viewport[3] * (v[1] + 1) / 2, 
                          (v[2] + 1) / 2);
    }

    template <typename T>
    vector3<T> unproject(const vector<T, 3>& window, const matrix<T, 4>& projection, const matrix<T, 4>& modelview, const vector<T, 4>& viewport)
    {
        matrix<T, 4> temp = inv(projection * modelview);

        T vx = (2 * (window[0] - viewport[0])) / viewport[2] - 1;
        T vy = (2 * (window[1] - viewport[1])) / viewport[3] - 1;
        T vz = (2 * window[2]) - 1;

        vector<T, 4> v = temp * vector4<T>(vx, vy, vz, 1);
        //v = 

        return vector3<T>(v);
    }
}

#undef PI

#endif
