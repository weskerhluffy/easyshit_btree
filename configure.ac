# Process this file with autoconf to produce a configure script.

# Prelude.
AC_PREREQ([2.59])
AC_INIT([Mierda], [1.1], [check-devel AT lists.sourceforge.net])

# unique source file --- primitive safety check 
AC_CONFIG_SRCDIR([src/easyshit_btree.c])

# place to put some extra build scripts installed
AC_CONFIG_AUX_DIR([build-aux])

# fairly severe build strictness
# change foreign to gnu or gnits to comply with gnu standards
#http://lists.gnu.org/archive/html/bug-automake/2012-05/msg00009.html
AM_INIT_AUTOMAKE([-Wall -Werror foreign 1.9.6])
AM_PROG_AR

# Checks for programs.
AC_PROG_CC
AC_PROG_LIBTOOL

# Checks for libraries.

# This macro is defined in check.m4 and tests if check.h and
# libcheck.a are installed in your system. It sets CHECK_CFLAGS and
# CHECK_LIBS accordingly.  
#  AM_PATH_CHECK([MINIMUM-VERSION,
#                [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]]])
AM_PATH_CHECK()

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([execinfo.h])
AC_CHECK_HEADERS([util.h])
AC_CANONICAL_HOST
# Check for which host we are on and setup a few things
# specifically based on the host
case $host_os in
  darwin* )
        # Do something specific for mac
        ;;
  linux*)
        # Do something specific for linux
        ;;
   *BSD*)
        # Do something specific for BSD
        ;;
   cygwin)
        echo "10 horas, 1000 oras, como un perro"
        ;;
    *)
        #Default Case
        echo "ya no the kiero " $host_os
        AC_MSG_ERROR([Your platform is not currently supported])
        ;;
esac

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC

# Output files
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 tests/Makefile])
                 
AC_CHECK_FUNCS([backtrace],[],[AC_DEFINE([backtrace(a,b)], [a-a],
                               [Era tan linda...])] )
                               
AC_CHECK_FUNCS([va_copy],[],[AC_DEFINE([va_copy], [__builtin_va_copy], [Mas linda q una stresha...])] ) 
                               
AC_OUTPUT
