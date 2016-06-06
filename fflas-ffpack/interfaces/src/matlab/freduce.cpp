/* ------------------------------------------------------------------ -*- c++ -*-
 *
 * (c) SILKAN           - 2014-2016
 * (c) ANR Project HPAC -  Generated by the 'ffinterg' tool (v0.4)
 *
 */

#include "ffintert_matlab.h"
int ff_freduce_0(double, size_t, ffintert::Vector<double>, size_t, ffintert::Vector<double>, size_t);
int ff_freduce_1(double, size_t, size_t, ffintert::Matrix<double>, size_t);



/* -------------------------------------------------------------------------- */

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  if ((((nrhs == 2) && ffintert::isField(prhs[0])) && (ffintert::isVector(prhs[1]) && ffintert::isElement(prhs[1])))) {
    double F = ffintert::getField(prhs[0]);
    ffintert::Vector<double> X = ffintert::getVector(prhs[1]);
    size_t n = ffintert::length(X);
    size_t _tmp_0 = ffintert::st(X);
    ffintert::Vector<double> Y = ffintert::createVector(plhs[0], n);
    size_t _tmp_1 = ffintert::st(Y);
    ff_freduce_0(F, n, X, _tmp_0, Y, _tmp_1);
  } else if ((((nrhs == 2) && ffintert::isField(prhs[0])) && (ffintert::isMatrix(prhs[1]) && ffintert::isElement(prhs[1])))) {
    double F = ffintert::getField(prhs[0]);
    ffintert::Matrix<double> A = ffintert::duplicateMatrix(prhs[1], plhs[0]);
    size_t m = ffintert::rows(A);
    size_t n = ffintert::cols(A);
    size_t _tmp_0 = ffintert::ld(A);
    ff_freduce_1(F, n, m, A, _tmp_0);
  } else {
    ffintert::error("wrong arguments types (or number) for routine: freduce.");
  }  
}

