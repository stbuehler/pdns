EXTRA_DIST += \
	auth/modules/pipebackend/backend.pl

libpipebackend_la_CPPFLAGS = $(AM_CPPFLAGS)
libpipebackend_la_SOURCES = \
	auth/modules/pipebackend/coprocess.cc auth/modules/pipebackend/coprocess.hh \
	auth/modules/pipebackend/pipebackend.cc auth/modules/pipebackend/pipebackend.hh

libpipebackend_la_LDFLAGS = -module -avoid-version

if BUILD_AUTH_MODULE_PIPE_DYNAMIC
pkglib_LTLIBRARIES += libpipebackend.la
else
EXTRA_LTLIBRARIES += libpipebackend.la
endif

if BUILD_AUTH_MODULE_PIPE_STATIC
auth_common_sources += $(libpipebackend_la_SOURCES)
endif
