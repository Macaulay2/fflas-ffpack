/* ------------------------------------------------------------------ -*- c++ -*-
 *
 * (c) SILKAN           - 2014-2016
 *     Generated by the 'ffinterg' tool (v0.4)
 *
 * ========LICENCE========
 * This file is part of the library FFLAS-FFPACK.
 *
 * FFLAS-FFPACK is free software: you can redistribute it and/or modify
 * it under the terms of the  GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 * ========LICENCE========
 */

#include "ffintert_cxx.h"
#include "fflas-ffpack/fflas/fflas.h"

using namespace FFLAS;
using namespace Givaro;
/* -------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------- */

void ff_fger(int32_t p, size_t m, size_t n, int32_t alpha, int32_t* _tmp0, size_t _tmp1, int32_t* _tmp2, size_t _tmp3, int32_t* _tmp4, size_t _tmp5, FP_C_RP fp_rp)
{
  if ((fp_rp == FP_C_RP_Modular)) {
    fger(Modular<int32_t>(p), m, n, (alpha), Modular<int32_t>::Element_ptr(_tmp0), _tmp1, Modular<int32_t>::Element_ptr(_tmp2), _tmp3, Modular<int32_t>::Element_ptr(_tmp4), _tmp5);
  } else if ((fp_rp == FP_C_RP_ModularBalanced)) {
    fger(ModularBalanced<int32_t>(p), m, n, (alpha), ModularBalanced<int32_t>::Element_ptr(_tmp0), _tmp1, ModularBalanced<int32_t>::Element_ptr(_tmp2), _tmp3, ModularBalanced<int32_t>::Element_ptr(_tmp4), _tmp5);
  } else {
    throw std::runtime_error("wrong field representation parameter.");
  }
}


/* -------------------------------------------------------------------------- */

void ff_fger(int64_t p, size_t m, size_t n, int64_t alpha, int64_t* _tmp0, size_t _tmp1, int64_t* _tmp2, size_t _tmp3, int64_t* _tmp4, size_t _tmp5, FP_C_RP fp_rp)
{
  if ((fp_rp == FP_C_RP_Modular)) {
    fger(Modular<int64_t>(p), m, n, (alpha), Modular<int64_t>::Element_ptr(_tmp0), _tmp1, Modular<int64_t>::Element_ptr(_tmp2), _tmp3, Modular<int64_t>::Element_ptr(_tmp4), _tmp5);
  } else if ((fp_rp == FP_C_RP_ModularBalanced)) {
    fger(ModularBalanced<int64_t>(p), m, n, (alpha), ModularBalanced<int64_t>::Element_ptr(_tmp0), _tmp1, ModularBalanced<int64_t>::Element_ptr(_tmp2), _tmp3, ModularBalanced<int64_t>::Element_ptr(_tmp4), _tmp5);
  } else {
    throw std::runtime_error("wrong field representation parameter.");
  }
}


/* -------------------------------------------------------------------------- */

void ff_fger(float p, size_t m, size_t n, float alpha, float* _tmp0, size_t _tmp1, float* _tmp2, size_t _tmp3, float* _tmp4, size_t _tmp5, FP_C_RP fp_rp)
{
  if ((fp_rp == FP_C_RP_Modular)) {
    fger(Modular<float>(p), m, n, (alpha), Modular<float>::Element_ptr(_tmp0), _tmp1, Modular<float>::Element_ptr(_tmp2), _tmp3, Modular<float>::Element_ptr(_tmp4), _tmp5);
  } else if ((fp_rp == FP_C_RP_ModularBalanced)) {
    fger(ModularBalanced<float>(p), m, n, (alpha), ModularBalanced<float>::Element_ptr(_tmp0), _tmp1, ModularBalanced<float>::Element_ptr(_tmp2), _tmp3, ModularBalanced<float>::Element_ptr(_tmp4), _tmp5);
  } else {
    throw std::runtime_error("wrong field representation parameter.");
  }
}


/* -------------------------------------------------------------------------- */

void ff_fger(double p, size_t m, size_t n, double alpha, double* _tmp0, size_t _tmp1, double* _tmp2, size_t _tmp3, double* _tmp4, size_t _tmp5, FP_C_RP fp_rp)
{
  if ((fp_rp == FP_C_RP_Modular)) {
    fger(Modular<double>(p), m, n, (alpha), Modular<double>::Element_ptr(_tmp0), _tmp1, Modular<double>::Element_ptr(_tmp2), _tmp3, Modular<double>::Element_ptr(_tmp4), _tmp5);
  } else if ((fp_rp == FP_C_RP_ModularBalanced)) {
    fger(ModularBalanced<double>(p), m, n, (alpha), ModularBalanced<double>::Element_ptr(_tmp0), _tmp1, ModularBalanced<double>::Element_ptr(_tmp2), _tmp3, ModularBalanced<double>::Element_ptr(_tmp4), _tmp5);
  } else {
    throw std::runtime_error("wrong field representation parameter.");
  }
}

