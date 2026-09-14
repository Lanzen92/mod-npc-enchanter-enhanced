#include "ValidationHelper.h"
#include "ConfigManager.h"
#include "EnchantManager.h"
#include "Player.h"
#include "PriceHelper.h"
#include "SharedDefines.h"


// Validate-Functions
// true = Enchant is available
// false = Enchant is not available.
// If false, also gives a reason.



//Check if player has an item equiped in that slot. (Also check if 2H when selecting 2H enchant)
bool ValidationHelper::ValidateEquipment(const Player* player, uint32 subCatId, std::string& reason)
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

//Check if the player has the correct profession and required skill for that enchant.
bool ValidationHelper::ValidateProfession(const Player* player, const EnchantDefinition& enchant, std::string& reason)
{
    if (NPCEnchanterEnhancedIgnoreProfessionRequirements || enchant.professionRequirement.empty())
        return true;

    SkillType reqSkill = GetProfessionSkillTypeFromString(enchant.professionRequirement);
    if (reqSkill != SKILL_NONE && (!player->HasSkill(reqSkill) || player->GetSkillValue(reqSkill) < enchant.professionSkillRequirement))
    {
        reason = " (Requires " + std::to_string(enchant.professionSkillRequirement) + " " + enchant.professionRequirement + ")";
        return false;
    }

    return true;
}

//Check if the player has enough gold to buy the enchant.
bool ValidationHelper::ValidateGold(const Player* player, const EnchantDefinition& enchant, std::string& reason, std::string& priceString)
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

//Check if the enchant is available in the current phase.
//This
bool ValidationHelper::ValidatePhase(uint32 playerPhase, const EnchantDefinition& enchant, std::string& reason)
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

//Check if the player has the required level for the enchant.
bool ValidationHelper::ValidateLevel(const Player* player, const EnchantDefinition& enchant, std::string& reason)
{
    if (NPCEnchanterEnhancedIgnoreLevelRequirements)
        return true;

    if (enchant.levelRequirement > player->GetLevel())
    {
        reason = "Requires level " + std::to_string(enchant.levelRequirement) + ".";
        return false;
    }

    return true;
}

//Check if the item got the required item level for the enchant
bool ValidationHelper::ValidateItemLevel(const Player* player, uint32 subCatId, const EnchantDefinition& enchant, std::string& reason)
{
    if (NPCEnchanterEnhancedIgnoreItemLevelRequirements)
        return true;

    EquipmentSlots targetSlot = GetEquipmentSlotFromSubCategory(subCatId);
    Item* targetItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, targetSlot);

    if (enchant.minItemLevel > targetItem->GetTemplate()->ItemLevel)
    {
        reason = "Requires itemlevel " + std::to_string(enchant.minItemLevel) + ".";
        return false;
    }

    return true;
}

//Check if the player class is able to get this enchant.
bool ValidationHelper::ValidatePlayerClass(const Player* player, const EnchantDefinition& enchant, std::string& reason)
{
    if (NPCEnchanterEnhancedIgnoreClassRequirements || enchant.classRequirement == CLASS_NONE)
        return true;

    if (player->getClass() != enchant.classRequirement)
    {
        reason = "Wrong class " + std::to_string(enchant.minItemLevel) + ".";
        return false;
    }

    return true;
}

bool ValidationHelper::FilterTier(const EnchantDefinition& enchant, const std::string& allowedTiersConfig)
{
    std::string tierName;

    switch (enchant.tier)
    {
        case EnchantTier::Leveling: tierName = "leveling"; break;
        case EnchantTier::PreRaid:  tierName = "preraid";  break;
        case EnchantTier::Raid:     tierName = "raid";     break;
        default: return true;
    }

    return allowedTiersConfig.find(tierName) != std::string::npos;
}


//Public
EnchantValidationResult ValidationHelper::EvaluateEnchant(const Player* player, uint32 subCatId, const EnchantDefinition& enchant, const uint32 currentPhase)
{
    EnchantValidationResult result;
    result.showEnchant = true;
    result.isLocked = false;

    if (!FilterTier(enchant, NPCEnchanterEnhancedTiersToShow))
    {
        result.showEnchant = false;
        return result;
    }
    if (!ValidatePlayerClass(player, enchant, result.reason))
    {
        result.showEnchant = false;
        return result;
    }

    if (!ValidatePhase(currentPhase, enchant, result.reason))
    {
        if (NPCEnchanterEnhancedHideUnavailableEnchants)
            result.showEnchant = false;

        result.isLocked = true;
        return result;
    }

    if (!ValidateEquipment(player, subCatId, result.reason))
    {
        if (NPCEnchanterEnhancedHideUnavailableEnchants)
            result.showEnchant = false;

        result.isLocked = true;
        return result;
    }

    if (!ValidateItemLevel(player, subCatId, enchant, result.reason))
    {
        if (NPCEnchanterEnhancedHideUnavailableEnchants)
            result.showEnchant = false;

        result.isLocked = true;
        return result;
    }

    if (!ValidateProfession(player, enchant, result.reason))
    {
        if (NPCEnchanterEnhancedHideUnavailableEnchants)
            result.showEnchant = false;

        result.isLocked = true;
        return result;
    }

    if (!ValidateGold(player, enchant, result.reason, result.priceString))
    {
        result.isLocked = true;
        result.showEnchant = true;
        return result;
    }

    return result;
}

//Get Individualprogression phase.
uint32 ValidationHelper::GetPlayerPhase(const Player* player)
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




