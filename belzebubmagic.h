#ifndef BELZEBUBMAGIC_H
#define BELZEBUBMAGIC_H

#include <vector>
#include <string>
#include <map>

namespace Belzebub {

    struct __attribute__ ((packed)) AttributeRare {
        unsigned short type;
        union {
            short value1;
            unsigned short uvalue1;
        };
        union {
            short value2;
            unsigned short uvalue2;
        };
    };
    struct __attribute__ ((packed)) AttributeUnique {
        unsigned char type;
        union {
            short value1;
            unsigned short uvalue1;
        };
        union {
            short value2;
            unsigned short uvalue2;
        };
    };
    struct __attribute__ ((packed)) AttributeSet {
        unsigned char type;
        union {
            short value1;
            unsigned short uvalue1;
        };
        union {
            short value2;
            unsigned short uvalue2;
        };
        union {
            char value3;
            unsigned char uvalue3;
        };
    };

    enum class SpellType : int {
        FrostShard = 0, FireBolt, ChargedBolt, Healing, HealOther, HolyBolt, Inferno,
        Warp, FireWall, Telekinesis, Lightning, TownPortal, Flash, CircleOfIce,
        Phasing, LightningWall, StoneCurse, FireBall, FlameWave, ChainLightning, IceBlast,
        empty1, MindMace, Elemental, Golem, FrozenOrb, MeteorCluster, Guardian,
        Nova, Sentinel, Teleport, Apocalypse, empty2, Blizzard, Immolation,
        DarkPack, empty3, Insanity, empty4, BoneSpirit, BloodStar, Sacrifice
    };
    enum class ItemPosition {Body, Head, Ring1, Ring2, Amulet, Hand1, Hand2, Belt};
    enum class ItemType {NoItem = 0, Quest = 7, Common = 8, Magic = 9, Rare = 10, Unique = 11, Set = 12, Crafted = 13};
    enum class Attribute {
        //Rare: position 0, 2, 4, 6
        //Crafted: position 0-3
        EvenMana, EvenEnhancedArmor, EvenChanceToHit, EvenEnhancedDamage, EvenAddsFireDamage, EvenAddsLightningDamage,
        EvenResistMagic, EvenResistFire, EvenResistLightning, EvenResistCold, EvenResistAll,
        EvenSpellsLevels, EvenIncreasedCharges, EvenCriticalHitChance,
        EvenSpellPower, EvenMagicItemsChance, EvenAddSpell, EvenIncreasedArmor,
        EvenMaximumResistMagic, EvenMaximumResistFire, EvenMaximumResistLightning, EvenMaximumResistCold, EvenMaximumResistAll,

        //Rare: position 1, 3, 5, 7
        //Crafted: position 4-7
        OddStrength, OddMagic, OddDexterity, OddVitality, OddAllAttributes,
        OddHitPoints, OddAddsPointsToDamage, OddDamageTakenFromEnemies,
        OddAddsFireDamage, OddAddsLightningDamage, OddAddsColdDamage,
        OddHitStealsLife, OddHitStealsMana, OddCriticalHitDamage, OddLightRadiusIncreased,
        OddAttackSpeed, OddHitRecoverySpeed,
        OddLowDurability, OddHighDurability, OddIndestructible, OddKnockback, OddBlockSpeed,
        OddRegeneratesLife, OddRegeneratesMana, OddCastingSpeed,
        OddAbsorbsHalfTrapDamage, OddAttackerTakesDamage,
        OddHalfFreezeDuration, OddChanceToKnockback,
        OddStrength2, OddMagic2, OddDexterity2, OddVitality2, OddHitPoints2,
        OddAddsPointsToDamage2, OddDamageTakenFromEnemies2, OddHitRecoverySpeed2, OddAttackerTakesDamage2,
        OddAddsFireDamage2, OddAddsLightningDamage2, OddAddsColdDamage2,
        OddTargetFireResistance, OddTargetLightningResistance, OddTargetColdResistance, OddTargetMagicResistance,
        OddCannotBeFrozen,

        //Unique
        UniqueStrength, UniqueMagic, UniqueDexterity, UniqueVitality, UniqueAllAttributes,
        UniqueArmorClass, UniqueIncreasedArmor, UniqueEnhancedArmor, UniqueChanceToHit, UniqueEnhancedDamage, UniqueAddPointsToDamage,
        UniqueLightningHitDamage, UniqueFireHitDamage, UniqueColdHitDamage, UniqueMagicHitDamage,
        UniqueResistAll, UniqueResistFire, UniqueResistLightning, UniqueResistMagic, UniqueResistCold, UniqueAllResistancesZero,
        UniqueRegeneratesLife, UniqueRegeneratesMana, UniqueFasterHitRecovery,
        UniqueIncreasedAttackSpeed, UniqueFasterBlockRate, UniqueFasterWalk, UniqueIncreasedCastSpeed, UniqueLightRadius,
        UniqueDamageTakenFromEnemies, UniqueHitPoints, UniqueMana,
        UniqueHighDurability, UniqueAlteredDurability, UniqueIndestructible, UniqueSpellLevels,
        UniqueHitStealsLife, UniqueHitStealsMana,
        UniqueRequirements, UniqueOneHandedWeapon, UniqueUnusualItemDamage, UniqueChanceToKnockback,
        UniqueDamageVsDemon, UniqueDamageVsUndead,
        UniqueSpellCharges,
        UniqueCriticalHitChance, UniqueCriticalHitDamage, UniqueSpellPower,
        UniqueExtraGold, UniqueMagicItemsChance,
        UniqueHalfTrapDamage, UniqueAttackerTakesDamage, UniqueIncreasedChanceOfBlocking,
        UniqueTargetResistances, UniqueTargetPhysicalResistances,
        UniqueTargetFireResistance, UniqueTargetLightningResistance, UniqueTargetColdResistance, UniqueTargetMagicResistance,
        UniquePiercingAttack, UniqueHalfFreezeDuration, UniqueCannotBeFrozen,
        UniqueMaximumMana, UniqueMaximumLife,
        UniqueHitPointsCharacterLevel, UniqueManaCharacterLevel,
        UniqueStrengthCharacterLevel,UniqueDexterityCharacterLevel, UniqueMagicCharacterLevel, UniqueVitalityCharacterLevel, UniqueAllStatsCharacterLevel,
        UniqueToHitCharacterLevel, UniqueDamageCharacterLevel, UniqueSpellPowerCharacterLevel,
        UniqueDamageVsDemonsCharacterLevel, UniqueDamageVsUndeadCharacterLevel, UniqueAddsDamageCharacterLevel, UniqueArmorClassCharacterLevel,
        UniqueResistAllCharacterLevel,
        UniqueFireDamageCharacterLevel, UniqueLightningDamageCharacterLevel, UniqueColdDamageCharacterLevel, UniqueMagicDamageCharacterLevel,
        UniqueMagicItemsChanceCharacterLevel, UniqueExtraGoldCharacterLevel,
        UniqueMaximumResistAll, UniqueMaximumResistFire, UniqueMaximumResistLightning, UniqueMaximumResistMagic, UniqueMaximumResistCold,
        UniqueAddSpell, UniqueActOfTransformation, UniqueDamageAbsorbedByMana,
        UniqueChanceToCastSpellOnStriking, UniqueChanceToCastSpellWhenStruck,
        UniqueIgnoreTargetDefense,

