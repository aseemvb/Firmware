/****************************************************************************
 *
 *   Copyright (C) 2012 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file Vector.cpp
 *
 * math vector
 */

#include <systemlib/test/test.hpp>

#include "Vector.hpp"

namespace math
{

void __EXPORT float2SigExp(
        const float & num,
        float & sig,
        int & exp)
{
    if (isnan(num) || isinf(num))
    {
        sig = 0.0f;
        exp = -99;
        return;
    }
    if (fabsf(num) < 1.0e-38f)
    {
        sig = 0;
        exp = 0;
        return;
    }
    exp = log10f(fabsf(num));
    if (exp>0) {
        exp = ceil(exp);
    } else {
        exp = floor(exp);
    }
    sig = num;
    // cheap power since it is integer
    if (exp>0) {
        for (int i=0;i<abs(exp);i++) sig /= 10;
    } else {
        for (int i=0;i<abs(exp);i++) sig *= 10;
    }
}

static const float data_a[] = {1,3};
static const float data_b[] = {4,1};

static Vector a(2,data_a);
static Vector b(2,data_b);

int __EXPORT vectorTest()
{
    vectorAddTest();
    vectorSubTest();
    return 0;
}

int vectorAddTest()
{
    printf("Test Vector Add\t\t: ");
    Vector r = a + b;
    ASSERT(equal(r(0),5.0f))
    ASSERT(equal(r(1),4.0f))
    printf("PASS\n");
    return 0;
}

int vectorSubTest()
{
    printf("Test Vector Sub\t\t: ");
    Vector c(2);
    c = a - b;
    ASSERT(equal(c(0),-3.0f))
    ASSERT(equal(c(1),2.0f))
    printf("PASS\n");
    return 0;
}


} // namespace math