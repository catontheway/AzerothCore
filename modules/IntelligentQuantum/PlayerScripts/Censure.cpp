#include "ScriptMgr.h"

static const char* List[] = { "game", "server", "guild", "fix", "event", "site", "bug", "ticket", "gm", "admin", "hack", "cheat", "change", "gaming", "trans", "wow", "chat", "dev", "sv", "ninja" };
static const char Forbidden[] = ":-\\";

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
		if (Lang == LANG_ADDON || Type == CHAT_MSG_ADDON || player->GetSession()->GetSecurity() > 0)
			return;

		std::string Filtered = Message;
		std::string CheckMessage = "";

		for (char c : Filtered)
			if (isalnum(c))
				CheckMessage += c;

		std::transform(CheckMessage.begin(), CheckMessage.end(), CheckMessage.begin(), ::tolower);
		CheckMessage.erase(std::unique(CheckMessage.begin(), CheckMessage.end()), CheckMessage.end());

		for (size_t i = 0; i < sizeof(List) / sizeof(*List); ++i)
		{
			if (CheckMessage.find(List[i]) != std::string::npos)
			{
				for (uint8 j = 0; j < strlen(Forbidden); ++j)
					Filtered.erase(std::remove(Filtered.begin(), Filtered.end(), Forbidden[j]), Filtered.end());

				sWorld->SendGMText(50000, player->GetPlayerName().c_str(), Mode.c_str(), Filtered.c_str());
				return;
			}
		}
	}
};

void AddSC_Censure()
{
	new PlayerScript_Censure();
}