        //Set (not same as Unique)
        SetStrength, SetMagic, SetDexterity, SetVitality, SetAllAttributes,
        SetArmorClass, SetIncreasedArmor, SetEnhancedArmor, SetChanceToHit, SetEnhancedDamage, SetAddPointsToDamage,
        SetLightningHitDamage, SetFireHitDamage, SetColdHitDamage, SetMagicHitDamage,
        SetResistAll, SetResistFire, SetResistLightning, SetResistMagic, SetResistCold, SetAllResistancesZero,
        SetRegeneratesLife, SetRegeneratesMana,
        SetIncreasedChanceOfBlocking, SetFasterHitRecovery, SetIncreasedAttackSpeed, SetFasterBlockRate,
        SetFasterWalk, SetIncreasedCastSpeed, SetLightRadius, SetDamageTakenFromEnemies,
        SetHitPoints, SetMana,
        SetHighDurability, SetAlteredDurability, SetIndestructible,
        SetSpellLevels, SetHitStealsLife, SetHitStealsMana,
        SetRequirements, SetOneHandedWeapon, SetOffhandWeapon, SetChanceToKnockback, SetDamageVsDemon, SetDamageVsUndead,
        SetCriticalHitChance, SetCriticalHitDamage, SetSpellPower,
        SetExtraGold, SetMagicItemsChance,
        SetHalfTrapDamage, SetAttackerTakesDamage,
        SetTargetResistances, SetTargetPhysicalResistances,
        SetTargetFireResistance, SetTargetLightningResistance, SetTargetColdResistance, SetTargetMagicResistance,
        SetPiercingAttack, SetHalfFreezeDuration, SetCannotBeFrozen,
        SetMaximumMana, SetMaximumLife,
        SetHitPointsCharacterLevel, SetManaCharacterLevel,
        SetStrengthCharacterLevel,SetDexterityCharacterLevel, SetMagicCharacterLevel, SetVitalityCharacterLevel, SetAllStatsCharacterLevel,
        SetToHitCharacterLevel, SetDamageCharacterLevel, SetSpellPowerCharacterLevel,
        SetDamageVsDemonsCharacterLevel, SetDamageVsUndeadCharacterLevel, SetAddsDamageCharacterLevel, SetArmorClassCharacterLevel,
        SetResistAllCharacterLevel,
        SetFireDamageCharacterLevel, SetLightningDamageCharacterLevel, SetColdDamageCharacterLevel, SetMagicDamageCharacterLevel,
        SetMagicItemsChanceCharacterLevel, SetExtraGoldCharacterLevel,
        SetMaximumResistAll, SetMaximumResistFire, SetMaximumResistLightning, SetMaximumResistMagic, SetMaximumResistCold,
        SetAddSpell, SetActOfTransformation, SetDamageAbsorbedByMana,
        SetChanceToCastSpellOnStriking, SetChanceToCastSpellWhenStruck,
        SetIgnoreTargetDefense,
    };
    enum class AttributeMode {Error, Even, Odd, Unique, Set};

    AttributeMode getAttributeMode(const ItemType itemType, const int attributePosition) {
        AttributeMode attributeMode = AttributeMode::Error;
        if (itemType == ItemType::Rare || itemType == ItemType::Magic) {
            if (attributePosition % 2 == 0) {
                attributeMode = AttributeMode::Even;
            }
            else {
                attributeMode = AttributeMode::Odd;
            }
        }
        else if (itemType == ItemType::Crafted) {
            if (attributePosition < 4) {
                attributeMode = AttributeMode::Even;
            }
            else {
                attributeMode = AttributeMode::Odd;
            }
        }
        else if (itemType == ItemType::Unique) {
            attributeMode = AttributeMode::Unique;
        }
        else if (itemType == ItemType::Set) {
            attributeMode = AttributeMode::Set;
        }
        return attributeMode;
    }

