#include "ScriptMgr.h"
#include "Player.h"
#include "Battleground.h"
#include "Configuration/Config.h"

class BGScript_BattlegroundsReward : public BGScript
{
public:
    BGScript_BattlegroundsReward() : BGScript("BGScript_BattlegroundsReward") {}

    void OnBattlegroundEndReward(Battleground* bg, Player* player, TeamId winnerTeamId) override
    {
        if (sConfigMgr->GetBoolDefault("Battleground.Reward.Enable", true) && !bg->isArena())
        {
            TeamId bgTeamId = player->GetBgTeamId();
            uint32 RewardCount = 0;

            if (bgTeamId == winnerTeamId)
                RewardCount = sConfigMgr->GetIntDefault("Battleground.Reward.WinnerTeam.Count", 2);
            else
                RewardCount = sConfigMgr->GetIntDefault("Battleground.Reward.LoserTeam.Count", 1);

            switch (player->GetZoneId())
            {
                case 3277:
                    player->AddItem(sConfigMgr->GetIntDefault("Battleground.Reward.ItemID.WS", 20558), RewardCount);
                    break;
                case 3358:
                    player->AddItem(sConfigMgr->GetIntDefault("Battleground.Reward.ItemID.AB", 20559), RewardCount);
                    break;
                case 3820:
                    player->AddItem(sConfigMgr->GetIntDefault("Battleground.Reward.ItemID.EY", 29024), RewardCount);
                    break;
                case 4710:
                    player->AddItem(sConfigMgr->GetIntDefault("Battleground.Reward.ItemID.IC", 47395), RewardCount);
                    break;
                case 4384:
                    player->AddItem(sConfigMgr->GetIntDefault("Battleground.Reward.ItemID.SA", 42425), RewardCount);
                    break;
                case 2597:
                    player->AddItem(sConfigMgr->GetIntDefault("Battleground.Reward.ItemID.AV", 20560), RewardCount);
                    break;
                default:
                    break;
            }
        }

        if (sConfigMgr->GetBoolDefault("Arena.Reward.Enable", true) && !bg->isBattleground())
        {
            if (ARENA_TEAM_2v2)
                player->AddItem(sConfigMgr->GetIntDefault("Arena.Reward.ItemID.2v2", 29434), sConfigMgr->GetIntDefault("Arena.Reward.Count.2v2", 1));
            else if (ARENA_TEAM_3v3)
                player->AddItem(sConfigMgr->GetIntDefault("Arena.Reward.ItemID.3v3", 29434), sConfigMgr->GetIntDefault("Arena.Reward.Count.3v3", 2));
            else if (ARENA_TEAM_5v5)
                player->AddItem(sConfigMgr->GetIntDefault("Arena.Reward.ItemID.5v5", 29434), sConfigMgr->GetIntDefault("Arena.Reward.Count.5v5", 3));
        }
    }
};

void AddSC_BattlegroundsReward()
{
	new BGScript_BattlegroundsReward();
}
