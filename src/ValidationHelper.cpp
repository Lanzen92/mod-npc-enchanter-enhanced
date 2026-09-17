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

//Check if player has an item equipped in that slot.
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

    if (subCatId == EnchantSubCategory::Subtype_Shield &&
        targetItem->GetTemplate()->InventoryType != INVTYPE_SHIELD)
    {
        reason = " (Requires Shield)";
        return false;
    }

    return true;
}

//Check if the player has the correct profession and required skill
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

//Check if the player has enough gold AND returns a pricestring.
bool ValidationHelper::ValidateGold(const Player* player, uint32 cost, std::string& reason, std::string& priceString)
{
    if (NPCEnchanterEnhancedFreeEnchants)
    {
        priceString = "";
        return true;
    }

    std::string coinIcon = "|TInterface\\MoneyFrame\\UI-GoldIcon:14:14:2:0|t";
    priceString = cost > 0 ? " - |cff000000" + std::to_string(cost) + coinIcon + "|r" : "";

    if (player->GetMoney() < COPPER(cost))
    {
        reason = "Not enough gold.";
        return false;
    }

    return true;
}

//Check if the enchant is available in the current phase.
bool ValidationHelper::ValidatePhase(uint32 playerPhase, const EnchantDefinition& enchant, std::string& reason)
{
    if (NPCEnchanterEnhancedPhase == 0 && !NPCEnchanterEnhancedIndividualProgression)
        return true;

    if (enchant.phase <= playerPhase)
        return true;

    if (enchant.phase >= playerPhase)
    {
        reason = "Unlocked in phase " + std::to_string(enchant.phase) + ".";
        return false;
    }

    return true;
}

//Check if the player has the required level
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

//Check if the item got the required item level
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

//Filter Tiers
bool ValidationHelper::FilterTier(const EnchantDefinition& enchant)
{
    std::string tierName;
    std::string NPCEnchanterEnhancedTiersToShow = sConfigMgr->GetOption<std::string>("NPCEnchanterEnhanced.TiersToShow", "Leveling, PreRaid, Raid");
    std::string allowedTiersConfig = ToLower(NPCEnchanterEnhancedTiersToShow);

    switch (enchant.tier)
    {
        case EnchantTier::Leveling: tierName = "leveling"; break;
        case EnchantTier::PreRaid:  tierName = "preraid"; break;
        case EnchantTier::Raid:     tierName = "raid"; break;
        default: return true;
    }
    return allowedTiersConfig.find(tierName) != std::string::npos;
}

//Public
EnchantValidationResult ValidationHelper::EvaluateEnchant(const Player* player, uint32 subCatId, const EnchantDefinition& enchant, uint32 enchantCost, const uint32 currentPhase)
{
    EnchantValidationResult result;
    result.showEnchant = true;
    result.isLocked = false;

    if (!FilterTier(enchant))
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

    if (!ValidateGold(player, enchantCost, result.reason, result.priceString))
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

    for (auto const& [progressionId, achievementId] : bossProgression)
    {
        if (player->HasAchieved(achievementId) && progressionId > currentPhase)
        {
            currentPhase = progressionId;
        }
    }

    return currentPhase;
}


//SubCategory helpers
bool ValidationHelper::ValidateSubCategoryProfession(const Player* player, const EnchantSubCategoryDefinition& subCat, std::string& reason)
{
    if (NPCEnchanterEnhancedIgnoreProfessionRequirements)
        return true;

    // Check if the manager defines a general profession lock phrase for this subcategory
    std::string profPhrase = sEnchantManager->GetProfessionLockedPhrase(subCat.enchantCategorySubTypeId);
    if (profPhrase.empty())
        return true; // No profession lock for this subcategory

    // Check if the player fails the profession requirement for the enchants inside
    for (const auto& enchant : subCat.enchants)
    {
        if (!enchant.professionRequirement.empty())
        {
            SkillType reqSkill = GetProfessionSkillTypeFromString(enchant.professionRequirement);
            if (reqSkill != SKILL_NONE && (!player->HasSkill(reqSkill) || player->GetSkillValue(reqSkill) < enchant.professionSkillRequirement))
            {
                reason = " (" + profPhrase + ")";
                return false;
            }
        }
    }

    return true;
}

bool ValidationHelper::ValidateSubCategoryEquipment(const Player* player, uint32 subCatId, std::string& reason)
{
    EquipmentSlots targetSlot = GetEquipmentSlotFromSubCategory(subCatId);
    Item* targetItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, targetSlot);

    if (!targetItem)
    {
        reason = " (No item equipped)";
        return false;
    }

    uint32 invType = targetItem->GetTemplate()->InventoryType;

    // Check specific subcategory slot & item type rules
    switch (subCatId)
    {
    case EnchantSubCategory::Weapon_2H_Melee:
    case EnchantSubCategory::Weapon_2H_Caster:
        if (invType != INVTYPE_2HWEAPON)
        {
            reason = " (Requires 2-Handed Weapon)";
            return false;
        }
        break;

    case EnchantSubCategory::Subtype_Shield:
        if (invType != INVTYPE_SHIELD)
        {
            reason = " (Requires Shield)";
            return false;
        }
        break;

    case EnchantSubCategory::Weapon_1H_Melee:
    case EnchantSubCategory::Weapon_1H_Caster:
        if (invType != INVTYPE_WEAPON && invType != INVTYPE_WEAPONMAINHAND)
        {
            reason = " (Requires 1-Handed Weapon)";
            return false;
        }
        break;

    case EnchantSubCategory::Weapon_1H_Melee_Offhand:
        if (invType != INVTYPE_WEAPON && invType != INVTYPE_WEAPONOFFHAND && invType != INVTYPE_SHIELD)
        {
            reason = " (Requires Off-Hand Item)";
            return false;
        }
        break;

    default:
        // For standard armor slots (Chest, Boots, Rings, etc.),
        // If targetItem exists, it's valid!
        break;
    }

    return true;
}



