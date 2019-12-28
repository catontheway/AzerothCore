#include "ScriptMgr.h"

enum Gems
{
    META_42_ATTACK_POWER_RUN_SPEED = 3625,
    META_21_INTELLECTL_RESTORE_MANA = 3627,
    META_21_AGILITY_3_CRITICAL_DAMAGE = 3628,
    META_21_CRITICAL_3_CRITICAL_DAMAGE = 3639,

    RED_20_ARMOR_PENETRATION = 3525,
    RED_23_SPELL_POWER = 3520,
    RED_20_STRENGTH = 3518,
    RED_40_ATTACK_POWER = 3521,
    RED_20_AGILITY = 3519,

    YELLOW_20_INTELLECT = 3865,
    YELLOW_20_HASTE = 3531,
    YELLOW_20_HIT = 3528,
    YELLOW_20_RESILIENCE = 3245,
    YELLOW_20_CRITICAL = 3527,

    PURPLE_12_SPELL_POWER_5_MANA = 3546,
    PURPLE_10_STRENGTH_15_STAMINA = 3536,
    PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION = 3548,
    PURPLE_10_ARMOR_PENETRATION_15_STAMINA = 3543,
    PURPLE_10_AGILITY_15_STAMINA = 3537,

    ORANGE_20_STRENGTH_10_HIT = 3550,
    ORANGE_10_STRENGTH_10_RESILIENCE = 3552,
    ORANGE_10_ATTACK_POWER_10_RESILIENCE = 3566,
    ORANGE_12_SPELL_POWER_10_HASTE = 3520,
    ORANGE_20_ATTACK_POWER_10_HIT = 3565,
    ORANGE_12_SPELL_POWER_10_RESILIENCE = 3561,

    GREEN_10_HASTE_13_SPELL_PENETRATION = 3590,
    GREEN_10_HASTE_15_STAMINA = 3577,
    GREEN_10_RESILIENCE_5_MANA = 3586,

    BLUE_20_SPELL_PENETRATION = 3535,
    BLUE_20_SPIRIT = 3864,

    ALL_STATS_10 = 3879
};

class CreatureScript_Template : public CreatureScript
{
public:
    CreatureScript_Template() : CreatureScript("CreatureScript_Template") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        for (uint8 i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; i++)
        {
            if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
            {
                if (item)
                {
                    player->GetSession()->SendAreaTriggerMessage("You need to remove all your equipped items in order to use this feature");
                    player->CLOSE_GOSSIP_MENU();
                    return true;
                }
            }
        }

