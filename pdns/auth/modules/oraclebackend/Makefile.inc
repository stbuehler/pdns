AM_CPPFLAGS += $(ORACLE_CFLAGS)

EXTRA_DIST += \
	auth/modules/oraclebackend/drop-schema.oracle.sql \
	auth/modules/oraclebackend/schema.oracle.sql

dist_doc_DATA += \
	auth/modules/oraclebackend/schema.oracle.sql \
	auth/modules/oraclebackend/drop-schema.oracle.sql

liboraclebackend_la_CPPFLAGS = $(AM_CPPFLAGS)
liboraclebackend_la_SOURCES = \
	auth/modules/oraclebackend/oraclebackend.cc auth/modules/oraclebackend/oraclebackend.hh
liboraclebackend_la_LDFLAGS = -module -avoid-version
liboraclebackend_la_LIBADD = $(ORACLE_LIBS) -lclntsh

if BUILD_AUTH_MODULE_ORACLE_DYNAMIC
pkglib_LTLIBRARIES += liboraclebackend.la
else
EXTRA_LTLIBRARIES += liboraclebackend.la
endif

if BUILD_AUTH_MODULE_ORACLE_STATIC
auth_common_sources += $(liboraclebackend_la_SOURCES)
auth_common_ldadd += $(liboraclebackend_la_LIBADD)
endif
