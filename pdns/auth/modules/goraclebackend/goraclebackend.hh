#ifndef PDNS_GORACLEBACKEND_HH
#define PDNS_GORACLEBACKEND_HH

#include <string>
#include <map>
#include "pdns/auth/backends/gsql/gsqlbackend.hh"

#include "pdns/common/namespaces.hh"

/** The gOracleBackend is a DNSBackend that can answer DNS related questions. It looks up data
    in PostgreSQL */
class gOracleBackend : public GSQLBackend
{
public:
  gOracleBackend(const string &mode, const string &suffix); //!< Makes our connection to the database. Throws an exception if it fails.
};

#endif /* PDNS_GORACLEBACKEND_HH */
