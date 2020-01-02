#include "ScriptMgr.h"

enum Gems
{
    META_21_INTELLECTL_RESTORE_MANA = 3627,
    META_21_AGILITY_3_CRITICAL_DAMAGE = 3628,
    META_21_CRITICAL_3_CRITICAL_DAMAGE = 3621,

    RED_20_ARMOR_PENETRATION = 3525,
    RED_23_SPELL_POWER = 3520,
    RED_20_STRENGTH = 3518,
    RED_40_ATTACK_POWER = 3521,

    YELLOW_20_RESILIENCE = 3530,
    YELLOW_20_CRITICAL = 3527,

    PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION = 3548,
    PURPLE_10_ARMOR_PENETRATION_15_STAMINA = 3543,

    ORANGE_10_STRENGTH_10_RESILIENCE = 3552,
    ORANGE_12_SPELL_POWER_10_HASTE = 3520,
    ORANGE_12_SPELL_POWER_10_RESILIENCE = 3561,

    GREEN_10_HASTE_13_SPELL_PENETRATION = 3590,
    GREEN_10_RESILIENCE_5_MANA = 3586,

    BLUE_20_SPELL_PENETRATION = 3535,
    BLUE_20_SPIRIT = 3864,

    ALL_STATS_10 = 3879
};

enum Enchant
{
    HEAD_50_ATTACK_POWER_20_RESILIENCE = 3795,
    HEAD_50_ATTACK_POWER_20_CRITICAL = 3817,
    HEAD_29_SPELL_POWER_20_RESILIENCE = 3796,

    SHOULDER_40_ATTACK_POWER_15_RESILIENCE = 3793,
    SHOULDER_40_ATTACK_POWER_15_CRITICAL = 3808,
    SHOULDER_23_SPELL_POWER_15_RESILIENCE = 3794,

    BACK_22_AGILITY = 1099,
    BACK_23_HASTE = 3831,

    CHEST_20_RESILIENCE = 3245,
    CHEST_ALL_STATS = 3832,

    WRIST_50_ATTACK_POWER = 3845,
    WRIST_30_SPELL_POWER = 2332,

    HANDS_44_ATTACK_POWER = 1603,
    HANDS_23_SPELL_POWER = 3246,

    WAIST_PRISMATIC = 3729,

    LEGS_40_RESILIENCE_28_STAMINA = 3853,
    LEGS_75_ATTACK_POWER_22_CRITICAL = 3823,
    LEGS_50_SPELL_POWER_30_STAMINA = 3721,

    FEET_15_STAMINA_MINOR_SPEED = 3232,

    WEAPON_BERSERKING = 3789,
    WEAPON_BLACK_MAGIC,
    WEAPON_63_SPELL_POWER = 3834,

    SHIELD_21_RESILIENCE = 3229,
    SHIELD_TITANIUM_PLATING = 3849,
};

