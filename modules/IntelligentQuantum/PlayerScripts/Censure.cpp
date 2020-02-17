#include "ScriptMgr.h"
#include "Player.h"
#include "World.h"
#include <cctype>

static const char* List[] = { "sv", "game", "hack", "gm", "admin", "wow", "www", "realm", "ip", "event", "server", "bug", "cheat", "gaming", "guild", "change", "site", "level", "lvl", "ticket", "335", "434", "548", "735", "neo", "harmez", "sv", "siren" };
static const size_t ListSize = sizeof(List) / sizeof(*List);
static const char Forbid[] = ":-\\";

class PlayerScript_Censure : public PlayerScript
{
    public:
        PlayerScript_Censure() : PlayerScript("PlayerScript_Censure") { }

        void OnChat(Player* player, uint32 Type, uint32 Lang, std::string& Message) override
        {
            CheckMessage(player, Type, Lang, Message, "[S.Y]:");
        }

        void OnChat(Player* player, uint32 Type, uint32 Lang, std::string& Message, Player* Target) override
        {
            CheckMessage(player, Type, Lang, Message, "To " + Target->GetPlayerName() + ": ");
        }

        void OnChat(Player* player, uint32 Type, uint32 Lang, std::string& Message, Group*) override
        {
            CheckMessage(player, Type, Lang, Message, "[R]:");
        }

        void OnChat(Player* player, uint32 Type, uint32 Lang, std::string& Message, Guild*) override
        {
            CheckMessage(player, Type, Lang, Message, "[G]:");
        }

        void OnChat(Player* player, uint32 Type, uint32 Lang, std::string& Message, Channel*) override
        {
            CheckMessage(player, Type, Lang, Message, "[C]:");
        }

        void CheckMessage(Player* player, uint32 Type, uint32 Lang, std::string& Message, std::string Mode)
        {
            if (Lang == LANG_ADDON || Type == CHAT_MSG_ADDON || player->GetSession()->GetSecurity() > SEC_PLAYER)
                return;

            std::string Filtered = Message;
            std::string CheckMessage = "";

            for (char c : Filtered)
                if (std::isalnum(c))
                    CheckMessage += c;

            std::transform(CheckMessage.begin(), CheckMessage.end(), CheckMessage.begin(), ::tolower);
            CheckMessage.erase(std::unique(CheckMessage.begin(), CheckMessage.end()), CheckMessage.end());

            for (size_t i = 0; i < ListSize; ++i)
            {
                if (CheckMessage.find(List[i]) != std::string::npos)
                {
                    for (uint8 x = 0; x < strlen(Forbid); ++x)
                        Filtered.erase(std::remove(Filtered.begin(), Filtered.end(), Forbid[x]), Filtered.end());

                    sWorld->SendGMText(30000, player->GetPlayerName().c_str(), Mode.c_str(), Filtered.c_str());
                    player->GetSession()->m_muteTime = time(nullptr) + 0;
                    return;
                }
            }
        }
};

void AddSC_Censure()
{
    new PlayerScript_Censure();
}
