AC_INIT(finit-plugins, 0.1, https://github.com/troglobit/finit-plugins/issues)
AC_CONFIG_AUX_DIR(aux)
AM_INIT_AUTOMAKE([1.11 foreign subdir-objects])
AM_SILENT_RULES([yes])

AC_CONFIG_SRCDIR([src/chronyd.c])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_FILES([Makefile src/Makefile])

# Older versions of autoconf (<2.58) do not have AC_CONFIG_MACRO_DIR()
#m4_include([m4/plugin.m4])
AC_CONFIG_MACRO_DIR([m4])

# Handle building plugins as dynamically loadable
LT_INIT([shared disable-static dlopen aix-soname=both disable-fast-install])

# Check for pkg-config first, warn if it's not installed
PKG_PROG_PKG_CONFIG

# Check for required libraries
PKG_CHECK_MODULES([lite], [libite >= 2.2.0])

# Check for extra plugins to enable
enable_all_plugins=auto
AC_PLUGIN([chrony],        [yes], [Set up and start system time service chronyd])

AC_EXPAND_DIR(plugin_path, "$libdir/finit/plugins")
AC_SUBST(plugin_path)
AC_DEFINE_UNQUOTED(PLUGIN_PATH, "$plugin_path", [Install path for plugins from this project])

# Generate all files
AC_OUTPUT
