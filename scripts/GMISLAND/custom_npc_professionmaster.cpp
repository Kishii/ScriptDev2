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
SDName: custom_npc_professionmaster
SD%Complete: 100
SDComment: Profession Master. Allows profession skills increasement.
SDCategory: NPC
SDAuthor: Darkiss @ Hellscream Network <http://www.hellscream-wow.com/>
SDTodo: Add ability to learn spells without trainers. (All-in-one)
EndScriptData */

#include "precompiled.h"
#include "../../../../shared/Config/Config.h"
#include "../../config.h"

bool GossipHello_custom_npc_professionmaster(Player* pPlayer, Creature* pCreature)
{
	Config SCConfig;
	if(!SCConfig.SetSource(_SCRIPTDEV2_CONFIG))
	error_log("ScriptDev2 : Unable to open configuration file");

	bool ProfessionsEnabled = SCConfig.GetBoolDefault("ProfessionMaster.ProfessionsEnabled", true);
	bool SecondarySkillsEnabled = SCConfig.GetBoolDefault("ProfessionMaster.SecondarySkillsEnabled", true);

	if (pPlayer->GetTeam() == ALLIANCE)
	{
		if(ProfessionsEnabled)
			pPlayer->ADD_GOSSIP_ITEM( 7, "Métiers" , GOSSIP_SENDER_MAIN, 1000);
		if(SecondarySkillsEnabled)
			pPlayer->ADD_GOSSIP_ITEM( 7, "Compétences secondaires" , GOSSIP_SENDER_MAIN, 2000);
	}
	else
	{
		if(ProfessionsEnabled)
			pPlayer->ADD_GOSSIP_ITEM( 7, "Métiers" , GOSSIP_SENDER_MAIN, 1000);
		if(SecondarySkillsEnabled)
			pPlayer->ADD_GOSSIP_ITEM( 7, "Compétences secondaires" , GOSSIP_SENDER_MAIN, 2000);
	}

		pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
		return true;
}

