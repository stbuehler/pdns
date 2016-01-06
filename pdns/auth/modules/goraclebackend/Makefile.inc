AM_CPPFLAGS += $(ORACLE_CFLAGS) $(MBEDTLS_CFLAGS)

EXTRA_DIST += \
	auth/modules/goraclebackend/drop-schema.goracle.sql \
	auth/modules/goraclebackend/schema.goracle.sql

dist_doc_DATA += \
	auth/modules/goraclebackend/drop-schema.goracle.sql \
	auth/modules/goraclebackend/schema.goracle.sql

libgoraclebackend_la_CPPFLAGS = $(AM_CPPFLAGS)
libgoraclebackend_la_SOURCES = \
	auth/modules/goraclebackend/goraclebackend.cc auth/modules/goraclebackend/goraclebackend.hh \
	auth/modules/goraclebackend/soracle.cc auth/modules/goraclebackend/soracle.hh

libgoraclebackend_la_LDFLAGS = -module -avoid-version
libgoraclebackend_la_LIBADD = \
	$(ORACLE_LIBS)

if BUILD_AUTH_MODULE_GORACLE_DYNAMIC
pkglib_LTLIBRARIES += libgoraclebackend.la
else
EXTRA_LTLIBRARIES += libgoraclebackend.la
endif

if BUILD_AUTH_MODULE_GORACLE_STATIC
auth_common_sources += $(libgoraclebackend_la_SOURCES)
auth_common_ldadd += $(libgoraclebackend_la_LIBADD)
endif
