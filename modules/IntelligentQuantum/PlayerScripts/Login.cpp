#include "ScriptMgr.h"
#include "Guild.h"

class PlayerScript_Login : public PlayerScript
{
    public:
        PlayerScript_Login() : PlayerScript("PlayerScript_Login") { }

        void OnLogin(Player* player) override
        {
            ChatHandler(player->GetSession()).PSendSysMessage("--------------------------------------------");
            ChatHandler(player->GetSession()).PSendSysMessage("-- Welcome Back - |cff00ffff%s|r", player->GetName().c_str());
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

            if (player->GetSession()->GetSecurity() == SEC_PLAYER)
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
