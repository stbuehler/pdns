librandombackend_la_CPPFLAGS = $(AM_CPPFLAGS)
librandombackend_la_SOURCES = \
	auth/modules/randombackend/randombackend.cc
librandombackend_la_LDFLAGS = -module -avoid-version

if BUILD_AUTH_MODULE_RANDOM_DYNAMIC
pkglib_LTLIBRARIES += librandombackend.la
else
EXTRA_LTLIBRARIES += librandombackend.la
endif

if BUILD_AUTH_MODULE_RANDOM_STATIC
auth_common_sources += $(librandombackend_la_SOURCES)
endif
