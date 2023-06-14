/*
* Copyright (C) 2010 - 2016 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/



#ifdef ENABLE_PLAYERBOTS
#include "playerbot.h"
#ifndef PLAYERBOTAIMETHODS_H
#define PLAYERBOTAIMETHODS_H

/***
 * Inherits all methods from: [Object], [WorldObject], [Unit], [Player]
 */
namespace LuaPlayerbotAI
{
    /**
     * Returns [PlayerbotAI]s [Player] object
     *
     * @return [Player] player
     */
    int GetBot(lua_State* L, PlayerbotAI* ai)
    {
        Eluna::Push(L, ai->GetBot());
        return 1;
    }

    /**
     * Returns 'true' if the trigger condition is currently true for [PlayerbotAI].
     *
     * @param string trigger
     * @return bool trigger active
     */
    int IsTriggerActive(lua_State* L, PlayerbotAI* ai)
    {
        std::string trigger = Eluna::CHECKVAL<std::string>(L, 2);

        AiObjectContext* context = ai->GetAiObjectContext();

        Eluna::Push(L, AI_VALUE2(bool, "trigger active", trigger));
        return 1;
    }

    /**
     * Returns the specified boolean value for [PlayerbotAI]
     *
     * @param string value
     * @return bool hasTrigger
     */
    int BoolValue(lua_State* L, PlayerbotAI* ai)
    {
        std::string value = Eluna::CHECKVAL<std::string>(L, 2);

        AiObjectContext* context = ai->GetAiObjectContext();

        Eluna::Push(L, AI_VALUE(bool, value));
        return 1;
    }
}
#endif //PLAYERBOTAIMETHODS_H
#endif //ENABLE_PLAYERBOTS
