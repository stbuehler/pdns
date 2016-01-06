############
## calidns
############

if TOOLS
if HAVE_RECVMMSG
bin_PROGRAMS += calidns
endif
endif

calidns_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	tools/tool-calidns.cc

calidns_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(common_ldflags) \
	$(authrec_common_ldflags)

calidns_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd)

############
## dnsbulktest
############

if TOOLS
bin_PROGRAMS += dnsbulktest
endif

dnsbulktest_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	tools/tool-dnsbulktest.cc

dnsbulktest_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(common_ldflags) \
	$(authrec_common_ldflags) \
	$(BOOST_PROGRAM_OPTIONS_LDFLAGS)

dnsbulktest_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd) \
	$(BOOST_PROGRAM_OPTIONS_LIBS)

############
## dnsdemog
############

EXTRA_PROGRAMS += dnsdemog

dnsdemog_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	tools/anadns.hh \
	tools/dnspcap.cc tools/dnspcap.hh \
	tools/tool-dnsdemog.cc

dnsdemog_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(common_ldflags) \
	$(authrec_common_ldflags)

dnsdemog_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd)

############
## dnsgram
############

if TOOLS
bin_PROGRAMS += dnsgram
endif

dnsgram_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	tools/anadns.hh \
	tools/dnspcap.cc tools/dnspcap.hh \
	tools/tool-dnsgram.cc

dnsgram_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(common_ldflags) \
	$(authrec_common_ldflags)

dnsgram_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd)

############
## dnsreplay
############

if TOOLS
bin_PROGRAMS += dnsreplay
endif

dnsreplay_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	tools/anadns.hh \
	tools/dnspcap.cc tools/dnspcap.hh \
	tools/tool-dnsreplay.cc

dnsreplay_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(common_ldflags) \
	$(authrec_common_ldflags) \
	$(BOOST_PROGRAM_OPTIONS_LDFLAGS)

dnsreplay_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd) \
	$(BOOST_PROGRAM_OPTIONS_LIBS)

############
## dnsscan
############

if TOOLS
bin_PROGRAMS += dnsscan
endif

dnsscan_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	tools/anadns.hh \
	tools/dnspcap.cc tools/dnspcap.hh \
	tools/tool-dnsscan.cc

dnsscan_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(common_ldflags) \
	$(authrec_common_ldflags)

dnsscan_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd)

############
## dnsscope
############

if TOOLS
bin_PROGRAMS += dnsscope
endif

dnsscope_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	tools/anadns.hh \
	tools/dnspcap.cc tools/dnspcap.hh \
	tools/tool-dnsscope.cc

dnsscope_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(common_ldflags) \
	$(authrec_common_ldflags) \
	$(BOOST_PROGRAM_OPTIONS_LDFLAGS)

dnsscope_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd) \
	$(BOOST_PROGRAM_OPTIONS_LIBS)

############
## dnstcpbench
############

if TOOLS
bin_PROGRAMS += dnstcpbench
endif

dnstcpbench_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	tools/tool-dnstcpbench.cc

dnstcpbench_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(common_ldflags) \
	$(authrec_common_ldflags) \
	$(BOOST_PROGRAM_OPTIONS_LDFLAGS)

dnstcpbench_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd) \
	$(BOOST_PROGRAM_OPTIONS_LIBS)

############
## dnswasher
############

if TOOLS
bin_PROGRAMS += dnswasher
endif

dnswasher_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	tools/dnspcap.cc tools/dnspcap.hh \
	tools/tool-dnswasher.cc

dnswasher_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(common_ldflags) \
	$(authrec_common_ldflags)

dnswasher_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd)

############
## dumresp
############

if TOOLS
bin_PROGRAMS += dumresp
endif

dumresp_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	tools/tool-dumresp.cc

dumresp_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(common_ldflags) \
	$(authrec_common_ldflags)
dumresp_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd)

############
## ixplore
############

if TOOLS
bin_PROGRAMS += ixplore
endif

ixplore_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	$(authrec_common_dnssec_sources) \
	$(authrec_common_resolver_sources) \
	tools/tool-ixplore.cc

ixplore_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(common_ldflags) \
	$(authrec_common_ldflags) \
	$(authrec_common_dnssec_ldflags) \
	$(authrec_common_resolver_ldflags)
ixplore_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd) \
	$(authrec_common_dnssec_ldadd) \
	$(authrec_common_resolver_ldadd)

############
## kvresp
############

EXTRA_PROGRAMS += kvresp

EXTRA_DIST += \
	tools/kv-example-script.lua

kvresp_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	tools/tool-kvresp.cc

kvresp_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(common_ldflags) \
	$(authrec_common_ldflags)

kvresp_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd)

############
## nsec3dig
############

if TOOLS
bin_PROGRAMS += nsec3dig
endif

nsec3dig_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	$(authrec_common_dnssec_sources) \
	tools/tool-nsec3dig.cc

nsec3dig_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(common_ldflags) \
	$(authrec_common_ldflags) \
	$(authrec_common_dnssec_ldflags)
nsec3dig_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd) \
	$(authrec_common_dnssec_ldadd)

############
## saxfr
############

if TOOLS
bin_PROGRAMS += saxfr
endif

saxfr_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	$(authrec_common_dnssec_sources) \
	tools/tool-saxfr.cc

saxfr_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(common_ldflags) \
	$(authrec_common_ldflags) \
	$(authrec_common_dnssec_ldflags)
saxfr_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd) \
	$(authrec_common_dnssec_ldadd)

############
## sdig
############

if TOOLS
bin_PROGRAMS += sdig
endif

sdig_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	tools/tool-sdig.cc

sdig_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(common_ldflags) \
	$(authrec_common_ldflags)

sdig_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd)

############
## speedtest
############

EXTRA_PROGRAMS += speedtest

speedtest_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	tools/tool-speedtest.cc

speedtest_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(common_ldflags) \
	$(authrec_common_ldflags)

speedtest_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd)

############
## tsig_tests
############

EXTRA_PROGRAMS += tsig_tests

tsig_tests_SOURCES = \
	$(common_sources) \
	$(authrec_common_sources) \
	$(authrec_common_dnssec_sources) \
	$(authrec_common_resolver_sources) \
	tools/tool-tsig-tests.cc

tsig_tests_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(common_ldflags) \
	$(authrec_common_ldflags) \
	$(authrec_common_dnssec_ldflags) \
	$(authrec_common_resolver_ldflags)
tsig_tests_LDADD = \
	$(common_ldadd) \
	$(authrec_common_ldadd) \
	$(authrec_common_dnssec_ldadd) \
	$(authrec_common_resolver_ldadd)
