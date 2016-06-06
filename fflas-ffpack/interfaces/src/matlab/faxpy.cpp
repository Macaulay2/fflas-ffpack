/* ------------------------------------------------------------------ -*- c++ -*-
 *
 * (c) SILKAN           - 2014-2016
 * (c) ANR Project HPAC -  Generated by the 'ffinterg' tool (v0.4)
 *
 */

#include "ffintert_matlab.h"
int ff_faxpy_0(double, size_t, double, ffintert::Vector<double>, size_t, ffintert::Vector<double>, size_t);
int ff_faxpy_1(double, size_t, size_t, double, ffintert::Matrix<double>, size_t, ffintert::Matrix<double>, size_t);



/* -------------------------------------------------------------------------- */

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  if ((((((nrhs == 4) && ffintert::isField(prhs[0])) && ffintert::isElement(prhs[1])) && (ffintert::isVector(prhs[2]) && ffintert::isElement(prhs[2]))) && (ffintert::isVector(prhs[3]) && ffintert::isElement(prhs[3])))) {
    double F = ffintert::getField(prhs[0]);
    double alpha = ffintert::getElement(prhs[1]);
    ffintert::Vector<double> X = ffintert::getVector(prhs[2]);
    ffintert::Vector<double> Y = ffintert::duplicateVector(prhs[3], plhs[0]);
    size_t n = ffintert::length(X);
    ffintert::check(n, ffintert::length(Y), "n");
    size_t _tmp_0 = ffintert::st(X);
    size_t _tmp_1 = ffintert::st(Y);
    ff_faxpy_0(F, n, alpha, X, _tmp_0, Y, _tmp_1);
  } else if ((((((nrhs == 4) && ffintert::isField(prhs[0])) && ffintert::isElement(prhs[1])) && (ffintert::isMatrix(prhs[2]) && ffintert::isElement(prhs[2]))) && (ffintert::isMatrix(prhs[3]) && ffintert::isElement(prhs[3])))) {
    double F = ffintert::getField(prhs[0]);
    double alpha = ffintert::getElement(prhs[1]);
    ffintert::Matrix<double> A = ffintert::getMatrix(prhs[2]);
    ffintert::Matrix<double> B = ffintert::duplicateMatrix(prhs[3], plhs[0]);
    size_t m = ffintert::rows(A);
    size_t n = ffintert::cols(A);
    ffintert::check(m, ffintert::rows(B), "m");
    ffintert::check(n, ffintert::cols(B), "n");
    size_t _tmp_0 = ffintert::ld(A);
    size_t _tmp_1 = ffintert::ld(B);
    ff_faxpy_1(F, n, m, alpha, A, _tmp_0, B, _tmp_1);
  } else {
    ffintert::error("wrong arguments types (or number) for routine: faxpy.");
  }  
}

