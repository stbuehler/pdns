AM_CPPFLAGS += $(YAML_CFLAGS) $(GEOIP_CFLAGS)

libgeoipbackend_la_CPPFLAGS = $(AM_CPPFLAGS)
libgeoipbackend_la_SOURCES = \
	auth/modules/geoipbackend/geoipbackend.cc auth/modules/geoipbackend/geoipbackend.hh

libgeoipbackend_la_LDFLAGS = -module -avoid-version
libgeoipbackend_la_LIBADD = \
	$(YAML_LIBS) \
	$(GEOIP_LIBS)

if BUILD_AUTH_MODULE_GEOIP_DYNAMIC
pkglib_LTLIBRARIES += libgeoipbackend.la
else
EXTRA_LTLIBRARIES += libgeoipbackend.la
endif

if BUILD_AUTH_MODULE_GEOIP_STATIC
auth_common_sources += $(libgeoipbackend_la_SOURCES)
auth_common_ldadd += $(libgeoipbackend_la_LIBADD)
endif