void SendDefaultMenu_custom_npc_professionmaster(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{

	// Vérification si le joueur est en combat
	if (pPlayer->isInCombat())
	{
		pPlayer->CLOSE_GOSSIP_MENU();
		pCreature->MonsterSay("Vous ête en combat !", LANG_UNIVERSAL, NULL);
		return;
	}

	Config SCConfig;
	if(!SCConfig.SetSource(_SCRIPTDEV2_CONFIG))
	error_log("ScriptDev2 : Unable to open configuration file");
			
	// Vérification de l'argent
	if (pPlayer->GetMoney() < (SCConfig.GetFloatDefault("ProfessionMaster.SkillPointCost",0)))
	{
		pPlayer->CLOSE_GOSSIP_MENU();
		pCreature->MonsterWhisper("Vous n'avez pas d'argent.", pPlayer->GetGUID());
		return;
	}

	bool ProfessionsEnabled = SCConfig.GetBoolDefault("ProfessionMaster.ProfessionsEnabled", true);
	bool SecondarySkillsEnabled = SCConfig.GetBoolDefault("ProfessionMaster.SecondarySkillsEnabled", true);

	switch(uiAction)
	{
		case 1000: // Métiers
			pPlayer->ADD_GOSSIP_ITEM( 5, "Alchimie" , GOSSIP_SENDER_MAIN, 1001);		// Skill 171
			pPlayer->ADD_GOSSIP_ITEM( 5, "Forge" , GOSSIP_SENDER_MAIN, 1002);			// Skill 164
			pPlayer->ADD_GOSSIP_ITEM( 5, "Enchantement" , GOSSIP_SENDER_MAIN, 1003);	// Skill 333
			pPlayer->ADD_GOSSIP_ITEM( 5, "Ingénierie" , GOSSIP_SENDER_MAIN, 1004);		// Skill 202
			pPlayer->ADD_GOSSIP_ITEM( 5, "Cueillette" , GOSSIP_SENDER_MAIN, 1005);		// Skill 182
			pPlayer->ADD_GOSSIP_ITEM( 5, "Calligraphie" , GOSSIP_SENDER_MAIN, 1006);	// Skill 773
			pPlayer->ADD_GOSSIP_ITEM( 5, "Joaillerie" , GOSSIP_SENDER_MAIN, 1007);		// Skill 755
			pPlayer->ADD_GOSSIP_ITEM( 5, "Travail du cuir" , GOSSIP_SENDER_MAIN, 1008);	// Skill 165
			pPlayer->ADD_GOSSIP_ITEM( 5, "Minage" , GOSSIP_SENDER_MAIN, 1009);			// Skill 186
			pPlayer->ADD_GOSSIP_ITEM( 5, "Dépeçage" , GOSSIP_SENDER_MAIN, 1010);		// Skill 393
			pPlayer->ADD_GOSSIP_ITEM( 5, "Couture" , GOSSIP_SENDER_MAIN, 1011);			// Skill 197
			pPlayer->ADD_GOSSIP_ITEM( 7, "Retour" , GOSSIP_SENDER_MAIN, 3000);
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
		break;

		case 2000: // Compétences secondaires
			pPlayer->ADD_GOSSIP_ITEM( 5, "Cuisine" , GOSSIP_SENDER_MAIN, 2001);			// Skill 185
			pPlayer->ADD_GOSSIP_ITEM( 5, "Secourisme" , GOSSIP_SENDER_MAIN, 2002);		// Skill 129
			pPlayer->ADD_GOSSIP_ITEM( 5, "Pêche" , GOSSIP_SENDER_MAIN, 2003); 			// Skill 356
			//pPlayer->ADD_GOSSIP_ITEM( 5, "Archéologie" , GOSSIP_SENDER_MAIN, 2005);
			pPlayer->ADD_GOSSIP_ITEM( 7, "Retour" , GOSSIP_SENDER_MAIN, 3000);
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
		break;

		case 3000:
		if (pPlayer->GetTeam() == ALLIANCE)
		{
			if(ProfessionsEnabled)
			pPlayer->ADD_GOSSIP_ITEM( 7, "Métiers" , GOSSIP_SENDER_MAIN, 1000);
			if(SecondarySkillsEnabled)
			pPlayer->ADD_GOSSIP_ITEM( 7, "Compétences secondaires" , GOSSIP_SENDER_MAIN, 2000);
		}
		else
		{
			if(ProfessionsEnabled)
			pPlayer->ADD_GOSSIP_ITEM( 7, "Métiers" , GOSSIP_SENDER_MAIN, 1000);
			if(SecondarySkillsEnabled)
			pPlayer->ADD_GOSSIP_ITEM( 7, "Compétences secondaires" , GOSSIP_SENDER_MAIN, 2000);
		}
		pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
		break;


		case 1001: // Alchimie
		if(!pPlayer->UpdateSkill(171,0))
		{
			pPlayer->learnSpell(51304, false);
			pPlayer->SetSkill(171, 450, 450);
			GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
			return;
		}
		else
		{
			pPlayer->SetSkill(171, 450, 450);
			pPlayer->ModifyMoney(-(SCConfig.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
			pPlayer->CLOSE_GOSSIP_MENU();
		}
		break;

		case 1002: // Forge
		if(!pPlayer->UpdateSkill(164,0))
		{
			pPlayer->learnSpell(51300, false);
			pPlayer->SetSkill(164, 450, 450);
			GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
			return;
		}
		else
		{
			pPlayer->SetSkill(164, 450, 450);
			pPlayer->ModifyMoney(-(SCConfig.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
			pPlayer->CLOSE_GOSSIP_MENU();
		}
		break;

		case 1003: // Enchantement
		if(!pPlayer->UpdateSkill(333,0))
		{
			pPlayer->learnSpell(51313, false);
			pPlayer->SetSkill(333, 450, 450);
			GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
			return;
		}
		else
		{
			pPlayer->SetSkill(333, 450, 450);
			pPlayer->ModifyMoney(-(SCConfig.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
			pPlayer->CLOSE_GOSSIP_MENU();
		}
		break;

		case 1004: // Ingénierie
		if(!pPlayer->UpdateSkill(202,0))
		{
			pPlayer->learnSpell(51306, false);
			pPlayer->learnSpell(20222, false);
			pPlayer->SetSkill(202, 450, 450);
			GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
			return;
		}
		else
		{
			pPlayer->SetSkill(202, 450, 450);
			pPlayer->ModifyMoney(-(SCConfig.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
			pPlayer->CLOSE_GOSSIP_MENU();
		}
		break;

		case 1005: // Cueillette
		if(!pPlayer->UpdateSkill(182,0))
		{
			pPlayer->learnSpell(51300, false);
			pPlayer->SetSkill(182, 450, 450);
			GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
			return;
		}
		else
		{
			pPlayer->SetSkill(182, 450, 450);
			pPlayer->ModifyMoney(-(SCConfig.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
			pPlayer->CLOSE_GOSSIP_MENU();
		}
		break;

		case 1006: // Calligraphie
		if(!pPlayer->UpdateSkill(773,0))
		{
			pPlayer->learnSpell(45363, false);
			pPlayer->SetSkill(773, 450, 450);
			GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
			return;
		}
		else
		{
			pPlayer->SetSkill(773, 450, 450);
			pPlayer->ModifyMoney(-(SCConfig.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
			pPlayer->CLOSE_GOSSIP_MENU();
		}
		break;

		case 1007: // Joaillerie
		if(!pPlayer->UpdateSkill(755,0))
		{
			pPlayer->learnSpell(51311, false);
			pPlayer->SetSkill(755, 450, 450);
			GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
			return;
		}
		else
		{
			pPlayer->SetSkill(755, 450, 450);
			pPlayer->ModifyMoney(-(SCConfig.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
			pPlayer->CLOSE_GOSSIP_MENU();
		}
		break;

		case 1008: // Travail du cuir
		if(!pPlayer->UpdateSkill(165,0))
		{
			pPlayer->learnSpell(51302, false);
			pPlayer->SetSkill(165, 450, 450);
			GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
		return;
		}
		else
		{
			pPlayer->SetSkill(165, 450, 450);
			pPlayer->ModifyMoney(-(SCConfig.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
			pPlayer->CLOSE_GOSSIP_MENU();
		}
		break;

		case 1009: // Minage
		if(!pPlayer->UpdateSkill(186,0))
		{
			pPlayer->learnSpell(50310, false);
			pPlayer->SetSkill(186, 450, 450);
			GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
			return;
		}
		else
		{
			pPlayer->SetSkill(186, 450, 450);
			pPlayer->ModifyMoney(-(SCConfig.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
			pPlayer->CLOSE_GOSSIP_MENU();
		}
		break;

		case 1010: // Dépeçage
		if(!pPlayer->UpdateSkill(393,0))
		{
			pPlayer->learnSpell(50305, false);
			pPlayer->SetSkill(393, 450, 450);
			GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
			return;
		}
		else
		{
			pPlayer->SetSkill(393, 450, 450);
			pPlayer->ModifyMoney(-(SCConfig.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
			pPlayer->CLOSE_GOSSIP_MENU();
		}
		break;

		case 1011: // Couture
		if(!pPlayer->UpdateSkill(197,0))
		{
			pPlayer->learnSpell(51309, false);
			pPlayer->SetSkill(197, 450, 450);
			GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
			return;
		}
		else
		{
			pPlayer->SetSkill(197, 450, 450);
			pPlayer->ModifyMoney(-(SCConfig.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
			pPlayer->CLOSE_GOSSIP_MENU();
		}
		break;

		case 2001: // Cuisine
		if(!pPlayer->UpdateSkill(185,0))
		{
			pPlayer->learnSpell(51296, false);
			pPlayer->SetSkill(185, 450, 450);
			GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
			return;
		}
		else
		{
			pPlayer->SetSkill(185, 450, 450);
			pPlayer->ModifyMoney(-(SCConfig.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
			pPlayer->CLOSE_GOSSIP_MENU();
		}
		break;

		case 2002: // Secourisme
		if(!pPlayer->UpdateSkill(129,0))
		{
			pPlayer->learnSpell(45542, false);
			pPlayer->SetSkill(129, 450, 450);
			GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
			return;
		}
		else
		{
			pPlayer->SetSkill(129, 450, 450);
			pPlayer->ModifyMoney(-(SCConfig.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
			pPlayer->CLOSE_GOSSIP_MENU();
		}
		break;

		case 2003: // Pêche
		if(!pPlayer->UpdateSkill(356,0))
		{
			pPlayer->learnSpell(51294, false);
			pPlayer->SetSkill(356, 450, 450);
			GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
			return;
		}
		else
		{
			pPlayer->SetSkill(356, 450, 450);
			pPlayer->ModifyMoney(-(SCConfig.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
			pPlayer->CLOSE_GOSSIP_MENU();
		}
		break;

		case 2005: // Archéologie
		if(!pPlayer->UpdateSkill(794,0))
		{
			pPlayer->learnSpell(78670, false);
			pPlayer->SetSkill(794, 75, 75);
			GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
			return;
		}
		else
		{
			pPlayer->SetSkill(794, 75, 75);
			pPlayer->ModifyMoney(-(SCConfig.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
			pPlayer->CLOSE_GOSSIP_MENU();
		}
		break;
		pPlayer->CLOSE_GOSSIP_MENU();
	}
}



bool GossipSelect_custom_npc_professionmaster(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
	if (uiSender == GOSSIP_SENDER_MAIN)
	SendDefaultMenu_custom_npc_professionmaster(pPlayer, pCreature, uiAction);
	return true;
}

void AddSC_custom_npc_professionmaster()
{
    Script *newscript;

	newscript = new Script;
    newscript->Name = "custom_npc_professionmaster";
    newscript->pGossipHello = &GossipHello_custom_npc_professionmaster;
    newscript->pGossipSelect = &GossipSelect_custom_npc_professionmaster;
    newscript->RegisterSelf();
}