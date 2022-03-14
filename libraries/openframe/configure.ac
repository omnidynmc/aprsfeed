#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([openframe], [1.0.0.1], [gcarter@openaprs.net])
AC_CONFIG_SRCDIR([src/StringTool.cpp])
AC_CONFIG_HEADERS([include/openframe/config.h])
AM_INIT_AUTOMAKE([openframe], [1.0.0.1])
LT_INIT
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX
AC_PROG_LIBTOOL

AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LN_S
AC_LANG([C++])

prefix="`pwd`"
bindir="`pwd`"
libdir="`pwd`/lib"
includedir="`pwd`/include"
mysql_includedir="/usr/include/mysql"
mysqlpp_includedir="/usr/include/mysql++"

CPPFLAGS="$CPPFLAGS -I/usr/include -I$mysql_includedir -I$mysqlpp_includedir"
CXXFLAGS="-Wall -pipe -g -I$includedir -I$mysql_includedir -I$mysqlpp_includedir"
CXX="g++"
LIBS="$LIBS"

# Checks for libraries.

AC_CHECK_LIB([dl], [dlopen], [], [
               echo "dynamic loadable library is required for this program"
               exit 1
             ])

AC_CHECK_LIB([pthread], [pthread_create], [], [
               echo "pthread library is required for this program"
               exit 1
             ])

AC_CHECK_LIB([rt], [clock_gettime], [], [
               echo "realtime library is required for this program"
               exit 1
             ])

AC_CHECK_LIB([termcap], [tgetent], [], [
               echo "termcap library is required for this program"
               exit 1
             ])

AC_MSG_CHECKING(--enable-mysql yes or no)

AC_ARG_ENABLE(mysql,
    [  --enable-mysql         include mysql interface],
    [enable_mysql=$enableval],
    [enable_mysql="yes"])
AC_MSG_RESULT($enable_mysql)

AM_CONDITIONAL(MYSQL, test "x$enable_mysql" = "xyes")

if test "$enable_mysql" = "yes"; then
  AC_DEFINE([FEAT_MYSQL], [1], [mysql support])

  AC_CHECK_LIB([mysqlclient], [main], [], [
                 echo "mysql library is required for this program"
                 exit 1
               ])

  AC_CHECK_LIB([mysqlpp], [main], [], [
                 echo "mysqlpp library is required for this program"
                 exit 1
               ])

# Checks for header files.

  AC_CHECK_HEADER([mysql.h], [], [
                   echo "mysql header files are required for this program"
                   exit 1
                 ])

  AC_CHECK_HEADER([mysql++.h], [], [
                   echo "mysqlpp header files are required for this program"
                   exit 1
                 ])
fi

dnl #########################
dnl ## Check for memcached ##
dnl #########################

AC_MSG_CHECKING(--enable-memcached yes or no)

AC_ARG_ENABLE(memcached,
    [  --enable-memcached         include memcached interface],
    [enable_memcached=$enableval],
    [enable_memcached="yes"])
AC_MSG_RESULT($enable_memcached)

AM_CONDITIONAL(MEMCACHED, test "x$enable_memcached" = "xyes")

if test "$enable_memcached" = "yes"; then
  AC_DEFINE([FEAT_MEMCACHED], [1], [memcached support])
  PKG_CHECK_MODULES(DEPS, libmemcached >= 0.8.0) AC_SUBST(DEPS_CFLAGS) AC_SUBST(DEPS_LIBS)
fi


AC_CHECK_READLINE

if test "x$have_readline" != "xyes"; then
  exit 1
fi


# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_SUBST(bindir)
AC_SUBST(LIBTOOL_DEPS)

dnl CXXFLAGS="$CXXFLAGS -I`pwd`/include -I$MYSQL_INCLUDE $DEPS_CFLAGS"
LIBS="$LIBS -L`pwd`/lib $DEPS_LIBS $READLINE_LIBS"

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/App/Makefile
                 src/Commands/Makefile
                 src/logging/Makefile
                 src/Socket/Makefile
                 src/Thread/Makefile
                 test/Makefile
               ])
AC_OUTPUT
