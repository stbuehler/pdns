libbindbackend_la_CPPFLAGS = $(AM_CPPFLAGS)
libbindbackend_la_SOURCES = \
	auth/bind-dnssec.schema.sqlite3.sql.h \
	auth/modules/bindbackend/bindbackend2.cc auth/modules/bindbackend/bindbackend2.hh \
	auth/modules/bindbackend/binddnssec.cc

libbindbackend_la_LDFLAGS = -module -avoid-version

if BUILD_AUTH_MODULE_BIND_DYNAMIC
pkglib_LTLIBRARIES += libbindbackend.la
else
EXTRA_LTLIBRARIES += libbindbackend.la
endif

if BUILD_AUTH_MODULE_BIND_STATIC
auth_common_sources += $(libbindbackend_la_SOURCES)
endif
