dnl  Check for BLAS
dnl  Copyright Pascal Giorgi 2005
dnl  This file is part of Fflas-Fpack (and comes from LinBox)
dnl  See COPYING for licence information.


dnl FF_CHECK_BLAS ([MINIMUM-VERSION [, ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]]])
dnl
dnl Test for BLAS and define BLAS_LIBS

AC_DEFUN([FF_CHECK_BLAS],
[

AC_ARG_WITH(blas,
[AC_HELP_STRING([--with-blas=<lib>|yes], [Use BLAS library. This library is mandatory for Fflas-Ffpack
   			compilation. If argument is yes or <empty> that means
			the library is reachable with the standard search path
			(/usr or /usr/local). Otherwise you give the <path> to
			the directory which contain the library.
	     ])],
	     [if test "$withval" = yes ; then
			BLAS_HOME_PATH="${DEFAULT_CHECKING_PATH}"
	      else
			BLAS_HOME_PATH="$withval"
			BLAS_VAL="$withval"
	     fi],
	     [BLAS_HOME_PATH="${DEFAULT_CHECKING_PATH}"])




dnl Check for existence

BACKUP_CXXFLAGS=${CXXFLAGS}
BACKUP_LIBS=${LIBS}

if test -n "$BLAS_HOME_PATH" ; then
AC_MSG_CHECKING(for C interface to BLAS)
fi


dnl
dnl Check first for C interface to BLAS
dnl


if test -n "$BLAS_VAL"; then

	dnl check with user supplied value
	CBLAS="yes"
	CBLAS_FLAG="-D__FFLAFLAS_HAVE_CBLAS"

	if   test -d "$BLAS_VAL"; then
		if test -r "$BLAS_VAL/lib/libcblas.a" -o -r "$BLAS_VAL/lib/libcblas.so" ; then
			ATLAS_NEEDED=`nm -u $BLAS_VAL/lib/libcblas.a | grep ATL`
			ATLAS_NEEDED2=`nm -Du $BLAS_VAL/lib/libcblas.so | grep ATL`
			if test -n "$ATLAS_NEEDED" -o -n "ATLAS_NEEDED2" ; then
dnl lapack_atlas is for hmrg at udel.  What a kludge that this specialization is here.
                if test -f "$BLAS_VAL/lib/liblapack_atlas.a"  -o  -f "$BLAS_VAL/lib/liblapack_atlas.so"   ; then
					ATLAS_LIBS="-llapack -llapack_atlas -lcblas -latlas"
				else
					ATLAS_LIBS="-llapack -lcblas -latlas"
				fi
			else
				ATLAS_LIBS="-lcblas -llapack"
			fi
			BLAS_LIBS="-L${BLAS_VAL}/lib $ATLAS_LIBS"

		elif test -r "$BLAS_VAL/libcblas.a" -o  -r "$BLAS_VAL/libcblas.so"  ; then
			ATLAS_NEEDED=`nm -u $BLAS_VAL/libcblas.a | grep ATL`
			ATLAS_NEEDED2=`nm -Du $BLAS_VAL/libcblas.so | grep ATL`
			if test -n "$ATLAS_NEEDED" -o -n "ATLAS_NEEDED2" ; then
                if test -f "$BLAS_VAL/liblapack_atlas.a"  -o  -f "$BLAS_VAL/liblapack_atlas.so"   ; then
					ATLAS_LIBS="-llapack -llapack_atlas -lcblas -latlas"
				else
					ATLAS_LIBS="-llapack -lcblas -latlas"
				fi
			else
				ATLAS_LIBS="-lcblas -llapack"
			fi
			BLAS_LIBS="-L${BLAS_VAL} $ATLAS_LIBS"
                elif test -r "$BLAS_VAL/include/mkl_cblas.h"; then
			case `./config.guess` in
				i686-*linux-gnu)
					MKL_ARCH=32;
					;;
				x86_64-*-linux-gnu)
					MKL_ARCH=em64t;
					;;
				*)
					echo "Sorry unsupported arch, please complain in ffpack-devel discussion group";
					;;
			esac
                        BLAS_LIBS="-L${BLAS_VAL}/lib/${MKL_ARCH}/ -lmkl_lapack64 -lmkl -lvml -lguide"
		fi
	else
		BLAS_LIBS="$BLAS_VAL"
	fi
	CXXFLAGS="${BACKUP_CXXFLAGS} ${CBLAS_FLAG}"
	LIBS="${BACKUP_LIBS} ${BLAS_LIBS}"

	AC_TRY_LINK(
	[#define __FFLAFLAS_CONFIGURATION
         #include "fflas-ffpack/config-blas.h"],
	[double a;],
	[
	AC_TRY_RUN(
	[#define __FFLAFLAS_CONFIGURATION
       	 #include "fflas-ffpack/config-blas.h"
	 int main () {  double a[4] = {1.,2.,3.,4.}; double b[4]= {4.,3.,2.,1.}; double c[4];
			cblas_dgemm(CblasRowMajor, CblasNoTrans,CblasNoTrans,2,2,2,1., a,2,b,2,0.,c,2);
			if ( (c[0]!=8.) && (c[1]!=5.) && (c[2]!=20.) && (c[3]!=13))
				return -1;
			else
				return 0;
		      }
	],[
	blas_found="yes"
	break
	],[
	blas_problem="$problem $BLAS_VAL"
	unset BLAS_LIBS
	],[
	blas_found="yes"
	blas_cross="yes"
	break
	])
	],
	[
	blas_found="no"
	blas_checked="$checked $BLAS_VAL"
	unset BLAS_LIBS
	])
else

	dnl check in default path
	for BLAS_HOME in ${DEFAULT_CHECKING_PATH}
	do
		CBLAS="yes"
		CBLAS_FLAG="-D__FFLAFLAS_HAVE_CBLAS"

		if test -r "/System/Library/Frameworks/Accelerate.framework"; then
			BLAS_LIBS="-Wl,-framework -Wl,Accelerate"
		elif test -r "$BLAS_HOME/lib/libcblas.a" -o -r "$BLAS_HOME/lib/libcblas.so"; then

			ATLAS_NEEDED=`nm -u $BLAS_HOME/lib/libcblas.a | grep ATL`
			ATLAS_NEEDED2=`nm -Du $BLAS_HOME/lib/libcblas.so | grep ATL`
			if test -n "$ATLAS_NEEDED" -o -n "$ATLAS_NEEDED2" ; then
                if test -f $BLAS_HOME/lib/liblapack_atlas.a -o -f $BLAS_HOME/lib/liblapack_atlas.so ; then
					ATLAS_LIBS="-llapack -llapack_atlas -lcblas -latlas"
				else
					ATLAS_LIBS="-llapack -lcblas -latlas"
				fi
			else
				ATLAS_LIBS="-lcblas -llapack"
			fi
			if test "x$BLAS_HOME" = "x/usr" -o "x$BLAS_HOME" = "x/usr/local" ; then
 				BLAS_LIBS=" ${ATLAS_LIBS}"
			else
				BLAS_LIBS="-L${BLAS_HOME}/lib ${ATLAS_LIBS}"
			fi

		elif test -r "$BLAS_HOME/libcblas.a"  -o -r "$BLAS_HOME/libcblas.so" ; then
			ATLAS_NEEDED=`nm -u $BLAS_HOME/libcblas.a | grep ATL`
			ATLAS_NEEDED2=`nm -Du $BLAS_HOME/libcblas.so | grep ATL`
			if test -n "$ATLAS_NEEDED" -o -n "$ATLAS_NEEDED2" ; then
                if test -f $BLAS_HOME/liblapack_atlas.a  -o -f $BLAS_HOME/liblapack_atlas.a ; then
					ATLAS_LIBS="-llapack -llapack_atlas -lcblas -latlas"
				else
					ATLAS_LIBS="-llapack -lcblas -latlas"
				fi
			else
				ATLAS_LIBS="-lcblas -llapack"
			fi
			BLAS_LIBS="-L${BLAS_HOME} ${ATLAS_LIBS}"
		fi

		CXXFLAGS="${BACKUP_CXXFLAGS} ${CBLAS_FLAG}"
		LIBS="${BACKUP_LIBS} ${BLAS_LIBS}"

		AC_TRY_LINK(
		[#define __FFLAFLAS_CONFIGURATION
       		  #include "fflas-ffpack/config-blas.h"],
		[double a;],
		[
		AC_TRY_RUN(
		[#define __FFLAFLAS_CONFIGURATION
     	         #include "fflas-ffpack/config-blas.h"
		 int main () {  double a[4] = {1.,2.,3.,4.}; double b[4]= {4.,3.,2.,1.}; double c[4];
				cblas_dgemm(CblasRowMajor, CblasNoTrans,CblasNoTrans,2,2,2,1., a,2,b,2,0.,c,2);
				if ( (c[0]!=8.) && (c[1]!=5.) && (c[2]!=20.) && (c[3]!=13))
					return -1;
				else
					return 0;
			      }
		],[
		blas_found="yes"
		break
		],[
		blas_problem="$problem $BLAS_HOME"
		unset BLAS_LIBS
		],[
		blas_found="yes"
		blas_cross="yes"
		break
		])
		],
		[
 		blas_found="no"
		blas_checked="$checked $BLAS_HOME"
		unset BLAS_LIBS
		])
	done
fi



if test "x$blas_found" = "xyes"; then
	AC_SUBST(BLAS_LIBS)
	AC_SUBST(CBLAS_FLAG)
	AC_DEFINE(HAVE_BLAS,1,[Define if BLAS is installed])
	AC_DEFINE(HAVE_CBLAS,1,[Define if C interface to BLAS is available])
	AC_DEFINE(BLAS_AVAILABLE,,[Define if BLAS routines are available])
	HAVE_BLAS=yes
	if test "x$blas_cross" != "xyes"; then
		AC_MSG_RESULT(found)
	else
		AC_MSG_RESULT(unknown)
		echo "WARNING: You appear to be cross compiling, so there is no way to determine"
		echo "whether your BLAS are good. I am assuming it is."
	fi

	dnl Check for lapack
	AC_MSG_CHECKING(for lapack)
	AC_TRY_RUN(
	[#define __FFLAFLAS_CONFIGURATION
	 #define __FFLAFLAS_HAVE_LAPACK 1
       	 #include "fflas-ffpack/config-blas.h"
	 int main () {  double a[4] = {1.,2.,3.,4.};
			int ipiv[2];
			clapack_dgetrf(CblasRowMajor, 2, 2, a, 2, ipiv);
			if ( (a[0]!=2.) && (a[1]!=0.5) && (a[2]!=4.) && (a[3]!=1.))
				return -1;
			else
				return 0;
		      }
	],[
	dgetrf_found="yes"
	break
	],[
	dgetrf_problem="$problem"
	],[
	break
	])

	if test "x$dgetrf_found" = "xyes"; then
		AC_MSG_RESULT(found)
		AC_DEFINE(HAVE_LAPACK,1,[Define if lapack is available])
	else
		AC_MSG_RESULT(disabling)
		dnl  AC_DEFINE(HAVE_LAPACK,0,[Define if lapack is available])
	fi

	ifelse([$2], , :, [$2])

elif test -n "$blas_problem"; then
	AC_MSG_RESULT(not working)
	dnl  echo "Sorry, your BLAS are not working. Disabling."
elif test "x$blas_found" = "xno" ; then
	AC_MSG_RESULT(not found)
fi


dnl
dnl  Check if other BLAS are available (only if C BLAS are not available)
dnl
if test "x$blas_found" != "xyes" ; then
	AC_MSG_CHECKING(for others BLAS)
	CBLAS="no"
	CBLAS_FLAG=""
	if test -n "$BLAS_VAL"; then
		if   test -d "$BLAS_VAL"; then
			if test -r "${BLAS_VAL}/lib/libblas.a" -o  -r "${BLAS_VAL}/lib/libblas.so"; then
				BLAS_LIBS="-L${BLAS_VAL}/lib  -lblas"
			fi
			if test -r "${BLAS_VAL}/libblas.a" -o -r "${BLAS_VAL}/libblas.a" ; then
				BLAS_LIBS="-L${BLAS_VAL}  -lblas"
			fi
		else
			BLAS_LIBS=$BLAS_VAL
		fi
		CXXFLAGS="${BACKUP_CXXFLAGS} ${CBLAS_FLAG}"
		LIBS="${BACKUP_LIBS} ${BLAS_LIBS}"

		AC_TRY_LINK(
		[#define __FFLAFLAS_CONFIGURATION
       		 #include "fflas-ffpack/config-blas.h"],
		[double a;],
		[
		AC_TRY_RUN(
		[#define __FFLAFLAS_CONFIGURATION
       		 #include "fflas-ffpack/config-blas.h"
		 int main () {  double a[4] = {1.,2.,3.,4.}; double b[4]= {4.,3.,2.,1.}; double c[4];
				cblas_dgemm(CblasRowMajor, CblasNoTrans,CblasNoTrans,2,2,2,1., a,2,b,2,0.,c,2);
				if ( (c[0]!=8.) && (c[1]!=5.) && (c[2]!=20.) && (c[3]!=13))
					return -1;
				else
					return 0;
			      }
		],[
		blas_found="yes"
		break
		],[
		blas_problem="$problem $BLAS_"
		unset BLAS_LIBS
		],[
		blas_found="yes"
		blas_cross="yes"
		break
		])
		],
		[
		blas_found="no"
		blas_checked="$checked $BLAS_VAL"
		unset BLAS_LIBS
		])
	else

		dnl check in default path
		for BLAS_HOME in ${DEFAULT_CHECKING_PATH}
		do
			CBLAS="no"
			CBLAS_FLAG=""

			BLAS_LIBS=""

dnl checking for libblas.a

			if test -r "$BLAS_HOME/lib64/libblas.a"  && test -r "$BLAS_HOME/lib64/liblapack.a" ; then
				BLAS_LIBS="-L${BLAS_HOME}/lib64 -llapack -lblas"
			elif test -r "$BLAS_HOME/lib/libblas.a" && test -r "$BLAS_HOME/lib/liblapack.a" ; then
				BLAS_LIBS="-L${BLAS_HOME}/lib -llapack -lblas"
			elif test -r "$BLAS_HOME/lib/libblas.a"; then
				if test "x$BLAS_HOME" = "x/usr" -o "x$BLAS_HOME" = "/usr/local" ; then
 					BLAS_LIBS="-lblas"
				else
					BLAS_LIBS="-L${BLAS_HOME}/lib  -lblas"
				fi
			elif test -r "$BLAS_HOME/lib64/libblas.a"; then
				if test "x$BLAS_HOME" = "x/usr" -o "x$BLAS_HOME" = "/usr/local" ; then
 					BLAS_LIBS="-lblas"
				else
					BLAS_LIBS="-L${BLAS_HOME}/lib64  -lblas"
				fi
			elif test -r "$BLAS_HOME/libblas.a"; then
				BLAS_LIBS="-L${BLAS_HOME} -lblas"
			fi

dnl checking for libblas.so

			if test -z "$BLAS_LIBS" ; then
				if test -r "$BLAS_HOME/lib64/libblas.so"  && test -r "$BLAS_HOME/lib64/liblapack.so" ; then
					BLAS_LIBS="-L${BLAS_HOME}/lib64 -llapack -lblas"
				elif test -r "$BLAS_HOME/lib/libblas.so" && test -r "$BLAS_HOME/lib/liblapack.so" ; then
					BLAS_LIBS="-L${BLAS_HOME}/lib -llapack -lblas"
				elif test -r "$BLAS_HOME/lib/libblas.so"; then
					if test "x$BLAS_HOME" = "x/usr" -o "x$BLAS_HOME" = "/usr/local" ; then
						BLAS_LIBS="-lblas"
					else
						BLAS_LIBS="-L${BLAS_HOME}/lib  -lblas"
					fi
				elif test -r "$BLAS_HOME/lib64/libblas.so"; then
					if test "x$BLAS_HOME" = "x/usr" -o "x$BLAS_HOME" = "/usr/local" ; then
						BLAS_LIBS="-lblas"
					else
						BLAS_LIBS="-L${BLAS_HOME}/lib64  -lblas"
					fi
				elif test -r "$BLAS_HOME/libblas.so"; then
					BLAS_LIBS="-L${BLAS_HOME} -lblas"
				fi
			fi


			CXXFLAGS="${BACKUP_CXXFLAGS} ${CBLAS_FLAG}"
			LIBS="${BACKUP_LIBS} ${BLAS_LIBS}"

			AC_TRY_LINK(
			[#define __FFLAFLAS_CONFIGURATION
       		         #include "fflas-ffpack/config-blas.h"],
			[double a;],
			[
			AC_TRY_RUN(
			[#define __FFLAFLAS_CONFIGURATION
     		         #include "fflas-ffpack/config-blas.h"
			 int main () {  double a[4] = {1.,2.,3.,4.}; double b[4]= {4.,3.,2.,1.}; double c[4];
					cblas_dgemm(CblasRowMajor, CblasNoTrans,CblasNoTrans,2,2,2,1., a,2,b,2,0.,c,2);
					if ( (c[0]!=8.) && (c[1]!=5.) && (c[2]!=20.) && (c[3]!=13))
						return -1;
					else
						return 0;
				      }
			],[
			blas_found="yes"
			break
			],[
			blas_problem="$problem $BLAS_HOME"
			unset BLAS_LIBS
			],[
			blas_found="yes"
			blas_cross="yes"
			break
			])
			],
			[
 			blas_found="no"
			blas_checked="$checked $BLAS_HOME"
			unset BLAS_LIBS
			])
		done
	fi


	if test "x$blas_found" = "xyes"; then
		AC_SUBST(BLAS_LIBS)
		AC_SUBST(CBLAS_FLAG)
		AC_DEFINE(HAVE_BLAS,1,[Define if BLAS is installed])
		AC_DEFINE(BLAS_AVAILABLE,,[Define if BLAS routines are available])
		HAVE_BLAS=yes
		if test "x$blas_cross" != "xyes"; then
			AC_MSG_RESULT(found)
		else
			AC_MSG_RESULT(unknown)
			echo "WARNING: You appear to be cross compiling, so there is no way to determine"
			echo "whether your BLAS are good. I am assuming it is."
		fi
		ifelse([$2], , :, [$2])
	elif test -n "$blas_problem"; then
		AC_MSG_RESULT(problem)
		echo "Sorry, your BLAS are not working. Disabling."
		ifelse([$3], , :, [$3])
	elif test "x$blas_found" = "xno" ; then
		AC_MSG_RESULT(not found)
		ifelse([$3], , :, [$3])
	fi




fi



AM_CONDITIONAL(FFLAFFLAS_HAVE_BLAS, test "x$HAVE_BLAS" = "xyes")

CXXFLAGS=${BACKUP_CXXFLAGS}
LIBS=${BACKUP_LIBS}
dnl  unset LD_LIBRARY_PATH


])


