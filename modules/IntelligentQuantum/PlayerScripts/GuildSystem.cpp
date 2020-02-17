#include "ScriptMgr.h"
#include "Chat.h"
#include "GroupMgr.h"
#include "Guild.h"
#include "World.h"
#include "WorldSession.h"

static const uint32 BossList[] = { 33113, 33186, 33118, 33293, 32930, 33515, 32845, 32865, 32906, 33271, 33288, 33350, 15898, 15956, 15954, 16028, 15931, 15928, 15932, 15953, 15952, 16061, 16011, 15936, 16060, 30449, 30452, 30451, 28860, 35013, 33993, 38433, 31125, 34564, 34497, 34780, 34797, 39747, 39751, 39746, 39863, 36612, 36855, 37813, 36626, 36627, 36678, 37970, 37955, 36789, 36853, 36597};
static const uint32 ListSize = sizeof(BossList) / sizeof(*BossList);

class PlayerScript_GuildSystem : public PlayerScript
{
    public:
        PlayerScript_GuildSystem() : PlayerScript("PlayerScript_GuildSystem") { }

        void OnCreatureKill(Player* player, Creature* creature) override
        {
            if (player->GetSession()->GetSecurity() > SEC_PLAYER)
                return;

            if (!creature->isWorldBoss() || !player->GetMap()->IsRaid() || !player->GetGroup())
                return;

            uint32 Entry = creature->GetEntry();

            if (!IsInBossList(Entry))
                return;

            if (Player* Leader = ObjectAccessor::FindPlayer(player->GetGroup()->GetLeaderGUID()))
            {
                if (Guild* guild = player->GetGuild())
                {
                    uint8 Mode = creature->GetMap()->GetDifficulty();

                    guild->IncreaseXP(GetBossXP(Entry) + GetModeXP(Mode));
                    guild->IncreasePoint(GetBossPoint(Entry) + GetModePoint(Mode));
                    SendAnnounce(creature->GetName(), guild->GetName(), Mode, Leader->GetName());
                }
            }
        }

        bool IsInBossList(uint32 Entry)
        {
            for (uint32 i = 0; i < ListSize; ++i)
                if (BossList[i] == Entry)
                    return true;

            return false;
        }

        uint32 GetBossPoint(uint32 Entry)
        {
            switch (Entry)
            {
                // ICC
                case 36597: return 10; // The Lich King
                case 36853: return 10; // Sindragosa
                case 37955: return 10; // Blood Queen
                case 36678: return 10; // Professor
                case 37970: return 10; // Prince Valanar
                case 36627: return 10; // Rotface
                case 36626: return 10; // Festergut
                case 37813: return 10; // DeathBringer
                case 36855: return 10; // Lady DeathWhisper
                case 36612: return 10; // Lord Marrowgar
                // RS
                case 39863: return 10; // Halion
                case 39747: return 10; // Saviana
                case 39751: return 10; // Baltharus
                case 39746: return 10; // General
                // TOC
                case 34564: return 10; // Anub'arak
                case 34497: return 10; // Twin
                case 34780: return 10; // Lord Jaraxxus
                case 34797: return 10; // IceHowl
                // OS
                case 28860: return 1; // Sartharion
                // Onyxia
                case 10184: return 1; // Onyxia
                // VoA
                case 38433: return 1; // Toravon The Ice Watcher
                case 35013: return 1; // Koralon The Flame Watcher
                case 33993: return 1; // Emalon The Storm Watcher
                case 31125: return 1; // Archavon The Stone Watcher
                // Naxx
                case 15990: return 1; // KelThudazd
                case 15898: return 1; // Sapphiron
                case 15956: return 1; // Anub'Rekhan
                case 15954: return 1; // Noth the Plaguebringer
                case 16028: return 1; // Patchwerk
                case 15931: return 1; // Grobbulus
                case 15932: return 1; // Gluth
                case 15928: return 1; // Thaddius
                case 15953: return 1; // Grand Widow Faerlina
                case 15952: return 1; // Maexxna
                case 16061: return 1; // Instructor Razuvious
                case 16011: return 1; // Loatheb
                case 15936: return 1; // Heigan the Unclean
                case 16060: return 1; // Gothik the Harvester
                // Ulduar
                case 33113: return 1; // Flame Leviathan
                case 33186: return 1; // Razorscale
                case 33118: return 1; // Ignis the furnace Master
                case 33293: return 1; // XT-002 Deconstructor
                case 32930: return 1; // Kologarn
                case 33515: return 1; // Auriaya
                case 32845: return 1; // Hodir
                case 32865: return 1; // Thorim
                case 32906: return 1; // Freya
                case 33271: return 1; // General Vezax
                case 33288: return 1; // Yogg-Saron
                case 33350: return 1; // Mimiron
            }

            return 1;
        }

