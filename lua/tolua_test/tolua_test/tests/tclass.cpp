extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "tclass.h"

//Test::Tst_A* Test::Tst_A::last;
//Test::Tst_B* Test::Tst_B::last;
//Test::Tst_C* Test::Tst_C::last;


int  tolua_tclass_open (lua_State*);

int run_tclass (lua_State* L)
{
	Test::Tst_B* b = new Test::Tst_B;         // instance used in Lua code

	luaL_openlibs(L);
	tolua_tclass_open(L);

	luaL_dofile(L,"tclass.lua");

	delete b;
	return 0;
}

