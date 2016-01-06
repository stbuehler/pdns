#include "config.h"

#include "pdns/common/namespaces.hh"
#include "rec-lua-conf.hh"

GlobalStateHolder<LuaConfigItems> g_luaconfs;

LuaConfigItems::LuaConfigItems()
{
  auto ds=std::unique_ptr<DSRecordContent>(dynamic_cast<DSRecordContent*>(DSRecordContent::make("19036 8 2 49aac11d7b6f6446702e54a1607371607a1a41855200fd2ce1cdde32f24e8fb5")));
  // this hurts physically
  dsAnchors[DNSName(".")] = *ds;
}
