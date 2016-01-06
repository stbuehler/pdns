AM_CPPFLAGS += $(MYSQL_CFLAGS)

EXTRA_DIST += \
	auth/modules/gmysqlbackend/dnssec-3.x_to_3.4.0_schema.mysql.sql \
	auth/modules/gmysqlbackend/nodnssec-3.x_to_3.4.0_schema.mysql.sql \
	auth/modules/gmysqlbackend/schema.mysql.sql

dist_doc_DATA += \
	auth/modules/gmysqlbackend/dnssec-3.x_to_3.4.0_schema.mysql.sql \
	auth/modules/gmysqlbackend/nodnssec-3.x_to_3.4.0_schema.mysql.sql \
	auth/modules/gmysqlbackend/schema.mysql.sql

libgmysqlbackend_la_CPPFLAGS = $(AM_CPPFLAGS)
libgmysqlbackend_la_SOURCES = \
	auth/modules/gmysqlbackend/gmysqlbackend.cc auth/modules/gmysqlbackend/gmysqlbackend.hh \
	auth/modules/gmysqlbackend/smysql.cc auth/modules/gmysqlbackend/smysql.hh

libgmysqlbackend_la_LDFLAGS = -module -avoid-version
libgmysqlbackend_la_LIBADD = \
	$(MYSQL_LIBS)

if BUILD_AUTH_MODULE_GMYSQL_DYNAMIC
pkglib_LTLIBRARIES += libgmysqlbackend.la
else
EXTRA_LTLIBRARIES += libgmysqlbackend.la
endif

if BUILD_AUTH_MODULE_GMYSQL_STATIC
auth_common_sources += $(libgmysqlbackend_la_SOURCES)
auth_common_ldadd += $(libgmysqlbackend_la_LIBADD)
endif
