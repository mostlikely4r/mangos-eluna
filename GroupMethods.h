/*
* Copyright (C) 2010 - 2016 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef GROUPMETHODS_H
#define GROUPMETHODS_H

/***
 * Inherits all methods from: none
 */
namespace LuaGroup
{
    /**
     * Returns 'true' if the [Player] is the [Group] leader
     *
     * @param ObjectGuid guid : guid of a possible leader
     * @return bool isLeader
     */
    int IsLeader(Eluna* E, Group* group)
    {
        ObjectGuid guid = Eluna::CHECKVAL<ObjectGuid>(E->L, 2);
        E->Push(E->L, group->IsLeader(guid));
        return 1;
    }

    /**
     * Returns 'true' if the [Group] is full
     *
     * @return bool isFull
     */
    int IsFull(Eluna* E, Group* group)
    {
        E->Push(E->L, group->IsFull());
        return 1;
    }

#if !(defined(CLASSIC) || defined(TBC))
    /**
     * Returns 'true' if the [Group] is a LFG group
     *
     * @return bool isLFGGroup
     */
    int IsLFGGroup(Eluna* E, Group* group)
    {
#ifdef CMANGOS
        E->Push(E->L, group->IsLFGGroup());
#else
        E->Push(E->L, group->isLFGGroup());
#endif
        return 1;
    }
#endif
    
    /**
     * Returns 'true' if the [Group] is a raid [Group]
     *
     * @return bool isRaid
     */
    int IsRaidGroup(Eluna* E, Group* group)
    {
#ifdef CMANGOS
        E->Push(E->L, group->IsRaidGroup());
#else
        E->Push(E->L, group->isRaidGroup());
#endif
        return 1;
    }

    /**
     * Returns 'true' if the [Group] is a battleground [Group]
     *
     * @return bool isBG
     */
    int IsBGGroup(Eluna* E, Group* group)
    {
#ifdef CMANGOS
        E->Push(E->L, group->IsBattleGroup());        
#else
        E->Push(E->L, group->isBGGroup());
#endif
        return 1;
    }

    /**
     * Returns 'true' if the [Player] is a member of this [Group]
     *
     * @param ObjectGuid guid : guid of a player
     * @return bool isMember
     */
    int IsMember(Eluna* E, Group* group)
    {
        ObjectGuid guid = Eluna::CHECKVAL<ObjectGuid>(E->L, 2);
        E->Push(E->L, group->IsMember(guid));
        return 1;
    }

    /**
     * Returns 'true' if the [Player] is an assistant of this [Group]
     *
     * @param ObjectGuid guid : guid of a player
     * @return bool isAssistant
     */
    int IsAssistant(Eluna* E, Group* group)
    {
        ObjectGuid guid = Eluna::CHECKVAL<ObjectGuid>(E->L, 2);
        E->Push(E->L, group->IsAssistant(guid));
        return 1;
    }

    /**
     * Returns 'true' if the [Player]s are in the same subgroup in this [Group]
     *
     * @param [Player] player1 : first [Player] to check
     * @param [Player] player2 : second [Player] to check
     * @return bool sameSubGroup
     */
    int SameSubGroup(Eluna* E, Group* group)
    {
        Player* player1 = Eluna::CHECKOBJ<Player>(E->L, 2);
        Player* player2 = Eluna::CHECKOBJ<Player>(E->L, 3);
        E->Push(E->L, group->SameSubGroup(player1, player2));
        return 1;
    }

    /**
     * Returns 'true' if the subgroup has free slots in this [Group]
     *
     * @param uint8 subGroup : subGroup ID to check
     * @return bool hasFreeSlot
     */
    int HasFreeSlotSubGroup(Eluna* E, Group* group)
    {
        uint8 subGroup = Eluna::CHECKVAL<uint8>(E->L, 2);

        if (subGroup >= MAX_RAID_SUBGROUPS)
        {
            luaL_argerror(E->L, 2, "valid subGroup ID expected");
            return 0;
        }

        E->Push(E->L, group->HasFreeSlotSubGroup(subGroup));
        return 1;
    }

