libopendbxbackend_la_SOURCES = \
	auth/modules/opendbxbackend/odbxbackend.cc auth/modules/opendbxbackend/odbxbackend.hh \
	auth/modules/opendbxbackend/odbxprivate.cc

libopendbxbackend_la_CPPFLAGS = $(AM_CPPFLAGS)
libopendbxbackend_la_LDFLAGS = -module -avoid-version
libopendbxbackend_la_LIBADD = $(OPENDBX_LIBS)

if BUILD_AUTH_MODULE_OPENDBX_DYNAMIC
pkglib_LTLIBRARIES += libopendbxbackend.la
else
EXTRA_LTLIBRARIES += libopendbxbackend.la
endif

if BUILD_AUTH_MODULE_OPENDBX_STATIC
auth_common_sources += $(libopendbxbackend_la_SOURCES)
auth_common_ldadd += $(libopendbxbackend_la_LIBADD)
endif
