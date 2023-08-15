#ifndef BELZEBUBCHR_H
#define BELZEBUBCHR_H

#include "file.h"
#include "spell.h"
#include "recipe.h"

#include <vector>
#include <string>

class BelzebubChr {
    std::vector<char> backupBuffer;
    std::vector<char> buffer1;
    std::vector<char> buffer2;
    bool loadBuffer(const std::string &fileName, const int num);
    void updateChecksum(const size_t position, const char value);
public:
    BelzebubChr();
    bool isOk = false;
    bool loadBuffer1(const std::string &fileName) {return loadBuffer(fileName, 1);}
    bool loadBuffer2(const std::string &fileName) {return loadBuffer(fileName, 2);}
    void saveBuffer(const std::string &fileName);
    void saveBackup(const std::string &fileName);
    void printDiff(); // Print file differences.
    void printItems(); // Print attributes on equiped items.
    void setDirect(const size_t position, const unsigned char value); // Set value without checksum.
    void setByte(const size_t position, const unsigned char value); // Set value with checksum.
    void setWord(const size_t position, const int value); // Set value with checksum.
    void updatePositionChecksum(const int position);
    int getByte(const size_t position);
    int getWord(const size_t position);
    void setGoldPositionLowerLeft(const int value); // There must be some gold at the position or it will not work.
    void setGoldPositionLowerRight(const int value); // There must be some gold at the position or it will not work.
    void turnRecipe(const int position);
    std::vector<int> getRecipes();
    void setSpellLevel(const Belzebub::SpellType spellType, const int value);
    void setStaffSpell(const Belzebub::SpellType spellType, const int maxCharges);
    Belzebub::ItemMagic getItemMagic(const Belzebub::ItemPosition itemPosition);
    void setItemMagic(const Belzebub::ItemPosition itemPosition, const Belzebub::ItemMagic itemMagic);
    const Belzebub::ItemType& getItemType(const Belzebub::ItemPosition itemPosition);
    void setItemType(const Belzebub::ItemPosition itemPosition, int value);
    void setItemDurability(const Belzebub::ItemPosition itemPosition, const int value);
    void setItemValue(const Belzebub::ItemPosition itemPosition, const int attributePosition, const int attributeType, const int value1, const int value2 = 0);
    void setItemAttribute(const Belzebub::ItemPosition itemPosition, const int attributePosition, const Belzebub::Attribute attribute, int value1, const int value2 = 0);

    Belzebub::AttributeValue getItemAttributeValue(const Belzebub::ItemPosition itemPosition, const int attributePosition);

    bool isBody();
    bool isHead();
    bool isRing1();
    bool isRing2();
    bool isAmulet();
    bool isHand1();
    bool isHand2();
    bool isBelt();

    bool isDurability(const Belzebub::ItemPosition itemPosition);
    int getItemDurability(const Belzebub::ItemPosition itemPosition);

    Belzebub::SpellType getStaffSpell(const Belzebub::ItemPosition itemPosition);
    int getStaffCharges(const Belzebub::ItemPosition itemPosition);

    int getSpellLevel(const Belzebub::SpellType spellType);

    std::vector<Belzebub::AttributeData> getAttributes(const Belzebub::AttributeMode attributeMode);
};

#endif // BELZEBUBCHR_H
