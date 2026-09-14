#pragma once

#include <string>
#include "EnchanterCommon.h"

class Player;
struct EnchantDefinition;

enum ProgressionAchievements
{
    KEL_THUZAD_40_KILL   = 533, // Vanilla
    KEL_THUZAD_KILL      = 575, // WotLK
    ONYXIA_KILL          = 684,
    NEFARIAN_KILL        = 685,
    RAGNAROS_KILL        = 686,
    C_THUN_KILL          = 687,
    MALCHEZAAR_KILL      = 690,
    ZUL_JIN_KILL         = 691,
    KAEL_THAS_KILL       = 696,
    ILLIDAN_KILL         = 697,
    KIL_JAEDEN_KILL      = 698,
    ANUB_ARAK_KILL       = 3916,
    LICH_KING_KILL       = 4597,
    HALION_KILL          = 4815
};

struct EnchantValidationResult {
    bool isLocked = false;
    std::string reason = "";
    std::string priceString = "";
    bool showEnchant = true;
};

class ValidationHelper
{
    static bool ValidateEquipment(const Player* player, uint32 subCatId, std::string& reason);
    static bool ValidateProfession(const Player* player, const EnchantDefinition& enchant, std::string& reason);
    static bool ValidateGold(const Player* player, const EnchantDefinition& enchant, std::string& reason, std::string& priceString);
    static bool ValidatePhase(uint32 playerPhase, const EnchantDefinition& enchant, std::string& reason);
    static bool ValidateLevel(const Player* player, const EnchantDefinition& enchant, std::string& reason);
    static bool ValidateItemLevel(const Player* player, uint32 subCatId, const EnchantDefinition& enchant, std::string& reason);
    static bool ValidatePlayerClass(const Player* player, const EnchantDefinition& enchant, std::string& reason);
    static bool FilterTier(const EnchantDefinition& enchant, const std::string& allowedTiersConfig);

public:
    static EnchantValidationResult EvaluateEnchant(const Player* player, uint32 subCatId, const EnchantDefinition& enchant, const uint32 currentPhase);
    static uint32 GetPlayerPhase(const Player* player);
};
