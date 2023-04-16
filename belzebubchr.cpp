#include "belzebubchr.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include "zlib.h"
using namespace std;
using namespace Belzebub;

BelzebubChr::BelzebubChr()
{
    for (auto &it : attrMap) {
        const_cast<AttributeData&>(it.second).attribute = it.first;
    }
}

bool BelzebubChr::loadBuffer(const string &fileName, const int num)
{
    try {
        std::ifstream myfile(fileName, ios::in | ios::binary);
        myfile.seekg(0, myfile.end);
        const size_t fileSize = myfile.tellg();
        vector<char> fileBuffer(fileSize);
        myfile.seekg(0, myfile.beg);
        myfile.read(fileBuffer.data(), fileSize);
        myfile.close();

        vector<char> &buffer = num == 1 ? buffer1 : buffer2;
        uLongf destLen = 1000000;
        buffer.resize(destLen);
        if (uncompress((Bytef*)buffer.data(), &destLen, (const Bytef*)fileBuffer.data(), (uLong)fileBuffer.size()) != Z_OK) {
            cout << "uncompress error" << endl;
            return false;
        }
        buffer.resize(destLen);
        if (num == 1) {
            backupBuffer = buffer1;
            isOk = true;
        }
        return true;
    }
    catch (...) {
        return false;
    }
}

void BelzebubChr::updateChecksum(const size_t position, const char value)
{
    union __attribute__ ((packed)) ChecksumType {
        char byte[2];
        short word;
    };
    ChecksumType &checksum = (ChecksumType&)buffer1[12];
    checksum.word += buffer1[position] - value;
}

void BelzebubChr::saveBuffer(const string &fileName) {
    if (!isOk) {
        return;
    }
    uLongf destLen = 1000000;
    vector<char> fileBuffer(destLen);
    compress((Bytef*)fileBuffer.data(), &destLen, (const Bytef*)buffer1.data(), (uLong)buffer1.size());
    fileBuffer.resize(destLen);
    std::ofstream myfile(fileName, ios::out | ios::binary);
    myfile.write(fileBuffer.data(), fileBuffer.size());
    myfile.close();
}

void BelzebubChr::saveBackup(const std::string &fileName)
{
    if (!isOk) {
        return;
    }
    uLongf destLen = 1000000;
    vector<char> fileBuffer(destLen);
    compress((Bytef*)fileBuffer.data(), &destLen, (const Bytef*)backupBuffer.data(), (uLong)backupBuffer.size());
    fileBuffer.resize(destLen);
    std::ofstream myfile(fileName, ios::out | ios::binary);
    myfile.write(fileBuffer.data(), fileBuffer.size());
    myfile.close();
}

void BelzebubChr::printDiff()
{
    cout << "position/signed diff/unsigned diff" << endl;
    size_t c = 0;
    for (size_t i = 0; i < buffer1.size(); ++i) {
        if (buffer1[i] != buffer2[i] || i == 12 || i == 13 || (1 && i < c) || (0 && i == 8376)) {
            if (c == 0 && i >= 8280) {
                c = i + 100;
            }
            cout << std::setw(4) << std::right << i << " " << std::setw(4) << std::right << int(buffer1[i]) << " " << std::setw(4) << std::right << int(buffer2[i]) << "  " << std::setw(4) << std::right << int((unsigned char)buffer1[i]) << " " << std::setw(4) << std::right << int((unsigned char)buffer2[i]) << endl;
        }
    }
}

void BelzebubChr::printItems()
{
    cout << "e - Even   o - Odd   u - Unique   s - Set" << endl;
    cout << "item.position  type/value1/value2   unsigned type/value1/value2" << endl;
    for (int k = 0; k < 8; ++k) {
        const ItemPosition itemPosition = ItemPosition(k);
        const ItemMagic itemMagic = getItemMagic(itemPosition);
        if (itemMagic == ItemMagic::NoItem) {
            continue;
        }
        string itemStr;
        switch (itemPosition) {
            case ItemPosition::Body: itemStr = "body"; break;
            case ItemPosition::Head: itemStr = "head"; break;
            case ItemPosition::Ring1: itemStr = "ring1"; break;
            case ItemPosition::Ring2: itemStr = "ring2"; break;
            case ItemPosition::Amulet: itemStr = "amulet"; break;
            case ItemPosition::Hand1: itemStr = "hand1"; break;
            case ItemPosition::Hand2: itemStr = "hand2"; break;
            case ItemPosition::Belt: itemStr = "belt"; break;
        }
        cout << std::setw(6) << std::left << itemStr << std::setw(5) << std::right << "type" << " " << std::setw(5) << std::right << "val1" << " " << std::setw(5) << std::right << "val2" << "  " << std::setw(5) << std::right << "uval1" << "  " << std::setw(5) << std::right << "uval2" << "  " << endl;
        for (int i = 0; i < attributeCount.at(itemMagic); ++i) {
            const AttributeMode attributeMode = attributeModeMap.at({itemMagic, i});
            cout << k << "." << i;
            if (attributeMode == AttributeMode::Even) {
                cout << " e ";
            }
            else if (attributeMode == AttributeMode::Odd) {
                cout << " o ";
            }
            else if (attributeMode == AttributeMode::Unique) {
                cout << " u ";
            }
            else if (attributeMode == AttributeMode::Set) {
                cout << " s ";
            }
            else {
                cout << "   ";
            }
            string typeName = "attribute unknown";
            const Belzebub::AttributeValue attributeValue = getItemAttributeValue(itemPosition, i);
            if (attributeValue.isNotUsed) {
                typeName = "attribute not used";
            }
            else {
                typeName = attributeValue.attributeData.name;
            }
            cout << std::setw(5) << std::right << attributeValue.attributeType << " " << std::setw(5) << std::right << attributeValue.value1 << " " << std::setw(5) << std::right << attributeValue.value2 << "  " << std::setw(5) << std::right << attributeValue.uvalue1 << "  " << std::setw(5) << std::right << attributeValue.uvalue2 << "  " << typeName << endl;
        }
    }
}

