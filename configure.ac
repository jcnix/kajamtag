AC_INIT(kajamtag, 0.2.6.1, jonescaseyb@gmail.com)
AM_INIT_AUTOMAKE(kajamtag, 0.2.6.1)
AC_CONFIG_HEADERS([config.h])
AC_PROG_LIBTOOL
AC_PROG_INSTALL
AC_CONFIG_MACRO_DIR([m4])
AC_PREFIX_DEFAULT(/usr)

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([strchr strdup])

AC_CONFIG_FILES([Makefile bin/Makefile src/Makefile])
AC_OUTPUT()
