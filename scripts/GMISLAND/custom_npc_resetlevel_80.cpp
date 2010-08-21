/* Copyright (C) 2009 - 2010 Project Dark-iCE <http://projectdarkice.clanice.com/>
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/
 
/* ScriptData
SDName: custom_npc_resetlevel
SD%Complete: 100
SDComment: Level Reseter with rewards.
SDCategory: NPC
SDAuthor: Darkiss @ Hellscream Network <http://www.hellscream-wow.com/>
EndScriptData */

#include "precompiled.h"
#include "../../../../shared/Config/Config.h"
#include "../../config.h"

bool GossipHello_custom_npc_resetlevel_80(Player* pPlayer, Creature* pCreature)
{
Config SCConfig;
if(!SCConfig.SetSource(_SCRIPTDEV2_CONFIG))
error_log("ScriptDev2 : Unable to open configuration file");

    pPlayer->ADD_GOSSIP_ITEM(0, "Voulez vous être level 80 ?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    pPlayer->ADD_GOSSIP_ITEM(0, "Non, merci.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);

    pPlayer->PlayerTalkClass->SendGossipMenu(907,pCreature->GetGUID());
    return true;
}

bool GossipSelect_custom_npc_resetlevel_80(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    Config SCConfig;
if(!SCConfig.SetSource(_SCRIPTDEV2_CONFIG))
error_log("ScriptDev2 : Unable to open configuration file");

    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
{
if (pPlayer->getClass() != CLASS_DEATH_KNIGHT)
{
         Config SCConfig;
         if(!SCConfig.SetSource(_SCRIPTDEV2_CONFIG))
        error_log("ScriptDev2 : Unable to open configuration file");

pCreature->MonsterWhisper("Vous avez ête mis level 80 !", pPlayer->GetGUID());
pPlayer->CLOSE_GOSSIP_MENU();
pPlayer->SetLevel(80);
pPlayer->resetSpells();
pPlayer->SendTalentsInfoData(true);
pPlayer->InitStatsForLevel(true);
pPlayer->RemoveAllAuras();
pPlayer->GetSession()->KickPlayer();
}
else
{
pCreature->MonsterWhisper("Votre level est trop bas ou trop haut pour celà !", pPlayer->GetGUID());
pPlayer->CLOSE_GOSSIP_MENU();
}
}

    if (uiAction == GOSSIP_ACTION_INFO_DEF+2)
    {
        pCreature->MonsterWhisper("D'accord, merci.", pPlayer->GetGUID());
        pPlayer->CLOSE_GOSSIP_MENU();
    }

    return true;
}

void AddSC_custom_npc_resetlevel_80()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "custom_npc_resetlevel_80";
    newscript->pGossipHello = &GossipHello_custom_npc_resetlevel_80;
    newscript->pGossipSelect = &GossipSelect_custom_npc_resetlevel_80;
    newscript->RegisterSelf();
}