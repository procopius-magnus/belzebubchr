#ifndef BELZEBUBCHR_H
#define BELZEBUBCHR_H

#include "belzebubmagic.h"

#include <vector>
#include <string>

class BelzebubChr {
    std::vector<char> buffer1;
    std::vector<char> buffer2;
    void loadBuffer(const std::string &fileName, const int num);
    void updateChecksum(const size_t position, const unsigned char value);
public:
    void loadBuffer1(const std::string &fileName) {loadBuffer(fileName, 1);}
    void loadBuffer2(const std::string &fileName) {loadBuffer(fileName, 2);}
    void saveBuffer(const std::string &fileName);
    void printDiff();
    void printItems();
    void setDirect(const size_t position, const unsigned char value);
    void setByte(const size_t position, const unsigned char value);
    void setWord(const int position, const int value);
    // There must be some gold at the position or it will not work.
    void setGoldPositionLowerLeft(const int value);
    void setGoldPositionLowerRight(const int value);
    void setSpellLevel(const Belzebub::SpellType spellType, const int value);
    void setStaffSpell(const Belzebub::SpellType spellType, const int maxCharges);
    Belzebub::ItemType getItemType(const Belzebub::ItemPosition itemPosition);
    void setItemType(const Belzebub::ItemPosition itemPosition, const Belzebub::ItemType itemType);
    void setItemType2(const Belzebub::ItemPosition itemPosition, int value);
    void setItemDurability(const Belzebub::ItemPosition itemPosition, const int value);
    void setItemValue(const Belzebub::ItemPosition itemPosition, const int attributePosition, const int attributeType, const int value1, const int value2 = 0);
    void setItemAttribute(const Belzebub::ItemPosition itemPosition, const int attributePosition, const Belzebub::Attribute attribute, const int value1, const int value2 = 0);
};

#endif // BELZEBUBCHR_H
