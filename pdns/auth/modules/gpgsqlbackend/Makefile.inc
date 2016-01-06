AM_CPPFLAGS += $(PGSQL_inc)

EXTRA_DIST += \
	auth/modules/gpgsqlbackend/dnssec-3.x_to_3.4.0_schema.pgsql.sql
	auth/modules/gpgsqlbackend/nodnssec-3.x_to_3.4.0_schema.pgsql.sql \
	auth/modules/gpgsqlbackend/schema.pgsql.sql

dist_doc_DATA += \
	auth/modules/gpgsqlbackend/schema.pgsql.sql \
	auth/modules/gpgsqlbackend/nodnssec-3.x_to_3.4.0_schema.pgsql.sql \
	auth/modules/gpgsqlbackend/dnssec-3.x_to_3.4.0_schema.pgsql.sql

libgpgsqlbackend_la_CPPFLAGS = $(AM_CPPFLAGS)
libgpgsqlbackend_la_SOURCES = \
	auth/modules/gpgsqlbackend/gpgsqlbackend.cc auth/modules/gpgsqlbackend/gpgsqlbackend.hh \
	auth/modules/gpgsqlbackend/spgsql.cc auth/modules/gpgsqlbackend/spgsql.hh

libgpgsqlbackend_la_LDFLAGS = -module -avoid-version
libgpgsqlbackend_la_LIBADD = \
	-lssl \
	-lcrypto \
	$(PGSQL_lib)

if BUILD_AUTH_MODULE_GPGSQL_DYNAMIC
pkglib_LTLIBRARIES += libgpgsqlbackend.la
else
EXTRA_LTLIBRARIES += libgpgsqlbackend.la
endif

if BUILD_AUTH_MODULE_GPGSQL_STATIC
auth_common_sources += $(libgpgsqlbackend_la_SOURCES)
auth_common_ldadd += $(libgpgsqlbackend_la_LIBADD)
endif
