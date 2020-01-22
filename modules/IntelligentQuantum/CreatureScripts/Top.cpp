#include "ScriptMgr.h"

class CreatureScript_TOP : public CreatureScript
{
	public:
		CreatureScript_TOP() : CreatureScript("CreatureScript_TOP") { }

	bool OnGossipHello(Player* player, Creature* creature) override
	{
		player->PlayerTalkClass->ClearMenus();

		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/PvPRankBadges/PvPRank13:25|t|r TOP Arena Team", GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface\\icons\\Achievement_bg_killxenemies_generalsroom:25|t|r TOP Killer", GOSSIP_SENDER_MAIN, 6);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface\\icons\\INV_Misc_Map_01:25|t|r TOP Played Time", GOSSIP_SENDER_MAIN, 10);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface\\icons\\Spell_Holy_DevineAegis:25|t|r TOP Guild", GOSSIP_SENDER_MAIN, 11);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/PvPRankBadges/PvPRank12:25|t|r TOP Achievement", GOSSIP_SENDER_MAIN, 12);

		player->SEND_GOSSIP_MENU(68, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 /*Sender*/, uint32 Action) override
	{
		player->PlayerTalkClass->ClearMenus();

		switch (Action)
		{
			case 1:
			{
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface\\icons\\Achievement_Arena_2v2_7:25|t|r Arena Team Top 2v2", GOSSIP_SENDER_MAIN, 2);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface\\icons\\Achievement_Arena_3v3_7:25|t|r Arena Team Top 3v3", GOSSIP_SENDER_MAIN, 3);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface\\icons\\Achievement_Arena_5v5_7:25|t|r Arena Team Top 5v5", GOSSIP_SENDER_MAIN, 4);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface\\PVPFrame\\Pvp-arenapoints-icon:25|t|r Top 5 Arena Points", GOSSIP_SENDER_MAIN, 5);

				player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
				return true;
			}
			case 2:
			{
				QueryResult Result = CharacterDatabase.Query("SELECT name, rating, seasonGames, seasonWins FROM arena_team WHERE type = 2 ORDER BY rating DESC LIMIT 10");

				if (Result)
				{
					Field* Fields = Result->Fetch();
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, ".::Arena Team 2vs2::. \n", GOSSIP_SENDER_MAIN, 0);

					do
					{
						std::string Name = Fields[0].GetString();
						int16 Rating = Fields[1].GetInt16();
						int16 Games = Fields[2].GetInt16();
						int16 Wins = Fields[3].GetInt16();

						std::stringstream TOP;
						TOP << "Name: " << Name.c_str() << " Rating: " << Rating << " Win: " << Wins << " Lose: " << Games - Wins;
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, TOP.str(), GOSSIP_SENDER_MAIN, 0);
					}
					while (Result->NextRow());

					player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
				}
				else
					player->PlayerTalkClass->SendCloseGossip();

				return true;
			}
            case 3:
            {
                QueryResult Result = CharacterDatabase.Query("SELECT name, rating, seasonGames, seasonWins FROM arena_team WHERE type = 3 ORDER BY rating DESC LIMIT 10");

                if (Result)
                {
                    Field* Fields = Result->Fetch();
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, ".::Arena Team 3vs3::. \n", GOSSIP_SENDER_MAIN, 0);

                    do
                    {
                        std::string Name = Fields[0].GetString();
                        int16 Rating = Fields[1].GetInt16();
                        int16 Games = Fields[2].GetInt16();
                        int16 Wins = Fields[3].GetInt16();

                        std::stringstream TOP;
                        TOP << "Name: " << Name.c_str() << " Rating: " << Rating << " Win: " << Wins << " Lose: " << Games - Wins;
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, TOP.str(), GOSSIP_SENDER_MAIN, 0);
                    }
                    while (Result->NextRow());

                    player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
                }
                else
                    player->PlayerTalkClass->SendCloseGossip();

                return true;
            }
            case 4:
            {
                QueryResult Result = CharacterDatabase.Query("SELECT name, rating, seasonGames, seasonWins FROM arena_team WHERE type = 5 ORDER BY rating DESC LIMIT 10");

                if (Result)
                {
                    Field* Fields = Result->Fetch();
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, ".::Arena Team 3vs3 Solo::. \n", GOSSIP_SENDER_MAIN, 0);

                    do
                    {
                        std::string Name = Fields[0].GetString();
                        int16 Rating = Fields[1].GetInt16();
                        int16 Games = Fields[2].GetInt16();
                        int16 Wins = Fields[3].GetInt16();

                        std::stringstream TOP;
                        TOP << "Name: " << Name.c_str() << " Rating: " << Rating << " Win: " << Wins << " Lose: " << Games - Wins;
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, TOP.str(), GOSSIP_SENDER_MAIN, 0);
                    }
                    while (Result->NextRow());

                    player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
                }
                else
                    player->PlayerTalkClass->SendCloseGossip();

                return true;
            }
            case 5:
            {
                QueryResult Result = CharacterDatabase.Query("SELECT name,arenaPoints FROM characters ORDER BY arenaPoints DESC LIMIT 10");

                if (Result)
                {
                    Field* Fields = Result->Fetch();
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, ".::Arena Points::. \n", GOSSIP_SENDER_MAIN, 0);

                    do
                    {
                        Fields = Result->Fetch();
                        std::string Name = Fields[0].GetString();
                        uint32 arenaPoints = Fields[1].GetUInt32();

                        std::stringstream TOP;
                        TOP << "Name: " << Name.c_str() << " Arena Points: " << arenaPoints;
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, TOP.str(), GOSSIP_SENDER_MAIN, 0);
                    }
                    while (Result->NextRow());

                    player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
                }
                else
                    player->PlayerTalkClass->SendCloseGossip();

                return true;
            }
            case 6:
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface\\icons\\Achievement_bg_kill_flag_carrier:25|t|r Total Kills", GOSSIP_SENDER_MAIN, 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface\\icons\\Achievement_bg_kill_flag_carriereos:25|t|r Today Kills", GOSSIP_SENDER_MAIN, 8);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface\\icons\\Achievement_bg_kill_flag_carrierwsg:25|t|r Yesterday Kills", GOSSIP_SENDER_MAIN, 9);

                player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
                return true;
            }
            case 7:
            {
                QueryResult Result = CharacterDatabase.Query("SELECT name,totalKills FROM characters ORDER BY totalKills DESC LIMIT 10");

                if (Result)
                {
                    Field* Fields = Result->Fetch();
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, ".::Total Kills::. \n", GOSSIP_SENDER_MAIN, 0);

                    do
                    {
                        Fields = Result->Fetch();
                        std::string Name = Fields[0].GetString();
                        uint32 totalKills = Fields[1].GetUInt32();

                        std::stringstream TOP;
                        TOP << "Name: " << Name.c_str() << " Total Kills: " << totalKills;
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, TOP.str(), GOSSIP_SENDER_MAIN, 0);
                    }
                    while (Result->NextRow());

                    player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
                }
                else
                    player->PlayerTalkClass->SendCloseGossip();

                return true;
            }
            case 8:
            {
                QueryResult Result = CharacterDatabase.Query("SELECT name,todayKills FROM characters ORDER BY todayKills DESC LIMIT 10");

                if (Result)
                {
                    Field* Fields = Result->Fetch();
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, ".::Today Kills::. \n", GOSSIP_SENDER_MAIN, 0);

                    do
                    {
                        Fields = Result->Fetch();
                        std::string Name = Fields[0].GetString();
                        uint16 todayKills = Fields[1].GetUInt16();

                        std::stringstream TOP;
                        TOP << "Name: " << Name.c_str() << " Today Kills: " << todayKills;
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, TOP.str(), GOSSIP_SENDER_MAIN, 0);
                    }
                    while (Result->NextRow());

                    player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
                }
                else
                    player->PlayerTalkClass->SendCloseGossip();

                return true;
            }
            case 9:
            {
                QueryResult Result = CharacterDatabase.Query("SELECT name,yesterdayKills FROM characters ORDER BY yesterdayKills DESC LIMIT 10");

                if (Result)
                {
                    Field* Fields = Result->Fetch();
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, ".::Yesterday Kills::. \n", GOSSIP_SENDER_MAIN, 0);

                    do
                    {
                        Fields = Result->Fetch();
                        std::string Name = Fields[0].GetString();
                        uint16 yesterdayKills = Fields[1].GetUInt16();

                        std::stringstream TOP;
                        TOP << "Name: " << Name.c_str() << " Yesterday Kills: " << yesterdayKills;
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, TOP.str(), GOSSIP_SENDER_MAIN, 0);
                    }
                    while (Result->NextRow());

                    player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
                }
                else
                    player->PlayerTalkClass->SendCloseGossip();

                return true;
            }
            case 10:
            {
                QueryResult Result = CharacterDatabase.Query("SELECT name,totaltime FROM characters WHERE name != '' ORDER BY totaltime DESC LIMIT 10");

                if (Result)
                {
                    Field* Fields = Result->Fetch();
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, ".::Played Time::. \n", GOSSIP_SENDER_MAIN, 0);

                    do
                    {
                        std::string Name = Fields[0].GetString();
                        uint32 Time = Fields[1].GetUInt32();

                        uint32 Day = floor(Time / 86400);
                        Time = Time - (Day * 86400);
                        uint32 Hour = floor(Time / 3600);
                        Time = Time - (Hour * 3600);
                        uint32 Min = floor(Time / 60);

                        std::stringstream TOP;
                        TOP << " Name: " << Name.c_str() << " Days: " << Day << " Hours: " << Hour << " Minutes: " << Min;
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, TOP.str(), GOSSIP_SENDER_MAIN, 0);
                    }
                    while (Result->NextRow());

                    player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
                }
                else
                    player->PlayerTalkClass->SendCloseGossip();

                return true;
            }
            case 11:
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface\\icons\\Ability_hunter_rapidkilling:25|t|r Level, XP", GOSSIP_SENDER_MAIN, 13);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface\\icons\\Ability_hunter_rapidkilling:25|t|r Kills, Points", GOSSIP_SENDER_MAIN, 14);

                player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
                return true;
            }
            case 13:
            {
                QueryResult Result = CharacterDatabase.Query("SELECT name, Level, XP FROM guild ORDER BY Level DESC, Level DESC, XP DESC LIMIT 10");

                if (Result)
                {
                    Field* Fields = Result->Fetch();
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, ".::Guild::. \n", GOSSIP_SENDER_MAIN, 0);

                    do
                    {
                        Fields = Result->Fetch();
                        std::string Name = Fields[0].GetString();
                        std::string Level = Fields[1].GetString();
                        uint32 Xp = Fields[2].GetUInt32();

                        std::stringstream TOP;
                        TOP << "Name: " << Name.c_str() << " Level: " << Level.c_str() << " XP: " << Xp;
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, TOP.str(), GOSSIP_SENDER_MAIN, 0);
                    }
                    while (Result->NextRow());

                    player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
                }
                else
                    player->PlayerTalkClass->SendCloseGossip();

                return true;
            }
            case 14:
            {
                QueryResult Result = CharacterDatabase.Query("SELECT name, `Kills`, Points FROM guild ORDER BY Points DESC LIMIT 10");

                if (Result)
                {
                    Field* Fields = Result->Fetch();
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, ".::Guild::. \n", GOSSIP_SENDER_MAIN, 0);

                    do
                    {
                        Fields = Result->Fetch();
                        std::string Name = Fields[0].GetString();
                        uint32 Kills = Fields[1].GetUInt32();
                        uint32 Points = Fields[2].GetUInt32();

                        std::stringstream TOP;
                        TOP << "Name: " << Name.c_str() << " Kills: " << Kills << " Points: " << Points;
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, TOP.str(), GOSSIP_SENDER_MAIN, 0);
                    }
                    while (Result->NextRow());

                    player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
                }
                else
                    player->PlayerTalkClass->SendCloseGossip();

                return true;
            }
            case 12:
            {
                QueryResult Result = CharacterDatabase.Query("SELECT Guid, COUNT(*) as Achievement FROM character_achievement GROUP BY guid ORDER BY Achievement DESC LIMIT 10");

                if (Result)
                {
                    Field* Fields = Result->Fetch();
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, ".::Achievement::. \n", GOSSIP_SENDER_MAIN, 0);

                    do
                    {
                        uint32 Guid = Fields[0].GetUInt32();
                        uint32 Achievement = Fields[1].GetUInt32();

                        QueryResult CharResult = CharacterDatabase.PQuery("SELECT name FROM `characters` WHERE `guid` = '%u' AND `name` <> ''", Guid);
                        if (CharResult)
                        {
                            Field* CharFields = CharResult->Fetch();
                            std::string Name = CharFields[0].GetString();

                            std::stringstream TOP;
                            TOP << "Name: " << Name.c_str() << " Achievement: " << (Achievement * 10);
                            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, TOP.str(), GOSSIP_SENDER_MAIN, 0);
                        }
                    }
                    while (Result->NextRow());

                    player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
                }
                else
                    player->PlayerTalkClass->SendCloseGossip();

                return true;
            }
            default:
                break;
		}

		player->CLOSE_GOSSIP_MENU();
		return true;
	}

};

void AddSC_TOP()
{
	new CreatureScript_TOP();
}
