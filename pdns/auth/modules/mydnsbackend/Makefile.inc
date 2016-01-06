AM_CPPFLAGS += $(MYSQL_CFLAGS)

EXTRA_DIST += \
	auth/modules/mydnsbackend/schema.mydns.sql

dist_doc_DATA += \
	auth/modules/mydnsbackend/schema.mydns.sql

libmydnsbackend_la_CPPFLAGS = $(AM_CPPFLAGS)
libmydnsbackend_la_SOURCES = \
	auth/modules/gmysqlbackend/smysql.cc auth/modules/gmysqlbackend/smysql.hh \
	auth/modules/mydnsbackend/mydnsbackend.cc auth/modules/mydnsbackend/mydnsbackend.hh

libmydnsbackend_la_LDFLAGS = -module -avoid-version
libmydnsbackend_la_LIBADD = \
	$(MYSQL_LIBS)

if BUILD_AUTH_MODULE_MYDNS_DYNAMIC
pkglib_LTLIBRARIES += libmydnsbackend.la
else
EXTRA_LTLIBRARIES += libmydnsbackend.la
endif

if BUILD_AUTH_MODULE_MYDNS_STATIC
auth_common_sources += $(libmydnsbackend_la_SOURCES)
auth_common_ldadd += $(libmydnsbackend_la_LIBADD)
endif