void BelzebubChr::setDirect(const size_t position, const unsigned char value) {
    buffer1[position] = value;
}

void BelzebubChr::setByte(const size_t position, const unsigned char value) {
    updateChecksum(position, value);
    buffer1[position] = value;
}

void BelzebubChr::setWord(const size_t position, const int value) {
    setByte(position, value % 256);
    setByte(position + 1, value / 256);
}

int BelzebubChr::getByte(const size_t position) {
    return (unsigned char)buffer1[position];
}

int BelzebubChr::getWord(const size_t position) {
    return (unsigned char)buffer1[position] + ((unsigned char)buffer1[position + 1]) * 256;
}

void BelzebubChr::setGoldPositionLowerLeft(const int value) {
    setByte(15764, value % 256);
    setByte(15765, value / 256);
    setByte(15768, value % 256);
    setByte(15769, value / 256);
    setByte(15770, value / 65536);
}
void BelzebubChr::setGoldPositionLowerRight(const int value) {
    setByte(16628, value % 256);
    setByte(16629, value / 256);
    setByte(16632, value % 256);
    setByte(16633, value / 256);
    setByte(16634, value / 65536);
}

void BelzebubChr::setSpellLevel(const Belzebub::SpellType spellType, const int value) {
    setDirect(572 + 4 * int(spellType), std::clamp(value, 0, 125));
}

void BelzebubChr::setStaffSpell(const SpellType spellType, const int maxCharges) {
    // Max and current charges.
    int bufferPosition = itemBufferStart.at(ItemPosition::Hand1);
    setWord(bufferPosition + 27, maxCharges);
    setWord(bufferPosition + 29, maxCharges);
    setByte(bufferPosition + 31, int(spellType));
}

ItemMagic BelzebubChr::getItemMagic(const ItemPosition itemPosition) {
    ItemMagic itemMagic = ItemMagic::NoItem;
    int bufferPosition = itemBufferStart.at(itemPosition);
    const int t = buffer1[bufferPosition];
    if (t == 7 || t == 8 || t == 9 || t == 10 || t == 11 || t == 12 || t == 13) {
        itemMagic = ItemMagic(t);
    }
    return itemMagic;
}

void BelzebubChr::setItemMagic(const ItemPosition itemPosition, const ItemMagic itemMagic) {
    int bufferPosition = itemBufferStart.at(itemPosition);
    setByte(bufferPosition, int(itemMagic));
}

const Belzebub::ItemType& BelzebubChr::getItemType(const Belzebub::ItemPosition itemPosition)
{
    int bufferPosition = itemBufferStart.at(itemPosition);
    size_t typeIndex = 0;
    const int number = getByte(bufferPosition + 20);
    for (size_t i = 0; i < Belzebub::itemTypes.size(); ++i) {
        if (Belzebub::itemTypes[i].number == number) {
            typeIndex = i;
            break;
        }
    }
    return Belzebub::itemTypes[typeIndex];
}

void BelzebubChr::setItemType(const ItemPosition itemPosition, int value) {
    int bufferPosition = itemBufferStart.at(itemPosition);
    setByte(bufferPosition + 20, value);
}

void BelzebubChr::setItemDurability(const ItemPosition itemPosition, const int value) {
    // Max and current durability.
    int bufferPosition = itemBufferStart.at(itemPosition);
    setWord(bufferPosition + 23, value);
    setWord(bufferPosition + 25, value);
}

