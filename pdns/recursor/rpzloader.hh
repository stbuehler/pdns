#pragma once
#include "pdns/authrec-common/filterpo.hh"
#include <string>
#include "pdns/authrec-common/dnsrecords.hh"

int loadRPZFromFile(const std::string& fname, DNSFilterEngine& target, boost::optional<DNSFilterEngine::Policy> defpol, int place);
std::shared_ptr<SOARecordContent> loadRPZFromServer(const ComboAddress& master, const DNSName& zone, DNSFilterEngine& target, boost::optional<DNSFilterEngine::Policy> defpol, int place);
void RPZRecordToPolicy(const DNSRecord& dr, DNSFilterEngine& target, bool addOrRemove, boost::optional<DNSFilterEngine::Policy> defpol, int place);
void RPZIXFRTracker(const ComboAddress& master, const DNSName& zone, shared_ptr<SOARecordContent> oursr);
