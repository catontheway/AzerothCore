#include "ScriptMgr.h"

class PlayerScript_Gurubashi : public PlayerScript
{
	public:
		PlayerScript_Gurubashi() : PlayerScript("PlayerScript_Gurubashi") {}

	void OnPVPKill(Player *Killer, Player *Killed)
	{
		if (Killed->GetMapId() == 0 && Killed->GetAreaId() == 2177)
        {
			if (Killer->GetGUID() == Killed->GetGUID() || Killed->GetMaxHealth() < 16000 || Killer->GetSession()->GetRemoteAddress() == Killed->GetSession()->GetRemoteAddress())
				return;

			if (Killed->GetTeamId() == TEAM_ALLIANCE)
			{
                Killer->ModifyHonorPoints(+350);
				killer->AddItem(100002, 1);
                Killed->RemoveAura(27827);
				Killed->ResurrectPlayer(100, false);
				Killed->AddAura(46705, Killed);
				Killed->AddAura(9438, Killed);
                Killed->CastSpell(Killed, 36910, true);
				Killed->TeleportTo(0, -13151.213867f, 224.389389f, 42.980206f, 2.379343f);
			}
			else
			{
                Killer->ModifyHonorPoints(+350);
				killer->AddItem(100002, 1);
                Killed->RemoveAura(27827);
				Killed->ResurrectPlayer(100, false);
				Killed->AddAura(46705, Killed);
				Killed->AddAura(9438, Killed);
                Killed->CastSpell(Killed, 36910, true);
				Killed->TeleportTo(0, -13275.427734f, 289.899292f, 42.980019f, 6.019665f);
			}
		}
	}

	void OnPlayerKilledByCreature(Creature */*Killer*/, Player *Killed)
	{
		if (Killed->GetMapId() == 0 && Killed->GetAreaId() == 2177)
		{
			if (Killed->GetTeamId() == TEAM_ALLIANCE)
			{
                Killed->RemoveAura(27827);
				Killed->ResurrectPlayer(100, false);
				Killed->AddAura(46705, Killed);
				Killed->AddAura(9438, Killed);
                Killed->CastSpell(Killed, 36910, true);
				Killed->TeleportTo(0, -13151.213867f, 224.389389f, 42.980206f, 2.379343f);
			}
			else
			{
                Killed->RemoveAura(27827);
				Killed->ResurrectPlayer(100, false);
				// Killed->AddAura(46705, Killed);
				Killed->AddAura(9438, Killed);
                Killed->CastSpell(Killed, 36910, true);
				Killed->TeleportTo(0, -13275.427734f, 289.899292f, 42.980019f, 6.019665f);
			}
		}
	}
};

class CreatureScript_Gurubashi : public CreatureScript
{
	public:
		CreatureScript_Gurubashi() : CreatureScript("CreatureScript_Gurubashi") {}

	struct CreatureScript_GurubashiAI : public ScriptedAI
	{
		CreatureScript_GurubashiAI(Creature* creature) : ScriptedAI(creature) {}

		void UpdateAI(uint32 /*diff*/)
		{
			if (Player* player = me->SelectNearestPlayer(0.7f))
			{
				if (!player || player->IsGameMaster())
					return;

				player->TeleportTo(0, -13200.083008f, 281.050232f, 21.857990f, 4.058437f);
			}
		}
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new CreatureScript_GurubashiAI(creature);
	}
};

void AddSC_Gurubashi()
{
    new PlayerScript_Gurubashi();
    new CreatureScript_Gurubashi();
}
