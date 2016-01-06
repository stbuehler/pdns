EXTRA_DIST += \
	auth/modules/gsqlite3backend/dnssec-3.x_to_3.4.0_schema.sqlite3.sql \
	auth/modules/gsqlite3backend/nodnssec-3.x_to_3.4.0_schema.sqlite3.sql \
	auth/modules/gsqlite3backend/schema.sqlite3.sql

dist_doc_DATA += \
	auth/modules/gsqlite3backend/dnssec-3.x_to_3.4.0_schema.sqlite3.sql \
	auth/modules/gsqlite3backend/nodnssec-3.x_to_3.4.0_schema.sqlite3.sql \
	auth/modules/gsqlite3backend/schema.sqlite3.sql

libgsqlite3backend_la_CPPFLAGS = $(AM_CPPFLAGS)
libgsqlite3backend_la_SOURCES = \
	auth/modules/gsqlite3backend/gsqlite3backend.cc auth/modules/gsqlite3backend/gsqlite3backend.hh

libgsqlite3backend_la_LDFLAGS = -module -avoid-version
libgsqlite3backend_la_LIBADD = \
	$(SQLITE3_LIBS)

if BUILD_AUTH_MODULE_GSQLITE3_DYNAMIC
pkglib_LTLIBRARIES += libgsqlite3backend.la
else
EXTRA_LTLIBRARIES += libgsqlite3backend.la
endif

if BUILD_AUTH_MODULE_GSQLITE3_STATIC
auth_common_sources += $(libgsqlite3backend_la_SOURCES)
auth_common_ldadd += $(libgsqlite3backend_la_LIBADD)
endif
