AM_CPPFLAGS += \
	$(YAHTTP_CFLAGS) \
	$(SANITIZER_FLAGS)

# AM_CPPFLAGS = -O3 -Wall

BUILT_SOURCES += \
	dns-dist/htmlfiles.h

dns-dist/htmlfiles.h:
	${srcdir}/dns-dist/incfiles ${srcdir}/dns-dist > $@

man_MANS += \
	dns-dist/dnsdist.1

dns-dist/dnsdist.1: ../docs/manpages/dnsdist.1.md
	pandoc -s -t man $< > $@

EXTRA_DIST += \
	dns-dist/dnsdistconf.lua \
	dns-dist/README.md \
	dns-dist/introduction.md \
	dns-dist/incfiles \
	dns-dist/html \
	dns-dist/dnsdist.1 \
	dns-dist/contrib

bin_PROGRAMS += dnsdist

dnsdist_SOURCES = \
	$(common_sources) \
	dns-dist/dnsdist-carbon.cc \
	dns-dist/dnsdist-console.cc \
	dns-dist/dnsdist-dnscrypt.cc \
	dns-dist/dnsdist-ecs.cc dns-dist/dnsdist-ecs.hh \
	dns-dist/dnsdist-lua.cc \
	dns-dist/dnsdist-lua2.cc \
	dns-dist/dnsdist-rings.cc \
	dns-dist/dnsdist-tcp.cc \
	dns-dist/dnsdist-web.cc \
	dns-dist/dnsrulactions.hh \
	dns-dist/dnsdist.cc dns-dist/dnsdist.hh \
	dns-dist/htmlfiles.h

dnsdist_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(common_ldflags) \
	-L$(top_builddir)/ext/json11

dnsdist_LDADD = \
	$(common_ldadd) \
	$(READLINE_LIBS) \
	$(LUA_LIBS) \
	$(YAHTTP_LIBS) \
	$(LIBSODIUM_LIBS) \
	$(SANITIZER_FLAGS) \
	-ljson11

if UNIT_TESTS
check_PROGRAMS += dnsdist_testrunner
TESTS += dnsdist_testrunner
endif

dnsdist_testrunner_SOURCES = \
	$(common_sources) \
	$(common_test_sources) \
	dns-dist/dnsdist-ecs.cc dns-dist/dnsdist-ecs.hh \
	dns-dist/dnsdist.hh \
	dns-dist/test-dnsdist_cc.cc \
	dns-dist/testrunner.cc

dnsdist_testrunner_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(common_ldflags) \
	$(common_test_ldflags) \
	$(BOOST_UNIT_TEST_FRAMEWORK_LDFLAGS)

dnsdist_testrunner_LDADD = \
	$(common_ldadd) \
	$(common_test_ldadd) \
	$(BOOST_UNIT_TEST_FRAMEWORK_LIBS) \
	$(LIBSODIUM_LIBS) \
	$(RT_LIBS) \
	$(SANITIZER_FLAGS)