enum Skills
{
    DAGGERS = 1180,
    ONE_H_AXES = 196,
    ONE_H_MACES = 198,
    ONE_H_SWORDS = 201,
    PLATE_MAIL = 750,
    MAIL = 8737
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
            case CLASS_PALADIN:
            case CLASS_DEATH_KNIGHT:
                player->learnSpell(PLATE_MAIL);
                player->learnSpell(ONE_H_AXES);
                break;
            case CLASS_SHAMAN:
                player->learnSpell(DAGGERS);
                player->learnSpell(ONE_H_AXES);
                player->learnSpell(MAIL);
                break;
            case CLASS_HUNTER:
                player->learnSpell(MAIL);
                break;
            case CLASS_ROGUE:
                player->learnSpell(ONE_H_SWORDS);
                player->learnSpell(ONE_H_AXES);
                break;
            case CLASS_PRIEST:
            case CLASS_MAGE:
                player->learnSpell(DAGGERS);
                break;
            case CLASS_WARLOCK:
                player->learnSpell(ONE_H_SWORDS);
                break;
            default:
                break;
        }

        switch (player->getClass())
        {
            case CLASS_WARRIOR:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\ability_rogue_eviscerate:25|t|r Warrior (Arms)", GOSSIP_SENDER_MAIN, 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\ability_warrior_innerrage:25|t|r Warrior (Fury)", GOSSIP_SENDER_MAIN, 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\ability_warrior_defensivestance:25|t|r Warrior (Protection)", GOSSIP_SENDER_MAIN, 3);
                break;
            case CLASS_PALADIN:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_holy_holybolt:25|t|r Paladin (Holy)", GOSSIP_SENDER_MAIN, 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_holy_devotionaura:25|t|r Paladin (Protection)", GOSSIP_SENDER_MAIN, 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_holy_auraoflight:25|t|r Paladin (Retribution)", GOSSIP_SENDER_MAIN, 6);
                break;
            case CLASS_ROGUE:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\ability_rogue_eviscerate:25|t|r Rogue (Assassination)", GOSSIP_SENDER_MAIN, 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\ability_backstab:25|t|r Rogue (Combat)", GOSSIP_SENDER_MAIN, 8);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\ability_stealth:25|t|r Rogue (Subtlety)", GOSSIP_SENDER_MAIN, 9);
                break;
            case CLASS_HUNTER:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\ability_hunter_beasttaming:25|t|r Hunter (Beast Mastery)", GOSSIP_SENDER_MAIN, 10);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\ability_marksmanship:25|t|r Hunter (Marksmanship)", GOSSIP_SENDER_MAIN, 11);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\ability_Hunter_swiftstrike:25|t|r Hunter (Survival)", GOSSIP_SENDER_MAIN, 12);
                break;
            case CLASS_PRIEST:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_holy_wordfortitude:25|t|r Priest (Discipline)", GOSSIP_SENDER_MAIN, 13);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_holy_holybolt:25|t|r Priest (Holy)", GOSSIP_SENDER_MAIN, 14);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_shadow_shadowwordpain:25|t|r Priest (Shadow)", GOSSIP_SENDER_MAIN, 15);
                break;
            case CLASS_DEATH_KNIGHT:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_deathknight_bloodpresence:25|t|r DeathKnight (Blood)", GOSSIP_SENDER_MAIN, 16);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_deathknight_frostpresence:25|t|r DeathKnight (Frost)", GOSSIP_SENDER_MAIN, 17);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_deathknight_unholypresence:25|t|r DeathKnight (Unholy)", GOSSIP_SENDER_MAIN, 18);
                break;
            case CLASS_SHAMAN:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_nature_lightning:25|t|r Shaman (Elemental)", GOSSIP_SENDER_MAIN, 19);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_nature_lightningshield:25|t|r Shaman (Enhancement)", GOSSIP_SENDER_MAIN, 20);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_nature_magicimmunity:25|t|r Shaman (Restoration)", GOSSIP_SENDER_MAIN, 21);
                break;
            case CLASS_MAGE:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_holy_magicalsentry:25|t|r Mage (Arcane)", GOSSIP_SENDER_MAIN, 22);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_fire_flamebolt:25|t|r Mage (Fire)", GOSSIP_SENDER_MAIN, 23);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_frost_frostbolt02:25|t|r Mage (Frost)", GOSSIP_SENDER_MAIN, 24);
                break;
            case CLASS_WARLOCK:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_shadow_deathcoil:25|t|r Warlock (Afflication)", GOSSIP_SENDER_MAIN, 25);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_shadow_metamorphosis:25|t|r Warlock (Demonology)", GOSSIP_SENDER_MAIN, 26);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_shadow_rainoffire:25|t|r Warlock (Destruction)", GOSSIP_SENDER_MAIN, 27);
                break;
            case CLASS_DRUID:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_nature_starfall:25|t|r Druid (Balance)", GOSSIP_SENDER_MAIN, 28);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\ability_racial_bearform:25|t|r Druid (Feral Combat)", GOSSIP_SENDER_MAIN, 29);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_nature_healingtouch:25|t|r Druid (Restoration)", GOSSIP_SENDER_MAIN, 30);
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

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, PURPLE_10_ARMOR_PENETRATION_15_STAMINA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_3, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, PURPLE_10_ARMOR_PENETRATION_15_STAMINA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT_2, PURPLE_10_ARMOR_PENETRATION_15_STAMINA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_50_ATTACK_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_40_ATTACK_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_22_AGILITY);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_50_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_44_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_40_RESILIENCE_28_STAMINA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BERSERKING);

                // Glyph
                Glyph(player, 0, 489);
				Glyph(player, 1, 484);
				Glyph(player, 2, 485);
				Glyph(player, 3, 499);
				Glyph(player, 4, 483);
				Glyph(player, 5, 500);

                // Talent
                player->learnSpell(12658); player->addTalent(12658, player->GetActiveSpecMask(), true);
                player->learnSpell(16464); player->addTalent(16464, player->GetActiveSpecMask(), true);
                player->learnSpell(12677); player->addTalent(12677, player->GetActiveSpecMask(), true);
                player->learnSpell(12959); player->addTalent(12959, player->GetActiveSpecMask(), true);
                player->learnSpell(12963); player->addTalent(12963, player->GetActiveSpecMask(), true);
                player->learnSpell(16494); player->addTalent(16494, player->GetActiveSpecMask(), true);
                player->learnSpell(12867); player->addTalent(12867, player->GetActiveSpecMask(), true);
                player->learnSpell(12712); player->addTalent(12712, player->GetActiveSpecMask(), true);
                player->learnSpell(56638); player->addTalent(56638, player->GetActiveSpecMask(), true);
                player->learnSpell(12785); player->addTalent(12785, player->GetActiveSpecMask(), true);
                player->learnSpell(12328); player->addTalent(12328, player->GetActiveSpecMask(), true);
                player->learnSpell(20505); player->addTalent(20505, player->GetActiveSpecMask(), true);
                player->learnSpell(23695); player->addTalent(23695, player->GetActiveSpecMask(), true);
                player->learnSpell(46855); player->addTalent(46855, player->GetActiveSpecMask(), true);
                player->learnSpell(29838); player->addTalent(29838, player->GetActiveSpecMask(), true);
                player->learnSpell(12294); player->addTalent(12294, player->GetActiveSpecMask(), true);
                player->learnSpell(46866); player->addTalent(46866, player->GetActiveSpecMask(), true);
                player->learnSpell(64976); player->addTalent(64976, player->GetActiveSpecMask(), true);
                player->learnSpell(35449); player->addTalent(35449, player->GetActiveSpecMask(), true);
                player->learnSpell(46860); player->addTalent(46860, player->GetActiveSpecMask(), true);
                player->learnSpell(29623); player->addTalent(29623, player->GetActiveSpecMask(), true);
                player->learnSpell(29859); player->addTalent(29859, player->GetActiveSpecMask(), true);
                player->learnSpell(56614); player->addTalent(56614, player->GetActiveSpecMask(), true);
                player->learnSpell(46924); player->addTalent(46924, player->GetActiveSpecMask(), true);
                player->learnSpell(61222); player->addTalent(61222, player->GetActiveSpecMask(), true);
                player->learnSpell(12856); player->addTalent(12856, player->GetActiveSpecMask(), true);
                player->learnSpell(13000); player->addTalent(13000, player->GetActiveSpecMask(), true);
                player->learnSpell(16492); player->addTalent(16492, player->GetActiveSpecMask(), true);
                player->learnSpell(12323); player->addTalent(12323, player->GetActiveSpecMask(), true);

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

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_NECK), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, PURPLE_10_ARMOR_PENETRATION_15_STAMINA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_3, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, PURPLE_10_ARMOR_PENETRATION_15_STAMINA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT_2, PURPLE_10_ARMOR_PENETRATION_15_STAMINA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), SOCK_ENCHANTMENT_SLOT_2, PURPLE_10_ARMOR_PENETRATION_15_STAMINA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_50_ATTACK_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_40_ATTACK_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_22_AGILITY);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_50_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_44_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_40_RESILIENCE_28_STAMINA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BERSERKING);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BERSERKING);

                // Glyph
                Glyph(player, 0, 509);
				Glyph(player, 1, 484);
				Glyph(player, 2, 851);
				Glyph(player, 3, 490);
				Glyph(player, 4, 483);
				Glyph(player, 5, 494);

                // Talent
                player->learnSpell(12664); player->addTalent(12664, player->GetActiveSpecMask(), true);
                player->learnSpell(16463); player->addTalent(16463, player->GetActiveSpecMask(), true);
                player->learnSpell(12960); player->addTalent(12960, player->GetActiveSpecMask(), true);
                player->learnSpell(12676); player->addTalent(12676, player->GetActiveSpecMask(), true);
                player->learnSpell(16494); player->addTalent(16494, player->GetActiveSpecMask(), true);
                player->learnSpell(12867); player->addTalent(12867, player->GetActiveSpecMask(), true);
                player->learnSpell(61222); player->addTalent(61222, player->GetActiveSpecMask(), true);
                player->learnSpell(12856); player->addTalent(12856, player->GetActiveSpecMask(), true);
                player->learnSpell(13002); player->addTalent(13002, player->GetActiveSpecMask(), true);
                player->learnSpell(16492); player->addTalent(16492, player->GetActiveSpecMask(), true);
                player->learnSpell(12323); player->addTalent(12323, player->GetActiveSpecMask(), true);
                player->learnSpell(23588); player->addTalent(23588, player->GetActiveSpecMask(), true);
                player->learnSpell(13048); player->addTalent(13048, player->GetActiveSpecMask(), true);
                player->learnSpell(12292); player->addTalent(12292, player->GetActiveSpecMask(), true);
                player->learnSpell(29889); player->addTalent(29889, player->GetActiveSpecMask(), true);
                player->learnSpell(12974); player->addTalent(12974, player->GetActiveSpecMask(), true);
                player->learnSpell(23881); player->addTalent(23881, player->GetActiveSpecMask(), true);
                player->learnSpell(29776); player->addTalent(29776, player->GetActiveSpecMask(), true);
                player->learnSpell(46911); player->addTalent(46911, player->GetActiveSpecMask(), true);
                player->learnSpell(29763); player->addTalent(29763, player->GetActiveSpecMask(), true);
                player->learnSpell(60970); player->addTalent(60970, player->GetActiveSpecMask(), true);
                player->learnSpell(29801); player->addTalent(29801, player->GetActiveSpecMask(), true);
                player->learnSpell(46915); player->addTalent(46915, player->GetActiveSpecMask(), true);
                player->learnSpell(56932); player->addTalent(56932, player->GetActiveSpecMask(), true);
                player->learnSpell(46917); player->addTalent(46917, player->GetActiveSpecMask(), true);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 3:
                // Warrior Protection Set
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 51227, true);
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 53132, true);
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 51229, true);

                if (player->GetTeamId() == TEAM_HORDE)
                    player->EquipNewItem(EQUIPMENT_SLOT_BACK, 47546, true);
                else
                    player->EquipNewItem(EQUIPMENT_SLOT_BACK, 47545, true);

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

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_AGILITY_3_CRITICAL_DAMAGE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_NECK), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_3, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, PURPLE_10_ARMOR_PENETRATION_15_STAMINA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, YELLOW_20_CRITICAL);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, PURPLE_10_ARMOR_PENETRATION_15_STAMINA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED), SOCK_ENCHANTMENT_SLOT, YELLOW_20_CRITICAL);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_50_ATTACK_POWER_20_CRITICAL);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_40_ATTACK_POWER_15_CRITICAL);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_22_AGILITY);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_ALL_STATS);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_50_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_44_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_75_ATTACK_POWER_22_CRITICAL);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BERSERKING);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), PERM_ENCHANTMENT_SLOT, SHIELD_TITANIUM_PLATING);

                // Glyph
                Glyph(player, 0, 503);
				Glyph(player, 1, 484);
				Glyph(player, 2, 485);
				Glyph(player, 3, 763);
				Glyph(player, 4, 483);
				Glyph(player, 5, 502);

                // Talent
                player->learnSpell(12658); player->addTalent(12658, player->GetActiveSpecMask(), true);
                player->learnSpell(12697); player->addTalent(12697, player->GetActiveSpecMask(), true);
                player->learnSpell(12727); player->addTalent(12727, player->GetActiveSpecMask(), true);
                player->learnSpell(12764); player->addTalent(12764, player->GetActiveSpecMask(), true);
                player->learnSpell(12799); player->addTalent(12799, player->GetActiveSpecMask(), true);
                player->learnSpell(12803); player->addTalent(12803, player->GetActiveSpecMask(), true);
                player->learnSpell(12804); player->addTalent(12804, player->GetActiveSpecMask(), true);
                player->learnSpell(12809); player->addTalent(12809, player->GetActiveSpecMask(), true);
                player->learnSpell(12818); player->addTalent(12818, player->GetActiveSpecMask(), true);
                player->learnSpell(12867); player->addTalent(12867, player->GetActiveSpecMask(), true);
                player->learnSpell(12958); player->addTalent(12958, player->GetActiveSpecMask(), true);
                player->learnSpell(12960); player->addTalent(12960, player->GetActiveSpecMask(), true);
                player->learnSpell(12975); player->addTalent(12975, player->GetActiveSpecMask(), true);
                player->learnSpell(16464); player->addTalent(16464, player->GetActiveSpecMask(), true);
                player->learnSpell(16494); player->addTalent(16494, player->GetActiveSpecMask(), true);
                player->learnSpell(16542); player->addTalent(16542, player->GetActiveSpecMask(), true);
                player->learnSpell(20243); player->addTalent(20243, player->GetActiveSpecMask(), true);
                player->learnSpell(29144); player->addTalent(29144, player->GetActiveSpecMask(), true);
                player->learnSpell(29594); player->addTalent(29594, player->GetActiveSpecMask(), true);
                player->learnSpell(29599); player->addTalent(29599, player->GetActiveSpecMask(), true);
                player->learnSpell(29792); player->addTalent(29792, player->GetActiveSpecMask(), true);
                player->learnSpell(46968); player->addTalent(46968, player->GetActiveSpecMask(), true);
                player->learnSpell(46953); player->addTalent(46953, player->GetActiveSpecMask(), true);
                player->learnSpell(47296); player->addTalent(47296, player->GetActiveSpecMask(), true);
                player->learnSpell(50687); player->addTalent(50687, player->GetActiveSpecMask(), true);
                player->learnSpell(57499); player->addTalent(57499, player->GetActiveSpecMask(), true);
                player->learnSpell(58874); player->addTalent(58874, player->GetActiveSpecMask(), true);
                player->learnSpell(61222); player->addTalent(61222, player->GetActiveSpecMask(), true);
                player->learnSpell(59089); player->addTalent(59089, player->GetActiveSpecMask(), true);

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

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_INTELLECTL_RESTORE_MANA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, GREEN_10_RESILIENCE_5_MANA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, GREEN_10_RESILIENCE_5_MANA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_RESILIENCE_5_MANA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_RESILIENCE_5_MANA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_29_SPELL_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_23_SPELL_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_23_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_30_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_23_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_50_SPELL_POWER_30_STAMINA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_63_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), PERM_ENCHANTMENT_SLOT, SHIELD_21_RESILIENCE);

                // Glyph
                Glyph(player, 0, 706);
				Glyph(player, 1, 455);
				Glyph(player, 2, 456);
				Glyph(player, 3, 183);
				Glyph(player, 4, 452);
				Glyph(player, 5, 195);

                // Talent
                player->learnSpell(20208); player->addTalent(20208, player->GetActiveSpecMask(), true);
                player->learnSpell(20239); player->addTalent(20239, player->GetActiveSpecMask(), true);
                player->learnSpell(20260); player->addTalent(20260, player->GetActiveSpecMask(), true);
                player->learnSpell(25836); player->addTalent(25836, player->GetActiveSpecMask(), true);
                player->learnSpell(31821); player->addTalent(31821, player->GetActiveSpecMask(), true);
                player->learnSpell(20215); player->addTalent(20215, player->GetActiveSpecMask(), true);
                player->learnSpell(20256); player->addTalent(20256, player->GetActiveSpecMask(), true);
                player->learnSpell(20216); player->addTalent(20216, player->GetActiveSpecMask(), true);
                player->learnSpell(20361); player->addTalent(20361, player->GetActiveSpecMask(), true);
                player->learnSpell(31826); player->addTalent(31826, player->GetActiveSpecMask(), true);
                player->learnSpell(25829); player->addTalent(25829, player->GetActiveSpecMask(), true);
                player->learnSpell(20473); player->addTalent(20473, player->GetActiveSpecMask(), true);
                player->learnSpell(53553); player->addTalent(53553, player->GetActiveSpecMask(), true);
                player->learnSpell(31840); player->addTalent(31840, player->GetActiveSpecMask(), true);
                player->learnSpell(31842); player->addTalent(31842, player->GetActiveSpecMask(), true);
                player->learnSpell(54154); player->addTalent(54154, player->GetActiveSpecMask(), true);
                player->learnSpell(53576); player->addTalent(53576, player->GetActiveSpecMask(), true);
                player->learnSpell(53557); player->addTalent(53557, player->GetActiveSpecMask(), true);
                player->learnSpell(53563); player->addTalent(53563, player->GetActiveSpecMask(), true);
                player->learnSpell(63650); player->addTalent(63650, player->GetActiveSpecMask(), true);
                player->learnSpell(53519); player->addTalent(53519, player->GetActiveSpecMask(), true);
                player->learnSpell(20175); player->addTalent(20175, player->GetActiveSpecMask(), true);
                player->learnSpell(64205); player->addTalent(64205, player->GetActiveSpecMask(), true);
                player->learnSpell(20470); player->addTalent(20470, player->GetActiveSpecMask(), true);
                player->learnSpell(20143); player->addTalent(20143, player->GetActiveSpecMask(), true);
                player->learnSpell(53530); player->addTalent(53530, player->GetActiveSpecMask(), true);
                player->learnSpell(20488); player->addTalent(20488, player->GetActiveSpecMask(), true);

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

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_AGILITY_3_CRITICAL_DAMAGE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_NECK), SOCK_ENCHANTMENT_SLOT, ALL_STATS_10);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_3, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_50_ATTACK_POWER_20_CRITICAL);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_40_ATTACK_POWER_15_CRITICAL);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_22_AGILITY);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_ALL_STATS);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_50_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_44_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_75_ATTACK_POWER_22_CRITICAL);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BERSERKING);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), PERM_ENCHANTMENT_SLOT, SHIELD_TITANIUM_PLATING);

                // Glyph
                Glyph(player, 0, 191);
				Glyph(player, 1, 456);
				Glyph(player, 2, 457);
				Glyph(player, 3, 705);
				Glyph(player, 4, 452);
				Glyph(player, 5, 183);

                // Talent
                player->learnSpell(20266); player->addTalent(20266, player->GetActiveSpecMask(), true);
                player->learnSpell(53519); player->addTalent(53519, player->GetActiveSpecMask(), true);
                player->learnSpell(20175); player->addTalent(20175, player->GetActiveSpecMask(), true);
                player->learnSpell(64205); player->addTalent(64205, player->GetActiveSpecMask(), true);
                player->learnSpell(20470); player->addTalent(20470, player->GetActiveSpecMask(), true);
                player->learnSpell(20143); player->addTalent(20143, player->GetActiveSpecMask(), true);
                player->learnSpell(53530); player->addTalent(53530, player->GetActiveSpecMask(), true);
                player->learnSpell(20488); player->addTalent(20488, player->GetActiveSpecMask(), true);
                player->learnSpell(20140); player->addTalent(20140, player->GetActiveSpecMask(), true);
                player->learnSpell(20911); player->addTalent(20911, player->GetActiveSpecMask(), true);
                player->learnSpell(20182); player->addTalent(20182, player->GetActiveSpecMask(), true);
                player->learnSpell(20198); player->addTalent(20198, player->GetActiveSpecMask(), true);
                player->learnSpell(33776); player->addTalent(33776, player->GetActiveSpecMask(), true);
                player->learnSpell(20925); player->addTalent(20925, player->GetActiveSpecMask(), true);
                player->learnSpell(31852); player->addTalent(31852, player->GetActiveSpecMask(), true);
                player->learnSpell(20135); player->addTalent(20135, player->GetActiveSpecMask(), true);
                player->learnSpell(31860); player->addTalent(31860, player->GetActiveSpecMask(), true);
                player->learnSpell(53592); player->addTalent(53592, player->GetActiveSpecMask(), true);
                player->learnSpell(31935); player->addTalent(31935, player->GetActiveSpecMask(), true);
                player->learnSpell(53585); player->addTalent(53585, player->GetActiveSpecMask(), true);
                player->learnSpell(53711); player->addTalent(53711, player->GetActiveSpecMask(), true);
                player->learnSpell(53595); player->addTalent(53595, player->GetActiveSpecMask(), true);
                player->learnSpell(20105); player->addTalent(20105, player->GetActiveSpecMask(), true);
                player->learnSpell(25957); player->addTalent(25957, player->GetActiveSpecMask(), true);
                player->learnSpell(20337); player->addTalent(20337, player->GetActiveSpecMask(), true);
                player->learnSpell(20121); player->addTalent(20121, player->GetActiveSpecMask(), true);
                player->learnSpell(31868); player->addTalent(31868, player->GetActiveSpecMask(), true);

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

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_AGILITY_3_CRITICAL_DAMAGE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, ORANGE_10_STRENGTH_10_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, ORANGE_10_STRENGTH_10_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, ORANGE_10_STRENGTH_10_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT_2, ALL_STATS_10);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_50_ATTACK_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_40_ATTACK_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_22_AGILITY);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_50_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_44_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_75_ATTACK_POWER_22_CRITICAL);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BERSERKING);

                // Glyph
                Glyph(player, 0, 183);
				Glyph(player, 1, 453);
				Glyph(player, 2, 455);
				Glyph(player, 3, 193);
				Glyph(player, 4, 456);
				Glyph(player, 5, 707);

                // Talent
                player->learnSpell(20105); player->addTalent(20105, player->GetActiveSpecMask(), true);
                player->learnSpell(20332); player->addTalent(20332, player->GetActiveSpecMask(), true);
                player->learnSpell(25836); player->addTalent(25836, player->GetActiveSpecMask(), true);
                player->learnSpell(20266); player->addTalent(20266, player->GetActiveSpecMask(), true);
                player->learnSpell(53519); player->addTalent(53519, player->GetActiveSpecMask(), true);
                player->learnSpell(20175); player->addTalent(20175, player->GetActiveSpecMask(), true);
                player->learnSpell(64205); player->addTalent(64205, player->GetActiveSpecMask(), true);
                player->learnSpell(25957); player->addTalent(25957, player->GetActiveSpecMask(), true);
                player->learnSpell(20337); player->addTalent(20337, player->GetActiveSpecMask(), true);
                player->learnSpell(20045); player->addTalent(20045, player->GetActiveSpecMask(), true);
                player->learnSpell(20121); player->addTalent(20121, player->GetActiveSpecMask(), true);
                player->learnSpell(26023); player->addTalent(26023, player->GetActiveSpecMask(), true);
                player->learnSpell(35397); player->addTalent(35397, player->GetActiveSpecMask(), true);
                player->learnSpell(31868); player->addTalent(31868, player->GetActiveSpecMask(), true);
                player->learnSpell(20113); player->addTalent(20113, player->GetActiveSpecMask(), true);
                player->learnSpell(31869); player->addTalent(31869, player->GetActiveSpecMask(), true);
                player->learnSpell(20057); player->addTalent(20057, player->GetActiveSpecMask(), true);
                player->learnSpell(31872); player->addTalent(31872, player->GetActiveSpecMask(), true);
                player->learnSpell(53488); player->addTalent(53488, player->GetActiveSpecMask(), true);
                player->learnSpell(20066); player->addTalent(20066, player->GetActiveSpecMask(), true);
                player->learnSpell(31878); player->addTalent(31878, player->GetActiveSpecMask(), true);
                player->learnSpell(31881); player->addTalent(31881, player->GetActiveSpecMask(), true);
                player->learnSpell(53376); player->addTalent(53376, player->GetActiveSpecMask(), true);
                player->learnSpell(35395); player->addTalent(35395, player->GetActiveSpecMask(), true);
                player->learnSpell(53503); player->addTalent(53503, player->GetActiveSpecMask(), true);
                player->learnSpell(53382); player->addTalent(53382, player->GetActiveSpecMask(), true);
                player->learnSpell(53385); player->addTalent(53385, player->GetActiveSpecMask(), true);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 7:
                // Rogue Assassination Set
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

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_AGILITY_3_CRITICAL_DAMAGE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ALL_STATS_10);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_3, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_50_ATTACK_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_40_ATTACK_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_22_AGILITY);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_50_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_44_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_75_ATTACK_POWER_22_CRITICAL);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BERSERKING);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BERSERKING);

                // Glyph
                Glyph(player, 0, 733);
				Glyph(player, 1, 464);
				Glyph(player, 2, 467);
				Glyph(player, 3, 405);
				Glyph(player, 4, 469);
				Glyph(player, 5, 408);

                // Talent
                player->learnSpell(14142); player->addTalent(14142, player->GetActiveSpecMask(), true);
                player->learnSpell(14161); player->addTalent(14161, player->GetActiveSpecMask(), true);
                player->learnSpell(13866); player->addTalent(13866, player->GetActiveSpecMask(), true);
                player->learnSpell(14983); player->addTalent(14983, player->GetActiveSpecMask(), true);
                player->learnSpell(14135); player->addTalent(14135, player->GetActiveSpecMask(), true);
                player->learnSpell(16515); player->addTalent(16515, player->GetActiveSpecMask(), true);
                player->learnSpell(14115); player->addTalent(14115, player->GetActiveSpecMask(), true);
                player->learnSpell(31209); player->addTalent(31209, player->GetActiveSpecMask(), true);
                player->learnSpell(14177); player->addTalent(14177, player->GetActiveSpecMask(), true);
                player->learnSpell(31245); player->addTalent(31245, player->GetActiveSpecMask(), true);
                player->learnSpell(14195); player->addTalent(14195, player->GetActiveSpecMask(), true);
                player->learnSpell(14159); player->addTalent(14159, player->GetActiveSpecMask(), true);
                player->learnSpell(51626); player->addTalent(51626, player->GetActiveSpecMask(), true);
                player->learnSpell(58426); player->addTalent(58426, player->GetActiveSpecMask(), true);
                player->learnSpell(51636); player->addTalent(51636, player->GetActiveSpecMask(), true);
                player->learnSpell(58410); player->addTalent(58410, player->GetActiveSpecMask(), true);
                player->learnSpell(31234); player->addTalent(31234, player->GetActiveSpecMask(), true);
                player->learnSpell(1329);  player->addTalent(1329,  player->GetActiveSpecMask(), true);
                player->learnSpell(13848); player->addTalent(13848, player->GetActiveSpecMask(), true);
                player->learnSpell(58425); player->addTalent(58425, player->GetActiveSpecMask(), true);
                player->learnSpell(13971); player->addTalent(13971, player->GetActiveSpecMask(), true);
                player->learnSpell(14072); player->addTalent(14072, player->GetActiveSpecMask(), true);
                player->learnSpell(14094); player->addTalent(14094, player->GetActiveSpecMask(), true);
                player->learnSpell(14063); player->addTalent(14063, player->GetActiveSpecMask(), true);
                player->learnSpell(14066); player->addTalent(14066, player->GetActiveSpecMask(), true);
                player->learnSpell(14173); player->addTalent(14173, player->GetActiveSpecMask(), true);
                player->learnSpell(30895); player->addTalent(30895, player->GetActiveSpecMask(), true);
                player->learnSpell(14185); player->addTalent(14185, player->GetActiveSpecMask(), true);
                player->learnSpell(14083); player->addTalent(14083, player->GetActiveSpecMask(), true);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 8:
                // Rogue Combat Set
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

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_AGILITY_3_CRITICAL_DAMAGE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ALL_STATS_10);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_NECK), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_3, ALL_STATS_10);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_50_ATTACK_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_40_ATTACK_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_22_AGILITY);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_50_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_44_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_75_ATTACK_POWER_22_CRITICAL);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BERSERKING);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BERSERKING);

                // Glyph
                Glyph(player, 0, 409);
				Glyph(player, 1, 464);
				Glyph(player, 2, 467);
				Glyph(player, 3, 404);
				Glyph(player, 4, 469);
				Glyph(player, 5, 715);

                // Talent
                player->learnSpell(5952); player->addTalent(5952, player->GetActiveSpecMask(), true);
                player->learnSpell(13750); player->addTalent(13750, player->GetActiveSpecMask(), true);
                player->learnSpell(13789); player->addTalent(13789, player->GetActiveSpecMask(), true);
                player->learnSpell(13803); player->addTalent(13803, player->GetActiveSpecMask(), true);
                player->learnSpell(13843); player->addTalent(13843, player->GetActiveSpecMask(), true);
                player->learnSpell(13852); player->addTalent(13852, player->GetActiveSpecMask(), true);
                player->learnSpell(13854); player->addTalent(13854, player->GetActiveSpecMask(), true);
                player->learnSpell(13863); player->addTalent(13863, player->GetActiveSpecMask(), true);
                player->learnSpell(13867); player->addTalent(13867, player->GetActiveSpecMask(), true);
                player->learnSpell(13875); player->addTalent(13875, player->GetActiveSpecMask(), true);
                player->learnSpell(13872); player->addTalent(13872, player->GetActiveSpecMask(), true);
                player->learnSpell(13877); player->addTalent(13877, player->GetActiveSpecMask(), true);
                player->learnSpell(13971); player->addTalent(13971, player->GetActiveSpecMask(), true);
                player->learnSpell(14062); player->addTalent(14062, player->GetActiveSpecMask(), true);
                player->learnSpell(14066); player->addTalent(14066, player->GetActiveSpecMask(), true);
                player->learnSpell(14094); player->addTalent(14094, player->GetActiveSpecMask(), true);
                player->learnSpell(14166); player->addTalent(14166, player->GetActiveSpecMask(), true);
                player->learnSpell(14251); player->addTalent(14251, player->GetActiveSpecMask(), true);
                player->learnSpell(14278); player->addTalent(14278, player->GetActiveSpecMask(), true);
                player->learnSpell(31126); player->addTalent(31126, player->GetActiveSpecMask(), true);
                player->learnSpell(31131); player->addTalent(31131, player->GetActiveSpecMask(), true);
                player->learnSpell(32601); player->addTalent(32601, player->GetActiveSpecMask(), true);
                player->learnSpell(51674); player->addTalent(51674, player->GetActiveSpecMask(), true);
                player->learnSpell(51689); player->addTalent(51689, player->GetActiveSpecMask(), true);
                player->learnSpell(51690); player->addTalent(51690, player->GetActiveSpecMask(), true);
                player->learnSpell(58413); player->addTalent(58413, player->GetActiveSpecMask(), true);
                player->learnSpell(58425); player->addTalent(58425, player->GetActiveSpecMask(), true);
                player->learnSpell(61329); player->addTalent(61329, player->GetActiveSpecMask(), true);
                player->learnSpell(61331); player->addTalent(61331, player->GetActiveSpecMask(), true);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 9:
                // Rogue Subtlety Set
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

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_AGILITY_3_CRITICAL_DAMAGE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ALL_STATS_10);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_3, ALL_STATS_10);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_50_ATTACK_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_40_ATTACK_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_22_AGILITY);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_50_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_44_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_75_ATTACK_POWER_22_CRITICAL);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BERSERKING);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BERSERKING);

                // Glyph
                Glyph(player, 0, 404);
				Glyph(player, 1, 464);
				Glyph(player, 2, 467);
				Glyph(player, 3, 716);
				Glyph(player, 4, 469);
				Glyph(player, 5, 408);

                // Talent
                player->learnSpell(13866); player->addTalent(13866, player->GetActiveSpecMask(), true);
                player->learnSpell(13971); player->addTalent(13971, player->GetActiveSpecMask(), true);
                player->learnSpell(13976); player->addTalent(13976, player->GetActiveSpecMask(), true);
                player->learnSpell(14063); player->addTalent(14063, player->GetActiveSpecMask(), true);
                player->learnSpell(14066); player->addTalent(14066, player->GetActiveSpecMask(), true);
                player->learnSpell(14072); player->addTalent(14072, player->GetActiveSpecMask(), true);
                player->learnSpell(14080); player->addTalent(14080, player->GetActiveSpecMask(), true);
                player->learnSpell(14083); player->addTalent(14083, player->GetActiveSpecMask(), true);
                player->learnSpell(14094); player->addTalent(14094, player->GetActiveSpecMask(), true);
                player->learnSpell(14132); player->addTalent(14132, player->GetActiveSpecMask(), true);
                player->learnSpell(14142); player->addTalent(14142, player->GetActiveSpecMask(), true);
                player->learnSpell(14160); player->addTalent(14160, player->GetActiveSpecMask(), true);
                player->learnSpell(14164); player->addTalent(14164, player->GetActiveSpecMask(), true);
                player->learnSpell(14173); player->addTalent(14173, player->GetActiveSpecMask(), true);
                player->learnSpell(14183); player->addTalent(14183, player->GetActiveSpecMask(), true);
                player->learnSpell(14185); player->addTalent(14185, player->GetActiveSpecMask(), true);
                player->learnSpell(14983); player->addTalent(14983, player->GetActiveSpecMask(), true);
                player->learnSpell(16511); player->addTalent(16511, player->GetActiveSpecMask(), true);
                player->learnSpell(30895); player->addTalent(30895, player->GetActiveSpecMask(), true);
                player->learnSpell(30906); player->addTalent(30906, player->GetActiveSpecMask(), true);
                player->learnSpell(31220); player->addTalent(31220, player->GetActiveSpecMask(), true);
                player->learnSpell(31223); player->addTalent(31223, player->GetActiveSpecMask(), true);
                player->learnSpell(36554); player->addTalent(36554, player->GetActiveSpecMask(), true);
                player->learnSpell(51696); player->addTalent(51696, player->GetActiveSpecMask(), true);
                player->learnSpell(51701); player->addTalent(51701, player->GetActiveSpecMask(), true);
                player->learnSpell(51712); player->addTalent(51712, player->GetActiveSpecMask(), true);
                player->learnSpell(51713); player->addTalent(51713, player->GetActiveSpecMask(), true);
                player->learnSpell(58425); player->addTalent(58425, player->GetActiveSpecMask(), true);

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

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_AGILITY_3_CRITICAL_DAMAGE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ALL_STATS_10);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_NECK), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_3, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_50_ATTACK_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_40_ATTACK_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_22_AGILITY);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_50_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_44_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_75_ATTACK_POWER_22_CRITICAL);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BERSERKING);

                // Glyph
                Glyph(player, 0, 351);
                Glyph(player, 1, 439);
                Glyph(player, 2, 440);
                Glyph(player, 3, 358);
                Glyph(player, 4, 441);
                Glyph(player, 5, 356);

                // Talent
                player->learnSpell(19421); player->addTalent(19421, player->GetActiveSpecMask(), true);
                player->learnSpell(19431); player->addTalent(19431, player->GetActiveSpecMask(), true);
                player->learnSpell(19434); player->addTalent(19434, player->GetActiveSpecMask(), true);
                player->learnSpell(19456); player->addTalent(19456, player->GetActiveSpecMask(), true);
                player->learnSpell(19490); player->addTalent(19490, player->GetActiveSpecMask(), true);
                player->learnSpell(19575); player->addTalent(19575, player->GetActiveSpecMask(), true);
                player->learnSpell(19574); player->addTalent(19574, player->GetActiveSpecMask(), true);
                player->learnSpell(19577); player->addTalent(19577, player->GetActiveSpecMask(), true);
                player->learnSpell(19587); player->addTalent(19587, player->GetActiveSpecMask(), true);
                player->learnSpell(19592); player->addTalent(19592, player->GetActiveSpecMask(), true);
                player->learnSpell(19602); player->addTalent(19602, player->GetActiveSpecMask(), true);
                player->learnSpell(19609); player->addTalent(19609, player->GetActiveSpecMask(), true);
                player->learnSpell(19620); player->addTalent(19620, player->GetActiveSpecMask(), true);
                player->learnSpell(19623); player->addTalent(19623, player->GetActiveSpecMask(), true);
                player->learnSpell(20895); player->addTalent(20895, player->GetActiveSpecMask(), true);
                player->learnSpell(34454); player->addTalent(34454, player->GetActiveSpecMask(), true);
                player->learnSpell(34460); player->addTalent(34460, player->GetActiveSpecMask(), true);
                player->learnSpell(34470); player->addTalent(34470, player->GetActiveSpecMask(), true);
                player->learnSpell(34484); player->addTalent(34484, player->GetActiveSpecMask(), true);
                player->learnSpell(34692); player->addTalent(34692, player->GetActiveSpecMask(), true);
                player->learnSpell(35030); player->addTalent(35030, player->GetActiveSpecMask(), true);
                player->learnSpell(53260); player->addTalent(53260, player->GetActiveSpecMask(), true);
                player->learnSpell(53264); player->addTalent(53264, player->GetActiveSpecMask(), true);
                player->learnSpell(53265); player->addTalent(53265, player->GetActiveSpecMask(), true);
                player->learnSpell(53270); player->addTalent(53270, player->GetActiveSpecMask(), true);
                player->learnSpell(56318); player->addTalent(56318, player->GetActiveSpecMask(), true);

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

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_AGILITY_3_CRITICAL_DAMAGE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ALL_STATS_10);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_NECK), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_3, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_50_ATTACK_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_40_ATTACK_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_22_AGILITY);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_50_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_44_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_75_ATTACK_POWER_22_CRITICAL);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BERSERKING);

                // Glyph
                Glyph(player, 0, 351);
                Glyph(player, 1, 439);
                Glyph(player, 2, 440);
                Glyph(player, 3, 358);
                Glyph(player, 4, 441);
                Glyph(player, 5, 366);

                // Talent
                player->learnSpell(19256); player->addTalent(19256, player->GetActiveSpecMask(), true);
                player->learnSpell(19286); player->addTalent(19286, player->GetActiveSpecMask(), true);
                player->learnSpell(19388); player->addTalent(19388, player->GetActiveSpecMask(), true);
                player->learnSpell(19407); player->addTalent(19407, player->GetActiveSpecMask(), true);
                player->learnSpell(19418); player->addTalent(19418, player->GetActiveSpecMask(), true);
                player->learnSpell(19431); player->addTalent(19431, player->GetActiveSpecMask(), true);
                player->learnSpell(19434); player->addTalent(19434, player->GetActiveSpecMask(), true);
                player->learnSpell(19466); player->addTalent(19466, player->GetActiveSpecMask(), true);
                player->learnSpell(19490); player->addTalent(19490, player->GetActiveSpecMask(), true);
                player->learnSpell(19500); player->addTalent(19500, player->GetActiveSpecMask(), true);
                player->learnSpell(19503); player->addTalent(19503, player->GetActiveSpecMask(), true);
                player->learnSpell(19506); player->addTalent(19506, player->GetActiveSpecMask(), true);
                player->learnSpell(19508); player->addTalent(19508, player->GetActiveSpecMask(), true);
                player->learnSpell(23989); player->addTalent(23989, player->GetActiveSpecMask(), true);
                player->learnSpell(24691); player->addTalent(24691, player->GetActiveSpecMask(), true);
                player->learnSpell(34476); player->addTalent(34476, player->GetActiveSpecMask(), true);
                player->learnSpell(34484); player->addTalent(34484, player->GetActiveSpecMask(), true);
                player->learnSpell(34489); player->addTalent(34489, player->GetActiveSpecMask(), true);
                player->learnSpell(34490); player->addTalent(34490, player->GetActiveSpecMask(), true);
                player->learnSpell(34496); player->addTalent(34496, player->GetActiveSpecMask(), true);
                player->learnSpell(34950); player->addTalent(34950, player->GetActiveSpecMask(), true);
                player->learnSpell(35102); player->addTalent(35102, player->GetActiveSpecMask(), true);
                player->learnSpell(35111); player->addTalent(35111, player->GetActiveSpecMask(), true);
                player->learnSpell(52785); player->addTalent(52785, player->GetActiveSpecMask(), true);
                player->learnSpell(53209); player->addTalent(53209, player->GetActiveSpecMask(), true);
                player->learnSpell(53217); player->addTalent(53217, player->GetActiveSpecMask(), true);
                player->learnSpell(53221); player->addTalent(53221, player->GetActiveSpecMask(), true);
                player->learnSpell(53232); player->addTalent(53232, player->GetActiveSpecMask(), true);
                player->learnSpell(53238); player->addTalent(53238, player->GetActiveSpecMask(), true);
                player->learnSpell(53246); player->addTalent(53246, player->GetActiveSpecMask(), true);

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

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_AGILITY_3_CRITICAL_DAMAGE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ALL_STATS_10);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_NECK), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_3, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_50_ATTACK_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_40_ATTACK_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_22_AGILITY);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_50_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_44_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_75_ATTACK_POWER_22_CRITICAL);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BERSERKING);

                // Glyph
                Glyph(player, 0, 351);
                Glyph(player, 1, 439);
                Glyph(player, 2, 440);
                Glyph(player, 3, 358);
                Glyph(player, 4, 441);
                Glyph(player, 5, 691);

                // Talent
                player->learnSpell(3674);  player->addTalent(3674,  player->GetActiveSpecMask(), true);
                player->learnSpell(19259); player->addTalent(19259, player->GetActiveSpecMask(), true);
                player->learnSpell(19287); player->addTalent(19287, player->GetActiveSpecMask(), true);
                player->learnSpell(19373); player->addTalent(19373, player->GetActiveSpecMask(), true);
                player->learnSpell(19386); player->addTalent(19386, player->GetActiveSpecMask(), true);
                player->learnSpell(19388); player->addTalent(19388, player->GetActiveSpecMask(), true);
                player->learnSpell(19431); player->addTalent(19431, player->GetActiveSpecMask(), true);
                player->learnSpell(19434); player->addTalent(19434, player->GetActiveSpecMask(), true);
                player->learnSpell(19490); player->addTalent(19490, player->GetActiveSpecMask(), true);
                player->learnSpell(19500); player->addTalent(19500, player->GetActiveSpecMask(), true);
                player->learnSpell(19503); player->addTalent(19503, player->GetActiveSpecMask(), true);
                player->learnSpell(19553); player->addTalent(19553, player->GetActiveSpecMask(), true);
                player->learnSpell(24297); player->addTalent(24297, player->GetActiveSpecMask(), true);
                player->learnSpell(34484); player->addTalent(34484, player->GetActiveSpecMask(), true);
                player->learnSpell(34496); player->addTalent(34496, player->GetActiveSpecMask(), true);
                player->learnSpell(34499); player->addTalent(34499, player->GetActiveSpecMask(), true);
                player->learnSpell(34503); player->addTalent(34503, player->GetActiveSpecMask(), true);
                player->learnSpell(34839); player->addTalent(34839, player->GetActiveSpecMask(), true);
                player->learnSpell(52785); player->addTalent(52785, player->GetActiveSpecMask(), true);
                player->learnSpell(53292); player->addTalent(53292, player->GetActiveSpecMask(), true);
                player->learnSpell(53301); player->addTalent(53301, player->GetActiveSpecMask(), true);
                player->learnSpell(56337); player->addTalent(56337, player->GetActiveSpecMask(), true);
                player->learnSpell(56341); player->addTalent(56341, player->GetActiveSpecMask(), true);
                player->learnSpell(56344); player->addTalent(56344, player->GetActiveSpecMask(), true);
                player->learnSpell(63458); player->addTalent(63458, player->GetActiveSpecMask(), true);

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

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_INTELLECTL_RESTORE_MANA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, GREEN_10_RESILIENCE_5_MANA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, GREEN_10_RESILIENCE_5_MANA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_RESILIENCE_5_MANA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_RESILIENCE_5_MANA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_29_SPELL_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_23_SPELL_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_23_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_30_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_23_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_50_SPELL_POWER_30_STAMINA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_63_SPELL_POWER);

                // Glyph
                Glyph(player, 0, 713);
                Glyph(player, 1, 458);
                Glyph(player, 2, 459);
                Glyph(player, 3, 257);
                Glyph(player, 4, 463);
                Glyph(player, 5, 710);

                // Talent
                player->learnSpell(14791); player->addTalent(14791, player->GetActiveSpecMask(), true);
                player->learnSpell(14785); player->addTalent(14785, player->GetActiveSpecMask(), true);
                player->learnSpell(14771); player->addTalent(14771, player->GetActiveSpecMask(), true);
                player->learnSpell(14777); player->addTalent(14777, player->GetActiveSpecMask(), true);
                player->learnSpell(14751); player->addTalent(14751, player->GetActiveSpecMask(), true);
                player->learnSpell(14769); player->addTalent(14769, player->GetActiveSpecMask(), true);
                player->learnSpell(33171); player->addTalent(33171, player->GetActiveSpecMask(), true);
                player->learnSpell(14781); player->addTalent(14781, player->GetActiveSpecMask(), true);
                player->learnSpell(14772); player->addTalent(14772, player->GetActiveSpecMask(), true);
                player->learnSpell(18555); player->addTalent(18555, player->GetActiveSpecMask(), true);
                player->learnSpell(63574); player->addTalent(63574, player->GetActiveSpecMask(), true);
                player->learnSpell(33190); player->addTalent(33190, player->GetActiveSpecMask(), true);
                player->learnSpell(34910); player->addTalent(34910, player->GetActiveSpecMask(), true);
                player->learnSpell(45244); player->addTalent(45244, player->GetActiveSpecMask(), true);
                player->learnSpell(10060); player->addTalent(10060, player->GetActiveSpecMask(), true);
                player->learnSpell(57472); player->addTalent(57472, player->GetActiveSpecMask(), true);
                player->learnSpell(47537); player->addTalent(47537, player->GetActiveSpecMask(), true);
                player->learnSpell(47508); player->addTalent(47508, player->GetActiveSpecMask(), true);
                player->learnSpell(47511); player->addTalent(47511, player->GetActiveSpecMask(), true);
                player->learnSpell(33206); player->addTalent(33206, player->GetActiveSpecMask(), true);
                player->learnSpell(47516); player->addTalent(47516, player->GetActiveSpecMask(), true);
                player->learnSpell(52800); player->addTalent(52800, player->GetActiveSpecMask(), true);
                player->learnSpell(47540); player->addTalent(47540, player->GetActiveSpecMask(), true);
                player->learnSpell(15012); player->addTalent(15012, player->GetActiveSpecMask(), true);
                player->learnSpell(15009); player->addTalent(15009, player->GetActiveSpecMask(), true);
                player->learnSpell(18535); player->addTalent(18535, player->GetActiveSpecMask(), true);
                player->learnSpell(19236); player->addTalent(19236, player->GetActiveSpecMask(), true);
                player->learnSpell(15363); player->addTalent(15363, player->GetActiveSpecMask(), true);

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

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_INTELLECTL_RESTORE_MANA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, GREEN_10_RESILIENCE_5_MANA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, GREEN_10_RESILIENCE_5_MANA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_RESILIENCE_5_MANA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_RESILIENCE_5_MANA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_29_SPELL_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_23_SPELL_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_23_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_30_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_23_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_50_SPELL_POWER_30_STAMINA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_63_SPELL_POWER);

                // Glyph
                Glyph(player, 0, 251);
                Glyph(player, 1, 458);
                Glyph(player, 2, 459);
                Glyph(player, 3, 257);
                Glyph(player, 4, 463);
                Glyph(player, 5, 255);

                // Talent
                player->learnSpell(14767); player->addTalent(14767, player->GetActiveSpecMask(), true);
                player->learnSpell(14771); player->addTalent(14771, player->GetActiveSpecMask(), true);
                player->learnSpell(14777); player->addTalent(14777, player->GetActiveSpecMask(), true);
                player->learnSpell(14791); player->addTalent(14791, player->GetActiveSpecMask(), true);
                player->learnSpell(15011); player->addTalent(15011, player->GetActiveSpecMask(), true);
                player->learnSpell(15014); player->addTalent(15014, player->GetActiveSpecMask(), true);
                player->learnSpell(15018); player->addTalent(15018, player->GetActiveSpecMask(), true);
                player->learnSpell(15031); player->addTalent(15031, player->GetActiveSpecMask(), true);
                player->learnSpell(15356); player->addTalent(15356, player->GetActiveSpecMask(), true);
                player->learnSpell(15362); player->addTalent(15362, player->GetActiveSpecMask(), true);
                player->learnSpell(17191); player->addTalent(17191, player->GetActiveSpecMask(), true);
                player->learnSpell(19236); player->addTalent(19236, player->GetActiveSpecMask(), true);
                player->learnSpell(20711); player->addTalent(20711, player->GetActiveSpecMask(), true);
                player->learnSpell(27790); player->addTalent(27790, player->GetActiveSpecMask(), true);
                player->learnSpell(27904); player->addTalent(27904, player->GetActiveSpecMask(), true);
                player->learnSpell(33142); player->addTalent(33142, player->GetActiveSpecMask(), true);
                player->learnSpell(33154); player->addTalent(33154, player->GetActiveSpecMask(), true);
                player->learnSpell(33162); player->addTalent(33162, player->GetActiveSpecMask(), true);
                player->learnSpell(34860); player->addTalent(34860, player->GetActiveSpecMask(), true);
                player->learnSpell(34861); player->addTalent(34861, player->GetActiveSpecMask(), true);
                player->learnSpell(47567); player->addTalent(47567, player->GetActiveSpecMask(), true);
                player->learnSpell(47788); player->addTalent(47788, player->GetActiveSpecMask(), true);
                player->learnSpell(63543); player->addTalent(63543, player->GetActiveSpecMask(), true);
                player->learnSpell(63737); player->addTalent(63737, player->GetActiveSpecMask(), true);

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

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ORANGE_12_SPELL_POWER_10_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_NECK), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_HASTE_13_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_29_SPELL_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_23_SPELL_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_23_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_30_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_23_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_50_SPELL_POWER_30_STAMINA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BLACK_MAGIC);

                // Glyph
                Glyph(player, 0, 263);
                Glyph(player, 1, 463);
                Glyph(player, 2, 458);
                Glyph(player, 3, 257);
                Glyph(player, 4, 459);
                Glyph(player, 5, 708);

                // Talent
                player->learnSpell(14747); player->addTalent(14747, player->GetActiveSpecMask(), true);
                player->learnSpell(14791); player->addTalent(14791, player->GetActiveSpecMask(), true);
                player->learnSpell(15008); player->addTalent(15008, player->GetActiveSpecMask(), true);
                player->learnSpell(15286); player->addTalent(15286, player->GetActiveSpecMask(), true);
                player->learnSpell(15308); player->addTalent(15308, player->GetActiveSpecMask(), true);
                player->learnSpell(15316); player->addTalent(15316, player->GetActiveSpecMask(), true);
                player->learnSpell(15317); player->addTalent(15317, player->GetActiveSpecMask(), true);
                player->learnSpell(15331); player->addTalent(15331, player->GetActiveSpecMask(), true);
                player->learnSpell(15336); player->addTalent(15336, player->GetActiveSpecMask(), true);
                player->learnSpell(15338); player->addTalent(15338, player->GetActiveSpecMask(), true);
                player->learnSpell(15407); player->addTalent(15407, player->GetActiveSpecMask(), true);
                player->learnSpell(15448); player->addTalent(15448, player->GetActiveSpecMask(), true);
                player->learnSpell(15473); player->addTalent(15473, player->GetActiveSpecMask(), true);
                player->learnSpell(15487); player->addTalent(15487, player->GetActiveSpecMask(), true);
                player->learnSpell(17191); player->addTalent(17191, player->GetActiveSpecMask(), true);
                player->learnSpell(17322); player->addTalent(17322, player->GetActiveSpecMask(), true);
                player->learnSpell(27816); player->addTalent(27816, player->GetActiveSpecMask(), true);
                player->learnSpell(27840); player->addTalent(27840, player->GetActiveSpecMask(), true);
                player->learnSpell(27904); player->addTalent(27904, player->GetActiveSpecMask(), true);
                player->learnSpell(33193); player->addTalent(33193, player->GetActiveSpecMask(), true);
                player->learnSpell(33213); player->addTalent(33213, player->GetActiveSpecMask(), true);
                player->learnSpell(33225); player->addTalent(33225, player->GetActiveSpecMask(), true);
                player->learnSpell(33371); player->addTalent(33371, player->GetActiveSpecMask(), true);
                player->learnSpell(34914); player->addTalent(34914, player->GetActiveSpecMask(), true);
                player->learnSpell(47570); player->addTalent(47570, player->GetActiveSpecMask(), true);
                player->learnSpell(47581); player->addTalent(47581, player->GetActiveSpecMask(), true);
                player->learnSpell(47585); player->addTalent(47585, player->GetActiveSpecMask(), true);
                player->learnSpell(51167); player->addTalent(51167, player->GetActiveSpecMask(), true);
                player->learnSpell(63627); player->addTalent(63627, player->GetActiveSpecMask(), true);
                player->learnSpell(64044); player->addTalent(64044, player->GetActiveSpecMask(), true);

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

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, BLUE_20_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, BLUE_20_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, BLUE_20_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, BLUE_20_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_20_ARMOR_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT_2, BLUE_20_SPELL_PENETRATION);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_50_ATTACK_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_40_ATTACK_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_22_AGILITY);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_50_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_44_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_75_ATTACK_POWER_22_CRITICAL);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BERSERKING);

                // Glyph
                Glyph(player, 0, 771);
                Glyph(player, 2, 555);
                Glyph(player, 1, 522);
                Glyph(player, 3, 558);
                Glyph(player, 4, 514);
                Glyph(player, 5, 528);

                // Talent
                player->learnSpell(48982); player->addTalent(48982, player->GetActiveSpecMask(), true);
                player->learnSpell(49005); player->addTalent(49005, player->GetActiveSpecMask(), true);
                player->learnSpell(49028); player->addTalent(49028, player->GetActiveSpecMask(), true);
                player->learnSpell(49393); player->addTalent(49393, player->GetActiveSpecMask(), true);
                player->learnSpell(49395); player->addTalent(49395, player->GetActiveSpecMask(), true);
                player->learnSpell(49480); player->addTalent(49480, player->GetActiveSpecMask(), true);
                player->learnSpell(49483); player->addTalent(49483, player->GetActiveSpecMask(), true);
                player->learnSpell(49489); player->addTalent(49489, player->GetActiveSpecMask(), true);
                player->learnSpell(49497); player->addTalent(49497, player->GetActiveSpecMask(), true);
                player->learnSpell(49504); player->addTalent(49504, player->GetActiveSpecMask(), true);
                player->learnSpell(49530); player->addTalent(49530, player->GetActiveSpecMask(), true);
                player->learnSpell(49534); player->addTalent(49534, player->GetActiveSpecMask(), true);
                player->learnSpell(49787); player->addTalent(49787, player->GetActiveSpecMask(), true);
                player->learnSpell(50029); player->addTalent(50029, player->GetActiveSpecMask(), true);
                player->learnSpell(50034); player->addTalent(50034, player->GetActiveSpecMask(), true);
                player->learnSpell(50147); player->addTalent(50147, player->GetActiveSpecMask(), true);
                player->learnSpell(50150); player->addTalent(50150, player->GetActiveSpecMask(), true);
                player->learnSpell(50371); player->addTalent(50371, player->GetActiveSpecMask(), true);
                player->learnSpell(51456); player->addTalent(51456, player->GetActiveSpecMask(), true);
                player->learnSpell(53138); player->addTalent(53138, player->GetActiveSpecMask(), true);
                player->learnSpell(55050); player->addTalent(55050, player->GetActiveSpecMask(), true);
                player->learnSpell(55062); player->addTalent(55062, player->GetActiveSpecMask(), true);
                player->learnSpell(55108); player->addTalent(55108, player->GetActiveSpecMask(), true);
                player->learnSpell(55225); player->addTalent(55225, player->GetActiveSpecMask(), true);
                player->learnSpell(55233); player->addTalent(55233, player->GetActiveSpecMask(), true);
                player->learnSpell(61158); player->addTalent(61158, player->GetActiveSpecMask(), true);
                player->learnSpell(62908); player->addTalent(62908, player->GetActiveSpecMask(), true);

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

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, BLUE_20_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, BLUE_20_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, BLUE_20_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, BLUE_20_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_50_ATTACK_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_40_ATTACK_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_22_AGILITY);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_50_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_44_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_75_ATTACK_POWER_22_CRITICAL);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BERSERKING);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BERSERKING);

                // Glyph
                Glyph(player, 0, 525);
                Glyph(player, 1, 522);
                Glyph(player, 2, 518);
                Glyph(player, 3, 773);
                Glyph(player, 4, 553);
                Glyph(player, 5, 521);

                // Talent
                player->learnSpell(48982); player->addTalent(48982, player->GetActiveSpecMask(), true);
                player->learnSpell(49039); player->addTalent(49039, player->GetActiveSpecMask(), true);
                player->learnSpell(49143); player->addTalent(49143, player->GetActiveSpecMask(), true);
                player->learnSpell(49184); player->addTalent(49184, player->GetActiveSpecMask(), true);
                player->learnSpell(49203); player->addTalent(49203, player->GetActiveSpecMask(), true);
                player->learnSpell(49393); player->addTalent(49393, player->GetActiveSpecMask(), true);
                player->learnSpell(49479); player->addTalent(49479, player->GetActiveSpecMask(), true);
                player->learnSpell(49483); player->addTalent(49483, player->GetActiveSpecMask(), true);
                player->learnSpell(49489); player->addTalent(49489, player->GetActiveSpecMask(), true);
                player->learnSpell(49491); player->addTalent(49491, player->GetActiveSpecMask(), true);
                player->learnSpell(49538); player->addTalent(49538, player->GetActiveSpecMask(), true);
                player->learnSpell(49657); player->addTalent(49657, player->GetActiveSpecMask(), true);
                player->learnSpell(49662); player->addTalent(49662, player->GetActiveSpecMask(), true);
                player->learnSpell(49791); player->addTalent(49791, player->GetActiveSpecMask(), true);
                player->learnSpell(49796); player->addTalent(49796, player->GetActiveSpecMask(), true);
                player->learnSpell(50043); player->addTalent(50043, player->GetActiveSpecMask(), true);
                player->learnSpell(50130); player->addTalent(50130, player->GetActiveSpecMask(), true);
                player->learnSpell(50138); player->addTalent(50138, player->GetActiveSpecMask(), true);
                player->learnSpell(50147); player->addTalent(50147, player->GetActiveSpecMask(), true);
                player->learnSpell(50191); player->addTalent(50191, player->GetActiveSpecMask(), true);
                player->learnSpell(50884); player->addTalent(50884, player->GetActiveSpecMask(), true);
                player->learnSpell(51130); player->addTalent(51130, player->GetActiveSpecMask(), true);
                player->learnSpell(51456); player->addTalent(51456, player->GetActiveSpecMask(), true);
                player->learnSpell(51473); player->addTalent(51473, player->GetActiveSpecMask(), true);
                player->learnSpell(54637); player->addTalent(54637, player->GetActiveSpecMask(), true);
                player->learnSpell(59057); player->addTalent(59057, player->GetActiveSpecMask(), true);
                player->learnSpell(66192); player->addTalent(66192, player->GetActiveSpecMask(), true);

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

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, BLUE_20_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, BLUE_20_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, BLUE_20_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, BLUE_20_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_20_STRENGTH);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT_2, RED_20_STRENGTH);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_50_ATTACK_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_40_ATTACK_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_22_AGILITY);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_50_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_44_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_75_ATTACK_POWER_22_CRITICAL);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BERSERKING);

                // Glyph
                Glyph(player, 0, 772);
                Glyph(player, 1, 522);
                Glyph(player, 2, 553);
                Glyph(player, 3, 771);
                Glyph(player, 4, 518);
                Glyph(player, 5, 527);

                // Talent
                player->learnSpell(49036); player->addTalent(49036, player->GetActiveSpecMask(), true);
                player->learnSpell(49039); player->addTalent(49039, player->GetActiveSpecMask(), true);
                player->learnSpell(49158); player->addTalent(49158, player->GetActiveSpecMask(), true);
                player->learnSpell(49194); player->addTalent(49194, player->GetActiveSpecMask(), true);
                player->learnSpell(49206); player->addTalent(49206, player->GetActiveSpecMask(), true);
                player->learnSpell(49222); player->addTalent(49222, player->GetActiveSpecMask(), true);
                player->learnSpell(49565); player->addTalent(49565, player->GetActiveSpecMask(), true);
                player->learnSpell(49568); player->addTalent(49568, player->GetActiveSpecMask(), true);
                player->learnSpell(49572); player->addTalent(49572, player->GetActiveSpecMask(), true);
                player->learnSpell(49589); player->addTalent(49589, player->GetActiveSpecMask(), true);
                player->learnSpell(49599); player->addTalent(49599, player->GetActiveSpecMask(), true);
                player->learnSpell(49611); player->addTalent(49611, player->GetActiveSpecMask(), true);
                player->learnSpell(49632); player->addTalent(49632, player->GetActiveSpecMask(), true);
                player->learnSpell(49638); player->addTalent(49638, player->GetActiveSpecMask(), true);
                player->learnSpell(49657); player->addTalent(49657, player->GetActiveSpecMask(), true);
                player->learnSpell(49664); player->addTalent(49664, player->GetActiveSpecMask(), true);
                player->learnSpell(50121); player->addTalent(50121, player->GetActiveSpecMask(), true);
                player->learnSpell(50147); player->addTalent(50147, player->GetActiveSpecMask(), true);
                player->learnSpell(50392); player->addTalent(50392, player->GetActiveSpecMask(), true);
                player->learnSpell(50886); player->addTalent(50886, player->GetActiveSpecMask(), true);
                player->learnSpell(51052); player->addTalent(51052, player->GetActiveSpecMask(), true);
                player->learnSpell(51161); player->addTalent(51161, player->GetActiveSpecMask(), true);
                player->learnSpell(51456); player->addTalent(51456, player->GetActiveSpecMask(), true);
                player->learnSpell(51746); player->addTalent(51746, player->GetActiveSpecMask(), true);
                player->learnSpell(52143); player->addTalent(52143, player->GetActiveSpecMask(), true);
                player->learnSpell(55090); player->addTalent(55090, player->GetActiveSpecMask(), true);
                player->learnSpell(55237); player->addTalent(55237, player->GetActiveSpecMask(), true);
                player->learnSpell(55623); player->addTalent(55623, player->GetActiveSpecMask(), true);
                player->learnSpell(55667); player->addTalent(55667, player->GetActiveSpecMask(), true);
                player->learnSpell(56835); player->addTalent(56835, player->GetActiveSpecMask(), true);

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

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, RED_23_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_NECK), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_23_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, ORANGE_12_SPELL_POWER_10_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_23_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_29_SPELL_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_23_SPELL_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_23_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_30_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_23_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_50_SPELL_POWER_30_STAMINA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BLACK_MAGIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), PERM_ENCHANTMENT_SLOT, SHIELD_21_RESILIENCE);

                // Glyph
                Glyph(player, 0, 754);
                Glyph(player, 2, 474);
                Glyph(player, 1, 476);
                Glyph(player, 3, 214);
                Glyph(player, 4, 552);
                Glyph(player, 5, 752);

                // Talent
                player->learnSpell(16041); player->addTalent(16041, player->GetActiveSpecMask(), true);
                player->learnSpell(16108); player->addTalent(16108, player->GetActiveSpecMask(), true);
                player->learnSpell(16130); player->addTalent(16130, player->GetActiveSpecMask(), true);
                player->learnSpell(16161); player->addTalent(16161, player->GetActiveSpecMask(), true);
                player->learnSpell(16164); player->addTalent(16164, player->GetActiveSpecMask(), true);
                player->learnSpell(16166); player->addTalent(16166, player->GetActiveSpecMask(), true);
                player->learnSpell(16287); player->addTalent(16287, player->GetActiveSpecMask(), true);
                player->learnSpell(16305); player->addTalent(16305, player->GetActiveSpecMask(), true);
                player->learnSpell(16582); player->addTalent(16582, player->GetActiveSpecMask(), true);
                player->learnSpell(17487); player->addTalent(17487, player->GetActiveSpecMask(), true);
                player->learnSpell(28998); player->addTalent(28998, player->GetActiveSpecMask(), true);
                player->learnSpell(29000); player->addTalent(29000, player->GetActiveSpecMask(), true);
                player->learnSpell(29065); player->addTalent(29065, player->GetActiveSpecMask(), true);
                player->learnSpell(29080); player->addTalent(29080, player->GetActiveSpecMask(), true);
                player->learnSpell(30666); player->addTalent(30666, player->GetActiveSpecMask(), true);
                player->learnSpell(30679); player->addTalent(30679, player->GetActiveSpecMask(), true);
                player->learnSpell(30706); player->addTalent(30706, player->GetActiveSpecMask(), true);
                player->learnSpell(43338); player->addTalent(43338, player->GetActiveSpecMask(), true);
                player->learnSpell(51470); player->addTalent(51470, player->GetActiveSpecMask(), true);
                player->learnSpell(51479); player->addTalent(51479, player->GetActiveSpecMask(), true);
                player->learnSpell(51482); player->addTalent(51482, player->GetActiveSpecMask(), true);
                player->learnSpell(51486); player->addTalent(51486, player->GetActiveSpecMask(), true);
                player->learnSpell(51490); player->addTalent(51490, player->GetActiveSpecMask(), true);
                player->learnSpell(60188); player->addTalent(60188, player->GetActiveSpecMask(), true);
                player->learnSpell(62101); player->addTalent(62101, player->GetActiveSpecMask(), true);
                player->learnSpell(63372); player->addTalent(63372, player->GetActiveSpecMask(), true);

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

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_AGILITY_3_CRITICAL_DAMAGE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ALL_STATS_10);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_50_ATTACK_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_40_ATTACK_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_22_AGILITY);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_50_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_44_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_75_ATTACK_POWER_22_CRITICAL);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BERSERKING);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BERSERKING);

                // Glyph
                Glyph(player, 0, 228);
                Glyph(player, 1, 552);
                Glyph(player, 2, 475);
                Glyph(player, 3, 736);
                Glyph(player, 4, 476);
                Glyph(player, 5, 754);

                // Talent
                player->learnSpell(16112); player->addTalent(16112, player->GetActiveSpecMask(), true);
                player->learnSpell(16130); player->addTalent(16130, player->GetActiveSpecMask(), true);
                player->learnSpell(16164); player->addTalent(16164, player->GetActiveSpecMask(), true);
                player->learnSpell(16268); player->addTalent(16268, player->GetActiveSpecMask(), true);
                player->learnSpell(16284); player->addTalent(16284, player->GetActiveSpecMask(), true);
                player->learnSpell(16272); player->addTalent(16272, player->GetActiveSpecMask(), true);
                player->learnSpell(16287); player->addTalent(16287, player->GetActiveSpecMask(), true);
                player->learnSpell(16305); player->addTalent(16305, player->GetActiveSpecMask(), true);
                player->learnSpell(16306); player->addTalent(16306, player->GetActiveSpecMask(), true);
                player->learnSpell(17364); player->addTalent(17364, player->GetActiveSpecMask(), true);
                player->learnSpell(17489); player->addTalent(17489, player->GetActiveSpecMask(), true);
                player->learnSpell(28998); player->addTalent(28998, player->GetActiveSpecMask(), true);
                player->learnSpell(29080); player->addTalent(29080, player->GetActiveSpecMask(), true);
                player->learnSpell(29086); player->addTalent(29086, player->GetActiveSpecMask(), true);
                player->learnSpell(29179); player->addTalent(29179, player->GetActiveSpecMask(), true);
                player->learnSpell(30798); player->addTalent(30798, player->GetActiveSpecMask(), true);
                player->learnSpell(30809); player->addTalent(30809, player->GetActiveSpecMask(), true);
                player->learnSpell(30814); player->addTalent(30814, player->GetActiveSpecMask(), true);
                player->learnSpell(30823); player->addTalent(30823, player->GetActiveSpecMask(), true);
                player->learnSpell(43338); player->addTalent(43338, player->GetActiveSpecMask(), true);
                player->learnSpell(51522); player->addTalent(51522, player->GetActiveSpecMask(), true);
                player->learnSpell(51524); player->addTalent(51524, player->GetActiveSpecMask(), true);
                player->learnSpell(51532); player->addTalent(51532, player->GetActiveSpecMask(), true);
                player->learnSpell(51533); player->addTalent(51533, player->GetActiveSpecMask(), true);
                player->learnSpell(51881); player->addTalent(51881, player->GetActiveSpecMask(), true);
                player->learnSpell(51885); player->addTalent(51885, player->GetActiveSpecMask(), true);
                player->learnSpell(60103); player->addTalent(60103, player->GetActiveSpecMask(), true);
                player->learnSpell(63374); player->addTalent(63374, player->GetActiveSpecMask(), true);

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

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_INTELLECTL_RESTORE_MANA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, GREEN_10_RESILIENCE_5_MANA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, GREEN_10_RESILIENCE_5_MANA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_RESILIENCE_5_MANA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_RESILIENCE_5_MANA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_29_SPELL_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_23_SPELL_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_23_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_30_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_23_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_50_SPELL_POWER_30_STAMINA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BLACK_MAGIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), PERM_ENCHANTMENT_SLOT, SHIELD_21_RESILIENCE);

                // Glyph
                Glyph(player, 0, 223);
                Glyph(player, 1, 476);
                Glyph(player, 2, 552);
                Glyph(player, 3, 751);
                Glyph(player, 4, 475);
                Glyph(player, 5, 754);

                // Talent
                player->learnSpell(974);   player->addTalent(974,   player->GetActiveSpecMask(), true);
                player->learnSpell(16130); player->addTalent(16130, player->GetActiveSpecMask(), true);
                player->learnSpell(16188); player->addTalent(16188, player->GetActiveSpecMask(), true);
                player->learnSpell(16190); player->addTalent(16190, player->GetActiveSpecMask(), true);
                player->learnSpell(16198); player->addTalent(16198, player->GetActiveSpecMask(), true);
                player->learnSpell(16206); player->addTalent(16206, player->GetActiveSpecMask(), true);
                player->learnSpell(16213); player->addTalent(16213, player->GetActiveSpecMask(), true);
                player->learnSpell(16214); player->addTalent(16214, player->GetActiveSpecMask(), true);
                player->learnSpell(16229); player->addTalent(16229, player->GetActiveSpecMask(), true);
                player->learnSpell(16232); player->addTalent(16232, player->GetActiveSpecMask(), true);
                player->learnSpell(16240); player->addTalent(16240, player->GetActiveSpecMask(), true);
                player->learnSpell(16287); player->addTalent(16287, player->GetActiveSpecMask(), true);
                player->learnSpell(16293); player->addTalent(16293, player->GetActiveSpecMask(), true);
                player->learnSpell(17487); player->addTalent(17487, player->GetActiveSpecMask(), true);
                player->learnSpell(29191); player->addTalent(29191, player->GetActiveSpecMask(), true);
                player->learnSpell(29202); player->addTalent(29202, player->GetActiveSpecMask(), true);
                player->learnSpell(30866); player->addTalent(30866, player->GetActiveSpecMask(), true);
                player->learnSpell(30869); player->addTalent(30869, player->GetActiveSpecMask(), true);
                player->learnSpell(30886); player->addTalent(30886, player->GetActiveSpecMask(), true);
                player->learnSpell(51555); player->addTalent(51555, player->GetActiveSpecMask(), true);
                player->learnSpell(51558); player->addTalent(51558, player->GetActiveSpecMask(), true);
                player->learnSpell(51561); player->addTalent(51561, player->GetActiveSpecMask(), true);
                player->learnSpell(51566); player->addTalent(51566, player->GetActiveSpecMask(), true);
                player->learnSpell(51881); player->addTalent(51881, player->GetActiveSpecMask(), true);
                player->learnSpell(51886); player->addTalent(51886, player->GetActiveSpecMask(), true);
                player->learnSpell(55198); player->addTalent(55198, player->GetActiveSpecMask(), true);
                player->learnSpell(61295); player->addTalent(61295, player->GetActiveSpecMask(), true);

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

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ORANGE_12_SPELL_POWER_10_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_HASTE_13_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_3, ORANGE_12_SPELL_POWER_10_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_29_SPELL_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_23_SPELL_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_23_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_30_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_23_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_50_SPELL_POWER_30_STAMINA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BLACK_MAGIC);

                // Glyph
                Glyph(player, 0, 329);
                Glyph(player, 2, 447);
                Glyph(player, 1, 446);
                Glyph(player, 3, 315);
                Glyph(player, 4, 451);
                Glyph(player, 5, 312);

                // Talent
                player->learnSpell(12042); player->addTalent(12042, player->GetActiveSpecMask(), true);
                player->learnSpell(12043); player->addTalent(12043, player->GetActiveSpecMask(), true);
                player->learnSpell(12469); player->addTalent(12469, player->GetActiveSpecMask(), true);
                player->learnSpell(12472); player->addTalent(12472, player->GetActiveSpecMask(), true);
                player->learnSpell(12496); player->addTalent(12496, player->GetActiveSpecMask(), true);
                player->learnSpell(12503); player->addTalent(12503, player->GetActiveSpecMask(), true);
                player->learnSpell(12577); player->addTalent(12577, player->GetActiveSpecMask(), true);
                player->learnSpell(12592); player->addTalent(12592, player->GetActiveSpecMask(), true);
                player->learnSpell(12598); player->addTalent(12598, player->GetActiveSpecMask(), true);
                player->learnSpell(12672); player->addTalent(12672, player->GetActiveSpecMask(), true);
                player->learnSpell(12840); player->addTalent(12840, player->GetActiveSpecMask(), true);
                player->learnSpell(15060); player->addTalent(15060, player->GetActiveSpecMask(), true);
                player->learnSpell(18459); player->addTalent(18459, player->GetActiveSpecMask(), true);
                player->learnSpell(18464); player->addTalent(18464, player->GetActiveSpecMask(), true);
                player->learnSpell(29440); player->addTalent(29440, player->GetActiveSpecMask(), true);
                player->learnSpell(31572); player->addTalent(31572, player->GetActiveSpecMask(), true);
                player->learnSpell(31583); player->addTalent(31583, player->GetActiveSpecMask(), true);
                player->learnSpell(31588); player->addTalent(31588, player->GetActiveSpecMask(), true);
                player->learnSpell(31589); player->addTalent(31589, player->GetActiveSpecMask(), true);
                player->learnSpell(35581); player->addTalent(35581, player->GetActiveSpecMask(), true);
                player->learnSpell(44379); player->addTalent(44379, player->GetActiveSpecMask(), true);
                player->learnSpell(44399); player->addTalent(44399, player->GetActiveSpecMask(), true);
                player->learnSpell(44403); player->addTalent(44403, player->GetActiveSpecMask(), true);
                player->learnSpell(44425); player->addTalent(44425, player->GetActiveSpecMask(), true);
                player->learnSpell(54490); player->addTalent(54490, player->GetActiveSpecMask(), true);
                player->learnSpell(54646); player->addTalent(54646, player->GetActiveSpecMask(), true);
                player->learnSpell(55094); player->addTalent(55094, player->GetActiveSpecMask(), true);
                player->learnSpell(55340); player->addTalent(55340, player->GetActiveSpecMask(), true);

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
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 47059, true);
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47041, true);
                }
                else
                {
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 47271, true);
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47432, true);
                }

                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51457, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 51532, true);

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, RED_23_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_CRITICAL);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_23_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_CRITICAL);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, BLUE_20_SPIRIT);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, BLUE_20_SPIRIT);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, BLUE_20_SPIRIT);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_23_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, BLUE_20_SPIRIT);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_3, YELLOW_20_CRITICAL);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_CRITICAL);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, YELLOW_20_CRITICAL);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, YELLOW_20_CRITICAL);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_23_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT_2, BLUE_20_SPIRIT);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_29_SPELL_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_23_SPELL_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_23_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_30_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_23_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_50_SPELL_POWER_30_STAMINA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BLACK_MAGIC);

                // Glyph
                Glyph(player, 0, 329);
                Glyph(player, 1, 446);
                Glyph(player, 2, 447);
                Glyph(player, 3, 315);
                Glyph(player, 4, 451);
                Glyph(player, 5, 324);

                // Talent
                player->learnSpell(11080); player->addTalent(11080, player->GetActiveSpecMask(), true);
                player->learnSpell(11113); player->addTalent(11113, player->GetActiveSpecMask(), true);
                player->learnSpell(11129); player->addTalent(11129, player->GetActiveSpecMask(), true);
                player->learnSpell(11247); player->addTalent(11247, player->GetActiveSpecMask(), true);
                player->learnSpell(11255); player->addTalent(11255, player->GetActiveSpecMask(), true);
                player->learnSpell(11366); player->addTalent(11366, player->GetActiveSpecMask(), true);
                player->learnSpell(11368); player->addTalent(11368, player->GetActiveSpecMask(), true);
                player->learnSpell(12350); player->addTalent(12350, player->GetActiveSpecMask(), true);
                player->learnSpell(12353); player->addTalent(12353, player->GetActiveSpecMask(), true);
                player->learnSpell(12358); player->addTalent(12358, player->GetActiveSpecMask(), true);
                player->learnSpell(12399); player->addTalent(12399, player->GetActiveSpecMask(), true);
                player->learnSpell(12469); player->addTalent(12469, player->GetActiveSpecMask(), true);
                player->learnSpell(12592); player->addTalent(12592, player->GetActiveSpecMask(), true);
                player->learnSpell(12840); player->addTalent(12840, player->GetActiveSpecMask(), true);
                player->learnSpell(12848); player->addTalent(12848, player->GetActiveSpecMask(), true);
                player->learnSpell(12873); player->addTalent(12873, player->GetActiveSpecMask(), true);
                player->learnSpell(13043); player->addTalent(13043, player->GetActiveSpecMask(), true);
                player->learnSpell(29444); player->addTalent(29444, player->GetActiveSpecMask(), true);
                player->learnSpell(31642); player->addTalent(31642, player->GetActiveSpecMask(), true);
                player->learnSpell(31658); player->addTalent(31658, player->GetActiveSpecMask(), true);
                player->learnSpell(31661); player->addTalent(31661, player->GetActiveSpecMask(), true);
                player->learnSpell(31680); player->addTalent(31680, player->GetActiveSpecMask(), true);
                player->learnSpell(34296); player->addTalent(34296, player->GetActiveSpecMask(), true);
                player->learnSpell(44448); player->addTalent(44448, player->GetActiveSpecMask(), true);
                player->learnSpell(44457); player->addTalent(44457, player->GetActiveSpecMask(), true);
                player->learnSpell(44472); player->addTalent(44472, player->GetActiveSpecMask(), true);
                player->learnSpell(54646); player->addTalent(54646, player->GetActiveSpecMask(), true);
                player->learnSpell(54659); player->addTalent(54659, player->GetActiveSpecMask(), true);
                player->learnSpell(54734); player->addTalent(54734, player->GetActiveSpecMask(), true);
                player->learnSpell(64357); player->addTalent(64357, player->GetActiveSpecMask(), true);

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

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ORANGE_12_SPELL_POWER_10_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_HASTE_13_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_3, ORANGE_12_SPELL_POWER_10_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_29_SPELL_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_23_SPELL_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_23_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_30_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_23_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_50_SPELL_POWER_30_STAMINA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BLACK_MAGIC);

                // Glyph
                Glyph(player, 0, 700);
                Glyph(player, 1, 446);
                Glyph(player, 2, 447);
                Glyph(player, 3, 315);
                Glyph(player, 4, 451);
                Glyph(player, 5, 329);

                // Talent
                player->learnSpell(12497); player->addTalent(12497, player->GetActiveSpecMask(), true);
                player->learnSpell(16766); player->addTalent(16766, player->GetActiveSpecMask(), true);
                player->learnSpell(55094); player->addTalent(55094, player->GetActiveSpecMask(), true);
                player->learnSpell(15047); player->addTalent(15047, player->GetActiveSpecMask(), true);
                player->learnSpell(28332); player->addTalent(28332, player->GetActiveSpecMask(), true);
                player->learnSpell(12571); player->addTalent(12571, player->GetActiveSpecMask(), true);
                player->learnSpell(12953); player->addTalent(12953, player->GetActiveSpecMask(), true);
                player->learnSpell(12472); player->addTalent(12472, player->GetActiveSpecMask(), true);
                player->learnSpell(16758); player->addTalent(16758, player->GetActiveSpecMask(), true);
                player->learnSpell(12983); player->addTalent(12983, player->GetActiveSpecMask(), true);
                player->learnSpell(11958); player->addTalent(11958, player->GetActiveSpecMask(), true);
                player->learnSpell(55092); player->addTalent(55092, player->GetActiveSpecMask(), true);
                player->learnSpell(28593); player->addTalent(28593, player->GetActiveSpecMask(), true);
                player->learnSpell(11426); player->addTalent(11426, player->GetActiveSpecMask(), true);
                player->learnSpell(54787); player->addTalent(54787, player->GetActiveSpecMask(), true);
                player->learnSpell(31683); player->addTalent(31683, player->GetActiveSpecMask(), true);
                player->learnSpell(44545); player->addTalent(44545, player->GetActiveSpecMask(), true);
                player->learnSpell(31687); player->addTalent(31687, player->GetActiveSpecMask(), true);
                player->learnSpell(44549); player->addTalent(44549, player->GetActiveSpecMask(), true);
                player->learnSpell(44571); player->addTalent(44571, player->GetActiveSpecMask(), true);
                player->learnSpell(44572); player->addTalent(44572, player->GetActiveSpecMask(), true);
                player->learnSpell(12592); player->addTalent(12592, player->GetActiveSpecMask(), true);
                player->learnSpell(12840); player->addTalent(12840, player->GetActiveSpecMask(), true);
                player->learnSpell(54659); player->addTalent(54659, player->GetActiveSpecMask(), true);
                player->learnSpell(29444); player->addTalent(29444, player->GetActiveSpecMask(), true);
                player->learnSpell(12606); player->addTalent(12606, player->GetActiveSpecMask(), true);
                player->learnSpell(12467); player->addTalent(12467, player->GetActiveSpecMask(), true);
                player->learnSpell(54646); player->addTalent(54646, player->GetActiveSpecMask(), true);
                player->learnSpell(12598); player->addTalent(12598, player->GetActiveSpecMask(), true);
                player->learnSpell(55340); player->addTalent(55340, player->GetActiveSpecMask(), true);

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

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ORANGE_12_SPELL_POWER_10_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_HASTE_13_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_29_SPELL_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_23_SPELL_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_23_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_30_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_23_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_50_SPELL_POWER_30_STAMINA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BLACK_MAGIC);

                // Glyph
                Glyph(player, 0, 759);
                Glyph(player, 1, 482);
                Glyph(player, 2, 477);
                Glyph(player, 3, 911);
                Glyph(player, 4, 478);
                Glyph(player, 5, 283);

                // Talent
                player->learnSpell(17785); player->addTalent(17785, player->GetActiveSpecMask(), true);
                player->learnSpell(17805); player->addTalent(17805, player->GetActiveSpecMask(), true);
                player->learnSpell(17814); player->addTalent(17814, player->GetActiveSpecMask(), true);
                player->learnSpell(18095); player->addTalent(18095, player->GetActiveSpecMask(), true);
                player->learnSpell(18176); player->addTalent(18176, player->GetActiveSpecMask(), true);
                player->learnSpell(18180); player->addTalent(18180, player->GetActiveSpecMask(), true);
                player->learnSpell(18219); player->addTalent(18219, player->GetActiveSpecMask(), true);
                player->learnSpell(18223); player->addTalent(18223, player->GetActiveSpecMask(), true);
                player->learnSpell(18275); player->addTalent(18275, player->GetActiveSpecMask(), true);
                player->learnSpell(18288); player->addTalent(18288, player->GetActiveSpecMask(), true);
                player->learnSpell(18699); player->addTalent(18699, player->GetActiveSpecMask(), true);
                player->learnSpell(18704); player->addTalent(18704, player->GetActiveSpecMask(), true);
                player->learnSpell(18708); player->addTalent(18708, player->GetActiveSpecMask(), true);
                player->learnSpell(18744); player->addTalent(18744, player->GetActiveSpecMask(), true);
                player->learnSpell(19028); player->addTalent(19028, player->GetActiveSpecMask(), true);
                player->learnSpell(30057); player->addTalent(30057, player->GetActiveSpecMask(), true);
                player->learnSpell(30064); player->addTalent(30064, player->GetActiveSpecMask(), true);
                player->learnSpell(30108); player->addTalent(30108, player->GetActiveSpecMask(), true);
                player->learnSpell(30143); player->addTalent(30143, player->GetActiveSpecMask(), true);
                player->learnSpell(32383); player->addTalent(32383, player->GetActiveSpecMask(), true);
                player->learnSpell(32394); player->addTalent(32394, player->GetActiveSpecMask(), true);
                player->learnSpell(32484); player->addTalent(32484, player->GetActiveSpecMask(), true);
                player->learnSpell(47200); player->addTalent(47200, player->GetActiveSpecMask(), true);
                player->learnSpell(47205); player->addTalent(47205, player->GetActiveSpecMask(), true);
                player->learnSpell(47231); player->addTalent(47231, player->GetActiveSpecMask(), true);
                player->learnSpell(48181); player->addTalent(48181, player->GetActiveSpecMask(), true);
                player->learnSpell(53759); player->addTalent(53759, player->GetActiveSpecMask(), true);
                player->learnSpell(58435); player->addTalent(58435, player->GetActiveSpecMask(), true);
                player->learnSpell(63108); player->addTalent(63108, player->GetActiveSpecMask(), true);

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

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ALL_STATS_10);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, ALL_STATS_10);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_29_SPELL_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_23_SPELL_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_23_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_30_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_23_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_50_SPELL_POWER_30_STAMINA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BLACK_MAGIC);

                // Glyph
                Glyph(player, 0, 759);
                Glyph(player, 1, 479);
                Glyph(player, 2, 480);
                Glyph(player, 3, 281);
                Glyph(player, 4, 477);
                Glyph(player, 5, 274);

                // Talent
                player->learnSpell(17791); player->addTalent(17791, player->GetActiveSpecMask(), true);
                player->learnSpell(17803); player->addTalent(17803, player->GetActiveSpecMask(), true);
                player->learnSpell(17877); player->addTalent(17877, player->GetActiveSpecMask(), true);
                player->learnSpell(17959); player->addTalent(17959, player->GetActiveSpecMask(), true);
                player->learnSpell(18693); player->addTalent(18693, player->GetActiveSpecMask(), true);
                player->learnSpell(18699); player->addTalent(18699, player->GetActiveSpecMask(), true);
                player->learnSpell(18708); player->addTalent(18708, player->GetActiveSpecMask(), true);
                player->learnSpell(18707); player->addTalent(18707, player->GetActiveSpecMask(), true);
                player->learnSpell(18710); player->addTalent(18710, player->GetActiveSpecMask(), true);
                player->learnSpell(18744); player->addTalent(18744, player->GetActiveSpecMask(), true);
                player->learnSpell(18756); player->addTalent(18756, player->GetActiveSpecMask(), true);
                player->learnSpell(18768); player->addTalent(18768, player->GetActiveSpecMask(), true);
                player->learnSpell(18773); player->addTalent(18773, player->GetActiveSpecMask(), true);
                player->learnSpell(19028); player->addTalent(19028, player->GetActiveSpecMask(), true);
                player->learnSpell(23785); player->addTalent(23785, player->GetActiveSpecMask(), true);
                player->learnSpell(30145); player->addTalent(30145, player->GetActiveSpecMask(), true);
                player->learnSpell(30146); player->addTalent(30146, player->GetActiveSpecMask(), true);
                player->learnSpell(30321); player->addTalent(30321, player->GetActiveSpecMask(), true);
                player->learnSpell(30248); player->addTalent(30248, player->GetActiveSpecMask(), true);
                player->learnSpell(35693); player->addTalent(35693, player->GetActiveSpecMask(), true);
                player->learnSpell(47231); player->addTalent(47231, player->GetActiveSpecMask(), true);
                player->learnSpell(47240); player->addTalent(47240, player->GetActiveSpecMask(), true);
                player->learnSpell(47247); player->addTalent(47247, player->GetActiveSpecMask(), true);
                player->learnSpell(59672); player->addTalent(59672, player->GetActiveSpecMask(), true);
                player->learnSpell(63123); player->addTalent(63123, player->GetActiveSpecMask(), true);
                player->learnSpell(63158); player->addTalent(63158, player->GetActiveSpecMask(), true);
                player->learnSpell(63351); player->addTalent(63351, player->GetActiveSpecMask(), true);

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

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ORANGE_12_SPELL_POWER_10_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_HASTE_13_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), SOCK_ENCHANTMENT_SLOT_2, ORANGE_12_SPELL_POWER_10_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_29_SPELL_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_23_SPELL_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_23_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_30_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_23_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_50_SPELL_POWER_30_STAMINA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BLACK_MAGIC);

                // Glyph
                Glyph(player, 0, 759);
                Glyph(player, 1, 479);
                Glyph(player, 2, 480);
                Glyph(player, 3, 273);
                Glyph(player, 4, 478);
                Glyph(player, 5, 283);

                // Talent
                player->learnSpell(17792); player->addTalent(17792, player->GetActiveSpecMask(), true);
                player->learnSpell(17834); player->addTalent(17834, player->GetActiveSpecMask(), true);
                player->learnSpell(17877); player->addTalent(17877, player->GetActiveSpecMask(), true);
                player->learnSpell(17918); player->addTalent(17918, player->GetActiveSpecMask(), true);
                player->learnSpell(17958); player->addTalent(17958, player->GetActiveSpecMask(), true);
                player->learnSpell(17962); player->addTalent(17962, player->GetActiveSpecMask(), true);
                player->learnSpell(18120); player->addTalent(18120, player->GetActiveSpecMask(), true);
                player->learnSpell(18130); player->addTalent(18130, player->GetActiveSpecMask(), true);
                player->learnSpell(18136); player->addTalent(18136, player->GetActiveSpecMask(), true);
                player->learnSpell(18699); player->addTalent(18699, player->GetActiveSpecMask(), true);
                player->learnSpell(18704); player->addTalent(18704, player->GetActiveSpecMask(), true);
                player->learnSpell(18708); player->addTalent(18708, player->GetActiveSpecMask(), true);
                player->learnSpell(18710); player->addTalent(18710, player->GetActiveSpecMask(), true);
                player->learnSpell(18744); player->addTalent(18744, player->GetActiveSpecMask(), true);
                player->learnSpell(18756); player->addTalent(18756, player->GetActiveSpecMask(), true);
                player->learnSpell(19028); player->addTalent(19028, player->GetActiveSpecMask(), true);
                player->learnSpell(30145); player->addTalent(30145, player->GetActiveSpecMask(), true);
                player->learnSpell(30283); player->addTalent(30283, player->GetActiveSpecMask(), true);
                player->learnSpell(30292); player->addTalent(30292, player->GetActiveSpecMask(), true);
                player->learnSpell(30302); player->addTalent(30302, player->GetActiveSpecMask(), true);
                player->learnSpell(34939); player->addTalent(34939, player->GetActiveSpecMask(), true);
                player->learnSpell(47231); player->addTalent(47231, player->GetActiveSpecMask(), true);
                player->learnSpell(47260); player->addTalent(47260, player->GetActiveSpecMask(), true);
                player->learnSpell(47270); player->addTalent(47270, player->GetActiveSpecMask(), true);
                player->learnSpell(50796); player->addTalent(50796, player->GetActiveSpecMask(), true);
                player->learnSpell(59741); player->addTalent(59741, player->GetActiveSpecMask(), true);
                player->learnSpell(63351); player->addTalent(63351, player->GetActiveSpecMask(), true);

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
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 47059, true);
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47041, true);
                }
                else
                {
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 47271, true);
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47432, true);
                }

                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51398, true);
                player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, 51407, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 51437, true);

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_CRITICAL_3_CRITICAL_DAMAGE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ORANGE_12_SPELL_POWER_10_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_HASTE_13_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, PURPLE_12_SPELL_POWER_12_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, GREEN_10_HASTE_13_SPELL_PENETRATION);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_29_SPELL_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_23_SPELL_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_23_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_30_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_23_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_50_SPELL_POWER_30_STAMINA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BLACK_MAGIC);

                // Glyph
                Glyph(player, 0, 676);
                Glyph(player, 1, 433);
                Glyph(player, 2, 434);
                Glyph(player, 3, 178);
                Glyph(player, 4, 551);
                Glyph(player, 5, 176);

                // Talent
                player->learnSpell(5570);  player->addTalent(5570,  player->GetActiveSpecMask(), true);
                player->learnSpell(16818); player->addTalent(16818, player->GetActiveSpecMask(), true);
                player->learnSpell(16820); player->addTalent(16820, player->GetActiveSpecMask(), true);
                player->learnSpell(16835); player->addTalent(16835, player->GetActiveSpecMask(), true);
                player->learnSpell(16840); player->addTalent(16840, player->GetActiveSpecMask(), true);
                player->learnSpell(16847); player->addTalent(16847, player->GetActiveSpecMask(), true);
                player->learnSpell(16864); player->addTalent(16864, player->GetActiveSpecMask(), true);
                player->learnSpell(16899); player->addTalent(16899, player->GetActiveSpecMask(), true);
                player->learnSpell(16913); player->addTalent(16913, player->GetActiveSpecMask(), true);
                player->learnSpell(17051); player->addTalent(17051, player->GetActiveSpecMask(), true);
                player->learnSpell(17066); player->addTalent(17066, player->GetActiveSpecMask(), true);
                player->learnSpell(17119); player->addTalent(17119, player->GetActiveSpecMask(), true);
                player->learnSpell(24858); player->addTalent(24858, player->GetActiveSpecMask(), true);
                player->learnSpell(33591); player->addTalent(33591, player->GetActiveSpecMask(), true);
                player->learnSpell(33596); player->addTalent(33596, player->GetActiveSpecMask(), true);
                player->learnSpell(33606); player->addTalent(33606, player->GetActiveSpecMask(), true);
                player->learnSpell(33956); player->addTalent(33956, player->GetActiveSpecMask(), true);
                player->learnSpell(33831); player->addTalent(33831, player->GetActiveSpecMask(), true);
                player->learnSpell(35364); player->addTalent(35364, player->GetActiveSpecMask(), true);
                player->learnSpell(48393); player->addTalent(48393, player->GetActiveSpecMask(), true);
                player->learnSpell(48396); player->addTalent(48396, player->GetActiveSpecMask(), true);
                player->learnSpell(48412); player->addTalent(48412, player->GetActiveSpecMask(), true);
                player->learnSpell(48505); player->addTalent(48505, player->GetActiveSpecMask(), true);
                player->learnSpell(48511); player->addTalent(48511, player->GetActiveSpecMask(), true);
                player->learnSpell(48514); player->addTalent(48514, player->GetActiveSpecMask(), true);
                player->learnSpell(48525); player->addTalent(48525, player->GetActiveSpecMask(), true);
                player->learnSpell(50516); player->addTalent(50516, player->GetActiveSpecMask(), true);
                player->learnSpell(57865); player->addTalent(57865, player->GetActiveSpecMask(), true);
                player->learnSpell(61346); player->addTalent(61346, player->GetActiveSpecMask(), true);

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

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_AGILITY_3_CRITICAL_DAMAGE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ALL_STATS_10);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, RED_40_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT_2, RED_40_ATTACK_POWER);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_50_ATTACK_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_40_ATTACK_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_22_AGILITY);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_50_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_44_ATTACK_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_75_ATTACK_POWER_22_CRITICAL);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_BERSERKING);

                // Glyph
                Glyph(player, 0, 166);
                Glyph(player, 1, 0);
                Glyph(player, 2, 0);
                Glyph(player, 3, 165);
                Glyph(player, 4, 551);
                Glyph(player, 5, 671);

                // Talent
                player->learnSpell(16835); player->addTalent(16835, player->GetActiveSpecMask(), true);
                player->learnSpell(16864); player->addTalent(16864, player->GetActiveSpecMask(), true);
                player->learnSpell(16931); player->addTalent(16931, player->GetActiveSpecMask(), true);
                player->learnSpell(16938); player->addTalent(16938, player->GetActiveSpecMask(), true);
                player->learnSpell(16941); player->addTalent(16941, player->GetActiveSpecMask(), true);
                player->learnSpell(16944); player->addTalent(16944, player->GetActiveSpecMask(), true);
                player->learnSpell(16949); player->addTalent(16949, player->GetActiveSpecMask(), true);
                player->learnSpell(16968); player->addTalent(16968, player->GetActiveSpecMask(), true);
                player->learnSpell(16975); player->addTalent(16975, player->GetActiveSpecMask(), true);
                player->learnSpell(16999); player->addTalent(16999, player->GetActiveSpecMask(), true);
                player->learnSpell(17007); player->addTalent(17007, player->GetActiveSpecMask(), true);
                player->learnSpell(17061); player->addTalent(17061, player->GetActiveSpecMask(), true);
                player->learnSpell(17071); player->addTalent(17071, player->GetActiveSpecMask(), true);
                player->learnSpell(24866); player->addTalent(24866, player->GetActiveSpecMask(), true);
                player->learnSpell(24894); player->addTalent(24894, player->GetActiveSpecMask(), true);
                player->learnSpell(33851); player->addTalent(33851, player->GetActiveSpecMask(), true);
                player->learnSpell(33856); player->addTalent(33856, player->GetActiveSpecMask(), true);
                player->learnSpell(33873); player->addTalent(33873, player->GetActiveSpecMask(), true);
                player->learnSpell(33867); player->addTalent(33867, player->GetActiveSpecMask(), true);
                player->learnSpell(33917); player->addTalent(33917, player->GetActiveSpecMask(), true);
                player->learnSpell(37116); player->addTalent(37116, player->GetActiveSpecMask(), true);
                player->learnSpell(48412); player->addTalent(48412, player->GetActiveSpecMask(), true);
                player->learnSpell(48485); player->addTalent(48485, player->GetActiveSpecMask(), true);
                player->learnSpell(48495); player->addTalent(48495, player->GetActiveSpecMask(), true);
                player->learnSpell(49377); player->addTalent(49377, player->GetActiveSpecMask(), true);
                player->learnSpell(50334); player->addTalent(50334, player->GetActiveSpecMask(), true);
                player->learnSpell(51269); player->addTalent(51269, player->GetActiveSpecMask(), true);
                player->learnSpell(61336); player->addTalent(61336, player->GetActiveSpecMask(), true);
                player->learnSpell(63503); player->addTalent(63503, player->GetActiveSpecMask(), true);

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
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 47059, true);
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47041, true);
                }
                else
                {
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 47271, true);
                    player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 47432, true);
                }

                player->EquipNewItem(EQUIPMENT_SLOT_MAINHAND, 51454, true);
                player->EquipNewItem(EQUIPMENT_SLOT_OFFHAND, 51409, true);
                player->EquipNewItem(EQUIPMENT_SLOT_RANGED, 47671, true);

                // Socket
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT, META_21_INTELLECTL_RESTORE_MANA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), SOCK_ENCHANTMENT_SLOT_2, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), SOCK_ENCHANTMENT_SLOT_2, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), SOCK_ENCHANTMENT_SLOT, GREEN_10_RESILIENCE_5_MANA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT, GREEN_10_RESILIENCE_5_MANA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_RESILIENCE_5_MANA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), SOCK_ENCHANTMENT_SLOT_2, GREEN_10_RESILIENCE_5_MANA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), SOCK_ENCHANTMENT_SLOT, YELLOW_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), SOCK_ENCHANTMENT_SLOT, ORANGE_12_SPELL_POWER_10_RESILIENCE);

                // Enchant
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), PERM_ENCHANTMENT_SLOT, HEAD_29_SPELL_POWER_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), PERM_ENCHANTMENT_SLOT, SHOULDER_23_SPELL_POWER_15_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), PERM_ENCHANTMENT_SLOT, BACK_23_HASTE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), PERM_ENCHANTMENT_SLOT, CHEST_20_RESILIENCE);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PERM_ENCHANTMENT_SLOT, WRIST_30_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PERM_ENCHANTMENT_SLOT, HANDS_23_SPELL_POWER);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, WAIST_PRISMATIC);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), PERM_ENCHANTMENT_SLOT, LEGS_50_SPELL_POWER_30_STAMINA);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), PERM_ENCHANTMENT_SLOT, FEET_15_STAMINA_MINOR_SPEED);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), PERM_ENCHANTMENT_SLOT, WEAPON_63_SPELL_POWER);

                // Glyph
                Glyph(player, 0, 169);
                Glyph(player, 1, 433);
                Glyph(player, 2, 435);
                Glyph(player, 3, 168);
                Glyph(player, 4, 551);
                Glyph(player, 5, 676);

                // Talent
                player->learnSpell(17051); player->addTalent(17051, player->GetActiveSpecMask(), true);
                player->learnSpell(17066); player->addTalent(17066, player->GetActiveSpecMask(), true);
                player->learnSpell(17120); player->addTalent(17120, player->GetActiveSpecMask(), true);
                player->learnSpell(16835); player->addTalent(16835, player->GetActiveSpecMask(), true);
                player->learnSpell(17108); player->addTalent(17108, player->GetActiveSpecMask(), true);
                player->learnSpell(16864); player->addTalent(16864, player->GetActiveSpecMask(), true);
                player->learnSpell(17051); player->addTalent(17051, player->GetActiveSpecMask(), true);
                player->learnSpell(48412); player->addTalent(48412, player->GetActiveSpecMask(), true);
                player->learnSpell(17113); player->addTalent(17113, player->GetActiveSpecMask(), true);
                player->learnSpell(17116); player->addTalent(17116, player->GetActiveSpecMask(), true);
                player->learnSpell(24946); player->addTalent(24946, player->GetActiveSpecMask(), true);
                player->learnSpell(33880); player->addTalent(33880, player->GetActiveSpecMask(), true);
                player->learnSpell(17075); player->addTalent(17075, player->GetActiveSpecMask(), true);
                player->learnSpell(34153); player->addTalent(34153, player->GetActiveSpecMask(), true);
                player->learnSpell(18562); player->addTalent(18562, player->GetActiveSpecMask(), true);
                player->learnSpell(33883); player->addTalent(33883, player->GetActiveSpecMask(), true);
                player->learnSpell(33890); player->addTalent(33890, player->GetActiveSpecMask(), true);
                player->learnSpell(65139); player->addTalent(65139, player->GetActiveSpecMask(), true);
                player->learnSpell(48536); player->addTalent(48536, player->GetActiveSpecMask(), true);
                player->learnSpell(63411); player->addTalent(63411, player->GetActiveSpecMask(), true);
                player->learnSpell(51181); player->addTalent(51181, player->GetActiveSpecMask(), true);
                player->learnSpell(16817); player->addTalent(16817, player->GetActiveSpecMask(), true);
                player->learnSpell(57814); player->addTalent(57814, player->GetActiveSpecMask(), true);
                player->learnSpell(16847); player->addTalent(16847, player->GetActiveSpecMask(), true);
                player->learnSpell(35364); player->addTalent(35364, player->GetActiveSpecMask(), true);
                player->learnSpell(57865); player->addTalent(57865, player->GetActiveSpecMask(), true);
                player->learnSpell(16820); player->addTalent(16820, player->GetActiveSpecMask(), true);
                player->learnSpell(16924); player->addTalent(16924, player->GetActiveSpecMask(), true);
                player->learnSpell(5570);  player->addTalent(5570,  player->GetActiveSpecMask(), true);

                player->PlayerTalkClass->SendCloseGossip();
                break;
            default:
                break;
        }

        player->SetFreeTalentPoints(0);
        player->SendTalentsInfoData(false);

        if (player->GetTeamId() == TEAM_ALLIANCE)
            player->AddItem(51377, 1);
        else
            player->AddItem(51378, 1);

        player->CastSpell(player, 24222, true);

        return true;
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

    void ApplyBonus(Player* player, Item* item, EnchantmentSlot slot, uint32 bonusEntry)
    {
        if (!item)
            return;

        if (!bonusEntry || bonusEntry == 0)
            return;

        player->ApplyEnchantment(item, slot);
        item->SetEnchantment(slot, bonusEntry, 0, 0);
        player->ApplyEnchantment(item, slot, true);
    }
};

void AddSC_Template()
{
    new CreatureScript_Template();
}