    /**
     * Adds a new member to the [Group]
     *
     * @param [Player] player : [Player] to add to the group
     * @return bool added : true if member was added
     */
    int AddMember(Eluna* E, Group* group)
    {
        Player* player = Eluna::CHECKOBJ<Player>(E->L, 2);

        if (player->GetGroup() || !group->IsCreated() || group->IsFull())
        {
            E->Push(E->L, false);
            return 1;
        }

        if (player->GetGroupInvite())
            player->UninviteFromGroup();

#if defined TRINITY || AZEROTHCORE
        bool success = group->AddMember(player);
        if (success)
            group->BroadcastGroupUpdate();
#else
        bool success = group->AddMember(player->GetObjectGuid(), player->GetName());
#endif

        E->Push(E->L, success);
        return 1;
    }

    /*int IsLFGGroup(Eluna* E, Group* group) // TODO: Implementation
    {
        E->Push(E->L, group->isLFGGroup());
        return 1;
    }*/

    /*int IsBFGroup(Eluna* E, Group* group) // TODO: Implementation
    {
        E->Push(E->L, group->isBFGroup());
        return 1;
    }*/

    /**
     * Returns a table with the [Player]s in this [Group]
     *
     * @return table groupPlayers : table of [Player]s
     */
    int GetMembers(Eluna* E, Group* group)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (GroupReference* itr = group->GetFirstMember(); itr; itr = itr->next())
        {
#if defined TRINITY || AZEROTHCORE
            Player* member = itr->GetSource();
#else
            Player* member = itr->getSource();
#endif

            if (!member || !member->GetSession())
                continue;

            E->Push(E->L, member);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns [Group] leader GUID
     *
     * @return ObjectGuid leaderGUID
     */
    int GetLeaderGUID(Eluna* E, Group* group)
    {
#if defined TRINITY || AZEROTHCORE
        E->Push(E->L, group->GetLeaderGUID());
#else
        E->Push(E->L, group->GetLeaderGuid());
#endif
        return 1;
    }

    /**
     * Returns the [Group]'s GUID
     *
     * @return ObjectGuid groupGUID
     */
    int GetGUID(Eluna* E, Group* group)
    {
#ifdef CLASSIC
        E->Push(E->L, group->GetId());
#else
        E->Push(E->L, group->GET_GUID());
#endif
        return 1;
    }

    /**
     * Returns a [Group] member's GUID by their name
     *
     * @param string name : the [Player]'s name
     * @return ObjectGuid memberGUID
     */
    int GetMemberGUID(Eluna* E, Group* group)
    {
        const char* name = Eluna::CHECKVAL<const char*>(E->L, 2);
#if defined TRINITY || AZEROTHCORE
        E->Push(E->L, group->GetMemberGUID(name));
#else
        E->Push(E->L, group->GetMemberGuid(name));
#endif
        return 1;
    }

    /**
     * Returns the member count of this [Group]
     *
     * @return uint32 memberCount
     */
    int GetMembersCount(Eluna* E, Group* group)
    {
        E->Push(E->L, group->GetMembersCount());
        return 1;
    }

    /**
     * Returns the [Player]'s subgroup ID of this [Group]
     *
     * @param ObjectGuid guid : guid of the player
     * @return uint8 subGroupID : a valid subgroup ID or MAX_RAID_SUBGROUPS+1
     */
    int GetMemberGroup(Eluna* E, Group* group)
    {
        ObjectGuid guid = Eluna::CHECKVAL<ObjectGuid>(E->L, 2);
        E->Push(E->L, group->GetMemberGroup(guid));
        return 1;
    }

    /**
     * Sets the leader of this [Group]
     *
     * @param ObjectGuid guid : guid of the new leader
     */
    int SetLeader(Eluna* E, Group* group)
    {
        ObjectGuid guid = Eluna::CHECKVAL<ObjectGuid>(E->L, 2);
        group->ChangeLeader(guid);
        group->SendUpdate();
        return 0;
    }

    /**
     * Sends a specified [WorldPacket] to this [Group]
     *
     * @param [WorldPacket] packet : the [WorldPacket] to send
     * @param bool ignorePlayersInBg : ignores [Player]s in a battleground
     * @param ObjectGuid ignore : ignore a [Player] by their GUID
     */
    int SendPacket(Eluna* E, Group* group)
    {
        WorldPacket* data = Eluna::CHECKOBJ<WorldPacket>(E->L, 2);
        bool ignorePlayersInBg = Eluna::CHECKVAL<bool>(E->L, 3);
        ObjectGuid ignore = Eluna::CHECKVAL<ObjectGuid>(E->L, 4);

#ifdef CMANGOS
        group->BroadcastPacket(*data, ignorePlayersInBg, -1, ignore);
#else
        group->BroadcastPacket(data, ignorePlayersInBg, -1, ignore);
#endif
        return 0;
    }

    /**
     * Removes a [Player] from this [Group] and returns 'true' if successful
     *
     * <pre>
     * enum RemoveMethod
     * {
     *     GROUP_REMOVEMETHOD_DEFAULT  = 0,
     *     GROUP_REMOVEMETHOD_KICK     = 1,
     *     GROUP_REMOVEMETHOD_LEAVE    = 2,
     *     GROUP_REMOVEMETHOD_KICK_LFG = 3
     * };
     * </pre>
     *
     * @param ObjectGuid guid : guid of the player to remove
     * @param [RemoveMethod] method : method used to remove the player
     * @return bool removed
     */
    int RemoveMember(Eluna* E, Group* group)
    {
        ObjectGuid guid = Eluna::CHECKVAL<ObjectGuid>(E->L, 2);
        uint32 method = Eluna::CHECKVAL<uint32>(E->L, 3, 0);

#if defined TRINITY || AZEROTHCORE
        E->Push(E->L, group->RemoveMember(guid, (RemoveMethod)method));
#else
        E->Push(E->L, group->RemoveMember(guid, method));
#endif
        return 1;
    }

    /**
     * Disbands this [Group]
     *
     */
    int Disband(Eluna* /*E*/, Group* group)
    {
        group->Disband();
        return 0;
    }

    /**
     * Converts this [Group] to a raid [Group]
     *
     */
    int ConvertToRaid(Eluna* /*E*/, Group* group)
    {
        group->ConvertToRaid();
        return 0;
    }

    /**
     * Sets the member's subGroup
     *
     * @param ObjectGuid guid : guid of the player to move
     * @param uint8 groupID : the subGroup's ID
     */
    int SetMembersGroup(Eluna* E, Group* group)
    {
        ObjectGuid guid = Eluna::CHECKVAL<ObjectGuid>(E->L, 2);
        uint8 subGroup = Eluna::CHECKVAL<uint8>(E->L, 3);

        if (subGroup >= MAX_RAID_SUBGROUPS)
        {
            luaL_argerror(E->L, 3, "valid subGroup ID expected");
            return 0;
        }

        if (!group->HasFreeSlotSubGroup(subGroup))
            return 0;

        group->ChangeMembersGroup(guid, subGroup);
        return 0;
    }

    /**
     * Sets the target icon of an object for the [Group]
     *
     * @param uint8 icon : the icon (Skull, Square, etc)
     * @param ObjectGuid target : GUID of the icon target, 0 is to clear the icon
     * @param ObjectGuid setter : GUID of the icon setter
     */
    int SetTargetIcon(Eluna* E, Group* group)
    {
        uint8 icon = Eluna::CHECKVAL<uint8>(E->L, 2);
        ObjectGuid target = Eluna::CHECKVAL<ObjectGuid>(E->L, 3);
        ObjectGuid setter = Eluna::CHECKVAL<ObjectGuid>(E->L, 4, ObjectGuid());

        if (icon >= TARGETICONCOUNT)
            return luaL_argerror(E->L, 2, "valid target icon expected");

#if (defined(CLASSIC) || defined(TBC))
        group->SetTargetIcon(icon, target);
#else
        group->SetTargetIcon(icon, setter, target);
#endif
        return 0;
    }

    /*int ConvertToLFG(Eluna* E, Group* group) // TODO: Implementation
    {
        group->ConvertToLFG();
        return 0;
    }*/
};

#endif
