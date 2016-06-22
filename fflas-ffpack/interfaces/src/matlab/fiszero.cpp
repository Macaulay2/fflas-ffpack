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

#include "ffintert_matlab.h"
using namespace ffintert;

bool ff_fiszero(int32_t, size_t, const int32_t*, size_t, FP_C_RP = FP_C_RP_ModularBalanced);
bool ff_fiszero(int64_t, size_t, const int64_t*, size_t, FP_C_RP = FP_C_RP_ModularBalanced);
bool ff_fiszero(Integer, size_t, const Integer*, size_t);
bool ff_fiszero(float, size_t, const float*, size_t, FP_C_RP = FP_C_RP_ModularBalanced);
bool ff_fiszero(double, size_t, const double*, size_t, FP_C_RP = FP_C_RP_ModularBalanced);
bool ff_fiszero(int32_t, size_t, size_t, const int32_t*, size_t, FP_C_RP = FP_C_RP_ModularBalanced);
bool ff_fiszero(int64_t, size_t, size_t, const int64_t*, size_t, FP_C_RP = FP_C_RP_ModularBalanced);
bool ff_fiszero(Integer, size_t, size_t, const Integer*, size_t);
bool ff_fiszero(float, size_t, size_t, const float*, size_t, FP_C_RP = FP_C_RP_ModularBalanced);
bool ff_fiszero(double, size_t, size_t, const double*, size_t, FP_C_RP = FP_C_RP_ModularBalanced);



/* -------------------------------------------------------------------------- */

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  if ((((nrhs == 2) && isElement<int32_t>(prhs[0])) && isVector<int32_t>(prhs[1]))) {
    int32_t p = getElement<int32_t>(prhs[0]);
    Vector<int32_t> X = getVector<int32_t>(prhs[1]);
    size_t n = length(X);
    const int32_t* _tmp_0 = constptr(X);
    size_t _tmp_1 = st(X);
    bool b = ff_fiszero(p, n, _tmp_0, _tmp_1);
    createAndSetBool(plhs[0], b);
  } else if ((((nrhs == 2) && isElement<int64_t>(prhs[0])) && isVector<int64_t>(prhs[1]))) {
    int64_t p = getElement<int64_t>(prhs[0]);
    Vector<int64_t> X = getVector<int64_t>(prhs[1]);
    size_t n = length(X);
    const int64_t* _tmp_0 = constptr(X);
    size_t _tmp_1 = st(X);
    bool b = ff_fiszero(p, n, _tmp_0, _tmp_1);
    createAndSetBool(plhs[0], b);
  } else if ((((nrhs == 2) && isElement<float>(prhs[0])) && isVector<float>(prhs[1]))) {
    float p = getElement<float>(prhs[0]);
    Vector<float> X = getVector<float>(prhs[1]);
    size_t n = length(X);
    const float* _tmp_0 = constptr(X);
    size_t _tmp_1 = st(X);
    bool b = ff_fiszero(p, n, _tmp_0, _tmp_1);
    createAndSetBool(plhs[0], b);
  } else if ((((nrhs == 2) && isElement<double>(prhs[0])) && isVector<double>(prhs[1]))) {
    double p = getElement<double>(prhs[0]);
    Vector<double> X = getVector<double>(prhs[1]);
    size_t n = length(X);
    const double* _tmp_0 = constptr(X);
    size_t _tmp_1 = st(X);
    bool b = ff_fiszero(p, n, _tmp_0, _tmp_1);
    createAndSetBool(plhs[0], b);
  } else if ((((nrhs == 2) && isElement<int32_t>(prhs[0])) && isMatrix<int32_t>(prhs[1]))) {
    int32_t p = getElement<int32_t>(prhs[0]);
    Matrix<int32_t> A = getMatrix<int32_t>(prhs[1]);
    size_t m = rows(A);
    size_t n = cols(A);
    const int32_t* _tmp_0 = constptr(A);
    size_t _tmp_1 = ld(A);
    bool b = ff_fiszero(p, n, m, _tmp_0, _tmp_1);
    createAndSetBool(plhs[0], b);
  } else if ((((nrhs == 2) && isElement<int64_t>(prhs[0])) && isMatrix<int64_t>(prhs[1]))) {
    int64_t p = getElement<int64_t>(prhs[0]);
    Matrix<int64_t> A = getMatrix<int64_t>(prhs[1]);
    size_t m = rows(A);
    size_t n = cols(A);
    const int64_t* _tmp_0 = constptr(A);
    size_t _tmp_1 = ld(A);
    bool b = ff_fiszero(p, n, m, _tmp_0, _tmp_1);
    createAndSetBool(plhs[0], b);
  } else if ((((nrhs == 2) && isElement<float>(prhs[0])) && isMatrix<float>(prhs[1]))) {
    float p = getElement<float>(prhs[0]);
    Matrix<float> A = getMatrix<float>(prhs[1]);
    size_t m = rows(A);
    size_t n = cols(A);
    const float* _tmp_0 = constptr(A);
    size_t _tmp_1 = ld(A);
    bool b = ff_fiszero(p, n, m, _tmp_0, _tmp_1);
    createAndSetBool(plhs[0], b);
  } else if ((((nrhs == 2) && isElement<double>(prhs[0])) && isMatrix<double>(prhs[1]))) {
    double p = getElement<double>(prhs[0]);
    Matrix<double> A = getMatrix<double>(prhs[1]);
    size_t m = rows(A);
    size_t n = cols(A);
    const double* _tmp_0 = constptr(A);
    size_t _tmp_1 = ld(A);
    bool b = ff_fiszero(p, n, m, _tmp_0, _tmp_1);
    createAndSetBool(plhs[0], b);
  } else {
    error("wrong arguments types (or number) for routine: fiszero.");
  }
}

