/* ------------------------------------------------------------------ -*- c++ -*-
 *
 * (c) SILKAN           - 2014-2016
 * (c) ANR Project HPAC -  Generated by the 'ffinterg' tool (v0.4)
 *
 */

#include "ffintert_matlab.h"
int ff_pfsub_0(double, size_t, size_t, ffintert::Matrix<double>, size_t, ffintert::Matrix<double>, size_t, ffintert::Matrix<double>, size_t, int);



/* -------------------------------------------------------------------------- */

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  if ((((((nrhs == 4) && ffintert::isField(prhs[0])) && (ffintert::isMatrix(prhs[1]) && ffintert::isElement(prhs[1]))) && (ffintert::isMatrix(prhs[2]) && ffintert::isElement(prhs[2]))) && ffintert::isInt(prhs[3]))) {
    double F = ffintert::getField(prhs[0]);
    ffintert::Matrix<double> A = ffintert::getMatrix(prhs[1]);
    ffintert::Matrix<double> B = ffintert::getMatrix(prhs[2]);
    int t = ffintert::getInt(prhs[3]);
    size_t m = ffintert::rows(A);
    ffintert::check(m, ffintert::rows(B), "m");
    size_t n = ffintert::cols(A);
    ffintert::check(n, ffintert::cols(B), "n");
    size_t _tmp_0 = ffintert::ld(A);
    size_t _tmp_1 = ffintert::ld(B);
    ffintert::Matrix<double> C = ffintert::createMatrix(plhs[0], m, n);
    size_t _tmp_2 = ffintert::ld(C);
    ff_pfsub_0(F, n, m, A, _tmp_0, B, _tmp_1, C, _tmp_2, t);
  } else {
    ffintert::error("wrong arguments types (or number) for routine: pfsub.");
  }  
}

