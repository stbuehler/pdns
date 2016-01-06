AM_CPPFLAGS += \
	$(YAHTTP_CFLAGS)

if GSS_TSIG
AM_CPPFLAGS += \
	$(GSS_CFLAGS)
endif

authrec_common_sources = \
	authrec-common/arguments.cc authrec-common/arguments.hh \
	authrec-common/cachecleaner.hh \
	authrec-common/comment.hh \
	authrec-common/dns_random.cc authrec-common/dns_random.hh \
	authrec-common/dnsrecords.cc authrec-common/dnsrecords.hh \
	authrec-common/filterpo.cc authrec-common/filterpo.hh \
	authrec-common/inflighter.hh \
	authrec-common/ixfr.cc authrec-common/ixfr.hh \
	authrec-common/json.cc authrec-common/json.hh \
	authrec-common/logger.cc authrec-common/logger.hh \
	authrec-common/md5.hh \
	authrec-common/mtasker_impl.hh authrec-common/mtasker.hh \
	authrec-common/nsecrecords.cc \
	authrec-common/randomhelper.cc \
	authrec-common/rcpgenerator.cc authrec-common/rcpgenerator.hh \
	authrec-common/sha.hh \
	authrec-common/sillyrecords.cc \
	authrec-common/sortlist.cc authrec-common/sortlist.hh \
	authrec-common/statbag.cc authrec-common/statbag.hh \
	authrec-common/unix_utility.cc \
	authrec-common/utility.hh \
	authrec-common/version.cc authrec-common/version.hh \
	authrec-common/zoneparser-tng.cc authrec-common/zoneparser-tng.hh
EXTRA_DIST += $(authrec_common_sources)
authrec_common_ldflags = \
	-L$(top_builddir)/ext/json11
authrec_common_ldadd = \
	-ljson11

authrec_common_dnssec_sources = \
	authrec-common/dnssecinfra.cc authrec-common/dnssecinfra.hh \
	authrec-common/gss_context.cc authrec-common/gss_context.hh \
	authrec-common/mbedtlssigners.cc \
	authrec-common/responsestats.cc authrec-common/responsestats.hh
EXTRA_DIST += $(authrec_common_dnssec_sources)
authrec_common_dnssec_ldflags =
authrec_common_dnssec_ldadd = \
	$(GSS_LIBS) \
	$(LIBDL)

# requires dnssec in turn
authrec_common_resolver_sources = \
	authrec-common/resolver.cc authrec-common/resolver.hh
EXTRA_DIST += $(authrec_common_resolver_sources)
authrec_common_resolver_ldflags =
authrec_common_resolver_ldadd =

authrec_common_lua_sources = \
	authrec-common/lua-iputils.cc \
	authrec-common/lua-pdns.cc authrec-common/lua-pdns.hh
EXTRA_DIST += $(authrec_common_lua_sources)
authrec_common_lua_ldflags =
authrec_common_lua_ldadd = \
	$(LUA_LIBS)

authrec_common_webserver_sources = \
	authrec-common/webserver.cc authrec-common/webserver.hh \
	authrec-common/ws-api.cc authrec-common/ws-api.hh
EXTRA_DIST += $(authrec_common_webserver_sources)
authrec_common_webserver_ldflags =
authrec_common_webserver_ldadd = \
	$(YAHTTP_LIBS)

authrec_common_test_sources = \
	authrec-common/test-arguments_cc.cc \
	authrec-common/test-dns_random_hh.cc \
	authrec-common/test-dnsname_cc.cc \
	authrec-common/test-dnsrecords_cc.cc \
	authrec-common/test-md5_hh.cc \
	authrec-common/test-rcpgenerator_cc.cc \
	authrec-common/test-sha_hh.cc \
	authrec-common/test-statbag_cc.cc \
	authrec-common/test-zoneparser_tng_cc.cc
EXTRA_DIST += $(authrec_common_test_sources)
authrec_common_test_ldflags =
authrec_common_test_ldadd =

############
## Signers
############

## Botan110
## --------

botan110_signer_sources = \
	authrec-common/botan110signers.cc \
	authrec-common/botansigners.cc

EXTRA_DIST += $(botan110_signer_sources)
if BOTAN110
AM_CPPFLAGS += $(BOTAN110_CFLAGS)
authrec_common_dnssec_sources += $(botan110_signer_sources)
authrec_common_dnssec_ldadd += $(BOTAN110_LIBS)
endif

## CryptoPP
## --------

cryptopp_signer_sources = \
	authrec-common/cryptoppsigners.cc

EXTRA_DIST += $(cryptopp_signer_sources)
if CRYPTOPP
authrec_common_dnssec_sources += $(cryptopp_signer_sources)
authrec_common_dnssec_ldadd += $(CRYPTOPP_LIBS)
endif

## openssl
## --------

openssl_signer_sources = \
	authrec-common/opensslsigners.cc authrec-common/opensslsigners.hh

EXTRA_DIST += $(openssl_signer_sources)
if OPENSSL
authrec_common_dnssec_sources += $(openssl_signer_sources)
authrec_common_dnssec_ldflags += $(OPENSSL_LDFLAGS)
authrec_common_dnssec_ldadd += $(OPENSSL_LIBS)
endif

## pkcs11
## --------

pkcs11_signer_sources = \
	authrec-common/pkcs11signers.cc authrec-common/pkcs11signers.hh

EXTRA_DIST += $(pkcs11_signer_sources)
if PKCS11
AM_CPPFLAGS += $(P11KIT1_CFLAGS)
authrec_common_dnssec_sources += $(pkcs11_signer_sources)
authrec_common_dnssec_ldadd += $(P11KIT1_LIBS)
endif

## sodium
## --------

sodium_signer_sources = \
	authrec-common/sodiumsigners.cc

EXTRA_DIST += $(sodium_signer_sources)
if LIBSODIUM
authrec_common_dnssec_sources += $(sodium_signer_sources)
authrec_common_dnssec_ldadd += $(LIBSODIUM_LIBS)
endif

############
## /Signers
############
