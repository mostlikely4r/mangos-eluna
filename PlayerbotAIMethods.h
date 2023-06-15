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
     * Returns [PlayerbotAI]s master [Player] object
     *
     * @return [Player] player
     */
    int GetMaster(lua_State* L, PlayerbotAI* ai)
    {
        Eluna::Push(L, ai->GetMaster());
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

#define ELUNA_AI_VALUE(TYPE, VALUE, QUALIFIER) \
    if (qualifier.empty())\
        Eluna::Push(L, AI_VALUE(TYPE, value));\
    else\
        Eluna::Push(L, AI_VALUE2(TYPE, value, qualifier))

    /**
     * Returns the specified AIVALUE for [PlayerbotAI]
     *
     * @param string type
     * @param string value
     * @param string qualifier = ""
     * @return <type> hasTrigger
     */
    int GetAIValue(lua_State* L, PlayerbotAI* ai)
    {
        std::string type = Eluna::CHECKVAL<std::string>(L, 2);
        std::string value = Eluna::CHECKVAL<std::string>(L, 3);
        std::string qualifier = Eluna::CHECKVAL<std::string>(L, 4, "");
        AiObjectContext* context = ai->GetAiObjectContext();
        if (type == "bool")
            ELUNA_AI_VALUE(bool, value, qualifier);
        else if (type == "uint8")
            ELUNA_AI_VALUE(uint8, value, qualifier);
        else if (type == "uint32")
            ELUNA_AI_VALUE(uint32, value, qualifier);
        else if (type == "float")
            ELUNA_AI_VALUE(float, value, qualifier);
        else if (type == "string")
            ELUNA_AI_VALUE(string, value, qualifier);
        else if (type == "Unit*")
            ELUNA_AI_VALUE(Unit*, value, qualifier);
        else if (type == "ObjectGuid")
            ELUNA_AI_VALUE(ObjectGuid, value, qualifier);
        else
            ELUNA_LOG_ERROR("[Eluna]: Error getting AI VALUE of unkown type `%s`.", type);

        return 1;
    }

    /**
     * Sends a specific chat command to [PlayerbotAI].
     *
     * @param string value
     */
    int ExecuteCommand(lua_State* L, PlayerbotAI* ai)
    {
        std::string command = Eluna::CHECKVAL<std::string>(L, 2);

        AiObjectContext* context = ai->GetAiObjectContext();

        ai->HandleCommand(CHAT_MSG_WHISPER, command, *ai->GetBot());

        return 1;
    }
}
#endif //PLAYERBOTAIMETHODS_H
#endif //ENABLE_PLAYERBOTS