    struct AttributeData {
        AttributeMode mode;
        int start;
        int end;
        std::string name;
    };
    const std::map<Attribute, AttributeData> attrMap = {
        {Attribute::EvenMana, {AttributeMode::Even, 0, 9, "Mana : +X"}},
        {Attribute::EvenEnhancedArmor, {AttributeMode::Even, 10, 21, "+X% Enhanced Armor"}},
        {Attribute::EvenChanceToHit, {AttributeMode::Even, 22, 44, "Chance To Hit : +X%"}},
        {Attribute::EvenEnhancedDamage, {AttributeMode::Even, 45, 57, "+X% Enhanced Damage"}},
        {Attribute::EvenAddsFireDamage, {AttributeMode::Even, 58, 58, "Adds X To Y Fire Damage"}},
        {Attribute::EvenAddsLightningDamage, {AttributeMode::Even, 59, 59, "Adds X To Y Lightning Damage"}},
        {Attribute::EvenResistMagic, {AttributeMode::Even, 60, 64, "Resist Magic : +X%"}},
        {Attribute::EvenResistFire, {AttributeMode::Even, 65, 69, "Resist Fire : +X%"}},
        {Attribute::EvenResistLightning, {AttributeMode::Even, 70, 74, "Resist Lightning : +X%"}},
        {Attribute::EvenResistCold, {AttributeMode::Even, 75, 79, "Resist Cold : +X%"}},
        {Attribute::EvenResistAll, {AttributeMode::Even, 80, 84, "Resist All : +X%"}},
        {Attribute::EvenSpellsLevels, {AttributeMode::Even, 85, 88, "Spells Are Increased X Levels"}},
        {Attribute::EvenIncreasedCharges, {AttributeMode::Even, 89, 90, "IncreasedCharges"}},
        {Attribute::EvenCriticalHitChance, {AttributeMode::Even, 91, 96, "Critical Hit Chance : +X%"}},
        {Attribute::EvenSpellPower, {AttributeMode::Even, 97, 103, "+X% Spell Power"}},
        {Attribute::EvenMagicItemsChance, {AttributeMode::Even, 104, 109, "+X% Chance Of Getting Magic Items"}},
        {Attribute::EvenAddSpell, {AttributeMode::Even, 110, 115, "+Y To Spell (X)"}},
        {Attribute::EvenIncreasedArmor, {AttributeMode::Even, 116, 127, "Increased Armor: +X"}},
        {Attribute::EvenMaximumResistMagic, {AttributeMode::Even, 128, 129, "Maximum Resist Magic : +X%"}},
        {Attribute::EvenMaximumResistFire, {AttributeMode::Even, 130, 131, "Maximum Resist Fire: +X%"}},
        {Attribute::EvenMaximumResistLightning, {AttributeMode::Even, 132, 133, "Maximum Resist Lightning: +X%"}},
        {Attribute::EvenMaximumResistCold, {AttributeMode::Even, 134, 135, "Maximum Resist Cold: +X%"}},
        {Attribute::EvenMaximumResistAll, {AttributeMode::Even, 136, 137, "Maximum Resist All: +X%"}},

        {Attribute::OddStrength, {AttributeMode::Odd, 0, 6, "+X To Strength"}},
        {Attribute::OddMagic, {AttributeMode::Odd, 7, 13, "+X To Magic"}},
        {Attribute::OddDexterity, {AttributeMode::Odd, 14, 20, "+X To Dexterity"}},
        {Attribute::OddVitality, {AttributeMode::Odd, 21, 27, "+X To Vitality"}},
        {Attribute::OddAllAttributes, {AttributeMode::Odd, 28, 34, "+X To All Attributes"}},
        {Attribute::OddHitPoints, {AttributeMode::Odd, 35, 44, "Hit Points : +X"}},
        {Attribute::OddAddsPointsToDamage, {AttributeMode::Odd, 45, 50, "Adds X Points To Damage"}},
        {Attribute::OddDamageTakenFromEnemies, {AttributeMode::Odd, 51, 57, "-X Damage Taken From Enemies"}},
        {Attribute::OddAddsFireDamage, {AttributeMode::Odd, 58, 61, "Adds X To Y Fire Damage"}},
        {Attribute::OddAddsLightningDamage, {AttributeMode::Odd, 62, 65, "Adds X To Y Lightning Damage"}},
        {Attribute::OddAddsColdDamage, {AttributeMode::Odd, 66, 69, "Adds X To Y Cold Damage"}},
        {Attribute::OddHitStealsLife, {AttributeMode::Odd, 70, 74, "Hit Steals X% Life"}},
        {Attribute::OddHitStealsMana, {AttributeMode::Odd, 75, 79, "Hit Steals X% Mana"}},
        {Attribute::OddCriticalHitDamage, {AttributeMode::Odd, 80, 85, "Critical Hit Damage : +X%"}},
        {Attribute::OddLightRadiusIncreased, {AttributeMode::Odd, 86, 89, "Light Radius Increased/Decreased By X%"}},
        {Attribute::OddAttackSpeed, {AttributeMode::Odd, 90, 93, "Attack Speed : +X%"}},
        {Attribute::OddHitRecoverySpeed, {AttributeMode::Odd, 94, 96, "Hit Recovery Speed : +X%"}},
        {Attribute::OddLowDurability, {AttributeMode::Odd, 97, 98, "Low Durability"}},
        {Attribute::OddHighDurability, {AttributeMode::Odd, 99, 103, "High Durability"}},
        {Attribute::OddIndestructible, {AttributeMode::Odd, 104, 104, "Indestructible"}},
        {Attribute::OddKnockback, {AttributeMode::Odd, 105, 105, "Knockback"}},
        {Attribute::OddBlockSpeed, {AttributeMode::Odd, 106, 106, "Block Speed : +X%"}},
        {Attribute::OddRegeneratesLife, {AttributeMode::Odd, 107, 109, "Regenerates X Life Per 5 Sec"}},
        {Attribute::OddRegeneratesMana, {AttributeMode::Odd, 110, 112, "Regenerates X Mana Per 5 Sec"}},
        {Attribute::OddCastingSpeed, {AttributeMode::Odd, 113, 114, "Casting Speed : +X%"}},
        {Attribute::OddAbsorbsHalfTrapDamage, {AttributeMode::Odd, 115, 115, "Absorbs Half Trap Damage"}},
        {Attribute::OddAttackerTakesDamage, {AttributeMode::Odd, 116, 116, "Attacker Takes X - Y Damage"}},
        {Attribute::OddHalfFreezeDuration, {AttributeMode::Odd, 117, 118, "Half Freeze Duration"}},
        {Attribute::OddChanceToKnockback, {AttributeMode::Odd, 119, 121, "+X% Chance To Knockback"}},
        {Attribute::OddStrength2, {AttributeMode::Odd, 122, 122, "+X To Strength (2)"}},
        {Attribute::OddMagic2, {AttributeMode::Odd, 123, 123, "+X To Magic (2)"}},
        {Attribute::OddDexterity2, {AttributeMode::Odd, 124, 124, "+X To Dexterity (2)"}},
        {Attribute::OddVitality2, {AttributeMode::Odd, 125, 125, "+X To Vitality (2)"}},
        {Attribute::OddHitPoints2, {AttributeMode::Odd, 126, 126, "Hit Points : +X"}},
        {Attribute::OddAddsPointsToDamage2, {AttributeMode::Odd, 127, 128, "Adds X Points To Damage (2)"}},
        {Attribute::OddDamageTakenFromEnemies2, {AttributeMode::Odd, 129, 129, "-X Damage Taken From Enemies (2)"}},
        {Attribute::OddHitRecoverySpeed2, {AttributeMode::Odd, 130, 130, "Hit Recovery Speed : +X% (2)"}},
        {Attribute::OddAttackerTakesDamage2, {AttributeMode::Odd, 131, 133, "Attacker Takes X - Y Damage (2)"}},
        {Attribute::OddAddsFireDamage2, {AttributeMode::Odd, 134, 134, "Adds X To Y Fire Damage (2)"}},
        {Attribute::OddAddsLightningDamage2, {AttributeMode::Odd, 135, 135, "Adds X To Y Lightning Damage (2)"}},
        {Attribute::OddAddsColdDamage2, {AttributeMode::Odd, 136, 136, "Adds X To Y Cold Damage (2)"}},
        {Attribute::OddTargetFireResistance, {AttributeMode::Odd, 137, 141, "Target Fire Resistance: -X%"}},
        {Attribute::OddTargetLightningResistance, {AttributeMode::Odd, 142, 146, "Target Lightning Resistance: -X%"}},
        {Attribute::OddTargetColdResistance, {AttributeMode::Odd, 147, 151, "Target Cold Resistance: -X%"}},
        {Attribute::OddTargetMagicResistance, {AttributeMode::Odd, 152, 156, "Target Magic Resistance: -X%"}},
        {Attribute::OddCannotBeFrozen, {AttributeMode::Odd, 157, 157, "Cannot Be Frozen"}},

        {Attribute::UniqueStrength, {AttributeMode::Unique, 1, 1, "+X To Strength"}},
        {Attribute::UniqueMagic, {AttributeMode::Unique, 2, 2, "+X To Magic"}},
        {Attribute::UniqueDexterity, {AttributeMode::Unique, 3, 3, "+X To Dexterity"}},
        {Attribute::UniqueVitality, {AttributeMode::Unique, 4, 4, "+X To Vitality"}},
        {Attribute::UniqueAllAttributes, {AttributeMode::Unique, 5, 5, "+X To All Attributes"}},
        {Attribute::UniqueArmorClass, {AttributeMode::Unique, 6, 6, "Armor Class: X"}},
        {Attribute::UniqueIncreasedArmor, {AttributeMode::Unique, 7, 7, "Increased Armor: X"}},
        {Attribute::UniqueEnhancedArmor, {AttributeMode::Unique, 8, 8, "+X% Enhanced Armor"}},
        {Attribute::UniqueChanceToHit, {AttributeMode::Unique, 9, 9, "Chance To Hit +X%"}},
        {Attribute::UniqueEnhancedDamage, {AttributeMode::Unique, 10, 10, "+X% Enhanced Damage"}},
        {Attribute::UniqueAddPointsToDamage, {AttributeMode::Unique, 11, 11, "Adds X Points To Damage"}},
        {Attribute::UniqueLightningHitDamage, {AttributeMode::Unique, 12, 12, "Lightning Hit Damage : X To Y"}},
        {Attribute::UniqueFireHitDamage, {AttributeMode::Unique, 13, 13, "Fire Hit Damage : X To Y"}},
        {Attribute::UniqueColdHitDamage, {AttributeMode::Unique, 14, 14, "Cold Hit Damage : X To Y"}},
        {Attribute::UniqueMagicHitDamage, {AttributeMode::Unique, 15, 15, "Magic Hit Damage : X To Y"}},
        {Attribute::UniqueResistAll, {AttributeMode::Unique, 16, 16, "Resist All : +X%"}},
        {Attribute::UniqueResistFire, {AttributeMode::Unique, 17, 17, "Resist Fire : +X%"}},
        {Attribute::UniqueResistLightning, {AttributeMode::Unique, 18, 18, "Resist Lightning : +X%"}},
        {Attribute::UniqueResistMagic, {AttributeMode::Unique, 19, 19, "Resist Magic : +X%"}},
        {Attribute::UniqueResistCold, {AttributeMode::Unique, 20, 20, "Resist Cold : +X%"}},
        {Attribute::UniqueAllResistancesZero, {AttributeMode::Unique, 21, 21, "All Resistances Equals 0%"}},
        {Attribute::UniqueRegeneratesLife, {AttributeMode::Unique, 22, 22, "Regenerates X Life Per 5 Sec"}},
        {Attribute::UniqueRegeneratesMana, {AttributeMode::Unique, 23, 23, "Regenerates X Mana Per 5 Sec"}},
        {Attribute::UniqueFasterHitRecovery, {AttributeMode::Unique, 24, 24, "X% Faster Hit Recovery"}},
        {Attribute::UniqueIncreasedAttackSpeed, {AttributeMode::Unique, 25, 25, "X% Increased Attack Speed"}},
        {Attribute::UniqueFasterBlockRate, {AttributeMode::Unique, 26, 26, "X% Faster Block Rate"}},
        {Attribute::UniqueFasterWalk, {AttributeMode::Unique, 27, 27, "X% Faster Walk"}},
        {Attribute::UniqueIncreasedCastSpeed, {AttributeMode::Unique, 28, 28, "X% Increased Cast Speed"}},
        {Attribute::UniqueLightRadius, {AttributeMode::Unique, 29, 29, "+X% Light Radius"}},
        {Attribute::UniqueDamageTakenFromEnemies, {AttributeMode::Unique, 30, 30, "-X Damage Taken From Enemies"}},
        {Attribute::UniqueHitPoints, {AttributeMode::Unique, 31, 31, "Hit Points : +X"}},
        {Attribute::UniqueMana, {AttributeMode::Unique, 32, 32, "Mana : +X"}},
        {Attribute::UniqueHighDurability, {AttributeMode::Unique, 33, 33, "High Durability"}},
        {Attribute::UniqueAlteredDurability, {AttributeMode::Unique, 34, 34, "Altered Durability"}},
        {Attribute::UniqueIndestructible, {AttributeMode::Unique, 35, 35, "Indestructible"}},
        {Attribute::UniqueSpellLevels, {AttributeMode::Unique, 36, 36, "Spells Are Increased X Levels"}},
        {Attribute::UniqueHitStealsLife, {AttributeMode::Unique, 37, 37, "Hit Steals X% Life"}},
        {Attribute::UniqueHitStealsMana, {AttributeMode::Unique, 38, 38, "Hit Steals X% Mana"}},
        {Attribute::UniqueRequirements, {AttributeMode::Unique, 39, 39, "Requirements +X%"}},
        {Attribute::UniqueOneHandedWeapon, {AttributeMode::Unique, 40, 40, "One Handed Weapon"}},
        {Attribute::UniqueUnusualItemDamage, {AttributeMode::Unique, 41, 41, "Unusual Item Damage"}},
        {Attribute::UniqueChanceToKnockback, {AttributeMode::Unique, 42, 42, "X% Change To Knockback"}},
        {Attribute::UniqueDamageVsDemon, {AttributeMode::Unique, 43, 43, "X% Damage Vs. Demon"}},
        {Attribute::UniqueDamageVsUndead, {AttributeMode::Unique, 44, 44, "X% Damage Vs. Undead"}},
        {Attribute::UniqueSpellCharges, {AttributeMode::Unique, 45, 45, "Spell (X) Charges (Y)"}},
        {Attribute::UniqueCriticalHitChance, {AttributeMode::Unique, 47, 47, "+X% Critical Hit Chance"}},
        {Attribute::UniqueCriticalHitDamage, {AttributeMode::Unique, 48, 48, "+X% Critical Hit Damage"}},
        {Attribute::UniqueSpellPower, {AttributeMode::Unique, 49, 49, "+X% Spell Power"}},
        {Attribute::UniqueExtraGold, {AttributeMode::Unique, 50, 50, "+X% Extra Gold From Monsters"}},
        {Attribute::UniqueMagicItemsChance, {AttributeMode::Unique, 51, 51, "+X% Chance Of Getting Magic Items"}},
        {Attribute::UniqueHalfTrapDamage, {AttributeMode::Unique, 52, 52, "Absorbs Half Trap Damage"}},
        {Attribute::UniqueAttackerTakesDamage, {AttributeMode::Unique, 53, 53, "Attacker Takes X - Y Damage"}},
        {Attribute::UniqueIncreasedChanceOfBlocking, {AttributeMode::Unique, 54, 54, "X% Increased Chance Of Blocking"}},
        {Attribute::UniqueTargetResistances, {AttributeMode::Unique, 55, 55, "Reduces Target Resistances: X%"}},
        {Attribute::UniqueTargetPhysicalResistances, {AttributeMode::Unique, 56, 56, "Reduces Target Physical Resistance: X%"}},
        {Attribute::UniqueTargetFireResistance, {AttributeMode::Unique, 57, 57, "Reduces Target Fire Resistance: X%"}},
        {Attribute::UniqueTargetLightningResistance, {AttributeMode::Unique, 58, 58, "Reduces Target Lightning Resistance: X%"}},
        {Attribute::UniqueTargetColdResistance, {AttributeMode::Unique, 59, 59, "Reduces Target Cold Resistance: X%"}},
        {Attribute::UniqueTargetMagicResistance, {AttributeMode::Unique, 60, 60, "Reduces Target Magic Resistance: X%"}},
        {Attribute::UniquePiercingAttack, {AttributeMode::Unique, 61, 61, "Piercing Attack: X%"}},
        {Attribute::UniqueHalfFreezeDuration, {AttributeMode::Unique, 62, 62, "Half Freeze Duration"}},
        {Attribute::UniqueCannotBeFrozen, {AttributeMode::Unique, 63, 63, "Cannot Be Frozen"}},
        {Attribute::UniqueMaximumMana, {AttributeMode::Unique, 64, 64, "Increased Maximum Mana X%"}},
        {Attribute::UniqueMaximumLife, {AttributeMode::Unique, 65, 65, "Increased Maximum Life X%"}},
        {Attribute::UniqueHitPointsCharacterLevel, {AttributeMode::Unique, 66, 66, "Hit Points : +(L*X/Y) (Based On Character Level)"}},
        {Attribute::UniqueManaCharacterLevel, {AttributeMode::Unique, 67, 67, "Mana : +(L*X/Y) (Based On Character Level)"}},
        {Attribute::UniqueStrengthCharacterLevel, {AttributeMode::Unique, 68, 68, "+(L*X/Y) To Strength (Based On Character Level)"}},
        {Attribute::UniqueDexterityCharacterLevel, {AttributeMode::Unique, 69, 69, "+(L*X/Y) To Dexterity (Based On Character Level)"}},
        {Attribute::UniqueMagicCharacterLevel, {AttributeMode::Unique, 70, 70, "+(L*X/Y) To Magic (Based On Character Level)"}},
        {Attribute::UniqueVitalityCharacterLevel, {AttributeMode::Unique, 71, 71, "+(L*X/Y) To Vitality (Based On Character Level)"}},
        {Attribute::UniqueAllStatsCharacterLevel, {AttributeMode::Unique, 72, 72, "+(L*X/Y) To All Stats. (Based On Character Level)"}},
        {Attribute::UniqueToHitCharacterLevel, {AttributeMode::Unique, 73, 73, "To Hit : (L*X/Y)% (Based On Character Level)"}},
        {Attribute::UniqueDamageCharacterLevel, {AttributeMode::Unique, 74, 74, "+(L*X/Y)% Damage (Based On Character Level)"}},
        {Attribute::UniqueSpellPowerCharacterLevel, {AttributeMode::Unique, 75, 75, "+(L*X/Y)% Spell Power (Based On Character Level)"}},
        {Attribute::UniqueDamageVsDemonsCharacterLevel, {AttributeMode::Unique, 76, 76, "+(L*X/Y)% Damage Vs.Demons (Based On Character Level)"}},
        {Attribute::UniqueDamageVsUndeadCharacterLevel, {AttributeMode::Unique, 77, 77, "+(L*X/Y)% Damage Vs.Undead (Based On Character Level)"}},
        {Attribute::UniqueAddsDamageCharacterLevel, {AttributeMode::Unique, 78, 78, "Adds (L*X/Y) Damage (Based On Character Level)"}},
        {Attribute::UniqueArmorClassCharacterLevel, {AttributeMode::Unique, 79, 79, "+(L*X/Y) To Armor Class (Based On Character Level)"}},
        {Attribute::UniqueResistAllCharacterLevel, {AttributeMode::Unique, 80, 80, "Resist All : +(L*X/Y)% (Based On Character Level)"}},
        {Attribute::UniqueFireDamageCharacterLevel, {AttributeMode::Unique, 81, 81, "+(L*X/Y)/2-(L*X/Y) Fire Damage (Based On Character Level)"}},
        {Attribute::UniqueLightningDamageCharacterLevel, {AttributeMode::Unique, 82, 82, "+1-(L*X/Y) Lightning Damage (Based On Character Level)"}},
        {Attribute::UniqueColdDamageCharacterLevel, {AttributeMode::Unique, 83, 83, "+(L*X/Y)/2-(L*X/Y) Cold Damage (Based On Character Level)"}},
        {Attribute::UniqueMagicDamageCharacterLevel, {AttributeMode::Unique, 84, 84, "+(L*X/Y)/2-(L*X/Y) Magic Damage (Based On Character Level)"}},
        {Attribute::UniqueMagicItemsChanceCharacterLevel, {AttributeMode::Unique, 85, 85, "+(L*X/Y)% Chance Of Getting Magic Items (Based On Character Level)"}},
        {Attribute::UniqueExtraGoldCharacterLevel, {AttributeMode::Unique, 86, 86, "+(L*X/Y)% Extra Gold From Monsters (Based On Character Level)"}},
        {Attribute::UniqueMaximumResistAll, {AttributeMode::Unique, 87, 87, "Maximum Resist All : +X%"}},
        {Attribute::UniqueMaximumResistFire, {AttributeMode::Unique, 88, 88, "Maximum Resist Fire : +X%"}},
        {Attribute::UniqueMaximumResistLightning, {AttributeMode::Unique, 89, 89, "Maximum Resist Lightning : +X%"}},
        {Attribute::UniqueMaximumResistMagic, {AttributeMode::Unique, 90, 90, "Maximum Resist Magic : +X%"}},
        {Attribute::UniqueMaximumResistCold, {AttributeMode::Unique, 91, 91, "Maximum Resist Cold : +X%"}},
        {Attribute::UniqueAddSpell, {AttributeMode::Unique, 92, 92, "+Y To Spell (X)"}},
        {Attribute::UniqueActOfTransformation, {AttributeMode::Unique, 99, 99, "Act Of Transformation (X)"}},
        {Attribute::UniqueDamageAbsorbedByMana, {AttributeMode::Unique, 100, 100, "X% Damage Absorbed By Mana"}},
        {Attribute::UniqueChanceToCastSpellOnStriking, {AttributeMode::Unique, 101, 101, "Y% Chance To Cast Spell (Y) On Striking"}},
        {Attribute::UniqueChanceToCastSpellWhenStruck, {AttributeMode::Unique, 102, 102, "Y% Chance To Cast Spell (Y) When Struck"}},
        {Attribute::UniqueIgnoreTargetDefense, {AttributeMode::Unique, 103, 103, "Ignore Target's Defense"}},

        {Attribute::SetStrength, {AttributeMode::Set, 1, 1, "+X To Strength"}},
        {Attribute::SetMagic, {AttributeMode::Set, 2, 2, "+X To Magic"}},
        {Attribute::SetDexterity, {AttributeMode::Set, 3, 3, "+X To Dexterity"}},
        {Attribute::SetVitality, {AttributeMode::Set, 4, 4, "+X To Vitality"}},
        {Attribute::SetAllAttributes, {AttributeMode::Set, 5, 5, "+X To All Attributes"}},
        {Attribute::SetArmorClass, {AttributeMode::Set, 6, 6, "Armor Class: X"}},
        {Attribute::SetIncreasedArmor, {AttributeMode::Set, 7, 7, "Increased Armor: X"}},
        {Attribute::SetEnhancedArmor, {AttributeMode::Set, 8, 8, "+X% Enhanced Armor"}},
        {Attribute::SetChanceToHit, {AttributeMode::Set, 9, 9, "Chance To Hit +X%"}},
        {Attribute::SetEnhancedDamage, {AttributeMode::Set, 10, 10, "+X% Enhanced Damage"}},
        {Attribute::SetAddPointsToDamage, {AttributeMode::Set, 11, 11, "Adds X Points To Damage"}},
        {Attribute::SetLightningHitDamage, {AttributeMode::Set, 12, 12, "Lightning Hit Damage : X To Y"}},
        {Attribute::SetFireHitDamage, {AttributeMode::Set, 13, 13, "Fire Hit Damage : X To Y"}},
        {Attribute::SetColdHitDamage, {AttributeMode::Set, 14, 14, "Cold Hit Damage : X To Y"}},
        {Attribute::SetMagicHitDamage, {AttributeMode::Set, 15, 15, "Magic Hit Damage : X To Y"}},
        {Attribute::SetResistAll, {AttributeMode::Set, 16, 16, "Resist All : +X%"}},
        {Attribute::SetResistFire, {AttributeMode::Set, 17, 17, "Resist Fire : +X%"}},
        {Attribute::SetResistLightning, {AttributeMode::Set, 18, 18, "Resist Lightning : +X%"}},
        {Attribute::SetResistMagic, {AttributeMode::Set, 19, 19, "Resist Magic : +X%"}},
        {Attribute::SetResistCold, {AttributeMode::Set, 20, 20, "Resist Cold : +X%"}},
        {Attribute::SetAllResistancesZero, {AttributeMode::Set, 21, 21, "All Resistances Equals 0%"}},
        {Attribute::SetRegeneratesLife, {AttributeMode::Set, 22, 22, "Regenerates X Life Per 5 Sec"}},
        {Attribute::SetRegeneratesMana, {AttributeMode::Set, 23, 23, "Regenerates X Mana Per 5 Sec"}},
        {Attribute::SetIncreasedChanceOfBlocking, {AttributeMode::Set, 24, 24, "X% Increased Chance Of Blocking"}},
        {Attribute::SetFasterHitRecovery, {AttributeMode::Set, 25, 25, "X% Faster Hit Recovery"}},
        {Attribute::SetIncreasedAttackSpeed, {AttributeMode::Set, 26, 26, "X% Increased Attack Speed"}},
        {Attribute::SetFasterBlockRate, {AttributeMode::Set, 27, 27, "X% Faster Block Rate"}},
        {Attribute::SetFasterWalk, {AttributeMode::Set, 28, 28, "X% Faster Walk"}},
        {Attribute::SetIncreasedCastSpeed, {AttributeMode::Set, 29, 29, "X% Increased Cast Speed"}},
        {Attribute::SetLightRadius, {AttributeMode::Set, 30, 30, "+X% Light Radius"}},
        {Attribute::SetDamageTakenFromEnemies, {AttributeMode::Set, 31, 31, "-X Damage Taken From Enemies"}},
        {Attribute::SetHitPoints, {AttributeMode::Set, 32, 32, "Hit Points : +X"}},
        {Attribute::SetMana, {AttributeMode::Set, 33, 33, "Mana : +X"}},
        {Attribute::SetHighDurability, {AttributeMode::Set, 34, 34, "High Durability"}},
        {Attribute::SetAlteredDurability, {AttributeMode::Set, 35, 35, "Altered Durability"}},
        {Attribute::SetIndestructible, {AttributeMode::Set, 36, 36, "Indestructible"}},
        {Attribute::SetSpellLevels, {AttributeMode::Set, 37, 37, "Spells Are Increased X Levels"}},
        {Attribute::SetHitStealsLife, {AttributeMode::Set, 38, 38, "Hit Steals X% Life"}},
        {Attribute::SetHitStealsMana, {AttributeMode::Set, 39, 39, "Hit Steals X% Mana"}},
        {Attribute::SetRequirements, {AttributeMode::Set, 40, 40, "Requirements +X%"}},
        {Attribute::SetOneHandedWeapon, {AttributeMode::Set, 41, 41, "One Handed Weapon"}},
        {Attribute::SetOffhandWeapon, {AttributeMode::Set, 42, 42, "Offhand Weapon"}},
        {Attribute::SetChanceToKnockback, {AttributeMode::Set, 43, 43, "X% Change To Knockback"}},
        {Attribute::SetDamageVsDemon, {AttributeMode::Set, 44, 44, "X% Damage Vs. Demon"}},
        {Attribute::SetDamageVsUndead, {AttributeMode::Set, 45, 45, "X% Damage Vs. Undead"}},
        {Attribute::SetCriticalHitChance, {AttributeMode::Set, 48, 48, "+X% Critical Hit Chance"}},
        {Attribute::SetCriticalHitDamage, {AttributeMode::Set, 49, 49, "+X% Critical Hit Damage"}},
        {Attribute::SetSpellPower, {AttributeMode::Set, 50, 50, "+X% Spell Power"}},
        {Attribute::SetExtraGold, {AttributeMode::Set, 51, 51, "+X% Extra Gold From Monsters"}},
        {Attribute::SetMagicItemsChance, {AttributeMode::Set, 52, 52, "+X% Chance Of Getting Magic Items"}},
        {Attribute::SetHalfTrapDamage, {AttributeMode::Set, 53, 53, "Absorbs Half Trap Damage"}},
        {Attribute::SetAttackerTakesDamage, {AttributeMode::Set, 54, 54, "Attacker Takes X - Y Damage"}},
        {Attribute::SetTargetResistances, {AttributeMode::Set, 55, 55, "Reduces Target Resistances: X%"}},
        {Attribute::SetTargetPhysicalResistances, {AttributeMode::Set, 56, 56, "Reduces Target Physical Resistance: X%"}},
        {Attribute::SetTargetFireResistance, {AttributeMode::Set, 57, 57, "Reduces Target Fire Resistance: X%"}},
        {Attribute::SetTargetLightningResistance, {AttributeMode::Set, 58, 58, "Reduces Target Lightning Resistance: X%"}},
        {Attribute::SetTargetColdResistance, {AttributeMode::Set, 59, 59, "Reduces Target Cold Resistance: X%"}},
        {Attribute::SetTargetMagicResistance, {AttributeMode::Set, 60, 60, "Reduces Target Magic Resistance: X%"}},
        {Attribute::SetPiercingAttack, {AttributeMode::Set, 61, 61, "Piercing Attack: X%"}},
        {Attribute::SetHalfFreezeDuration, {AttributeMode::Set, 62, 62, "Half Freeze Duration"}},
        {Attribute::SetCannotBeFrozen, {AttributeMode::Set, 63, 63, "Cannot Be Frozen"}},
        {Attribute::SetMaximumMana, {AttributeMode::Set, 64, 64, "Increased Maximum Mana X%"}},
        {Attribute::SetMaximumLife, {AttributeMode::Set, 65, 65, "Increased Maximum Life X%"}},
        {Attribute::SetHitPointsCharacterLevel, {AttributeMode::Set, 66, 66, "Hit Points : +(L*X/Y) (Based On Character Level)"}},
        {Attribute::SetManaCharacterLevel, {AttributeMode::Set, 67, 67, "Mana : +(L*X/Y) (Based On Character Level)"}},
        {Attribute::SetStrengthCharacterLevel, {AttributeMode::Set, 68, 68, "+(L*X/Y) To Strength (Based On Character Level)"}},
        {Attribute::SetDexterityCharacterLevel, {AttributeMode::Set, 69, 69, "+(L*X/Y) To Dexterity (Based On Character Level)"}},
        {Attribute::SetMagicCharacterLevel, {AttributeMode::Set, 70, 70, "+(L*X/Y) To Magic (Based On Character Level)"}},
        {Attribute::SetVitalityCharacterLevel, {AttributeMode::Set, 71, 71, "+(L*X/Y) To Vitality (Based On Character Level)"}},
        {Attribute::SetAllStatsCharacterLevel, {AttributeMode::Set, 72, 72, "+(L*X/Y) To All Stats. (Based On Character Level)"}},
        {Attribute::SetToHitCharacterLevel, {AttributeMode::Set, 73, 73, "To Hit : (L*X/Y)% (Based On Character Level)"}},
        {Attribute::SetDamageCharacterLevel, {AttributeMode::Set, 74, 74, "+(L*X/Y)% Damage (Based On Character Level)"}},
        {Attribute::SetSpellPowerCharacterLevel, {AttributeMode::Set, 75, 75, "+(L*X/Y)% Spell Power (Based On Character Level)"}},
        {Attribute::SetDamageVsDemonsCharacterLevel, {AttributeMode::Set, 76, 76, "+(L*X/Y)% Damage Vs.Demons (Based On Character Level)"}},
        {Attribute::SetDamageVsUndeadCharacterLevel, {AttributeMode::Set, 77, 77, "+(L*X/Y)% Damage Vs.Undead (Based On Character Level)"}},
        {Attribute::SetAddsDamageCharacterLevel, {AttributeMode::Set, 78, 78, "Adds (L*X/Y) Damage (Based On Character Level)"}},
        {Attribute::SetArmorClassCharacterLevel, {AttributeMode::Set, 79, 79, "+(L*X/Y) To Armor Class (Based On Character Level)"}},
        {Attribute::SetResistAllCharacterLevel, {AttributeMode::Set, 80, 80, "Resist All : +(L*X/Y)% (Based On Character Level)"}},
        {Attribute::SetFireDamageCharacterLevel, {AttributeMode::Set, 81, 81, "+(L*X/Y)/2-(L*X/Y) Fire Damage (Based On Character Level)"}},
        {Attribute::SetLightningDamageCharacterLevel, {AttributeMode::Set, 82, 82, "+1-(L*X/Y) Lightning Damage (Based On Character Level)"}},
        {Attribute::SetColdDamageCharacterLevel, {AttributeMode::Set, 83, 83, "+(L*X/Y)/2-(L*X/Y) Cold Damage (Based On Character Level)"}},
        {Attribute::SetMagicDamageCharacterLevel, {AttributeMode::Set, 84, 84, "+(L*X/Y)/2-(L*X/Y) Magic Damage (Based On Character Level)"}},
        {Attribute::SetMagicItemsChanceCharacterLevel, {AttributeMode::Set, 85, 85, "+(L*X/Y)% Chance Of Getting Magic Items (Based On Character Level)"}},
        {Attribute::SetExtraGoldCharacterLevel, {AttributeMode::Set, 86, 86, "+(L*X/Y)% Extra Gold From Monsters (Based On Character Level)"}},
        {Attribute::SetMaximumResistAll, {AttributeMode::Set, 87, 87, "Maximum Resist All : +X%"}},
        {Attribute::SetMaximumResistFire, {AttributeMode::Set, 88, 88, "Maximum Resist Fire : +X%"}},
        {Attribute::SetMaximumResistLightning, {AttributeMode::Set, 89, 89, "Maximum Resist Lightning : +X%"}},
        {Attribute::SetMaximumResistMagic, {AttributeMode::Set, 90, 90, "Maximum Resist Magic : +X%"}},
        {Attribute::SetMaximumResistCold, {AttributeMode::Set, 91, 91, "Maximum Resist Cold : +X%"}},
        {Attribute::SetAddSpell, {AttributeMode::Set, 92, 92, "+Y To Spell (X)"}},
        {Attribute::SetActOfTransformation, {AttributeMode::Set, 99, 99, "Act Of Transformation (X)"}},
        {Attribute::SetDamageAbsorbedByMana, {AttributeMode::Set, 100, 100, "X% Damage Absorbed By Mana"}},
        {Attribute::SetChanceToCastSpellOnStriking, {AttributeMode::Set, 101, 101, "Y% Chance To Cast Spell (Y) On Striking"}},
        {Attribute::SetChanceToCastSpellWhenStruck, {AttributeMode::Set, 102, 102, "Y% Chance To Cast Spell (Y) When Struck"}},
        {Attribute::SetIgnoreTargetDefense, {AttributeMode::Set, 103, 103, "Ignore Target's Defense"}},
    };

    const std::map<ItemPosition, int> itemBufferStart = {
        {ItemPosition::Body, 8280},
        {ItemPosition::Head, 8376},
        {ItemPosition::Ring1, 8472},
        {ItemPosition::Ring2, 8568},
        {ItemPosition::Amulet, 8664},
        {ItemPosition::Hand1, 8760},
        {ItemPosition::Hand2, 8856},
        {ItemPosition::Belt, 8952}
    };

    const std::map<ItemType, int> attributeStart = {
        {ItemType::NoItem, -1},
        {ItemType::Quest, -1},
        {ItemType::Common, -1},
        {ItemType::Magic, 35},
        {ItemType::Rare, 35},
        {ItemType::Unique, 37},
        {ItemType::Set, 39},
        {ItemType::Crafted, 35},
        };

    const std::map<ItemType, int> attributeCount = {
        {ItemType::NoItem, -1},
        {ItemType::Quest, -1},
        {ItemType::Common, -1},
        {ItemType::Magic, 2},
        {ItemType::Rare, 8},
        {ItemType::Unique, 9},
        {ItemType::Set, 8},
        {ItemType::Crafted, 8}
    };
}

#endif // BELZEBUBMAGIC_H
