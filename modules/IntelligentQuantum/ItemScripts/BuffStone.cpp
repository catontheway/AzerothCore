#include "ScriptMgr.h"
#include "Player.h"
#include "Item.h"

class ItemScript_BuffStone1 : public ItemScript
{
public:
    ItemScript_BuffStone1() : ItemScript("ItemScript_BuffStone1") { }

    bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const& /*targets*/) override
    {
        if (!player->InArena() && !player->duel && !player->IsInCombat())
        {
            player->AddAura(48162, player);
        }

        return true;
    }
};

class ItemScript_BuffStone2 : public ItemScript
{
public:
    ItemScript_BuffStone2() : ItemScript("ItemScript_BuffStone2") { }

    bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const& /*targets*/) override
    {
        if (!player->InArena() && !player->duel && !player->IsInCombat())
        {
            player->AddAura(48162, player);
            player->AddAura(48170, player);
        }

        return true;
    }
};

class ItemScript_BuffStone3 : public ItemScript
{
public:
    ItemScript_BuffStone3() : ItemScript("ItemScript_BuffStone3") { }

    bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const& /*targets*/) override
    {
        if (!player->InArena() && !player->duel && !player->IsInCombat())
        {
            player->AddAura(48162, player);
            player->AddAura(48170, player);
            player->AddAura(48074, player);
        }

        return true;
    }
};

class ItemScript_BuffStone4 : public ItemScript
{
public:
    ItemScript_BuffStone4() : ItemScript("ItemScript_BuffStone4") { }

    bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const& /*targets*/) override
    {
        if (!player->InArena() && !player->duel && !player->IsInCombat())
        {
            player->AddAura(48162, player);
            player->AddAura(48170, player);
            player->AddAura(48074, player);
            player->AddAura(48470, player);
        }

        return true;
    }
};

class ItemScript_BuffStone5 : public ItemScript
{
public:
    ItemScript_BuffStone5() : ItemScript("ItemScript_BuffStone5") { }

    bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const& /*targets*/) override
    {
        if (!player->InArena() && !player->duel && !player->IsInCombat())
        {
            player->AddAura(48162, player);
            player->AddAura(48170, player);
            player->AddAura(48074, player);
            player->AddAura(48470, player);
            player->AddAura(43002, player);
        }

        return true;
    }
};

class ItemScript_BuffStone6 : public ItemScript
{
public:
    ItemScript_BuffStone6() : ItemScript("ItemScript_BuffStone6") { }

    bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const& /*targets*/) override
    {
        if (!player->InArena() && !player->duel && !player->IsInCombat())
        {
            player->AddAura(43223, player);
            player->AddAura(48162, player);
            player->AddAura(48074, player);
            player->AddAura(48170, player);
            player->AddAura(48470, player);
            player->AddAura(43002, player);
        }

        return true;
    }
};

void AddSC_BuffStone()
{
    new ItemScript_BuffStone1();
    new ItemScript_BuffStone2();
    new ItemScript_BuffStone3();
    new ItemScript_BuffStone4();
    new ItemScript_BuffStone5();
    new ItemScript_BuffStone6();
}
