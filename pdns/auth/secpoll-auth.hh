#ifndef PDNS_SECPOLL_AUTH_HH
#define PDNS_SECPOLL_AUTH_HH
#include <time.h>
#include "pdns/common/namespaces.hh"

void doSecPoll(bool first);
void secPollParseResolveConf();
extern std::string g_security_message;

#endif
