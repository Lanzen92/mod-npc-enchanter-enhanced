#include "ValidationHelper.h"
#include "ConfigManager.h"
#include "EnchantManager.h"
#include "Player.h"
#include "PriceHelper.h"
#include "SharedDefines.h"



//Todo:
//Check Phases
//Check levelRequirement
//Check itemLevelRequirements


bool ValidationHelper::CheckEquipment(Player* player, uint32 subCatId, std::string& reason)
{
    EquipmentSlots targetSlot = GetEquipmentSlotFromSubCategory(subCatId);
    Item* targetItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, targetSlot);

    if (!targetItem)
    {
        reason = " (No item equipped)";
        return true;
    }

    if ((subCatId == EnchantSubCategory::Weapon_2H_Melee ||
         subCatId == EnchantSubCategory::Weapon_2H_Caster) &&
        targetItem->GetTemplate()->InventoryType != INVTYPE_2HWEAPON)
    {
        reason = " (Requires 2-Handed Weapon)";
        return true;
    }

    return false;
}

bool ValidationHelper::CheckProfession(Player* player, const EnchantDefinition& enchant, std::string& reason)
{
    if (!NPCEnchanterEnhancedLockProfessionEnchants || enchant.professionRequirement.empty())
        return false;

    SkillType reqSkill = GetProfessionSkillTypeFromString(enchant.professionRequirement);
    if (reqSkill != SKILL_NONE && (!player->HasSkill(reqSkill) || player->GetSkillValue(reqSkill) < enchant.professionSkillRequirement))
    {
        reason = " (Requires " + std::to_string(enchant.professionSkillRequirement) + " " + enchant.professionRequirement + ")";
        return true;
    }

    return false;
}

bool ValidationHelper::CheckGold(Player* player, const EnchantDefinition& enchant, std::string& reason, std::string& priceString)
{
    if (!NPCEnchanterEnhancedFreeEnchants || NPCEnchanterEnhancedDynamicPricesOnEnchants)
    {
        uint32 currentGoldCost = PriceHelper::GetEnchantPriceInGold(&enchant);
        priceString = currentGoldCost > 0 ? "   |cffffd700(" + std::to_string(currentGoldCost) + "g)|r" : "";

        uint32 totalCostCopper = PriceHelper::GetEnchantPriceInCopper(&enchant);
        if (player->GetMoney() < totalCostCopper)
        {
            reason = " (Not enough gold)";
            return true;
        }
    }
    return false;
}

EnchantValidationResult ValidationHelper::ValidateEnchant(Player* player, uint32 subCatId, const EnchantDefinition& enchant)
{
    EnchantValidationResult result;

    // 1. Check Equipment First
    if (CheckEquipment(player, subCatId, result.reason))
    {
        result.isLocked = true;
        return result; // Stop further checks if base equipment is invalid
    }

    // 2. Check Profession
    if (CheckProfession(player, enchant, result.reason))
    {
        result.isLocked = true;
    }

    // 3. Check Gold & Format Price String
    if (CheckGold(player, enchant, result.reason, result.priceString))
    {
        result.isLocked = true;
    }

    return result;
}
