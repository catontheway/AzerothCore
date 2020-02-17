#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "Group.h"

static const Position PlayerSpawnPoint[5] =
{
    {1082.826172f, -2574.552490f, 59.957962f, 0.459430f},
    {1108.761353f, -2516.412109f, 59.954971f, 5.195375f},
    {1146.359497f, -2508.554932f, 62.094009f, 3.879836f},
    {1150.805664f, -2576.504395f, 64.738426f, 1.920263f},
    {1175.773560f, -2521.281494f, 61.110966f, 3.432152f}
};

class PlayerScript_PvPZone : public PlayerScript
{
	public:
		PlayerScript_PvPZone() : PlayerScript("PlayerScript_PvPZone") { }

	void OnPVPKill(Player * Killer, Player * Killed) override
	{
		if (Killed->GetMapId() == 0 && Killed->GetAreaId() == 2298)
        {
			if (Killer->GetGUID() == Killed->GetGUID() || Killed->GetMaxHealth() < 20000 || Killer->GetSession()->GetRemoteAddress() == Killed->GetSession()->GetRemoteAddress())
				return;

			Killer->AddAura(62374, Killer);
			Killer->AddItem(100002, 3);
			Killed->AddItem(100002, 1);
			Killed->ResurrectPlayer(100, false);
			Killed->CastSpell(Killed, 36910, true);

			int32 RespawnPos = urand(0, 5 - 1);
			Killed->TeleportTo(0, PlayerSpawnPoint[RespawnPos].GetPositionX(), PlayerSpawnPoint[RespawnPos].GetPositionY(), PlayerSpawnPoint[RespawnPos].GetPositionZ(), PlayerSpawnPoint[RespawnPos].GetOrientation());
		}
	}

	void OnPlayerKilledByCreature (Creature * Killer, Player * Killed) override
	{
		if (Killed->GetMapId() == 0 && Killed->GetAreaId() == 2298)
		{
			Killer->AddAura(62374, Killer);
			Killed->ResurrectPlayer(100, false);
			Killed->CastSpell(Killed, 36910, true);

			int32 RespawnPos = urand(0, 5 - 1);
			Killed->TeleportTo(0, PlayerSpawnPoint[RespawnPos].GetPositionX(), PlayerSpawnPoint[RespawnPos].GetPositionY(), PlayerSpawnPoint[RespawnPos].GetPositionZ(), PlayerSpawnPoint[RespawnPos].GetOrientation());
		}
	}
};

void AddSC_PvPZone()
{
	new PlayerScript_PvPZone();
}