void BelzebubChr::setItemValue(const ItemPosition itemPosition, const int attributePosition, const int attributeType, const int value1, const int value2) {
    const ItemMagic itemMagic = getItemMagic(itemPosition);
    int bufferPosition = itemBufferStart.at(itemPosition);
    bufferPosition += attributeStart.at(itemMagic);
    if (itemMagic == ItemMagic::Rare || itemMagic == ItemMagic::Crafted || itemMagic == ItemMagic::Magic) {
        bufferPosition += attributePosition * 6;
        if (attributeType != (int)Attribute::NoAttribute) {
            setWord(bufferPosition, attributeType);
            if (value1 < 0) {
                setByte(bufferPosition + 2, value1);
                setByte(bufferPosition + 3, -1);
            }
            else {
                setWord(bufferPosition + 2, value1);
            }
            setWord(bufferPosition + 4, value2);
        }
        else {
            setByte(bufferPosition + 0, 255);
            setByte(bufferPosition + 1, 255);
            setByte(bufferPosition + 2, 0);
            setByte(bufferPosition + 3, 0);
            setByte(bufferPosition + 4, 0);
            setByte(bufferPosition + 5, 0);
        }
    }
    else if (itemMagic == ItemMagic::Unique) {
        bufferPosition += attributePosition * 5;
        if (attributeType != (int)Attribute::NoAttribute) {
            setByte(bufferPosition, attributeType);
            /*
            if (value1 < 0) {
                setByte(bufferPosition + 1, value1);
                setByte(bufferPosition + 2, -1);
            }
            else {
                setWord(bufferPosition + 1, value1);
            }
            */
            setWord(bufferPosition + 1, value1);
            setWord(bufferPosition + 3, value2);
        }
        else {
            setByte(bufferPosition + 0, 0);
            setByte(bufferPosition + 1, 0);
            setByte(bufferPosition + 2, 0);
            setByte(bufferPosition + 3, 0);
            setByte(bufferPosition + 4, 0);
            setByte(bufferPosition + 5, 0);
        }
    }
    else if (itemMagic == ItemMagic::Set) {
        bufferPosition += attributePosition * 6;
        if (attributeType != (int)Attribute::NoAttribute) {
            setByte(bufferPosition, attributeType);
            /*
            if (value1 < 0) {
                setByte(bufferPosition + 1, value1);
                setByte(bufferPosition + 2, -1);
            }
            else {
                setWord(bufferPosition + 1, value1);
            }
            */
            setWord(bufferPosition + 1, value1);
            setWord(bufferPosition + 3, value2);
            setByte(bufferPosition + 4, 0);

        }
        else {
            setByte(bufferPosition + 0, 0);
            setByte(bufferPosition + 1, 0);
            setByte(bufferPosition + 2, 0);
            setByte(bufferPosition + 3, 0);
            setByte(bufferPosition + 4, 0);
            setByte(bufferPosition + 5, 0);
            setByte(bufferPosition + 6, 0);
        }
    }
}

void BelzebubChr::setItemAttribute(const ItemPosition itemPosition, const int attributePosition, const Attribute attribute, const int value1, const int value2) {
    const ItemMagic itemMagic = getItemMagic(itemPosition);
    if ((value1 < -125) || (value2 < -125) || (value1 > 32000) || (value2 > 32000)) {
        cout << "value too small/big <-125, 32000> in  "  << int(itemPosition) << "." << attributePosition << "  " << value1 << " " << value2 << endl;
        return;
    }
    if (attributePosition < 0 || attributePosition >= attributeCount.at(itemMagic)) {
        cout << "invalid position <0," << attributeCount.at(itemMagic) - 1 << "> in  "  << int(itemPosition) << "." << attributePosition << "  " << value1 << " " << value2 << endl;
        return;
    }
    const AttributeData &attributeData = attrMap.at(attribute);
    const AttributeMode attributeMode = attributeModeMap.at({itemMagic, attributePosition});
    if (attributeData.mode != attributeMode && attributeData.attribute != Attribute::NoAttribute) {
        cout << "invalid attribute (even/odd/unique/set) in  " << int(itemPosition) << "." << attributePosition << " " << value1 << " " << value2 << endl;
        return;
    }
    //cout << int(itemPosition) << " " << attributePosition << " " << attributeData.start << " " << value1 << " " << value2 << endl;
    setItemValue(itemPosition, attributePosition, attributeData.start, value1, value2);
}

