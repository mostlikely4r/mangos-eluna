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
     * Returns 'true' if the [Player] has an active [Quest] by specific ID, 'false' otherwise.
     *
     * @param string triggerName
     * @return bool hasTrigger
     */
    int HasTrigger(lua_State* L, PlayerbotAI* ai)
    {
        std::string triggerName = Eluna::CHECKVAL<std::string>(L, 2);

        bool hasTrigger = false;

        AiObjectContext* context = ai->GetAiObjectContext();

        if (AI_VALUE2(bool, "trigger active", triggerName))
            hasTrigger = true;
              
            Eluna::Push(L, hasTrigger);
        return 1;
    }
}
#endif //PLAYERBOTAIMETHODS_H
#endif //ENABLE_PLAYERBOTS
