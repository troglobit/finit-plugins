pkglibdir           = $(plugin_path)
AM_LDFLAGS          = -module -avoid-version -shared
AM_CFLAGS           = -W -Wall -Wextra -Wno-unused-parameter -std=gnu99
AM_CPPFLAGS         = -I$(top_srcdir)/src -U_FORTIFY_SOURCE
AM_CPPFLAGS        += -D_XOPEN_SOURCE=600 -D_BSD_SOURCE -D_GNU_SOURCE -D_DEFAULT_SOURCE
AM_CPPFLAGS        += $(lite_CFLAGS)

pkglib_LTLIBRARIES  =

if BUILD_CHRONY_PLUGIN
pkglib_LTLIBRARIES += chronyd.la
endif

if BUILD_QMI_PROXY_PLUGIN
pkglib_LTLIBRARIES += qmi-proxy.la
endif
