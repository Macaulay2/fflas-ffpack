/* ------------------------------------------------------------------ -*- c++ -*-
 *
 * (c) SILKAN           - 2014-2016
 * (c) ANR Project HPAC -  Generated by the 'ffinterg' tool (v0.4)
 *
 */

#include "ffintert_matlab.h"
int ff_fscal_0(double, size_t, double, ffintert::Vector<double>, size_t, ffintert::Vector<double>, size_t);
int ff_fscal_1(double, size_t, size_t, double, ffintert::Matrix<double>, size_t, ffintert::Matrix<double>, size_t);



/* -------------------------------------------------------------------------- */

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  if (((((nrhs == 3) && ffintert::isField(prhs[0])) && ffintert::isElement(prhs[1])) && (ffintert::isVector(prhs[2]) && ffintert::isElement(prhs[2])))) {
    double F = ffintert::getField(prhs[0]);
    double alpha = ffintert::getElement(prhs[1]);
    ffintert::Vector<double> X = ffintert::getVector(prhs[2]);
    size_t n = ffintert::length(X);
    size_t _tmp_0 = ffintert::st(X);
    ffintert::Vector<double> Y = ffintert::createVector(plhs[0], n);
    size_t _tmp_1 = ffintert::st(Y);
    ff_fscal_0(F, n, alpha, X, _tmp_0, Y, _tmp_1);
  } else if (((((nrhs == 3) && ffintert::isField(prhs[0])) && ffintert::isElement(prhs[1])) && (ffintert::isMatrix(prhs[2]) && ffintert::isElement(prhs[2])))) {
    double F = ffintert::getField(prhs[0]);
    double alpha = ffintert::getElement(prhs[1]);
    ffintert::Matrix<double> A = ffintert::getMatrix(prhs[2]);
    size_t m = ffintert::rows(A);
    size_t n = ffintert::cols(A);
    size_t _tmp_0 = ffintert::ld(A);
    ffintert::Matrix<double> B = ffintert::createMatrix(plhs[0], m, n);
    size_t _tmp_1 = ffintert::ld(B);
    ff_fscal_1(F, n, m, alpha, A, _tmp_0, B, _tmp_1);
  } else {
    ffintert::error("wrong arguments types (or number) for routine: fscal.");
  }  
}

