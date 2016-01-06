AM_CPPFLAGS += $(UNIXODBC_CFLAGS)

dist_doc_DATA += \
	auth/modules/godbcbackend/schema.mssql.sql

libgodbcbackend_la_CPPFLAGS = $(AM_CPPFLAGS)
libgodbcbackend_la_SOURCES = \
	auth/modules/godbcbackend/godbcbackend.cc auth/modules/godbcbackend/godbcbackend.hh \
	auth/modules/godbcbackend/sodbc.cc auth/modules/godbcbackend/sodbc.hh

libgodbcbackend_la_LDFLAGS = -module -avoid-version
libgodbcbackend_la_LIBADD = \
	$(UNIXODBC_LIBS)

if BUILD_AUTH_MODULE_GODBC_DYNAMIC
pkglib_LTLIBRARIES += libgodbcbackend.la
else
EXTRA_LTLIBRARIES += libgodbcbackend.la
endif

if BUILD_AUTH_MODULE_GODBC_STATIC
auth_common_sources += $(libgodbcbackend_la_SOURCES)
auth_common_ldadd += $(libgodbcbackend_la_LIBADD)
endif
