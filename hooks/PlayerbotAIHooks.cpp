/*
 * Copyright (C) 2010 - 2016 Eluna Lua Engine <http://emudevs.com/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */
#ifdef ENABLE_PLAYERBOTS
#include "Hooks.h"
#include "HookHelpers.h"
#include "LuaEngine.h"
#include "BindingMap.h"
#include "ElunaIncludes.h"
#include "ElunaTemplate.h"
#include "ElunaLoader.h"
using namespace Hooks;

#define START_HOOK(EVENT, QUALIFIER) \
    auto key = StringKey<PlayerbotAIEvents>(EVENT, QUALIFIER);\
    if (!PlayerbotAIEventBindings->HasBindingsFor(key))\
        return;\

#define START_HOOK_WITH_RETVAL(EVENT, QUALIFIER, RETVAL) \
    auto key = String<PlayerbotAIEvents>(EVENT, QUALIFIER);\
    if (!PlayerbotAIEventBindings->HasBindingsFor(key))\
        return RETVAL;\
   
void Eluna::OnUpdateAI(PlayerbotAI* ai, std::string botName)
{
    START_HOOK(PLAYERBOTAI_EVENT_ON_UPDATE_AI, botName);
    Push(ai);
    CallAllFunctions(PlayerbotAIEventBindings, key);
}
void Eluna::OnTriggerCheck(PlayerbotAI* ai, std::string trigger, bool enabled)
{
    START_HOOK(PLAYERBOTAI_EVENT_ON_TRIGGER_CHECK, trigger);
    Push(ai);
    Push(trigger);
    Push(enabled);
    CallAllFunctions(PlayerbotAIEventBindings, key);
}
void Eluna::OnActionExecute(PlayerbotAI* ai, std::string action, bool success)
{
    START_HOOK(PLAYERBOTAI_EVENT_ON_ACTION_EXECUTE, action);
    Push(ai);
    Push(action);
    Push(success);
    CallAllFunctions(PlayerbotAIEventBindings, key);
}
#endif //ENABLE_PLAYERBOTS
