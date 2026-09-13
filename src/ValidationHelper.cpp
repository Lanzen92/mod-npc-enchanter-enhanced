#include "ValidationHelper.h"
#include "ConfigManager.h"
#include "EnchantManager.h"
#include "Player.h"
#include "PriceHelper.h"
#include "SharedDefines.h"

bool ValidationHelper::CheckEquipment(const Player* player, uint32 subCatId, std::string& reason)
{
    EquipmentSlots targetSlot = GetEquipmentSlotFromSubCategory(subCatId);
    Item* targetItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, targetSlot);

    if (!targetItem)
    {
        reason = " (No item equipped)";
        return false;
    }

    if ((subCatId == EnchantSubCategory::Weapon_2H_Melee ||
            subCatId == EnchantSubCategory::Weapon_2H_Caster) &&
        targetItem->GetTemplate()->InventoryType != INVTYPE_2HWEAPON)
    {
        reason = " (Requires 2-Handed Weapon)";
        return false;
    }

    return true;
}

bool ValidationHelper::CheckProfession(const Player* player, const EnchantDefinition& enchant, std::string& reason)
{
    if (!NPCEnchanterEnhancedLockProfessionEnchants || enchant.professionRequirement.empty())
        return true;

    SkillType reqSkill = GetProfessionSkillTypeFromString(enchant.professionRequirement);
    if (reqSkill != SKILL_NONE && (!player->HasSkill(reqSkill) || player->GetSkillValue(reqSkill) < enchant.professionSkillRequirement))
    {
        reason = " (Requires " + std::to_string(enchant.professionSkillRequirement) + " " + enchant.professionRequirement + ")";
        return false;
    }

    return true;
}

bool ValidationHelper::CheckGold(const Player* player, const EnchantDefinition& enchant, std::string& reason, std::string& priceString)
{
    if (NPCEnchanterEnhancedFreeEnchants)
    {
        priceString = "";
        return true;
    }

    uint32 currentGoldCost = PriceHelper::GetEnchantPriceInGold(&enchant);
    priceString = currentGoldCost > 0 ? "   |cffffd700(" + std::to_string(currentGoldCost) + "g)|r" : "";

    uint32 totalCostCopper = PriceHelper::GetEnchantPriceInCopper(&enchant);
    if (player->GetMoney() < totalCostCopper)
    {
        reason = "Not enough gold.";
        return false;
    }

    return true;
}

bool ValidationHelper::CheckPhase(uint32 playerPhase, const EnchantDefinition& enchant, std::string& reason)
{
    if (NPCEnchanterEnhancedPhase == 0 && !NPCEnchanterEnhancedIndividualProgression)
        return true;

    if (enchant.phase > playerPhase)
    {
        reason = "Unlocked in phase " + std::to_string(enchant.phase) + ".";
        return false;
    }

    return true;
}

bool ValidationHelper::CheckLevel(const Player* player, const EnchantDefinition& enchant, std::string& reason)
{
    if (enchant.levelRequirement > player->GetLevel())
    {
        reason = "Requires level " + std::to_string(enchant.levelRequirement) + ".";
        return false;
    }

    return true;
}

bool ValidationHelper::CheckItemLevel(const Player* player, uint32 subCatId, const EnchantDefinition& enchant, std::string& reason)
{
    EquipmentSlots targetSlot = GetEquipmentSlotFromSubCategory(subCatId);
    Item* targetItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, targetSlot);

    if (enchant.minItemLevel > targetItem->GetTemplate()->ItemLevel)
    {
        reason = "Requires itemlevel " + std::to_string(enchant.minItemLevel) + ".";
        return false;
    }

    return true;
}

//Public
EnchantValidationResult ValidationHelper::ValidateEnchant(const Player* player, uint32 subCatId, const EnchantDefinition& enchant, const uint32 currentPhase)
{
    EnchantValidationResult result;
    result.isLocked = false;

    if (!CheckPhase(currentPhase, enchant, result.reason))
    {
        result.isLocked = true;
        return result;
    }

    if (!CheckEquipment(player, subCatId, result.reason))
    {
        result.isLocked = true;
        return result;
    }

    if (!CheckItemLevel(player, subCatId, enchant, result.reason))
    {
        result.isLocked = true;
        return result;
    }

    if (!CheckProfession(player, enchant, result.reason))
    {
        result.isLocked = true;
        return result;
    }

    if (!CheckGold(player, enchant, result.reason, result.priceString))
    {
        result.isLocked = true;
        return result;
    }

    return result;
}

uint32 ValidationHelper::CalculatePlayerPhase(const Player* player)
{
    uint32 currentPhase = 1;
    static const std::vector<std::pair<uint8, uint32>> bossProgression =
    {
        { 0,  RAGNAROS_KILL     }, // 686
        { 1,  ONYXIA_KILL       }, // 684
        { 2,  NEFARIAN_KILL     }, // 685
        { 5,  C_THUN_KILL       }, // 687
        { 8,  MALCHEZAAR_KILL   }, // 690
        { 9,  KAEL_THAS_KILL    }, // 696
        { 10, ILLIDAN_KILL      }, // 697
        { 12, KIL_JAEDEN_KILL   }, // 698
        { 13, KEL_THUZAD_KILL   }, // 575
        { 15, ANUB_ARAK_KILL    }, // 3916
        { 16, LICH_KING_KILL    }, // 4597
        { 17, HALION_KILL       }, // 4815
    };

    for (auto const& [progressionId, achievementId] : bossProgression)
    {
        if (player->HasAchieved(achievementId) && progressionId > currentPhase)
        {
            currentPhase = progressionId;
        }
    }

    return currentPhase;
}




