/*
* Copyright (C) 2010 - 2016 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef BATTLEGROUNDMETHODS_H
#define BATTLEGROUNDMETHODS_H

/***
 * Contains the state of a battleground, e.g. Warsong Gulch, Arathi Basin, etc.
 *
 * Inherits all methods from: none
 */
namespace LuaBattleGround
{
    /**
     * Returns the name of the [BattleGround].
     *
     * @return string name
     */
    int GetName(Eluna* E, BattleGround* bg)
    {
        E->Push(E->L, bg->GetName());
        return 1;
    }

    /**
     * Returns the amount of alive players in the [BattleGround] by the team ID.
     *
     * @param [Team] team : team ID
     * @return uint32 count
     */
    int GetAlivePlayersCountByTeam(Eluna* E, BattleGround* bg)
    {
        uint32 team = Eluna::CHECKVAL<uint32>(E->L, 2);

#ifndef AZEROTHCORE
        E->Push(E->L, bg->GetAlivePlayersCountByTeam((Team)team));
#else
        E->Push(E->L, bg->GetAlivePlayersCountByTeam((TeamId)team));
#endif
        return 1;
    }

    /**
     * Returns the [Map] of the [BattleGround].
     *
     * @return [Map] map
     */
    int GetMap(Eluna* E, BattleGround* bg)
    {
        E->Push(E->L, static_cast<Map*>(bg->GetBgMap()));
        return 1;
    }

    /**
     * Returns the bonus honor given by amount of kills in the specific [BattleGround].
     *
     * @param uint32 kills : amount of kills
     * @return uint32 bonusHonor
     */
    int GetBonusHonorFromKillCount(Eluna* E, BattleGround* bg)
    {
        uint32 kills = Eluna::CHECKVAL<uint32>(E->L, 2);

        E->Push(E->L, bg->GetBonusHonorFromKill(kills));
        return 1;
    }

#ifndef AZEROTHCORE
    /**
     * Returns the bracket ID of the specific [BattleGround].
     *
     * @return [BattleGroundBracketId] bracketId
     */
    int GetBracketId(Eluna* E, BattleGround* bg)
    {
        E->Push(E->L, bg->GetBracketId());
        return 1;
    }
#endif

    /**
     * Returns the end time of the [BattleGround].
     *
     * @return uint32 endTime
     */
    int GetEndTime(Eluna* E, BattleGround* bg)
    {
#ifdef CATA
        E->Push(E->L, bg->GetRemainingTime());
#else
        E->Push(E->L, bg->GetEndTime());
#endif
        return 1;
    }

    /**
     * Returns the amount of free slots for the selected team in the specific [BattleGround].
     *
     * @param [Team] team : team ID
     * @return uint32 freeSlots
     */
    int GetFreeSlotsForTeam(Eluna* E, BattleGround* bg)
    {
        uint32 team = Eluna::CHECKVAL<uint32>(E->L, 2);

#ifndef AZEROTHCORE
        E->Push(E->L, bg->GetFreeSlotsForTeam((Team)team));
#else
        E->Push(E->L, bg->GetFreeSlotsForTeam((TeamId)team));
#endif
        return 1;
    }

    /**
     * Returns the instance ID of the [BattleGround].
     *
     * @return uint32 instanceId
     */
    int GetInstanceId(Eluna* E, BattleGround* bg)
    {
#ifdef CMANGOS
        E->Push(E->L, bg->GetInstanceId());
#else
        E->Push(E->L, bg->GetInstanceID());
#endif
        return 1;
    }

    /**
     * Returns the map ID of the [BattleGround].
     *
     * @return uint32 mapId
     */
    int GetMapId(Eluna* E, BattleGround* bg)
    {
        E->Push(E->L, bg->GetMapId());
        return 1;
    }

    /**
     * Returns the type ID of the [BattleGround].
     *
     * @return [BattleGroundTypeId] typeId
     */
    int GetTypeId(Eluna* E, BattleGround* bg)
    {
#ifdef CMANGOS
        E->Push(E->L, bg->GetTypeId());
#elif !AZEROTHCORE
        E->Push(E->L, bg->GetTypeID());
#else
        E->Push(E->L, bg->GetBgTypeID());
#endif
        return 1;
    }

    /**
     * Returns the max allowed [Player] level of the specific [BattleGround].
     *
     * @return uint32 maxLevel
     */
    int GetMaxLevel(Eluna* E, BattleGround* bg)
    {
        E->Push(E->L, bg->GetMaxLevel());
        return 1;
    }

    /**
     * Returns the minimum allowed [Player] level of the specific [BattleGround].
     *
     * @return uint32 minLevel
     */
    int GetMinLevel(Eluna* E, BattleGround* bg)
    {
        E->Push(E->L, bg->GetMinLevel());
        return 1;
    }

    /**
     * Returns the maximum allowed [Player] count of the specific [BattleGround].
     *
     * @return uint32 maxPlayerCount
     */
    int GetMaxPlayers(Eluna* E, BattleGround* bg)
    {
#ifndef AZEROTHCORE
        E->Push(E->L, bg->GetMaxPlayers());
#else
        E->Push(E->L, bg->GetMaxPlayersPerTeam() * 2);
#endif
        return 1;
    }

    /**
     * Returns the minimum allowed [Player] count of the specific [BattleGround].
     *
     * @return uint32 minPlayerCount
     */
    int GetMinPlayers(Eluna* E, BattleGround* bg)
    {
#ifndef AZEROTHCORE
        E->Push(E->L, bg->GetMinPlayers());
#else
        E->Push(E->L, bg->GetMaxPlayersPerTeam() * 2);
#endif
        return 1;
    }

    /**
     * Returns the maximum allowed [Player] count per team of the specific [BattleGround].
     *
     * @return uint32 maxTeamPlayerCount
     */
    int GetMaxPlayersPerTeam(Eluna* E, BattleGround* bg)
    {
        E->Push(E->L, bg->GetMaxPlayersPerTeam());
        return 1;
    }

    /**
     * Returns the minimum allowed [Player] count per team of the specific [BattleGround].
     *
     * @return uint32 minTeamPlayerCount
     */
    int GetMinPlayersPerTeam(Eluna* E, BattleGround* bg)
    {
        E->Push(E->L, bg->GetMinPlayersPerTeam());
        return 1;
    }

    /**
     * Returns the winning team of the specific [BattleGround].
     *
     * @return [Team] team
     */
    int GetWinner(Eluna* E, BattleGround* bg)
    {
        E->Push(E->L, bg->GetWinner());
        return 1;
    }

    /**
     * Returns the status of the specific [BattleGround].
     *
     * @return [BattleGroundStatus] status
     */
    int GetStatus(Eluna* E, BattleGround* bg)
    {
        E->Push(E->L, bg->GetStatus());
        return 1;
    }
};
#endif
