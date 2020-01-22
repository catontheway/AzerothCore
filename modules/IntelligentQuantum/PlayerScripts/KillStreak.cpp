#include "ScriptMgr.h"
#include "Guild.h"

class PlayerScript_KillStreak : public PlayerScript
{
	public:
		PlayerScript_KillStreak() : PlayerScript("PlayerScript_KillStreak") { }

	void OnPVPKill(Player* Killer, Player* Killed) override
	{
		if (Killer->GetGUID() == Killed->GetGUID())
			return;

		if (Killer->GetSession()->GetRemoteAddress() == Killed->GetSession()->GetRemoteAddress())
		{
			std::string Message = "|cffff0000Check " + Killer->GetPlayerName() + " Farm Kill/Honor|r";
			sWorld->SendGMText(6613, Message.c_str());
		}

		if (Killer->GetAreaId() == 4234 || Killer->GetAreaId() == 3711 || Killer->GetAreaId() == 4302 || Killed->GetAreaId() == 4234 || Killed->GetAreaId() == 3711 || Killed->GetAreaId() == 4302)
		{
			Killer->ModifyHonorPoints(-1000);

			std::string Message = "|cffff0000Check " + Killer->GetPlayerName() + " Farm Kill/Honor|r";
			sWorld->SendGMText(6613, Message.c_str());
		}

        if (Guild* guild = Killer->GetGuild())
		{
			guild->IncreaseXP(urand(75, 150));
			guild->IncreaseKill();
		}

		if (Killer->GetSession()->GetSecurity() == SEC_PLAYER)
		{
			uint32 KillerGUID = Killer->GetGUID();
			uint32 KilledGUID = Killed->GetGUID();

			if (KillStreakData[KillerGUID].LastKill == KilledGUID)
				return;

			KillStreakData[KillerGUID].KillCount++;
			KillStreakData[KillerGUID].LastKill = KilledGUID;
			KillStreakData[KilledGUID].KillCount = 0;
			KillStreakData[KilledGUID].LastKill = 0;

			switch (KillStreakData[KillerGUID].KillCount)
			{
				case 4:
					SendMessage(Killer->GetName(), Killer->GetTeamId() == TEAM_ALLIANCE ? "Private" : "Scout", "|cff00ff00|TInterface/PvPRankBadges/PvPRank01:20:20|t|r");
					break;
				case 10:
					SendMessage(Killer->GetName(), Killer->GetTeamId() == TEAM_ALLIANCE ? "Corporal" : "Grunt", "|cff00ff00|TInterface/PvPRankBadges/PvPRank02:20:20|t|r");
					break;
				case 16:
					SendMessage(Killer->GetName(), Killer->GetTeamId() == TEAM_ALLIANCE ? "Sergeant Alliance" : "Sergeant Horde", "|cff00ff00|TInterface/PvPRankBadges/PvPRank03:20:20|t|r");
					break;
				case 20:
					SendMessage(Killer->GetName(), Killer->GetTeamId() == TEAM_ALLIANCE ? "Master Sergeant" : "Senior Sergeant", "|cff00ff00|TInterface/PvPRankBadges/PvPRank04:20:20|t|r");
					break;
				case 24:
					SendMessage(Killer->GetName(), Killer->GetTeamId() == TEAM_ALLIANCE ? "Sergeant Major" : "First Sergeant", "|cff00ff00|TInterface/PvPRankBadges/PvPRank05:20:20|t|r");
					break;
				case 29:
					SendMessage(Killer->GetName(), Killer->GetTeamId() == TEAM_ALLIANCE ? "Knight" : "Stone Guard", "|cff00ff00|TInterface/PvPRankBadges/PvPRank06:20:20|t|r");
					break;
				case 30:
					SendMessage(Killer->GetName(), Killer->GetTeamId() == TEAM_ALLIANCE ? "Knight Lieutenant" : "Blood Guard", "|cff00ff00|TInterface/PvPRankBadges/PvPRank07:20:20|t|r");
					break;
				case 38:
					SendMessage(Killer->GetName(), Killer->GetTeamId() == TEAM_ALLIANCE ? "Knight Captain" : "Legionnaire", "|cff00ff00|TInterface/PvPRankBadges/PvPRank08:20:20|t|r");
					break;
				case 42:
					SendMessage(Killer->GetName(), Killer->GetTeamId() == TEAM_ALLIANCE ? "Knight Champion" : "Centurion", "|cff00ff00|TInterface/PvPRankBadges/PvPRank09:20:20|t|r");
					break;
				case 48:
					SendMessage(Killer->GetName(), Killer->GetTeamId() == TEAM_ALLIANCE ? "Lieutenant Commander" : "Champion", "|cff00ff00|TInterface/PvPRankBadges/PvPRank10:20:20|t|r");
					break;
				case 50:
					SendMessage(Killer->GetName(), Killer->GetTeamId() == TEAM_ALLIANCE ? "Commander" : "Lieutenant General", "|cff00ff00|TInterface/PvPRankBadges/PvPRank11:20:20|t|r");
					break;
				case 55:
					SendMessage(Killer->GetName(), Killer->GetTeamId() == TEAM_ALLIANCE ? "Marshal" : "General", "|cff00ff00|TInterface/PvPRankBadges/PvPRank12:20:20|t|r");
					break;
				case 60:
					SendMessage(Killer->GetName(), Killer->GetTeamId() == TEAM_ALLIANCE ? "Field Marshal" : "Warlord", "|cff00ff00|TInterface/PvPRankBadges/PvPRank13:20:20|t|r");
					break;
				case 70:
					SendMessage(Killer->GetName(), Killer->GetTeamId() == TEAM_ALLIANCE ? "Grand Marshal" : "High Warlord", "|cff00ff00|TInterface/PvPRankBadges/PvPRank14:20:20|t|r");
					break;
				default:
					break;
			}
		}
	}

private:
	void SendMessage(std::string Name, std::string Rank, std::string Icon)
	{
		std::string Message = Icon + " |cffffff00" + Name + "|r |cff80e031Is On|r |cffff0000" + Rank + "|r";
		SessionMap Sessions = sWorld->GetAllSessions();

		for (SessionMap::iterator itr = Sessions.begin(); itr != Sessions.end(); ++itr)
			if (Player* plr = itr->second->GetPlayer())
			{
				WorldPacket data(SMSG_SERVER_MESSAGE, (Message.size() + 1));
				data << uint32(3);
				data << Message;
				plr->GetSession()->SendPacket(&data);
			}
	}

	struct KillStreakStruct
	{
		uint8 KillCount;
		uint32 LastKill;
	};

	std::unordered_map<uint32, KillStreakStruct> KillStreakData;
};

void AddSC_KillStreak()
{
	new PlayerScript_KillStreak();
}