        uint32 GetBossXP(uint32 Entry)
        {
            switch (Entry)
            {
                // ICC
                case 36597: return 6000; break; // The Lich King
                case 36853: return 4500; break; // Sindragosa
                case 37955: return 4500; break; // Blood Queen
                case 36678: return 4500; break; // Professor
                case 37970: return 3500; break; // Prince Valanar
                case 36627: return 3500; break; // Rotface
                case 36626: return 3500; break; // Festergut
                case 37813: return 2500; break; // DeathBringer
                case 36855: return 2500; break; // Lady DeathWhisper
                case 36612: return 2500; break; // Lord Marrowgar
                // RS
                case 39863: return 4500; break; // Halion
                case 39747: return 2500; break; // Saviana
                case 39751: return 2500; break; // Baltharus
                case 39746: return 2500; break; // General
                // TOC
                case 34564: return 4500; break; // Anub'arak
                case 34497: return 2500; break; // Twin
                case 34780: return 2500; break; // Lord Jaraxxus
                case 34797: return 2500; break; // IceHowl
                // OS
                case 28860: return 5000; break; // Sartharion
                // Onyxia
                case 10184: return 5000; break; // Onyxia
                // VoA
                case 38433: return 4500; break; // Toravon The Ice Watcher
                case 35013: return 3500; break; // Koralon The Flame Watcher
                case 33993: return 2500; break; // Emalon The Storm Watcher
                case 31125: return 2500; break; // Archavon The Stone Watcher
                // Naxx
                case 15990: return 3500; break; // KelThudazd
                case 15898: return 3500; break; // Sapphiron
                case 15956: return 2500; break; // Anub'Rekhan
                case 15954: return 2500; break; // Noth the Plaguebringer
                case 16028: return 2500; break; // Patchwerk
                case 15931: return 2500; break; // Grobbulus
                case 15932: return 2500; break; // Gluth
                case 15928: return 3000; break; // Thaddius
                case 15953: return 2500; break; // Grand Widow Faerlina
                case 15952: return 3000; break; // Maexxna
                case 16061: return 2500; break; // Instructor Razuvious
                case 16011: return 2500; break; // Loatheb
                case 15936: return 2500; break; // Heigan the Unclean
                case 16060: return 2500; break; // Gothik the Harvester
                // Ulduar
                case 33113: return 3500; // Flame Leviathan
                case 33186: return 3500; // Razorscale
                case 33118: return 3500; // Ignis the furnace Master
                case 33293: return 3500; // XT-002 Deconstructor
                case 32930: return 3500; // Kologarn
                case 33515: return 3500; // Auriaya
                case 32845: return 3500; // Hodir
                case 32865: return 3500; // Thorim
                case 32906: return 3500; // Freya
                case 33271: return 3500; // General Vezax
                case 33288: return 3500; // Yogg-Saron
                case 33350: return 3500; // Mimiron
                default: break;
            }

            return 1;
        }

        uint16 GetModePoint(uint8 Mode)
        {
            switch (Mode)
            {
                case 1:
                    return 25;
                    break;
                case 2:
                    return 25;
                    break;
                case 3:
                    return 50;
                    break;
            }

            return 0;
        }

        uint16 GetModeXP(uint8 Mode)
        {
            switch (Mode)
            {
                case 1:
                    return 500;
                    break;
                case 2:
                    return 1000;
                    break;
                case 3:
                    return 1500;
                    break;
                default:
                    break;
            }

            return 0;
        }

        std::string GetModeName(uint8 Mode)
        {
            switch (Mode)
            {
                case 1:
                    return "25N";
                    break;
                case 2:
                    return "10HC";
                    break;
                case 3:
                    return "25HC";
                    break;
                default:
                    break;
            }

            return "10N";
        }

        void SendAnnounce(std::string CreatureName, std::string GuildName, uint8 Mode, std::string LeaderName)
        {
            std::string Message = "|cffff0000" + CreatureName + "|r |cffffffff Have Been Killed By Guild|r |cff00f130" + GuildName + "|r|cffffffff On|r |cff00f130 " + GetModeName(Mode) + "|r |cffffffff Leader Was|r |cff00f130" + LeaderName + "|r";
            SessionMap Sessions = sWorld->GetAllSessions();

            for (SessionMap::iterator itr = Sessions.begin(); itr != Sessions.end(); ++itr)
                if (Player* player = itr->second->GetPlayer())
                    if (player->m_guildSystem)
                    {
                        WorldPacket data(SMSG_SERVER_MESSAGE, Message.size() + 1);
                        data << uint32(3);
                        data << Message;
                        player->GetSession()->SendPacket(&data);
                    }
        }
};

void AddSC_GuildSystem()
{
    new PlayerScript_GuildSystem();
}
