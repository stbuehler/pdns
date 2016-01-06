AM_CPPFLAGS += \
	-I$(top_srcdir)/ext/json11 \
	$(MBEDTLS_CFLAGS)

EXTRA_DIST += \
	common/dnslabeltext.rl \
	common/dnslabeltext.cc

BUILT_SOURCES += \
	common/dnslabeltext.cc

common/dnslabeltext.cc: common/dnslabeltext.rl
	@$(MKDIR_P) common
	$(AM_V_GEN)$(RAGEL) $< -o $@

common_sources = \
	common/base32.cc common/base32.hh \
	common/base64.cc common/base64.hh \
	common/delaypipe_impl.hh common/delaypipe.hh \
	common/dns.cc common/dns.hh \
	common/dnscrypt.cc common/dnscrypt.hh \
	common/dnslabeltext.cc \
	common/dnsname.cc common/dnsname.hh \
	common/dnsparser.cc common/dnsparser.hh \
	common/dnswriter.cc common/dnswriter.hh \
	common/dolog.hh \
	common/ednssubnet.cc common/ednssubnet.hh \
	common/iputils.cc common/iputils.hh \
	common/lock.hh \
	common/mbedtlscompat.hh \
	common/misc.cc common/misc.hh \
	common/namespaces.hh \
	common/pdnsexception.hh \
	common/qtype.cc common/qtype.hh \
	common/sholder.hh \
	common/sodcrypto.cc common/sodcrypto.hh \
	common/sstuff.hh
EXTRA_DIST += $(common_sources)
common_ldflags = \
	$(THREADFLAGS)
common_ldadd = \
	$(MBEDTLS_LIBS) \
	$(JSON11_LIBS) \
	$(RT_LIBS)

common_test_sources = \
	common/test-base32_cc.cc \
	common/test-base64_cc.cc \
	common/test-delaypipe_hh.cc \
	common/test-dnscrypt_cc.cc \
	common/test-iputils_hh.cc \
	common/test-misc_hh.cc \
	common/test-nmtree.cc \
	common/test-sholder_hh.cc
EXTRA_DIST += $(common_test_sources)
common_test_ldflags =
common_test_ldadd =
