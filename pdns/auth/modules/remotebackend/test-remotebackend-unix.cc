#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE unit

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <boost/test/unit_test.hpp>
#include <boost/assign/list_of.hpp>

#include <boost/tuple/tuple.hpp>
#include "pdns/common/namespaces.hh"
#include "pdns/common/dns.hh"
#include "pdns/auth/dnsbackend.hh"
#include "pdns/auth/dnspacket.hh"
#include "pdns/auth/ueberbackend.hh"
#include "pdns/common/pdnsexception.hh"
#include "pdns/authrec-common/logger.hh"
#include "pdns/authrec-common/arguments.hh"
#include "pdns/authrec-common/dnsrecords.hh"
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include "pdns/authrec-common/statbag.hh"
#include "pdns/authrec-common/packetcache.hh"

StatBag S;
PacketCache PC;
ArgvMap &arg()
{
  static ArgvMap arg;
  return arg;
};

class RemoteLoader
{
   public:
      RemoteLoader();
};

DNSBackend *be;

struct RemotebackendSetup {
    RemotebackendSetup()  {
	be = 0; 
	try {
		// setup minimum arguments
		::arg().set("module-dir")="./.libs";
                new RemoteLoader();
		BackendMakers().launch("remote");
                // then get us a instance of it 
                ::arg().set("remote-connection-string")="unix:path=/tmp/remotebackend.sock";
                ::arg().set("remote-dnssec")="yes";
                be = BackendMakers().all()[0];
		// load few record types to help out
		SOARecordContent::report();
		NSRecordContent::report();
                ARecordContent::report();
	} catch (PDNSException &ex) {
		BOOST_TEST_MESSAGE("Cannot start remotebackend: " << ex.reason );
	};
    }
    ~RemotebackendSetup()  {  }
};

BOOST_GLOBAL_FIXTURE( RemotebackendSetup );

