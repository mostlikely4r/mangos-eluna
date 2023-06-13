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

using namespace Hooks;

#define START_HOOK(EVENT) \
    if (!IsEnabled())\
        return;\
    auto key = EventKey<PlayerbotAIEvents>(EVENT);\
    if (!PlayerbotAIEventBindings->HasBindingsFor(key))\
        return;\
    LOCK_ELUNA

#define START_HOOK_WITH_RETVAL(EVENT, RETVAL) \
    if (!IsEnabled())\
        return RETVAL;\
    auto key = EventKey<PlayerbotAIEvents>(EVENT);\
    if (!PlayerbotAIEventBindings->HasBindingsFor(key))\
        return RETVAL;\
    LOCK_ELUNA

void Eluna::OnUpdateAI(PlayerbotAI * ai)
{
    START_HOOK(PLAYERBOTAI_EVENT_ON_UPDATE_AI);
    Push(ai);
    CallAllFunctions(PlayerbotAIEventBindings, key);
}
#endif //ENABLE_PLAYERBOTS
