#ifndef PDNS_LUA_AUTH_HH
#define PDNS_LUA_AUTH_HH
#include "pdns/common/dns.hh"
#include "pdns/common/iputils.hh"
#include "dnspacket.hh"
#include "pdns/authrec-common/lua-pdns.hh"
#include "pdns/common/lock.hh"

class AuthLua : public PowerDNSLua
{
public:
  explicit AuthLua(const std::string& fname);
  // ~AuthLua();
  bool axfrfilter(const ComboAddress& remote, const DNSName& zone, const DNSResourceRecord& in, vector<DNSResourceRecord>& out);
  DNSPacket* prequery(DNSPacket *p);
  int police(DNSPacket *req, DNSPacket *resp, bool isTcp=false);
  string policycmd(const vector<string>&parts);

private:
  void registerLuaDNSPacket(void);

  pthread_mutex_t d_lock;
};

#endif
