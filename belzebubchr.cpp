#include "belzebubchr.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include "zlib.h"
using namespace std;
using namespace Belzebub;

void BelzebubChr::loadBuffer(const string &fileName, const int num)
{
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
    }
    buffer.resize(destLen);
}

void BelzebubChr::updateChecksum(const size_t position, const unsigned char value)
{
    unsigned int checksum = (unsigned char)buffer1[12] + ((unsigned char)buffer1[13]) * 256;
    checksum += int((unsigned char)buffer1[position] - value);
    buffer1[12] = (unsigned char)(checksum % 256);
    buffer1[13] = (unsigned char)(checksum / 256);
}

void BelzebubChr::saveBuffer(const string &fileName) {
    uLongf destLen = 1000000;
    vector<char> fileBuffer(destLen);
    compress((Bytef*)fileBuffer.data(), &destLen, (const Bytef*)buffer1.data(), (uLong)buffer1.size());
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
        if (buffer1[i] != buffer2[i] || (0 && i < c)) {
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
        const ItemType itemType = getItemType(itemPosition);
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
        int bufferPosition = itemBufferStart.at(itemPosition);
        bufferPosition += attributeStart.at(itemType);
        for (int i = 0; i < attributeCount.at(itemType); ++i) {
            const AttributeMode attributeMode = getAttributeMode(itemType, i);
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
            int attributeType = 65535;
            int value1 = 0;
            int value2 = 0;
            int uvalue1 = 0;
            int uvalue2 = 0;
            int attributeSize = 0;
            if (itemType == ItemType::Rare || itemType == ItemType::Crafted || itemType == ItemType::Magic) {
                const AttributeRare &attributeValue = (AttributeRare&)buffer1[bufferPosition];
                attributeType = attributeValue.type;
                value1 = attributeValue.value1;
                value2 = attributeValue.value2;
                uvalue1 = attributeValue.uvalue1;
                uvalue2 = attributeValue.uvalue2;
                attributeSize = sizeof(AttributeRare);
            }
            else if (itemType == ItemType::Unique) {
                const AttributeUnique &attributeValue = (AttributeUnique&)buffer1[bufferPosition];
                attributeType = attributeValue.type;
                value1 = attributeValue.value1;
                value2 = attributeValue.value2;
                uvalue1 = attributeValue.uvalue1;
                uvalue2 = attributeValue.uvalue2;
                attributeSize = sizeof(AttributeUnique);
            }
            else if (itemType == ItemType::Set) {
                const AttributeSet &attributeValue = (AttributeSet&)buffer1[bufferPosition];
                attributeType = attributeValue.type;
                value1 = attributeValue.value1;
                value2 = attributeValue.value2;
                uvalue1 = attributeValue.uvalue1;
                uvalue2 = attributeValue.uvalue2;
                attributeSize = sizeof(AttributeSet);
            }
            string typeName = "attribute not found";
            if (attributeType == 65535 || (attributeType == 0 && (itemType == ItemType::Unique || itemType == ItemType::Set))) {
                typeName = "attribute not used";
            }
            else {
                for (const auto &it : attrMap) {
                    const AttributeData &attributeData = it.second;
                    if (attributeMode == attributeData.mode && attributeType >= attributeData.start && attributeType <= attributeData.end) {
                        typeName = attributeData.name;
                    }
                }
            }
            cout << std::setw(5) << std::right << attributeType << " " << std::setw(5) << std::right << value1 << " " << std::setw(5) << std::right << value2 << "  " << std::setw(5) << std::right << uvalue1 << "  " << std::setw(5) << std::right << uvalue2 << "  " << typeName << endl;
            bufferPosition += attributeSize;
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

void BelzebubChr::setWord(const int position, const int value) {
    setByte(position, value % 256);
    setByte(position + 1, value / 256);
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

ItemType BelzebubChr::getItemType(const ItemPosition itemPosition) {
    ItemType itemType = ItemType::NoItem;
    int bufferPosition = itemBufferStart.at(itemPosition);
    const int t = buffer1[bufferPosition];
    if (t == 7 || t == 8 || t == 9 || t == 10 || t == 11 || t == 12 || t == 13) {
        itemType = ItemType(t);
    }
    return itemType;
}

void BelzebubChr::setItemType(const ItemPosition itemPosition, const ItemType itemType) {
    int bufferPosition = itemBufferStart.at(itemPosition);
    setByte(bufferPosition, int(itemType));
}

void BelzebubChr::setItemType2(const ItemPosition itemPosition, int value) {
    // 8780  94 Composite Staff, 192 Gothic Staff, 193 Rune Staff, 194 Archon Staff
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
    const ItemType itemType = getItemType(itemPosition);
    int bufferPosition = itemBufferStart.at(itemPosition);
    bufferPosition += attributeStart.at(itemType);
    if (itemType == ItemType::Rare || itemType == ItemType::Crafted || itemType == ItemType::Magic) {
        bufferPosition += attributePosition * 6;
        if (value1 != 0) {
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
            setByte(bufferPosition + 2, 255);
            setByte(bufferPosition + 3, 255);
            setByte(bufferPosition + 4, 0);
            setByte(bufferPosition + 5, 0);
        }
    }
    else if (itemType == ItemType::Unique) {
        bufferPosition += attributePosition * 5;
        if (value1 != 0) {
            setByte(bufferPosition, attributeType);
            if (value1 < 0) {
                setByte(bufferPosition + 1, value1);
                setByte(bufferPosition + 2, -1);
            }
            else {
                setWord(bufferPosition + 1, value1);
            }
            setWord(bufferPosition + 3, value2);
        }
        else {
            setByte(bufferPosition + 0, 255);
            setByte(bufferPosition + 1, 255);
            setByte(bufferPosition + 2, 255);
            setByte(bufferPosition + 3, 255);
            setByte(bufferPosition + 4, 0);
            setByte(bufferPosition + 5, 0);
        }
    }
    else if (itemType == ItemType::Set) {
        bufferPosition += attributePosition * 6;
        if (value1 != 0) {
            setByte(bufferPosition, attributeType);
            if (value1 < 0) {
                setByte(bufferPosition + 1, value1);
                setByte(bufferPosition + 2, -1);
            }
            else {
                setWord(bufferPosition + 1, value1);
            }
            setWord(bufferPosition + 3, value2);
            setByte(bufferPosition + 4, 0);

        }
        else {
            setByte(bufferPosition + 0, 255);
            setByte(bufferPosition + 1, 255);
            setByte(bufferPosition + 2, 255);
            setByte(bufferPosition + 3, 255);
            setByte(bufferPosition + 4, 0);
            setByte(bufferPosition + 5, 0);
            setByte(bufferPosition + 6, 0);
        }
    }
}

void BelzebubChr::setItemAttribute(const ItemPosition itemPosition, const int attributePosition, const Attribute attribute, const int value1, const int value2) {
    const ItemType itemType = getItemType(itemPosition);
    if ((value1 < -125) || (value2 < -125) || (value1 > 32000) || (value2 > 32000)) {
        cout << "value too small/big <-125, 32000> in  "  << int(itemPosition) << "." << attributePosition << "  " << value1 << " " << value2 << endl;
        return;
    }
    if (attributePosition < 0 || attributePosition >= attributeCount.at(itemType)) {
        cout << "invalid position <0," << attributeCount.at(itemType) - 1 << "> in  "  << int(itemPosition) << "." << attributePosition << "  " << value1 << " " << value2 << endl;
        return;
    }
    const AttributeData &attributeData = attrMap.at(attribute);
    const AttributeMode attributeMode = getAttributeMode(itemType, attributePosition);
    if (attributeData.mode != attributeMode) {
        cout << "invalid attribute (even/odd/unique/set) in  " << int(itemPosition) << "." << attributePosition << " " << value1 << " " << value2 << endl;
        return;
    }
    setItemValue(itemPosition, attributePosition, attributeData.start, value1, value2);
}
