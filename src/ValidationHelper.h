#pragma once

#include <string>
#include "EnchanterCommon.h"

class Player;
struct EnchantDefinition;

struct EnchantValidationResult {
    bool isLocked = false;
    std::string reason = "";
    std::string priceString = "";
};

class ValidationHelper
{
    static bool CheckEquipment(Player* player, uint32 subCatId, std::string& reason);
    static bool CheckProfession(Player* player, const EnchantDefinition& enchant, std::string& reason);
    static bool CheckGold(Player* player, const EnchantDefinition& enchant, std::string& reason, std::string& priceString);

public:
    static EnchantValidationResult ValidateEnchant(Player* player, uint32 subCatId, const EnchantDefinition& enchant);
};
