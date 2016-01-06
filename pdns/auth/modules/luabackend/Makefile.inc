AM_CPPFLAGS += $(LUA_CFLAGS)

libluabackend_la_CPPFLAGS = $(AM_CPPFLAGS)
libluabackend_la_SOURCES = \
	auth/modules/luabackend/dnssec.cc \
	auth/modules/luabackend/lua_functions.cc auth/modules/luabackend/lua_functions.hh \
	auth/modules/luabackend/luabackend.cc auth/modules/luabackend/luabackend.hh \
	auth/modules/luabackend/master.cc \
	auth/modules/luabackend/minimal.cc \
	auth/modules/luabackend/private.cc \
	auth/modules/luabackend/reload.cc \
	auth/modules/luabackend/slave.cc \
	auth/modules/luabackend/supermaster.cc

libluabackend_la_LDFLAGS = -module -avoid-version
libluabackend_la_LIBADD = $(LUA_LIBS)

if BUILD_AUTH_MODULE_LUA_DYNAMIC
pkglib_LTLIBRARIES += libluabackend.la
else
EXTRA_LTLIBRARIES += libluabackend.la
endif

if BUILD_AUTH_MODULE_LUA_STATIC
auth_common_sources += $(libluabackend_la_SOURCES)
auth_common_ldadd += $(libluabackend_la_LIBADD)
endif
