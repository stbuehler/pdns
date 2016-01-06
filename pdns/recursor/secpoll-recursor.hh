#ifndef PDNS_SECPOLL_RECURSOR_HH
#define PDNS_SECPOLL_RECURSOR_HH
#include <time.h>
#include "pdns/common/namespaces.hh"
#include <stdint.h>

void doSecPoll(time_t* );
extern uint32_t g_security_status;
extern std::string g_security_message;

#endif
