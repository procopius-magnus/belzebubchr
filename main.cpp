#include "belzebubchr.h"

#include <iostream>
using namespace std;

int main()
{
    if (1) {
        // Print attributes on equiped items.
        BelzebubChr belzebubChr;
        belzebubChr.loadBuffer1("/home/le/DiabloHD/game_info/data/Data/saves/save0.chr");
        belzebubChr.printItems();
    }

    if (1) {
        // Print file differences.
        // Usage: backup your save, then drop one item to the ground and make another save.
        BelzebubChr belzebubChr;
        belzebubChr.loadBuffer1("/home/le/DiabloHD/game_info/data/Data/saves/save0.chr");
        belzebubChr.loadBuffer2("/home/le/DiabloHD/game_info/data/Data/saves/save1.chr");
        belzebubChr.printDiff();
    }

    {

        BelzebubChr belzebubChr;
        belzebubChr.loadBuffer1("/home/le/DiabloHD/game_info/data/Data/saves/save0.chr");

        if (0) {
            belzebubChr.setGoldPositionLowerLeft(900000);
            belzebubChr.setGoldPositionLowerRight(900000);
        }

        if (0) {
            belzebubChr.setSpellLevel(Belzebub::SpellType::FrostShard, 0);
            belzebubChr.setSpellLevel(Belzebub::SpellType::FireBolt, 0);
            belzebubChr.setSpellLevel(Belzebub::SpellType::ChargedBolt, 0);
            belzebubChr.setSpellLevel(Belzebub::SpellType::Healing, 15);
            belzebubChr.setSpellLevel(Belzebub::SpellType::HealOther, 0);
            belzebubChr.setSpellLevel(Belzebub::SpellType::HolyBolt, 15);
            belzebubChr.setSpellLevel(Belzebub::SpellType::Inferno, 0);

            belzebubChr.setSpellLevel(Belzebub::SpellType::Warp, 0);
            belzebubChr.setSpellLevel(Belzebub::SpellType::FireWall, 0);
            belzebubChr.setSpellLevel(Belzebub::SpellType::Telekinesis, 0);
            belzebubChr.setSpellLevel(Belzebub::SpellType::Lightning, 0);
            belzebubChr.setSpellLevel(Belzebub::SpellType::TownPortal, 15);
            belzebubChr.setSpellLevel(Belzebub::SpellType::Flash, 0);
            belzebubChr.setSpellLevel(Belzebub::SpellType::CircleOfIce, 0);

            belzebubChr.setSpellLevel(Belzebub::SpellType::Phasing, 0);
            belzebubChr.setSpellLevel(Belzebub::SpellType::LightningWall, 0);
            belzebubChr.setSpellLevel(Belzebub::SpellType::StoneCurse, 15);
            belzebubChr.setSpellLevel(Belzebub::SpellType::FireBall, 15);
            belzebubChr.setSpellLevel(Belzebub::SpellType::FlameWave, 0);
            belzebubChr.setSpellLevel(Belzebub::SpellType::ChainLightning, 15);
            belzebubChr.setSpellLevel(Belzebub::SpellType::IceBlast, 15);

            belzebubChr.setSpellLevel(Belzebub::SpellType::MindMace, 0);
            belzebubChr.setSpellLevel(Belzebub::SpellType::Elemental, 0);
            belzebubChr.setSpellLevel(Belzebub::SpellType::Golem, 15);
            belzebubChr.setSpellLevel(Belzebub::SpellType::FrozenOrb, 0);
            belzebubChr.setSpellLevel(Belzebub::SpellType::MeteorCluster, 15);
            belzebubChr.setSpellLevel(Belzebub::SpellType::Guardian, 15);

            belzebubChr.setSpellLevel(Belzebub::SpellType::Nova, 15);
            belzebubChr.setSpellLevel(Belzebub::SpellType::Sentinel, 0);
            belzebubChr.setSpellLevel(Belzebub::SpellType::Teleport, 15);
            belzebubChr.setSpellLevel(Belzebub::SpellType::Apocalypse, 15);
            belzebubChr.setSpellLevel(Belzebub::SpellType::Blizzard, 0);
            belzebubChr.setSpellLevel(Belzebub::SpellType::Immolation, 15);

            belzebubChr.setSpellLevel(Belzebub::SpellType::DarkPact, 0);
            belzebubChr.setSpellLevel(Belzebub::SpellType::Insanity, 0);
            belzebubChr.setSpellLevel(Belzebub::SpellType::BoneSpirit, 15);
            belzebubChr.setSpellLevel(Belzebub::SpellType::BloodStar, 0);
            belzebubChr.setSpellLevel(Belzebub::SpellType::Sacrifice, 0);
        }

        if (0) {
            // for testing
            int i = 1;
            int type = 137;
            belzebubChr.setItemValue(Belzebub::ItemPosition::Hand1, i, type, 17);
            //belzebubChr.setItemValue(Belzebub::ItemPosition::Hand2, i, type, 17);
            belzebubChr.setItemValue(Belzebub::ItemPosition::Amulet, i, type, 17);
            belzebubChr.setItemValue(Belzebub::ItemPosition::Head, i, type, 17);
            belzebubChr.setItemValue(Belzebub::ItemPosition::Body, i, type, 17);
            belzebubChr.setItemValue(Belzebub::ItemPosition::Belt, i, type, 17);
            belzebubChr.setItemValue(Belzebub::ItemPosition::Ring1, i, type, 17);
            belzebubChr.setItemValue(Belzebub::ItemPosition::Ring2, i, type, 17);
        }
        {
            // for testing
            //belzebubChr.setDirect(8, 182 + 2);
            //belzebubChr.setDirect(2356, 2 -> 0);
            //belzebubChr.setDirect(4516, 0);
        }

        if (0) {
            // example:
            belzebubChr.setItemAttribute(Belzebub::ItemPosition::Ring2, 1, Belzebub::Attribute::OddStrength, 30);
            belzebubChr.setItemAttribute(Belzebub::ItemPosition::Ring2, 2, Belzebub::Attribute::EvenResistAll, 40);
            belzebubChr.setStaffSpell(Belzebub::SpellType::ChainLightning, 5000); // You must be equiped with (blue/yellow/orange) staff!
        }

        belzebubChr.saveBuffer("/home/le/DiabloHD/game_info/data/Data/player_save/save0.chr");
    }

    return 0;
}
