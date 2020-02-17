#include "ScriptMgr.h"

class CreatureScript_TOP : public CreatureScript
{
	public:
		CreatureScript_TOP() : CreatureScript("CreatureScript_TOP") { }

	bool OnGossipHello(Player* player, Creature* creature) override
	{
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Top Arena", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Top Guild", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Top Activity", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Top Killer", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Top Money", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Top Achievement", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);

        SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature);
        return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 /*Sender*/, uint32 Action) override
	{
		player->PlayerTalkClass->ClearMenus();

        switch (Action)
        {
            case GOSSIP_ACTION_INFO_DEF + 1:
            {
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "2 Vs 2", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "3 Vs 3", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "5 Vs 5", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);

                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                return true;
            }
            case GOSSIP_ACTION_INFO_DEF + 2:
            {
                QueryResult Result = CharacterDatabase.Query("SELECT name,rating,seasonGames,seasonWins FROM arena_team WHERE type = 2 ORDER BY rating DESC LIMIT 10");

                if (Result)
                {
                    Field* Fields = Result->Fetch();
                    ChatHandler(player->GetSession()).PSendSysMessage("|cffffffff[Top Arena 2 vs 2]|r");

                    do
                    {
                        std::string Name = Fields[0].GetString();
                        uint16 Rating = Fields[1].GetUInt16();
                        uint16 Games = Fields[2].GetUInt16();
                        uint16 Wins = Fields[3].GetUInt16();
                        ChatHandler(player->GetSession()).PSendSysMessage("Name: |cff00ffff%s|r Rating: |cff00ffff%u|r Win: |cff00ffff%u|r Lose: |cff00ffff%u|r", Name.c_str(), Rating, Wins, Games - Wins);
                    } while (Result->NextRow());
                }

                CloseGossipMenuFor(player);
            }
            break;
            case GOSSIP_ACTION_INFO_DEF + 3:
            {
                QueryResult Result = CharacterDatabase.Query("SELECT name,rating,seasonGames,seasonWins FROM arena_team WHERE type = 3 ORDER BY rating DESC LIMIT 10");

                if (Result)
                {
                    Field* Fields = Result->Fetch();
                    ChatHandler(player->GetSession()).PSendSysMessage("|cffffffff[Top Arena 3 vs 3]|r");

                    do
                    {
                        std::string Name = Fields[0].GetString();
                        uint16 Rating = Fields[1].GetUInt16();
                        uint16 Games = Fields[2].GetUInt16();
                        uint16 Wins = Fields[3].GetUInt16();
                        ChatHandler(player->GetSession()).PSendSysMessage("Name: |cff00ffff%s|r Rating: |cff00ffff%u|r Win: |cff00ffff%u|r Lose: |cff00ffff%u|r", Name.c_str(), Rating, Wins, Games - Wins);
                    } while (Result->NextRow());
                }

                CloseGossipMenuFor(player);
            }
            break;
            case GOSSIP_ACTION_INFO_DEF + 4:
            {
                QueryResult Result = CharacterDatabase.Query("SELECT name,rating,seasonGames,seasonWins FROM arena_team WHERE type = 5 ORDER BY rating DESC LIMIT 10");

                if (Result)
                {
                    Field* Fields = Result->Fetch();
                    ChatHandler(player->GetSession()).PSendSysMessage("|cffffffff[Top Arena 5 vs 5]|r");

                    do
                    {
                        std::string Name = Fields[0].GetString();
                        uint16 Rating = Fields[1].GetUInt16();
                        uint16 Games = Fields[2].GetUInt16();
                        uint16 Wins = Fields[3].GetUInt16();
                        ChatHandler(player->GetSession()).PSendSysMessage("Name: |cff00ffff%s|r Rating: |cff00ffff%u|r Win: |cff00ffff%u|r Lose: |cff00ffff%u|r", Name.c_str(), Rating, Wins, Games - Wins);
                    } while (Result->NextRow());
                }

                CloseGossipMenuFor(player);
            }
            break;
            case GOSSIP_ACTION_INFO_DEF + 5:
            {
                QueryResult Result = CharacterDatabase.Query("SELECT name,level,`kill`,point FROM guild ORDER BY point DESC LIMIT 10");

                if (Result)
                {
                    Field* Fields = Result->Fetch();
                    ChatHandler(player->GetSession()).PSendSysMessage("|cffffffff[Top Guild]|r");

                    do
                    {
                        std::string Name = Fields[0].GetString();
                        uint32 Level = Fields[1].GetUInt32();
                        uint32 Kill = Fields[2].GetUInt32();
                        uint32 Point = Fields[3].GetUInt32();
                        ChatHandler(player->GetSession()).PSendSysMessage("Name: |cff00ffff%s|r Point: |cff00ffff%u|r Kill: |cff00ffff%u|r Level: |cff00ffff%u|r", Name.c_str(), Point, Kill, Level);
                    } while (Result->NextRow());
                }

                CloseGossipMenuFor(player);
            }
            break;
            case GOSSIP_ACTION_INFO_DEF + 6:
            {
                QueryResult Result = CharacterDatabase.Query("SELECT name,leveltime FROM characters ORDER BY leveltime DESC LIMIT 10");
                if (Result)
                {
                    Field* Fields = Result->Fetch();
                    ChatHandler(player->GetSession()).PSendSysMessage("|cffffffff[Top Activity]|r");

                    do
                    {
                        std::string Name = Fields[0].GetString();
                        uint32 Time = Fields[1].GetUInt32();

                        Time = std::floor(Time / 1000);

                        ChatHandler(player->GetSession()).PSendSysMessage("Name: |cff00ffff%s|r Activity: |cff00ffff%u|r Hours", Name.c_str(), Time);
                    } while (Result->NextRow());
                }

                CloseGossipMenuFor(player);
            }
            break;
            case GOSSIP_ACTION_INFO_DEF + 7:
            {
                QueryResult Result = CharacterDatabase.Query("SELECT name,totalKills FROM characters ORDER BY totalKills DESC LIMIT 10");

                if (Result)
                {
                    Field* Fields = Result->Fetch();
                    ChatHandler(player->GetSession()).PSendSysMessage("|cffffffff[Top Killer]|r");

                    do
                    {
                        std::string Name = Fields[0].GetString();
                        uint32 Kill = Fields[1].GetUInt32();
                        ChatHandler(player->GetSession()).PSendSysMessage("Name: |cff00ffff%s|r Kill: |cff00ffff%u|r", Name.c_str(), Kill);
                    } while (Result->NextRow());
                }

                CloseGossipMenuFor(player);
            }
            break;
            case GOSSIP_ACTION_INFO_DEF + 8:
            {
                QueryResult Result = CharacterDatabase.Query("SELECT name,money FROM characters ORDER BY money DESC LIMIT 10");
                if (Result)
                {
                    Field* Fields = Result->Fetch();
                    ChatHandler(player->GetSession()).PSendSysMessage("|cffffffff[Top Money]|r");

                    do
                    {
                        std::string Name = Fields[0].GetString();
                        uint32 Money = Fields[1].GetUInt32();

                        Money = std::floor(Money / 10000);

                        ChatHandler(player->GetSession()).PSendSysMessage("Name: |cff00ffff%s|r Money: |cff00ffff%u|r Gold", Name.c_str(), Money);
                    } while (Result->NextRow());
                }

                CloseGossipMenuFor(player);
            }
            break;
            case GOSSIP_ACTION_INFO_DEF + 9:
            {
                QueryResult Result = CharacterDatabase.Query("SELECT Guid, COUNT(*) as Achievement FROM character_achievement GROUP BY guid ORDER BY Achievement DESC LIMIT 20");
                if (Result)
                {
                    Field* Fields = Result->Fetch();
                    ChatHandler(player->GetSession()).PSendSysMessage("|cffffffff[Top Achievement]|r");

                    do
                    {
                        uint32 Guid = Fields[0].GetUInt32();
                        uint32 Achievement = Fields[1].GetUInt32();

                        QueryResult CharResult = CharacterDatabase.PQuery("SELECT name FROM `characters` WHERE `guid` = '%u' AND `name` <> ''", Guid);
                        if (CharResult)
                        {
                            Field* CharFields = CharResult->Fetch();

                            std::string Name = CharFields[0].GetString();

                            ChatHandler(player->GetSession()).PSendSysMessage("Name: |cff00ffff%s|r Achievement: |cff00ffff%u|r", Name.c_str(), (Achievement * 10));
                        }
                    } while (Result->NextRow());
                }

                CloseGossipMenuFor(player);
            }
            break;
            default:
                CloseGossipMenuFor(player);
                break;
        }

		return true;
	}

};

void AddSC_TOP()
{
	new CreatureScript_TOP();
}
