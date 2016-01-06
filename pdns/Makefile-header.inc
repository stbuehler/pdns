AM_CXXFLAGS = \
	-DSYSCONFDIR=\"$(sysconfdir)\" \
	-DPKGLIBDIR=\"$(pkglibdir)\" \
	-DLOCALSTATEDIR=\"$(socketdir)\"

AM_LDFLAGS = \
	$(PROGRAM_LDFLAGS)

AM_LFLAGS = -i
AM_YFLAGS = -d --verbose --debug

if LUA
AM_CPPFLAGS +=$(LUA_CFLAGS)
endif

TESTS_ENVIRONMENT = env BOOST_TEST_LOG_LEVEL=message SRCDIR='$(srcdir)'

CLEANFILES =
EXTRA_DIST =
BUILT_SOURCES =
TESTS =
noinst_SCRIPTS =
sysconf_DATA =
EXTRA_PROGRAMS =
sbin_PROGRAMS =
bin_PROGRAMS =
check_PROGRAMS =
man_MANS =
EXTRA_LTLIBRARIES =
pkglib_LTLIBRARIES =
dist_doc_DATA =

if !UNIT_TESTS
check-local:
	@echo "Unit tests are not enabled"
	@echo "Run ./configure --enable-unit-tests"
endif
