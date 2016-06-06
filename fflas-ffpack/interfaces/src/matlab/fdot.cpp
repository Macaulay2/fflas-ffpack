/* ------------------------------------------------------------------ -*- c++ -*-
 *
 * (c) SILKAN           - 2014-2016
 * (c) ANR Project HPAC -  Generated by the 'ffinterg' tool (v0.4)
 *
 */

#include "ffintert_matlab.h"
double ff_fdot_0(double, size_t, ffintert::Vector<double>, size_t, ffintert::Vector<double>, size_t);



/* -------------------------------------------------------------------------- */

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  if (((((nrhs == 3) && ffintert::isField(prhs[0])) && (ffintert::isVector(prhs[1]) && ffintert::isElement(prhs[1]))) && (ffintert::isVector(prhs[2]) && ffintert::isElement(prhs[2])))) {
    double F = ffintert::getField(prhs[0]);
    ffintert::Vector<double> X = ffintert::getVector(prhs[1]);
    ffintert::Vector<double> Y = ffintert::getVector(prhs[2]);
    size_t n = ffintert::length(X);
    ffintert::check(n, ffintert::length(Y), "n");
    size_t _tmp_0 = ffintert::st(X);
    size_t _tmp_1 = ffintert::st(Y);
    double Z = ff_fdot_0(F, n, X, _tmp_0, Y, _tmp_1);
    ffintert::createAndSetElement(plhs[0], Z);
  } else {
    ffintert::error("wrong arguments types (or number) for routine: fdot.");
  }  
}

