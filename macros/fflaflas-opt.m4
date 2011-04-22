# Copyright (c) Fflas-Ffpack
# This file was taken from LinBox linbox-opt.m4
# see COPYING for licence



AC_DEFUN([FF_OPT],
[
AC_MSG_CHECKING([whether to use run time optimization])

AC_ARG_ENABLE(optimization,
[  --enable-optimization  Enable run time optimization in FflasFpack code],
[
AC_MSG_RESULT(yes)


BACKUP_CXXFLAGS=${CXXFLAGS}
BACKUP_LIBS=${LIBS}

if test "x$HAVE_BLAS" = "xyes" ;then
AC_MSG_CHECKING([best threshold for Strassen-Winograd matrix multiplication])


CXXFLAGS="${BACKUP_CXXFLAGS} -I`pwd` -I`pwd`/fflas-ffpack ${BLAS_CFLAGS} ${CBLAS_FLAG}"
LIBS="${BACKUP_LIBS} ${BLAS_LIBS} "


AC_TRY_RUN([	//#define LinBoxSrcOnly
		#include <iostream>
		#include <fstream>
		//#define _LINBOX_LINBOX_CONFIG_H
		#define __FFLAFLAS_CONFIGURATION
		#include <fflas-ffpack/config-blas.h>
		#include <fflas-ffpack/fflasffpack-config.h>
		#include <fflas-ffpack/field/modular-positive.h>
		#include <fflas-ffpack/fflas/fflas.h>
		#include <tests/timer.h>

		//using namespace LinBox;
		int main () {

		  FFPACK::Modular<double> F((long int)17);
		  size_t n=300, nmax=5000, prec=512, nbest=0, count=0;
		  Timer chrono;
		  double basetime, time;
		  bool bound=false;

		  double *A, *C;
		  A = new double[nmax*nmax];
		  C = new double[nmax*nmax];
		  for (size_t i=0; i<nmax*nmax;++i){
		    A[i]=2.;
	  	  }

		  std::ofstream outlog;
		  outlog.open("config.log", std::ofstream::out | std::ofstream::app);
		  outlog << std::endl
			 << "Threshold for finite field Strassen-Winograd matrix multiplication"
			 << std::endl;
		  do {
		    chrono.start();
		    FFLAS::fgemm(F, FFLAS::FflasNoTrans, FFLAS::FflasNoTrans,
				 n, n, n, 1., A, n, A, n, 0., C, n, 0);
		    chrono.stop();
		    std::cout << std::endl
			      << "fgemm " << n << "x" << n << ": "
			      << chrono.usertime() << " s, "
                              << (2.0/chrono.usertime()*n/100.0*n/100.0*n/100.0) << " Mffops"
			      << std::endl;
		    outlog << std::endl
			      << "fgemm " << n << "x" << n << ": "
			      << chrono.usertime() << " s, "
                              << (2.0/chrono.usertime()*n/100.0*n/100.0*n/100.0) << " Mffops"
			      << std::endl;
		    basetime= chrono.usertime();
		    chrono.clear();
		    chrono.start();
		    FFLAS::fgemm(F, FFLAS::FflasNoTrans, FFLAS::FflasNoTrans,
				 n, n, n, 1., A, n, A, n, 0., C, n, 1);
		    chrono.stop();
		    std::cout << "1Wino " << n << "x" << n << ": "
			      << chrono.usertime() << " s, "
			      << (2.0/chrono.usertime()*n/100.0*n/100.0*n/100.0) << " Mffops"
			      << std::endl;
		    outlog << "1Wino " << n << "x" << n << ": "
			      << chrono.usertime() << " s, "
			      << (2.0/chrono.usertime()*n/100.0*n/100.0*n/100.0) << " Mffops"
			      << std::endl;
		    time= chrono.usertime();

		    if (basetime > time ){
		      count++;
		      if (count > 1){
	    		 nbest=n;
		         bound=true;
		         prec=prec>>1;
		         n-=prec;
		      }
		    }
		    else{
		      count=0;
		      if (bound)
			prec=prec>>1;
		      n+=prec;
		    }
		  } while ((prec > 64 ) && (n < nmax));

		  std::ofstream out("WinoThreshold");
		  out<<nbest;
		  out.close();

		  outlog << "defined __FFLAFLAS_STRASSEN_OPTIMIZATION" << std::endl
			 << "defined __FFLAFLAS_WINOTHRESHOLD to " << nbest << "" << std::endl;
	          outlog.close();

		  delete[] A;
		  delete[] C;

		  return 0;
		}
	],[
	AC_MSG_RESULT(done)
	WT="`cat WinoThreshold`"
	if test "$WT" != "0"; then
	 AC_DEFINE(STRASSEN_OPTIMIZATION,,[Define if optimized  threshold for Strassen-Winograd matrix multiplication is available])
	 AC_DEFINE_UNQUOTED(WINOTHRESHOLD, $WT, [optimized threshold for switching to strassen matrix multiplication])
	fi
	],[
	AC_MSG_RESULT(problem)
	strassen_opti="no"
	break
	],[
	AC_MSG_RESULT(cross compilation)
	strassen_opti="no"
	break
	\rm -f fflas-ffpack/fflasffpack-config,h 2>&1 > /dev/null
	])

fi;
],[
AC_MSG_RESULT(no)
\rm -f fflas-ffpack/fflasffpack-config.h  2>&1 > /dev/null
])

])
