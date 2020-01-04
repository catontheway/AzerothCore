#include "ScriptMgr.h"
#include "Configuration/Config.h"

class PlayerScript_Level : public PlayerScript
{
    public:
        PlayerScript_Level() : PlayerScript("PlayerScript_Level") { }

        void OnLevelChanged(Player* player, uint8 /* Level */) override
        {
			if (!sConfigMgr->GetBoolDefault("Event.Level.Active", true))
				return;

			if (player->getClass() != CLASS_DEATH_KNIGHT)
			{
				if (player->getLevel() >= sConfigMgr->GetIntDefault("Event.Start.Level", 60))
				{
					player->GiveLevel(sConfigMgr->GetIntDefault("Event.Max.Level", 80));
					player->InitTalentForLevel();
					player->ModifyMoney(sConfigMgr->GetIntDefault("Event.Reward.Money", 10000000));
				}
			}

			if (player->getClass() == CLASS_DEATH_KNIGHT)
			{
				if (player->getLevel() >= sConfigMgr->GetIntDefault("Event.Start.Level.Heroic", 70))
				{
					player->GiveLevel(sConfigMgr->GetIntDefault("Event.Max.Level", 80));
					player->InitTalentForLevel();
					player->ModifyMoney(sConfigMgr->GetIntDefault("Event.Reward.Money", 10000000));
				}
			}
        }
};

void AddSC_Level()
{
    new PlayerScript_Level();
}
