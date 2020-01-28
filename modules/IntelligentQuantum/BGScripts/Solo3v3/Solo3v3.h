#ifndef SOLO_3V3_H
#define SOLO_3V3_H

const uint32 SOLO_3V3_TALENTS_MELEE[] = {383, 163, 161, 182, 398, 164, 181, 263, 281, 399, 183, 381, 400, 0};
const uint32 SOLO_3V3_TALENTS_RANGE[] = {81, 261, 283, 302, 361, 41, 303, 363, 61, 203, 301, 362, 0};
const uint32 SOLO_3V3_TALENTS_HEAL[] = {201, 202, 382, 262, 282, 0};

enum Solo3v3TalentCat
{
    MELEE = 0,
    RANGE,
    HEALER,
    MAX_TALENT_CAT
};

static Solo3v3TalentCat GetTalentCatForSolo3v3(Player* player)
{
    if (!player)
        return MELEE;

    uint32 count[MAX_TALENT_CAT];
    for (int i = 0; i < MAX_TALENT_CAT; i++)
        count[i] = 0;

    for (uint32 talentId = 0; talentId < sTalentStore.GetNumRows(); ++talentId)
    {
        TalentEntry const* talentInfo = sTalentStore.LookupEntry(talentId);

        if (!talentInfo)
            continue;

        for (int8 rank = MAX_TALENT_RANK-1; rank >= 0; --rank)
        {
            if (talentInfo->RankID[rank] == 0)
                continue;

            if (player->HasTalent(talentInfo->RankID[rank], player->GetActiveSpec()))
            {
                for (int8 i = 0; SOLO_3V3_TALENTS_MELEE[i] != 0; i++)
                    if (SOLO_3V3_TALENTS_MELEE[i] == talentInfo->TalentTab)
                        count[MELEE] += rank + 1;

				for (int8 i = 0; SOLO_3V3_TALENTS_RANGE[i] != 0; i++)
					if (SOLO_3V3_TALENTS_RANGE[i] == talentInfo->TalentTab)
						count[RANGE] += rank + 1;

                for (int8 i = 0; SOLO_3V3_TALENTS_HEAL[i] != 0; i++)
                    if (SOLO_3V3_TALENTS_HEAL[i] == talentInfo->TalentTab)
                        count[HEALER] += rank + 1;
            }
        }
    }

    uint32 prevCount = 0;
    Solo3v3TalentCat talCat = MELEE;
    for (int i = 0; i < MAX_TALENT_CAT; i++)
    {
        if (count[i] > prevCount)
        {
            talCat = (Solo3v3TalentCat)i;
            prevCount = count[i];
        }
    }

    return talCat;
}

#endif
