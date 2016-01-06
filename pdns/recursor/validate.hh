#pragma once

#include "pdns/common/dnsparser.hh"
#include "pdns/common/dnsname.hh"
#include <vector>
#include "pdns/common/namespaces.hh"
#include "pdns/authrec-common/dnsrecords.hh"
 
// 4033 5
enum vState { Indeterminate, Bogus, Insecure, Secure };
extern const char *vStates[];

// NSEC(3) results
enum dState { NODATA, NXDOMAIN, ENT, INSECURE };
extern const char *dStates[];


class DNSRecordOracle
{
public:
  virtual std::vector<DNSRecord> get(const DNSName& qname, uint16_t qtype)=0;
};


struct ContentSigPair
{
  vector<shared_ptr<DNSRecordContent>> records;
  vector<shared_ptr<RRSIGRecordContent>> signatures;
  // ponder adding a validate method that accepts a key
};
typedef map<pair<DNSName,uint16_t>, ContentSigPair> cspmap_t;
void validateWithKeySet(const cspmap_t& rrsets, cspmap_t& validated, const std::set<DNSKEYRecordContent>& keys);
cspmap_t harvestCSPFromRecs(const vector<DNSRecord>& recs);
vState getKeysFor(DNSRecordOracle& dro, const DNSName& zone, std::set<DNSKEYRecordContent> &keyset);

