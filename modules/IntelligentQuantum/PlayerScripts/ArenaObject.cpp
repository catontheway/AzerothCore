#include "ScriptMgr.h"

class PlayerScript_Arena : public PlayerScript
{
	public:
		PlayerScript_Arena() : PlayerScript("PlayerScript_Arena") {  }

	void OnUpdateZone(Player* player, uint32 /*zone*/, uint32 /*area*/)
	{
		float x = player->GetPositionX();
		float y = player->GetPositionY();
		float z = player->GetPositionZ();
		float ang = player->GetOrientation();
		float rot2 = std::sin(ang / 2);
		float rot3 = std::cos(ang / 2);

		switch (player->getClass())
		{
			case CLASS_MAGE:
			{
				if (Battleground *bg = player->GetBattleground())
					if (bg->isArena() && player->HasAura(SPELL_ARENA_PREPARATION))
						player->SummonGameObject(193061, x + 2, y + 2, z, ang, 0, 0, rot2, rot3, 30);
			}
			break;

			case CLASS_WARLOCK:
			{
				if (Battleground *bg = player->GetBattleground())
					if (bg->isArena() && player->HasAura(SPELL_ARENA_PREPARATION))
						player->SummonGameObject(193169, x - 2, y - 2, z, ang, 0, 0, rot2, rot3, 30);
			}
			break;
		}
	}
};

void AddSC_ArenaObject()
{
	new PlayerScript_Arena();
}