Belzebub::AttributeValue BelzebubChr::getItemAttributeValue(const Belzebub::ItemPosition itemPosition, const int attributePosition)
{
    int bufferPosition = itemBufferStart.at(itemPosition);
    const ItemMagic itemMagic = getItemMagic(itemPosition);
    const AttributeMode attributeMode = attributeModeMap.at({itemMagic, attributePosition});
    bufferPosition += attributeStart.at(itemMagic);
    bufferPosition += attributeSizeMap.at(itemMagic) * attributePosition;
    AttributeValue attributeValue;
    if (itemMagic == ItemMagic::Rare || itemMagic == ItemMagic::Crafted || itemMagic == ItemMagic::Magic) {
        const AttributeRare &attribute = (AttributeRare&)buffer1[bufferPosition];
        attributeValue.attributeType = attribute.type;
        attributeValue.value1 = attribute.value1;
        attributeValue.value2 = attribute.value2;
        attributeValue.uvalue1 = attribute.uvalue1;
        attributeValue.uvalue2 = attribute.uvalue2;
    }
    else if (itemMagic == ItemMagic::Unique) {
        const AttributeUnique &attribute = (AttributeUnique&)buffer1[bufferPosition];
        attributeValue.attributeType = attribute.type;
        attributeValue.value1 = attribute.value1;
        attributeValue.value2 = attribute.value2;
        attributeValue.uvalue1 = attribute.uvalue1;
        attributeValue.uvalue2 = attribute.uvalue2;
    }
    else if (itemMagic == ItemMagic::Set) {
        const AttributeSet &attribute = (AttributeSet&)buffer1[bufferPosition];
        attributeValue.attributeType = attribute.type;
        attributeValue.value1 = attribute.value1;
        attributeValue.value2 = attribute.value2;
        attributeValue.uvalue1 = attribute.uvalue1;
        attributeValue.uvalue2 = attribute.uvalue2;
    }
    if (attributeValue.attributeType == 65535 || (attributeValue.attributeType == 0 && (itemMagic == ItemMagic::Unique || itemMagic == ItemMagic::Set))) {
        attributeValue.isNotUsed = true;
    }
    else {
        for (const auto &it : attrMap) {
            const AttributeData &attributeData = it.second;
            if (attributeMode == attributeData.mode && attributeValue.attributeType >= attributeData.start && attributeValue.attributeType <= attributeData.end) {
                attributeValue.attributeData = attributeData;
            }
        }
        if (attributeValue.attributeData.name.empty()) {
            attributeValue.isUnknown = true;
        }
    }
    return attributeValue;
}

bool BelzebubChr::isBody() {
    return getItemMagic(ItemPosition::Body) != ItemMagic::NoItem;
}
bool BelzebubChr::isHead() {
    return getItemMagic(ItemPosition::Head) != ItemMagic::NoItem;
}
bool BelzebubChr::isRing1() {
    return getItemMagic(ItemPosition::Ring1) != ItemMagic::NoItem;
}
bool BelzebubChr::isRing2() {
    return getItemMagic(ItemPosition::Ring2) != ItemMagic::NoItem;
}
bool BelzebubChr::isAmulet() {
    return getItemMagic(ItemPosition::Amulet) != ItemMagic::NoItem;
}
bool BelzebubChr::isHand1() {
    return getItemMagic(ItemPosition::Hand1) != ItemMagic::NoItem;
}
bool BelzebubChr::isHand2() {
    return getItemMagic(ItemPosition::Hand2) != ItemMagic::NoItem;
}
bool BelzebubChr::isBelt() {
    return getItemMagic(ItemPosition::Belt) != ItemMagic::NoItem;
}

bool BelzebubChr::isDurability(const Belzebub::ItemPosition itemPosition)
{
    int bufferPosition = itemBufferStart.at(itemPosition);
    int durability = getWord(bufferPosition + 23);
    return durability != 0;
}

int BelzebubChr::getItemDurability(const Belzebub::ItemPosition itemPosition)
{
    int bufferPosition = itemBufferStart.at(itemPosition);
    return getWord(bufferPosition + 23);
}

Belzebub::SpellType BelzebubChr::getStaffSpell(const Belzebub::ItemPosition itemPosition)
{
    int bufferPosition = itemBufferStart.at(itemPosition);
    return (Belzebub::SpellType)getByte(bufferPosition + 31);
}

int BelzebubChr::getStaffCharges(const Belzebub::ItemPosition itemPosition)
{
    int bufferPosition = itemBufferStart.at(itemPosition);
    return getWord(bufferPosition + 27);
}

int BelzebubChr::getSpellLevel(const Belzebub::SpellType spellType)
{
    return (unsigned char)buffer1[572 + 4 * int(spellType)];
}

std::vector<Belzebub::AttributeData> BelzebubChr::getAttributes(const Belzebub::AttributeMode attributeMode)
{
    std::vector<Belzebub::AttributeData> attributes;
    for (const auto &it : attrMap) {
        const AttributeData &attributeData = it.second;
        if (attributeMode == attributeData.mode || attributeData.attribute == Attribute::NoAttribute) {
            attributes.push_back(attributeData);
        }
    }
    return attributes;
}
