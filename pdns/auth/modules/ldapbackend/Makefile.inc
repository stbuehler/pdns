EXTRA_DIST += \
	auth/modules/ldapbackend/dns.ldif

libldapbackend_la_CPPFLAGS = $(AM_CPPFLAGS)
libldapbackend_la_SOURCES = \
	auth/modules/ldapbackend/ldapbackend.cc auth/modules/ldapbackend/ldapbackend.hh \
	auth/modules/ldapbackend/powerldap.cc auth/modules/ldapbackend/powerldap.hh \
	auth/modules/ldapbackend/utils.hh

libldapbackend_la_LDFLAGS = -module -avoid-version
libldapbackend_la_LIBADD = \
	$(LDAP_LIBS)

if BUILD_AUTH_MODULE_LDAP_DYNAMIC
pkglib_LTLIBRARIES += libldapbackend.la
else
EXTRA_LTLIBRARIES += libldapbackend.la
endif

if BUILD_AUTH_MODULE_LDAP_STATIC
auth_common_sources += $(libldapbackend_la_SOURCES)
auth_common_ldadd += $(libldapbackend_la_LIBADD)
endif
