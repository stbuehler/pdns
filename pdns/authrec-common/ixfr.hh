#include "pdns/common/namespaces.hh"
#include "pdns/common/iputils.hh"
#include "pdns/common/dnsparser.hh"

vector<pair<vector<DNSRecord>, vector<DNSRecord> > >   getIXFRDeltas(const ComboAddress& master, const DNSName& zone, const DNSRecord& sr);
