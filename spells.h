#ifndef SPELLS_H
#define SPELLS_H

#include <vector>
#include <string>
#include <map>

namespace Belzebub {

enum class SpellType : int {
    NoSpell = -1, FrostShard = 0, FireBolt, ChargedBolt, Healing, HealOther, HolyBolt, Inferno,
    Warp, FireWall, Telekinesis, Lightning, TownPortal, Flash, CircleOfIce,
    Phasing, LightningWall, StoneCurse, FireBall, FlameWave, ChainLightning, IceBlast,
    empty1, MindMace, Elemental, Golem, FrozenOrb, MeteorCluster, Guardian,
    Nova, Sentinel, Teleport, Apocalypse, empty2, Blizzard, Immolation,
    DarkPact, empty3, Insanity, empty4, BoneSpirit, BloodStar, Sacrifice
};
const std::map<SpellType, std::string> spellNames = {
    {SpellType::NoSpell, "No Spell"},
    {SpellType::FrostShard, "Frost Shard"},
    {SpellType::FireBolt, "Fire Bolt"},
    {SpellType::ChargedBolt, "Charged Bolt"},
    {SpellType::Healing, "Healing"},
    {SpellType::HealOther, "Heal Other"},
    {SpellType::HolyBolt, "Holy Bolt"},
    {SpellType::Inferno, "Inferno"},
    {SpellType::Warp, "Warp"},
    {SpellType::FireWall, "Fire Wall"},
    {SpellType::Telekinesis, "Telekinesis"},
    {SpellType::Lightning, "Lightning"},
    {SpellType::TownPortal, "Town Portal"},
    {SpellType::Flash, "Flash"},
    {SpellType::CircleOfIce, "Circle Of Ice"},
    {SpellType::Phasing, "Phasing"},
    {SpellType::LightningWall, "Lightning Wall"},
    {SpellType::StoneCurse, "Stone Curse"},
    {SpellType::FireBall, "Fire Ball"},
    {SpellType::FlameWave, "Flame Wave"},
    {SpellType::ChainLightning, "Chain Lightning"},
    {SpellType::IceBlast, "Ice Blast"},
    {SpellType::MindMace, "Mind Mace"},
    {SpellType::Elemental, "Elemental"},
    {SpellType::Golem, "Golem"},
    {SpellType::FrozenOrb, "Frozen Orb"},
    {SpellType::MeteorCluster, "Meteor Cluster"},
    {SpellType::Guardian, "Guardian"},
    {SpellType::Nova, "Nova"},
    {SpellType::Sentinel, "Sentinel"},
    {SpellType::Teleport, "Teleport"},
    {SpellType::Apocalypse, "Apocalypse"},
    {SpellType::Blizzard, "Blizzard"},
    {SpellType::Immolation, "Immolation"},
    {SpellType::DarkPact, "Dark Pact"},
    {SpellType::Insanity, "Insanity"},
    {SpellType::BoneSpirit, "Bone Spirit"},
    {SpellType::BloodStar, "Blood Star"},
    {SpellType::Sacrifice, "Sacrifice"}
};

}

#endif // SPELLS_H
