AM_CPPFLAGS += \
	-I$(top_srcdir)/ext/rapidjson/include \
	$(YAHTTP_CFLAGS) \
	$(LIBZMQ_CFLAGS)

EXTRA_DIST += \
	auth/modules/remotebackend/testrunner.sh \
	auth/modules/remotebackend/unittest_http.rb \
	auth/modules/remotebackend/unittest_json.rb \
	auth/modules/remotebackend/unittest_pipe.rb \
	auth/modules/remotebackend/unittest_zeromq.rb \
	auth/modules/remotebackend/unittest_post.rb \
	auth/modules/remotebackend/unittest.rb \
	auth/modules/remotebackend/Gemfile \
	auth/modules/remotebackend/Gemfile.lock

libremotebackend_la_CPPFLAGS = $(AM_CPPFLAGS)
libremotebackend_la_SOURCES = \
	auth/modules/remotebackend/httpconnector.cc \
	auth/modules/remotebackend/pipeconnector.cc \
	auth/modules/remotebackend/remotebackend.cc \ auth/modules/remotebackend/remotebackend.hh \
	auth/modules/remotebackend/unixconnector.cc \
	auth/modules/remotebackend/zmqconnector.cc

libremotebackend_la_LDFLAGS = -module -avoid-version $(THREADFLAGS)
libremotebackend_la_LIBADD =

if REMOTEBACKEND_ZEROMQ
libremotebackend_la_LIBADD += \
	$(LIBZMQ_LIBS)
endif

if BUILD_AUTH_MODULE_REMOTE_DYNAMIC
pkglib_LTLIBRARIES += libremotebackend.la
else
EXTRA_LTLIBRARIES += libremotebackend.la
endif

if BUILD_AUTH_MODULE_REMOTE_STATIC
auth_common_sources += $(libremotebackend_la_SOURCES)
auth_common_ldflags += $(THREADFLAGS)
auth_common_ldadd += $(libremotebackend_la_LIBADD)
endif

############
## unit tests
############

if BUILD_AUTH_MODULE_REMOTE
EXTRA_PROGRAMS += \
	remotebackend_pipe.test \
	remotebackend_unix.test \
	remotebackend_http.test \
	remotebackend_post.test \
	remotebackend_json.test \
	remotebackend_zeromq.test

EXTRA_LTLIBRARIES += libtestremotebackend.la

# TESTS_ENVIRONMENT = \
# 	BOOST_TEST_LOG_LEVEL=message; \
# 	export BOOST_TEST_LOG_LEVEL; \
# 	REMOTEBACKEND_ZEROMQ=$(REMOTEBACKEND_ZEROMQ); \
# 	export REMOTEBACKEND_ZEROMQ;

# TEST_EXTENSIONS = .test

# TEST_LOG_COMPILER = $(abs_srcdir)/testrunner.sh

# RECHECK_LOGS = \
# 	$(TEST_LOGS) \
# 	remotebackend_http_server.log \
# 	remotebackend_post_server.log \
# 	remotebackend_json_server.log \
# 	remotebackend_zeromq_server.log

## The http, post and json test are using the same TCP port.
## To prevent "Address already in use - bind(2) (Errno::EADDRINUSE)"
## errors when running `make check` in parallel, we need to specify
## an order
remotebackend_post.log: remotebackend_http.log

remotebackend_json.log: remotebackend_http.log remotebackend_post.log

if BACKEND_UNIT_TESTS
TESTS += \
	remotebackend_pipe.test \
	remotebackend_unix.test \
	remotebackend_http.test \
	remotebackend_post.test \
	remotebackend_json.test \
	remotebackend_zeromq.test
endif

endif BUILD_AUTH_MODULE_REMOTE

############
## shared test code
############

testremotebackend_sources = \
	$(common_sources) \
	$(authrec_common_sources) \
	$(authrec_common_dnssec_sources) \
	$(auth_common_sources) \
	$(libremotebackend_la_SOURCES)

testremotebackend_ldflags = \
	$(AM_LDFLAGS) \
	$(common_ldflags) \
	$(authrec_common_ldflags) \
	$(authrec_common_dnssec_ldflags) \
	$(auth_common_ldflags) \
	$(libremotebackend_la_LIBADD) \
	$(BOOST_PROGRAM_OPTIONS_LDFLAGS)

testremotebackend_ldadd = \
	$(common_ldadd) \
	$(authrec_common_ldadd) \
	$(authrec_common_dnssec_ldadd) \
	$(auth_common_ldadd) \
	$(libremotebackend_la_LIBADD) \
	$(BOOST_SERIALIZATION_LIBS) \
	$(BOOST_PROGRAM_OPTIONS_LIBS)

############
## remotebackend_http.test
############

remotebackend_http_test_SOURCES = \
	$(testremotebackend_sources)
	test-remotebackend.cc \
	test-remotebackend-http.cc \
	test-remotebackend-keys.hh
remotebackend_http_test_LDFLAGS = $(testremotebackend_ldflags)
remotebackend_http_test_LDADD = $(testremotebackend_ldadd)

############
## remotebackend_json.test
############

remotebackend_json_test_SOURCES = \
	$(testremotebackend_sources)
	test-remotebackend.cc \
	test-remotebackend-json.cc \
	test-remotebackend-keys.hh
remotebackend_json_test_LDFLAGS = $(testremotebackend_ldflags)
remotebackend_json_test_LDADD = $(testremotebackend_ldadd)

############
## remotebackend_pipe.test
############

remotebackend_pipe_test_SOURCES = \
	$(testremotebackend_sources)
	test-remotebackend.cc \
	test-remotebackend-pipe.cc \
	test-remotebackend-keys.hh 
remotebackend_pipe_test_LDFLAGS = $(testremotebackend_ldflags)
remotebackend_pipe_test_LDADD = $(testremotebackend_ldadd)

############
## remotebackend_post.test
############

remotebackend_post_test_SOURCES = \
	$(testremotebackend_sources)
	test-remotebackend.cc \
	test-remotebackend-post.cc \
	test-remotebackend-keys.hh
remotebackend_post_test_LDFLAGS = $(testremotebackend_ldflags)
remotebackend_post_test_LDADD = $(testremotebackend_ldadd)

############
## remotebackend_unix.test
############

remotebackend_unix_test_SOURCES = \
	$(testremotebackend_sources)
	test-remotebackend.cc \
	test-remotebackend-unix.cc \
	test-remotebackend-keys.hh
remotebackend_unix_test_LDFLAGS = $(testremotebackend_ldflags)
remotebackend_unix_test_LDADD = $(testremotebackend_ldadd)

############
## remotebackend_zeromq.test
############

remotebackend_zeromq_test_SOURCES = \
	$(testremotebackend_sources)
	test-remotebackend.cc \
	test-remotebackend-zeromq.cc \
	test-remotebackend-keys.hh
remotebackend_zeromq_test_LDFLAGS = $(testremotebackend_ldflags)
remotebackend_zeromq_test_LDADD = $(testremotebackend_ldadd)
