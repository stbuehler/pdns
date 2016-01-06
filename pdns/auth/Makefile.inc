EXTRA_DIST += \
	auth/bind-dnssec.schema.sqlite3.sql \
	auth/named.conf.parsertest

CLEANFILES += \
	auth/*.gcda \
	auth/*.gcno \
	auth/*.gcov \
	auth/backends/gsql/gsqlbackend.gcda \
	auth/backends/gsql/gsqlbackend.gcno \
	auth/backends/gsql/gsqlbackend.gcov

noinst_SCRIPTS += auth/pdns.init
sysconf_DATA += auth/pdns.conf-dist

sbin_PROGRAMS += pdns_server
bin_PROGRAMS += pdnsutil pdns_control

# pdns_server and pdnsutil
auth_common_sources = \
	auth/bind-dnssec.schema.sqlite3.sql.h \
	auth/bindlexer.l \
	auth/bindparser.yy \
	auth/bindparserclasses.hh \
	auth/dbdnsseckeeper.cc \
	auth/dnsbackend.cc auth/dnsbackend.hh \
	auth/dnspacket.cc auth/dnspacket.hh \
	auth/dnssecsigner.cc \
	auth/dynlistener.cc auth/dynlistener.hh \
	auth/packetcache.cc auth/packetcache.hh \
	auth/serialtweaker.cc \
	auth/signingpipe.cc auth/signingpipe.hh \
	auth/ueberbackend.cc auth/ueberbackend.hh \
	auth/backends/gsql/gsqlbackend.cc auth/backends/gsql/gsqlbackend.hh \
	auth/backends/gsql/ssql.hh
auth_common_ldflags = \
	$(DYNLINKFLAGS)
auth_common_ldadd = \
	$(ORACLE_LIBS)

if SQLITE3
AM_CPPFLAGS += $(SQLITE3_CFLAGS)
auth_common_sources += \
	auth/ssqlite3.cc auth/ssqlite3.hh
auth_common_ldadd += \
	$(SQLITE3_LIBS)
endif

auth/bind-dnssec.schema.sqlite3.sql.h: auth/bind-dnssec.schema.sqlite3.sql
	@$(MKDIR_P) auth
	( echo 'static char sqlCreate[] __attribute__((unused))=' ; sed 's/$$/"/g' $< | sed 's/^/"/g'  ; echo ';' ) > $@

############
## modules
############

# static modules add themself to auth_common_{sources,ldflags,ldadd}

include $(srcdir)/auth/modules/Makefile.inc

############
## pdns_server
############

pdns_server_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	$(authrec_common_dnssec_sources) \
	$(authrec_common_lua_sources) \
	$(authrec_common_resolver_sources) \
	$(authrec_common_webserver_sources) \
	$(auth_common_sources) \
	auth/auth-carbon.cc \
	auth/common_startup.cc auth/common_startup.hh \
	auth/communicator.cc auth/communicator.hh \
	auth/distributor.hh \
	auth/dnsproxy.cc auth/dnsproxy.hh \
	auth/dnsseckeeper.hh \
	auth/dynhandler.cc auth/dynhandler.hh \
	auth/dynmessenger.cc auth/dynmessenger.hh \
	auth/lua-auth.cc auth/lua-auth.hh \
	auth/mastercommunicator.cc \
	auth/nameserver.cc auth/nameserver.hh \
	auth/packethandler.cc auth/packethandler.hh \
	auth/receiver.cc \
	auth/responsestats-auth.cc \
	auth/rfc2136handler.cc \
	auth/secpoll-auth.cc auth/secpoll-auth.hh \
	auth/slavecommunicator.cc \
	auth/tcpreceiver.cc auth/tcpreceiver.hh \
	auth/tkey.cc \
	auth/unix_semaphore.cc \
	auth/ws-auth.cc auth/ws-auth.hh

pdns_server_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(common_ldflags) \
	$(authrec_common_ldflags) \
	$(authrec_common_dnssec_ldflags) \
	$(authrec_common_lua_ldflags) \
	$(authrec_common_resolver_ldflags) \
	$(authrec_common_webserver_ldflags) \
	$(auth_common_ldflags)

pdns_server_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd) \
	$(authrec_common_dnssec_ldadd) \
	$(authrec_common_lua_ldadd) \
	$(authrec_common_resolver_ldadd) \
	$(authrec_common_webserver_ldadd) \
	$(auth_common_ldadd)

############
## pdnsutil
############

pdnsutil_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	$(authrec_common_dnssec_sources) \
	$(auth_common_sources) \
	auth/tool-pdnsutil.cc

pdnsutil_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(common_ldflags) \
	$(authrec_common_ldflags) \
	$(authrec_common_dnssec_ldflags) \
	$(auth_common_ldflags) \
	$(BOOST_PROGRAM_OPTIONS_LDFLAGS)

pdnsutil_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd) \
	$(authrec_common_dnssec_ldadd) \
	$(auth_common_ldadd) \
	$(BOOST_PROGRAM_OPTIONS_LIBS)

############
## pdns_control
############

pdns_control_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	auth/dynmessenger.cc \
	auth/tool-pdns_control.cc

pdns_control_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(common_ldflags) \
	$(authrec_common_ldflags)

pdns_control_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd)

############
## unit tests
############

if UNIT_TESTS
check_PROGRAMS += auth_testrunner
TESTS += auth_testrunner
endif

auth_testrunner_SOURCES = \
	$(common_sources) \
	$(common_test_sources) \
	$(authrec_common_sources) \
	$(authrec_common_dnssec_sources) \
	$(authrec_common_test_sources) \
	$(auth_common_sources) \
	auth/nameserver.cc auth/nameserver.hh \
	auth/responsestats-auth.cc \
	auth/test-bindparser_cc.cc \
	auth/test-distributor_hh.cc \
	auth/test-nameserver_cc.cc \
	auth/test-packetcache_cc.cc \
	auth/testrunner.cc

auth_testrunner_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(common_ldflags) \
	$(common_test_ldflags) \
	$(authrec_common_ldflags) \
	$(authrec_common_dnssec_ldflags) \
	$(authrec_common_test_ldflags) \
	$(auth_common_ldflags) \
	$(BOOST_UNIT_TEST_FRAMEWORK_LDFLAGS)

auth_testrunner_LDADD = \
	$(common_ldadd) \
	$(common_test_ldadd) \
	$(authrec_common_ldadd) \
	$(authrec_common_dnssec_ldadd) \
	$(authrec_common_test_ldadd) \
	$(auth_common_ldadd) \
	$(BOOST_UNIT_TEST_FRAMEWORK_LIBS)

############
###### Tools
############

############
## zone2sql
############

bin_PROGRAMS += zone2sql

zone2sql_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	auth/bind-dnssec.schema.sqlite3.sql.h \
	auth/bindlexer.l \
	auth/bindparser.yy \
	auth/bindparserclasses.hh \
	auth/tool-zone2sql.cc

zone2sql_LDFLAGS = \
	$(common_ldflags) \
	$(authrec_common_ldflags)

zone2sql_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd)

############
## zone2json
############

bin_PROGRAMS += zone2json

zone2json_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	auth/bind-dnssec.schema.sqlite3.sql.h \
	auth/bindlexer.l \
	auth/bindparser.yy \
	auth/bindparserclasses.hh \
	auth/tool-zone2json.cc

zone2json_LDFLAGS = \
	$(common_ldflags) \
	$(authrec_common_ldflags)

zone2json_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd)

############
## zone2ldap
############

if LDAP
bin_PROGRAMS += zone2ldap
endif

zone2ldap_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	auth/bind-dnssec.schema.sqlite3.sql.h \
	auth/bindlexer.l \
	auth/bindparser.yy \
	auth/bindparserclasses.hh \
	auth/tool-zone2ldap.cc

zone2ldap_LDFLAGS = \
	$(common_ldflags) \
	$(authrec_common_ldflags)

zone2ldap_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd)
