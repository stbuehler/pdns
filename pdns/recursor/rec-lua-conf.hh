#pragma once
#include "pdns/common/sholder.hh"
#include "pdns/authrec-common/sortlist.hh"
#include "pdns/authrec-common/filterpo.hh"

class LuaConfigItems
{
public:
  LuaConfigItems();
  SortList sortlist;
  DNSFilterEngine dfe;
  map<DNSName,DSRecordContent> dsAnchors;
};

extern GlobalStateHolder<LuaConfigItems> g_luaconfs;
