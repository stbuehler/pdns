noinst_SCRIPTS += recursor/pdns-recursor.init.d

sbin_PROGRAMS += pdns_recursor
bin_PROGRAMS += rec_control

EXTRA_DIST += \
	recursor/effective_tld_names.dat \
	recursor/pubsuffix.cc

curl_verbose = $(curl_verbose_$(V))
curl_verbose_ = $(curl_verbose_$(AM_DEFAULT_VERBOSITY))
curl_verbose_0 = @echo "  CURL    " $@;
recursor/effective_tld_names.dat:
	$(curl_verbose)if ! curl -s https://publicsuffix.org/list/public_suffix_list.dat > $@; then rm -f $@; exit 1; fi

recursor/pubsuffix.cc: recursor/effective_tld_names.dat
	$(AM_V_GEN)$(srcdir)/recursor/mkpubsuffixcc <$< >$@

############
## event queues (multiplexer)
############

mplexer_sources = \
	recursor/mplexer.hh \
	recursor/selectmplexer.cc
#	recursor/pollmplexer.cc
mplexer_ldflags =
mplexer_ldadd =

if HAVE_FREEBSD
mplexer_sources += \
	recursor/kqueuemplexer.cc
endif

if HAVE_LINUX
mplexer_sources += \
	recursor/epollmplexer.cc
endif

if HAVE_SOLARIS
mplexer_sources += \
	recursor/devpollmplexer.cc \
	recursor/portsmplexer.cc
endif

############
## /event queues (multiplexer)
############

############
## pdns_recursor
############

pdns_recursor_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	$(authrec_common_dnssec_sources) \
	$(authrec_common_lua_sources) \
	$(authrec_common_resolver_sources) \
	$(authrec_common_webserver_sources) \
	$(mplexer_sources) \
	recursor/lua-recursor.cc recursor/lua-recursor.hh \
	recursor/lua-recursor4.cc recursor/lua-recursor4.hh \
	recursor/lwres.cc recursor/lwres.hh \
	recursor/malloctrace.cc recursor/malloctrace.hh \
	recursor/pdns_recursor.cc \
	recursor/pubsuffix.cc recursor/pubsuffix.hh \
	recursor/rec-carbon.cc \
	recursor/rec-lua-conf.cc recursor/rec-lua-conf.hh \
	recursor/rec-lua-conf-loader.cc recursor/rec-lua-conf-loader.hh \
	recursor/rec_channel.cc recursor/rec_channel.hh \
	recursor/rec_channel_rec.cc \
	recursor/recpacketcache.cc recursor/recpacketcache.hh \
	recursor/recursor_cache.cc recursor/recursor_cache.hh \
	recursor/reczones.cc \
	recursor/rpzloader.cc recursor/rpzloader.hh \
	recursor/secpoll-recursor.cc recursor/secpoll-recursor.hh \
	recursor/syncres.cc recursor/syncres.hh \
	recursor/validate-recursor.cc recursor/validate-recursor.hh \
	recursor/validate.cc recursor/validate.hh \
	recursor/ws-recursor.cc recursor/ws-recursor.hh

pdns_recursor_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(common_ldflags) \
	$(authrec_common_ldflags) \
	$(authrec_common_dnssec_ldflags) \
	$(authrec_common_lua_ldflags) \
	$(authrec_common_resolver_ldflags) \
	$(authrec_common_webserver_ldflags) \
	$(mplexer_ldflags)

pdns_recursor_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd) \
	$(authrec_common_dnssec_ldadd) \
	$(authrec_common_lua_ldadd) \
	$(authrec_common_resolver_ldadd) \
	$(authrec_common_webserver_ldadd) \
	$(mplexer_ldadd)

############
## rec_control
############

rec_control_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	recursor/rec_channel.cc recursor/rec_channel.hh \
	recursor/tool-rec_control.cc

rec_control_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(common_ldflags) \
	$(authrec_common_ldflags)

rec_control_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd)

############
## unit tests
############

if UNIT_TESTS
check_PROGRAMS += pdns_hw
TESTS += pdns_hw
endif

pdns_hw_SOURCES = \
	recursor/test-pdns_hw.cc

############
###### Tools
############

############
## notify
############

if TOOLS
bin_PROGRAMS += notify
endif

notify_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	$(mplexer_sources) \
	recursor/tool-notify.cc

notify_LDFLAGS = \
	$(common_ldflags) \
	$(authrec_common_ldflags) \
	$(mplexer_ldflags) \
	$(BOOST_PROGRAM_OPTIONS_LDFLAGS)

notify_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd) \
	$(mplexer_ldadd) \
	$(BOOST_PROGRAM_OPTIONS_LIBS)

############
## nproxy
############

if TOOLS
bin_PROGRAMS += nproxy
endif

nproxy_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	$(mplexer_sources) \
	recursor/tool-nproxy.cc

nproxy_LDFLAGS = \
	$(common_ldflags) \
	$(authrec_common_ldflags) \
	$(mplexer_ldflags) \
	$(BOOST_PROGRAM_OPTIONS_LDFLAGS)

nproxy_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd) \
	$(mplexer_ldadd) \
	$(BOOST_PROGRAM_OPTIONS_LIBS)

############
## toysdig
############

EXTRA_PROGRAMS += toysdig

toysdig_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	$(authrec_common_dnssec_sources) \
	recursor/rec-lua-conf.cc recursor/rec-lua-conf.hh \
	recursor/validate.cc recursor/validate.hh \
	recursor/tool-toysdig.cc

toysdig_LDFLAGS = \
	$(common_ldflags) \
	$(authrec_common_ldflags) \
	$(authrec_common_dnssec_ldflags)

toysdig_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd) \
	$(authrec_common_dnssec_ldadd) \
	$(LUA_LIBS)
