
enum EnchantCategory : uint32 {
    Weapon = 1,
    Armor  = 2,
    Shield = 3
};

enum EnchantSubType : uint32 {
    Weapon_1H_Melee = 10,
    Weapon_1H_Melee_Offhand = 11,
    Weapon_2H_Melee = 12,
    Weapon_Ranged = 13,
    Weapon_1H_Caster = 14,
    Weapon_2H_Caster = 15,

    Subtype_Shield = 20,

    Armor_Helm = 30,
    Armor_Shoulders = 31,
    Armor_Cloak = 32,
    Armor_Chest = 33,
    Armor_Bracers = 34,
    Armor_Gloves = 35,
    Armor_Legs = 36,
    Armor_Boots = 37,
    Armor_Rings = 38,

};

struct EnchantDefinition {
    uint32 spellId;
    uint32 enchantId;
    std::string name;
    EnchantCategory category;
    EnchantSubtype subType;
    std::string professionRequirement;
    uint32 professionSkillRequirement;
    uint32 minItemLevel;
    uint32 phase;
    uint32 cost;
};

struct EnchantCategorySubTypeDefinition {
    uint32 enchantCategorySubTypeId;
    std::string name;
    std::string icon;
    std::string professionRequirement;
    uint32 professionSkillRequirement;
    uint32 minItemLevel;
    uint32 phase;
    std::vector<EnchantDefinition> enchants;
};

struct EnchantCategoryDefinition {
    uint32 enchantCategoryId;
    std::string name;
    std::string icon;
    std::vector<EnchantCategorySubTypeDefinition> subTypes;
};

std::vector<EnchantCategoryDefinition> GetEnchantDatabase();
