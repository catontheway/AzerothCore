#include "Player.h"
#include "ScriptMgr.h"
#include "Chat.h"

class PlayerScript_PlayedTimeReward : public PlayerScript
{
    public:
        PlayerScript_PlayedTimeReward() : PlayerScript("PlayerScript_PlayedTimeReward") {}

        uint32 InitTimer = 1 * HOUR * IN_MILLISECONDS;
        uint32 RewardTimer = InitTimer;

        void OnBeforeUpdate(Player* player, uint32 p_time) override
        {
            if (RewardTimer > 0)
            {
                if (player->isAFK())
                    return;

                if (RewardTimer <= p_time)
                {
                    ChatHandler(player->GetSession()).PSendSysMessage("|cff00ffffYou Have Been Received Online Time Reward|r");

                    player->AddItem(100006, 1);
                    RewardTimer = InitTimer;
                }
            }
        }
};

void AddSC_PlayedTimeReward()
{
    new PlayerScript_PlayedTimeReward();
}