        switch (player->getClass())
        {
            case CLASS_WARRIOR:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Warrior (Arms)", GOSSIP_SENDER_MAIN, 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Warrior (Fury)", GOSSIP_SENDER_MAIN, 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Warrior (Protection)", GOSSIP_SENDER_MAIN, 3);
                break;
            case CLASS_PALADIN:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Paladin (Holy)", GOSSIP_SENDER_MAIN, 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Paladin (Protection)", GOSSIP_SENDER_MAIN, 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Paladin (Retribution)", GOSSIP_SENDER_MAIN, 6);
                break;
            case CLASS_ROGUE:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Rouge (Assassination)", GOSSIP_SENDER_MAIN, 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Rouge (Combat)", GOSSIP_SENDER_MAIN, 8);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Rouge (Subtlety)", GOSSIP_SENDER_MAIN, 9);
                break;
            case CLASS_HUNTER:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Hunter (Beast Mastery)", GOSSIP_SENDER_MAIN, 10);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Hunter (Marksmanship)", GOSSIP_SENDER_MAIN, 11);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Hunter (Survival)", GOSSIP_SENDER_MAIN, 12);
                break;
            case CLASS_PRIEST:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Priest (Discipline)", GOSSIP_SENDER_MAIN, 13);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Priest (Holy)", GOSSIP_SENDER_MAIN, 14);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Priest (Shadow)", GOSSIP_SENDER_MAIN, 15);
                break;
            case CLASS_DEATH_KNIGHT:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "DeathKnight (Blood)", GOSSIP_SENDER_MAIN, 16);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "DeathKnight (Frost)", GOSSIP_SENDER_MAIN, 17);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "DeathKnight (Unholy)", GOSSIP_SENDER_MAIN, 18);
                break;
            case CLASS_SHAMAN:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Shaman (Elemental)", GOSSIP_SENDER_MAIN, 19);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Shaman (Enhancement)", GOSSIP_SENDER_MAIN, 20);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Shaman (Restoration)", GOSSIP_SENDER_MAIN, 21);
                break;
            case CLASS_MAGE:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Mage (Arcane)", GOSSIP_SENDER_MAIN, 22);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Mage (Fire)", GOSSIP_SENDER_MAIN, 23);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Mage (Frost)", GOSSIP_SENDER_MAIN, 24);
                break;
            case CLASS_WARLOCK:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Warlock (Afflication)", GOSSIP_SENDER_MAIN, 25);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Warlock (Demonology)", GOSSIP_SENDER_MAIN, 26);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Warlock (Destruction)", GOSSIP_SENDER_MAIN, 27);
                break;
            case CLASS_DRUID:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Druid (Balance)", GOSSIP_SENDER_MAIN, 28);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Druid (Feral Combat)", GOSSIP_SENDER_MAIN, 29);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Druid (Restoration)", GOSSIP_SENDER_MAIN, 30);
                break;
        }

        player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*Sender*/, uint32 Actions)
    {
        player->PlayerTalkClass->ClearMenus();
        player->resetTalents(true);
        player->SendTalentsInfoData(false);

        switch (Actions)
        {
            case 1:
                // Warrior Arms Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51543, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 51353, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51545, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51356, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51541, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 50659, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51542, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 50620, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 51544, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 50639, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 54567, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 50693, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 54569, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 50363, true);
                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51389, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 51880, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, PURPLE_10_ARMOR_PENETRATION_15_STAMINA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, PURPLE_10_ARMOR_PENETRATION_15_STAMINA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT_2, PURPLE_10_ARMOR_PENETRATION_15_STAMINA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 2:
                // Warrior Fury Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51543, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 53132, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51545, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51356, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51541, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 50659, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51542, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 50620, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 51544, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 50639, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 54567, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 50693, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 50363, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 54569, true);
                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51389, true);
                player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, 51391, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 51880, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_NECK), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, PURPLE_10_ARMOR_PENETRATION_15_STAMINA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, PURPLE_10_ARMOR_PENETRATION_15_STAMINA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT_2, PURPLE_10_ARMOR_PENETRATION_15_STAMINA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), SOCK_ENCHANTMENT_SLOT_2, PURPLE_10_ARMOR_PENETRATION_15_STAMINA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 3:
                // Warrior Protection Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51227, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 53132, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51229, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 47546, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51225, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 54559, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51222, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 50620, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 51223, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 50639, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 54567, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 50693, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 54569, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 50363, true);
                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 50672, true);
                player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, 50729, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 51880, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_AGILITY_3_CRITICAL_DAMAGE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_NECK), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, PURPLE_10_ARMOR_PENETRATION_15_STAMINA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, YELLOW_20_CRITICAL);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, PURPLE_10_ARMOR_PENETRATION_15_STAMINA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED), SOCK_ENCHANTMENT_SLOT, YELLOW_20_CRITICAL);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 4:
                // Paladin Holy Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51470, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 51347, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51473, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51346, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51468, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 51361, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51469, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 51359, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 51471, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 51360, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 51336, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 50610, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 50726, true);

                if (player->GetTeamId() == TEAM_ALLIANCE)
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47059, true);
                else
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47432, true);

                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51454, true);
                player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, 51455, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 51472, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_INTELLECTL_RESTORE_MANA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, GREEN_10_RESILIENCE_5_MANA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, GREEN_10_RESILIENCE_5_MANA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_RESILIENCE_5_MANA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 5:
                // Paladin Protection Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51476, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 50647, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51279, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 50677, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51474, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 50659, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51267, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 51821, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 51268, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 53125, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 51855, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 51358, true);

                if (player->GetTeamId() == TEAM_ALLIANCE)
                {
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 47115, true);
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47131, true);
                }
                else
                {
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 47303, true);
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47464, true);
                }

                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51516, true);
                player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, 50729, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 50461, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_AGILITY_3_CRITICAL_DAMAGE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_NECK), SOCK_ENCHANTMENT_SLOT, ALL_STATS_10);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 6:
                // Paladin Retribution Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51476, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 51355, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51479, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51354, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51474, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 51364, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51475, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 51362, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 51477, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 53125, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 51358, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 50453, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 50706, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47464, true);
                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51393, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 50455, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_AGILITY_3_CRITICAL_DAMAGE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, ORANGE_10_STRENGTH_10_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, ORANGE_10_STRENGTH_10_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, ORANGE_10_STRENGTH_10_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT_2, ALL_STATS_10);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 7:
                // Rouge Assassination Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51494, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 51357, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51496, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51356, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51492, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 51370, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51493, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 50707, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 51495, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 50607, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 50618, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 50678, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 54569, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 50363, true);
                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51518, true);
                player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, 51528, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 51880, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ALL_STATS_10);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 8:
                // Rouge Combat Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51494, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 51822, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51496, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51356, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51492, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 50670, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51493, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 50707, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 51495, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 50607, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 50618, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 50678, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 54569, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 50363, true);
                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 50672, true);
                player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, 50672, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 51880, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ALL_STATS_10);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_NECK), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 9:
                // Rouge Subtlety Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51494, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 51357, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51496, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51356, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51492, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 51370, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51493, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 50707, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 51495, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 50607, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 50618, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 50678, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 54569, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 50363, true);
                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51518, true);
                player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, 51526, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 51880, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ALL_STATS_10);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 10:
                // Hunter Beast Mastery Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51460, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 50452, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51462, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51354, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51458, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 51352, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51459, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 51935, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 51461, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 50711, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 51358, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 50618, true);

                if (player->GetTeamId() == TEAM_ALLIANCE)
                {
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 47115, true);
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47131, true);
                }
                else
                {
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 47303, true);
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47464, true);
                }

                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51389, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 51395, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ALL_STATS_10);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_NECK), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 11:
                // Hunter Marksmanship Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51460, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 50452, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51462, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51354, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51458, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 51352, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51459, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 51935, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 51461, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 50711, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 51358, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 50618, true);

                if (player->GetTeamId() == TEAM_ALLIANCE)
                {
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 47115, true);
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47131, true);
                }
                else
                {
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 47303, true);
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47464, true);
                }

                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51389, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 51395, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ALL_STATS_10);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_NECK), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 12:
                // Hunter Survival Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51460, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 50452, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51462, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51354, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51458, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 51352, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51459, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 51935, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 51461, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 50711, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 51358, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 50618, true);

                if (player->GetTeamId() == TEAM_ALLIANCE)
                {
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 47115, true);
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47131, true);
                }
                else
                {
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 47303, true);
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47464, true);
                }

                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51389, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 51395, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ALL_STATS_10);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_NECK), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 13:
                // Priest Discipline Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51484, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 51335, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51486, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51348, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51482, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 51367, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51483, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 51365, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 51485, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 51366, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 50610, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 50636, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 50726, true);

                if (player->GetTeamId() == TEAM_ALLIANCE)
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47059, true);
                else
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47432, true);

                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51454, true);
                player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, 51409, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 51532, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_INTELLECTL_RESTORE_MANA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, GREEN_10_RESILIENCE_5_MANA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, GREEN_10_RESILIENCE_5_MANA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_RESILIENCE_5_MANA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 14:
                // Priest Holy Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51484, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 51335, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51486, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51348, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51482, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 51367, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51483, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 51365, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 51485, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 51366, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 50610, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 50636, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 50726, true);

                if (player->GetTeamId() == TEAM_ALLIANCE)
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47059, true);
                else
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47432, true);

                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51454, true);
                player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, 51409, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 51532, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_INTELLECTL_RESTORE_MANA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, GREEN_10_RESILIENCE_5_MANA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, GREEN_10_RESILIENCE_5_MANA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_RESILIENCE_5_MANA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 15:
                // Priest Shadow Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51489, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 50658, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51491, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51332, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51487, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 51339, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51488, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 51337, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 51490, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 51338, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 50714, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 50610, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 50348, true);

                if (player->GetTeamId() == TEAM_ALLIANCE)
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47059, true);
                else
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47432, true);

                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51398, true);
                player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, 51407, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 51531, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ORANGE_12_SPELL_POWER_10_HASTE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_NECK), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_HASTE_13_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_HASTE_13_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 16:
                // DeathKnight Blood Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51415, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 51355, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 50674, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51354, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51413, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 51364, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51414, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 51362, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 51416, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 53125, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 50693, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 50657, true);

                if (player->GetTeamId() == TEAM_ALLIANCE)
                {
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 47115, true);
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47131, true);
                }
                else
                {
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 47303, true);
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47464, true);
                }

                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51393, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 45254, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, BLUE_20_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, BLUE_20_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, BLUE_20_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT_2, BLUE_20_SPELL_PENETRATION);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 17:
                // DeathKnight Frost Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51415, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 51355, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 50674, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51354, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51413, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 51364, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51414, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 51362, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 51416, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 53125, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 50693, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 50657, true);

                if (player->GetTeamId() == TEAM_ALLIANCE)
                {
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 47115, true);
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47131, true);
                }
                else
                {
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 47303, true);
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47464, true);
                }

                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51516, true);
                player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, 51526, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 45254, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, BLUE_20_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, BLUE_20_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, BLUE_20_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 18:
                // DeathKnight Unholy Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51415, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 51355, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 50674, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51354, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51413, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 51364, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51414, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 51362, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 51416, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 53125, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 50693, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 50657, true);

                if (player->GetTeamId() == TEAM_ALLIANCE)
                {
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 47115, true);
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47131, true);
                }
                else
                {
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 47303, true);
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47464, true);
                }

                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51393, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 45254, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, BLUE_20_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, BLUE_20_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, BLUE_20_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 19:
                // Shaman Elemental Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51511, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 50658, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51514, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51334, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51509, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 51376, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51510, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 51374, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 51512, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 51375, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 50714, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 51336, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 54572, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 50348, true);
                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51398, true);
                player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, 51452, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 50458, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, RED_23_SPELL_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_NECK), SOCK_ENCHANTMENT_SLOT_2, ORANGE_12_SPELL_POWER_10_HASTE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_23_SPELL_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, ORANGE_12_SPELL_POWER_10_HASTE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_23_SPELL_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 20:
                // Shaman Enhancement Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51505, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 51357, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51508, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51356, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51503, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 51352, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51504, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 51350, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 51506, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 51351, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 51358, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 50604, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 47131, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47115, true);
                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51516, true);
                player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, 51526, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 50463, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ALL_STATS_10);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 21:
                // Shaman Restoration Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51499, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 51347, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51502, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51346, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51497, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 51373, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51498, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 51371, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 51500, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 51372, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 50610, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 53490, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 50726, true);

                if (player->GetTeamId() == TEAM_ALLIANCE)
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47059, true);
                else
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47432, true);

                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51454, true);
                player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, 51455, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 51501, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_INTELLECTL_RESTORE_MANA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, GREEN_10_RESILIENCE_5_MANA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, GREEN_10_RESILIENCE_5_MANA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_RESILIENCE_5_MANA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 22:
                // Mage Arcane Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51465, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 51333, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51467, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51332, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51463, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 51339, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51464, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 51337, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 50694, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 51338, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 50664, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 50714, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 50348, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 54572, true);
                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51398, true);
                player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, 51407, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 51451, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ORANGE_12_SPELL_POWER_10_HASTE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_HASTE_13_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_3, ORANGE_12_SPELL_POWER_10_HASTE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 23:
                // Mage Fire Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51465, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 51349, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51467, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51348, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51463, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 51367, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51464, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 51365, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 50694, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 51366, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 50636, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 50610, true);

                if (player->GetTeamId() == TEAM_ALLIANCE)
                {
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 47115, true);
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47131, true);
                }
                else
                {
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 47271, true);
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47432, true);
                }

                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51457, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 51532, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, RED_23_SPELL_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_CRITICAL);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_23_SPELL_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_CRITICAL);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, BLUE_20_SPIRIT);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, BLUE_20_SPIRIT);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_23_SPELL_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, BLUE_20_SPIRIT);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_3, YELLOW_20_CRITICAL);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_CRITICAL);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, YELLOW_20_CRITICAL);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, YELLOW_20_CRITICAL);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_23_SPELL_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT_2, BLUE_20_SPIRIT);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 24:
                // Mage Frost Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51465, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 51333, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51467, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51332, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51463, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 51339, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51464, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 51337, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 50694, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 51338, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 50664, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 50714, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 50348, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 54572, true);
                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51398, true);
                player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, 51407, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 51451, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ORANGE_12_SPELL_POWER_10_HASTE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_HASTE_13_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_3, ORANGE_12_SPELL_POWER_10_HASTE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 25:
                // Warlock Afflication Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51538, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 51335, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51540, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51332, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51536, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 53486, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51537, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 51337, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 51539, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 51338, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 50714, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 50664, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 50348, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 54572, true);
                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 50427, true);
                player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, 51407, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 51451, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ORANGE_12_SPELL_POWER_10_HASTE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_HASTE_13_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 26:
                // Warlock Demonology Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51538, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 51335, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51540, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51332, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51536, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 51339, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51537, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 51337, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 51539, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 51338, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 51336, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 42118, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 54572, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 50348, true);
                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51398, true);
                player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, 51407, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 51451, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ALL_STATS_10);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 27:
                // Warlock Destruction Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51538, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 51335, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51540, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51332, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51536, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 53486, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51537, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 51337, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 51539, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 51338, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 50714, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 50664, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 50348, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 54572, true);
                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 50427, true);
                player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, 51407, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 51451, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ORANGE_12_SPELL_POWER_10_HASTE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_HASTE_13_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 28:
                // Druid Balance Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51435, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 51333, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51438, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51332, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51419, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 51342, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51434, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 51340, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 51436, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 51341, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 50610, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 50636, true);

                if (player->GetTeamId() == TEAM_ALLIANCE)
                {
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 47115, true);
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47131, true);
                }
                else
                {
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 47271, true);
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47432, true);
                }

                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51398, true);
                player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, 51407, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 51437, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ORANGE_12_SPELL_POWER_10_HASTE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_HASTE_13_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 29:
                // Druid Feral Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51427, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 51353, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51430, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51356, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51425, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 50670, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51426, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 51368, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 51428, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 51369, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 50618, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 50604, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 50363, true);
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 54569, true);
                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51432, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 50456, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ALL_STATS_10);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 30:
                // Druid Restoration Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51421, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 51335, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51424, true);
                player->EquipNewItem(EQUIPMENT_SLOT_BACK, 51334, true);
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 51419, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 51342, true);
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 51420, true);
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 51340, true);
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 51422, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 51341, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 50610, true);
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 51884, true);

                if (player->GetTeamId() == TEAM_ALLIANCE)
                {
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 47115, true);
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47131, true);
                }
                else
                {
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 47271, true);
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47432, true);
                }

                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51454, true);
                player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, 51409, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 47671, true);

                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_INTELLECTL_RESTORE_MANA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, GREEN_10_RESILIENCE_5_MANA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, GREEN_10_RESILIENCE_5_MANA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_RESILIENCE_5_MANA);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                Socket(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            default:
                break;
        }

        player->InitRunes();
        player->InitStatsForLevel(true);
        player->InitGlyphsForLevel();
        player->InitTalentForLevel();

        if (player->GetTeamId() == TEAM_ALLIANCE)
            player->AddItem(51377, 1);
        else
            player->AddItem(51378, 1);

        return true;
    }

    void Enchant(Player* player, Item* item, uint32 EnchantId)
    {
        if (!item)
            return;

        if (!EnchantId)
            return;

        player->ApplyEnchantment(item, PERM_ENCHANTMENT_SLOT, false);
        item->SetEnchantment(PERM_ENCHANTMENT_SLOT, EnchantId, 0, 0);
        player->ApplyEnchantment(item, PERM_ENCHANTMENT_SLOT, true);
    }

    void Glyph(Player* player, uint8 Slot, uint32 GlyphId)
    {
        if (GlyphPropertiesEntry const* gp = sGlyphPropertiesStore.LookupEntry(GlyphId))
        {
            if (uint32 oldGlyph = player->GetGlyph(Slot))
                player->RemoveAurasDueToSpell(sGlyphPropertiesStore.LookupEntry(oldGlyph)->SpellId);

            player->CastSpell(player, gp->SpellId, true);
            player->SetGlyph(Slot, GlyphId, true);
            player->SendTalentsInfoData(false);
        }
    }

    void Socket(Player* player, Item* item, EnchantmentSlot Slot, uint32 SocketId)
    {
        if (!item)
            return;

        if (!SocketId)
            return;

        player->ApplyEnchantment(item, Slot, false);
        item->SetEnchantment(Slot, SocketId, 0, 0);
        player->ApplyEnchantment(item, Slot, true);
    }
};

void AddSC_Template()
{
    new CreatureScript_Template();
}
