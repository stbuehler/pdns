AM_CPPFLAGS += $(CDB_CFLAGS)

libtinydnsbackend_la_CPPFLAGS = $(AM_CPPFLAGS)
libtinydnsbackend_la_SOURCES = \
	auth/modules/tinydnsbackend/cdb.cc auth/modules/tinydnsbackend/cdb.hh \
	auth/modules/tinydnsbackend/tinydnsbackend.cc auth/modules/tinydnsbackend/tinydnsbackend.hh

libtinydnsbackend_la_LDFLAGS = -module -avoid-version
libtinydnsbackend_la_LIBADD = $(CDB_LIBS)

if BUILD_AUTH_MODULE_TINYDNS_DYNAMIC
pkglib_LTLIBRARIES += libtinydnsbackend.la
else
EXTRA_LTLIBRARIES += libtinydnsbackend.la
endif

if BUILD_AUTH_MODULE_TINYDNS_STATIC
auth_common_sources += $(libtinydnsbackend_la_SOURCES)
auth_common_ldadd += $(libtinydnsbackend_la_LIBADD)
endif
