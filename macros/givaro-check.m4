dnl Check for GIVARO
dnl Copyright (c) the Givaro group
dnl This file is part of Givaro

 dnl ========LICENCE========
dnl Givaro is governed by the CeCILL-B license under French law
dnl and abiding by the rules of distribution of free software.
dnl see the COPYRIGHT file for more details.
dnl
 dnl ========LICENCE========
 dnl
dnl adapted from LinBox by BB.

dnl FF_CHECK_GIVARO ([MINIMUM-VERSION [, ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]]])
dnl
dnl Tests for Givaro and define GIVARO_CFLAGS and GIVARO_LIBS
dnl Defines HAVE_GIVARO

AC_DEFUN([FF_CHECK_GIVARO],
[

AC_ARG_WITH(givaro,
[AC_HELP_STRING([--with-givaro=<path>|yes], [Use Givaro library. This library is mandatory for
                           LinBox compilation. If argument is yes or <empty>
			   that means the library is reachable with the standard
			   search path (/usr or /usr/local). Otherwise you give
			   the <path> to the directory which contains the
			   library.
])],
	     [if test "$withval" = yes ; then
			GIVARO_HOME_PATH="${DEFAULT_CHECKING_PATH}"
	      elif test "$withval" != no ; then
			GIVARO_HOME_PATH="$withval ${DEFAULT_CHECKING_PATH}"
	     fi],
	     [GIVARO_HOME_PATH="${DEFAULT_CHECKING_PATH}"])

dnl -------------- dnl
dnl GIVARO VERSION dnl
dnl -------------- dnl

dnl those versions are really any if we only need Integer
version_min=30800
version_max=30900

dnl Check for existence

BACKUP_CXXFLAGS=${CXXFLAGS}
BACKUP_LIBS=${LIBS}

AC_MSG_CHECKING(for GIVARO >= $version_min and < $version_max)

for GIVARO_HOME in ${GIVARO_HOME_PATH}
 do
if test -r "$GIVARO_HOME/include/givaro/givconfig.h"; then

	if test "x$GIVARO_HOME" != "x/usr" -a "x$GIVARO_HOME" != "x/usr/local"; then
		GIVARO_CFLAGS="-I${GIVARO_HOME}/include"
		GIVARO_LIBS="-L${GIVARO_HOME}/lib -lgivaro"
	else
		GIVARO_CFLAGS=
		GIVARO_LIBS="-lgivaro"
	fi
	CXXFLAGS="${BACKUP_CXXFLAGS} ${GIVARO_CFLAGS} ${GMP_CFLAGS}"
	LIBS="${BACKUP_LIBS} ${GIVARO_LIBS} ${GMP_LIBS}"

	AC_TRY_LINK(
	[#include <givaro/givinteger.h>],
	[Givaro::Integer a;],
	[
	AC_TRY_RUN(
	[#include <givaro/givconfig.h>
	 int main () { if (GIVARO_VERSION >= $version_min && GIVARO_VERSION < $version_max) return 0; else return -1; /* old version of Givaro are defined as hexa 0x03yyzz*/ }
	],[
	givaro_found="yes"
	break
	],[
	givaro_problem="$problem $GIVARO_HOME"
	unset GIVARO_CFLAGS
	unset GIVARO_LIBS
	],[
	givaro_found="yes"
	givaro_cross="yes"

	break
	])
	],
	[
	givaro_found="yes"
	givaro_checked="$checked $GIVARO_HOME"
#unset GIVARO_CFLAGS
#unset GIVARO_LIBS
	break

	])
else
	givaro_found="no"
fi
done

if test "x$givaro_found" = "xyes" ; then
	AC_SUBST(GIVARO_CFLAGS)
	AC_SUBST(GIVARO_LIBS)
	dnl  echo $GIVARO_CFLAGS $GIVARO_LIBS
	AC_DEFINE(HAVE_GIVARO,1,[Define if GIVARO is installed])
	HAVE_GIVARO=yes
	if test "x$givaro_cross" != "xyes"; then
		AC_MSG_RESULT(found)
	else
		AC_MSG_RESULT(unknown)
		echo "WARNING: You appear to be cross compiling, so there is no way to determine"
		echo "whether your GIVARO version is new enough. I am assuming it is."
	fi
	ifelse([$2], , :, [$2])
elif test -n "$givaro_problem"; then
	AC_MSG_RESULT(problem)
	echo "Sorry, your GIVARO version is too old. Disabling."
	ifelse([$3], , :, [$3])
elif test "x$givaro_found" = "xno" ; then
	AC_MSG_RESULT(not found)
	ifelse([$3], , :, [$3])
fi

AM_CONDITIONAL(FFLASFFPACK_HAVE_GIVARO, test "x$HAVE_GIVARO" = "xyes")

CXXFLAGS=${BACKUP_CXXFLAGS}
LIBS=${BACKUP_LIBS}
#unset LD_LIBRARY_PATH

])
