#include "ScriptMgr.h"
#include "Guild.h"

class PlayerScript_Login : public PlayerScript
{
    public:
        PlayerScript_Login() : PlayerScript("PlayerScript_Login") { }

        void OnLogin(Player* player) override
        {
            std::string AccountType;

            switch (player->GetSession()->GetSecurity())
            {
                case SEC_PLAYER:            AccountType = "Player";             break;
                case SEC_TRIAL_GAMEMASTER:  AccountType = "Trial Game Master";  break;
                case SEC_OPERATOR:          AccountType = "Operator";           break;
                case SEC_GAMEMASTER:        AccountType = "Game Master";        break;
                case SEC_PVPMASTER:         AccountType = "PvP Master";         break;
                case SEC_EVENTMASTER:       AccountType = "Event Master";       break;
                case SEC_TRANSFERMASTER:    AccountType = "Transfer Master";    break;
                case SEC_HEAD_GAMEMASTER:   AccountType = "Head Game Master";   break;
                case SEC_DEVELOPER:         AccountType = "Developer";          break;
                case SEC_ADMINISTRATOR:     AccountType = "Administrator";      break;
                case SEC_CONSOLE:           AccountType = "Console";            break;
            }

            ChatHandler(player->GetSession()).PSendSysMessage("--------------------------------------------");
            ChatHandler(player->GetSession()).PSendSysMessage("-- Welcome Back - |cff00ffff%s|r", player->GetName().c_str());
            ChatHandler(player->GetSession()).PSendSysMessage("-- Account Type - |cff00ffff%s|r", AccountType.c_str());
            ChatHandler(player->GetSession()).PSendSysMessage("--------------------------------------------");
            ChatHandler(player->GetSession()).PSendSysMessage("-- ItemLevel - |cff00ffff%u|r", (int) player->GetAverageItemLevel());
            ChatHandler(player->GetSession()).PSendSysMessage("-- Total Kill - |cff00ffff%u|r", player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS));
            ChatHandler(player->GetSession()).PSendSysMessage("-- Arena Points - |cff00ffff%u|r", player->GetArenaPoints());
            ChatHandler(player->GetSession()).PSendSysMessage("-- Honor Points - |cff00ffff%u|r", player->GetHonorPoints());

            if (Guild* guild = player->GetGuild())
            {
                ChatHandler(player->GetSession()).PSendSysMessage("--------------------------------------------");
                ChatHandler(player->GetSession()).PSendSysMessage("-- Guild XP - |cff00ffff(%u / %u)|r", guild->GuildXP, guild->GuildNextLevel);
                ChatHandler(player->GetSession()).PSendSysMessage("-- Guild Kill - |cff00ffff%u|r", guild->CurrentKill);
                ChatHandler(player->GetSession()).PSendSysMessage("-- Guild Point - |cff00ffff%u|r", guild->CurrentPoint);
                ChatHandler(player->GetSession()).PSendSysMessage("-- Guild Level - |cff00ffff%u|r", guild->GuildLevel);
            }

            ChatHandler(player->GetSession()).PSendSysMessage("--------------------------------------------");

            if (player->GetSession()->GetSecurity() == 0)
            {
                uint32 SkillCount = 0;

                if (player->HasSkill(SKILL_MINING))
                    SkillCount++;

                if (player->HasSkill(SKILL_SKINNING))
                    SkillCount++;

                if (player->HasSkill(SKILL_HERBALISM))
                    SkillCount++;

                for (uint32 I = 1; I < sSkillLineStore.GetNumRows(); ++I)
                {
                    if (SkillLineEntry const* SkillInfo = sSkillLineStore.LookupEntry(I))
                    {
                        if (SkillInfo->categoryId == SKILL_CATEGORY_SECONDARY)
                            continue;

                        if ((SkillInfo->categoryId != SKILL_CATEGORY_PROFESSION) || !SkillInfo->canLink)
                            continue;

                        if (player->HasSkill(SkillInfo->id))
                            SkillCount++;
                    }
                }

                if (SkillCount > 2)
                {
                    std::string Message = player->GetPlayerName() + " |cffff0000Has " + std::to_string(SkillCount) + " Works|r";
                    sWorld->SendGMText(50000, Message.c_str());
                }
            }
        }
};

void AddSC_Login()
{
    new PlayerScript_Login();
}
