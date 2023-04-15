#ifndef BELZEBUBMAGIC_H
#define BELZEBUBMAGIC_H

#include "itemtype.h"
#include "attribute.h"

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

    enum class ItemPosition {Body, Head, Ring1, Ring2, Amulet, Hand1, Hand2, Belt};

    const std::map<std::pair<ItemMagic, int>, AttributeMode> attributeModeMap = {
        {{ItemMagic::Magic, 0}, AttributeMode::Even},
        {{ItemMagic::Magic, 1}, AttributeMode::Odd},

        {{ItemMagic::Rare, 0}, AttributeMode::Even},
        {{ItemMagic::Rare, 1}, AttributeMode::Odd},
        {{ItemMagic::Rare, 2}, AttributeMode::Even},
        {{ItemMagic::Rare, 3}, AttributeMode::Odd},
        {{ItemMagic::Rare, 4}, AttributeMode::Even},
        {{ItemMagic::Rare, 5}, AttributeMode::Odd},
        {{ItemMagic::Rare, 6}, AttributeMode::Even},
        {{ItemMagic::Rare, 7}, AttributeMode::Odd},

        {{ItemMagic::Crafted, 0}, AttributeMode::Even},
        {{ItemMagic::Crafted, 1}, AttributeMode::Even},
        {{ItemMagic::Crafted, 2}, AttributeMode::Even},
        {{ItemMagic::Crafted, 3}, AttributeMode::Even},
        {{ItemMagic::Crafted, 4}, AttributeMode::Odd},
        {{ItemMagic::Crafted, 5}, AttributeMode::Odd},
        {{ItemMagic::Crafted, 6}, AttributeMode::Odd},
        {{ItemMagic::Crafted, 7}, AttributeMode::Odd},

        {{ItemMagic::Unique, 0}, AttributeMode::Unique},
        {{ItemMagic::Unique, 1}, AttributeMode::Unique},
        {{ItemMagic::Unique, 2}, AttributeMode::Unique},
        {{ItemMagic::Unique, 3}, AttributeMode::Unique},
        {{ItemMagic::Unique, 4}, AttributeMode::Unique},
        {{ItemMagic::Unique, 5}, AttributeMode::Unique},
        {{ItemMagic::Unique, 6}, AttributeMode::Unique},
        {{ItemMagic::Unique, 7}, AttributeMode::Unique},
        {{ItemMagic::Unique, 8}, AttributeMode::Unique},

        {{ItemMagic::Set, 0}, AttributeMode::Set},
        {{ItemMagic::Set, 1}, AttributeMode::Set},
        {{ItemMagic::Set, 2}, AttributeMode::Set},
        {{ItemMagic::Set, 3}, AttributeMode::Set},
        {{ItemMagic::Set, 4}, AttributeMode::Set},
        {{ItemMagic::Set, 5}, AttributeMode::Set},
        {{ItemMagic::Set, 6}, AttributeMode::Set},
        {{ItemMagic::Set, 7}, AttributeMode::Set},
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

    const std::map<ItemMagic, int> attributeStart = {
        {ItemMagic::NoItem, -1},
        {ItemMagic::Quest, -1},
        {ItemMagic::Common, -1},
        {ItemMagic::Magic, 35},
        {ItemMagic::Rare, 35},
        {ItemMagic::Unique, 37},
        {ItemMagic::Set, 39},
        {ItemMagic::Crafted, 35},
    };

    const std::map<ItemMagic, int> attributeCount = {
        {ItemMagic::NoItem, -1},
        {ItemMagic::Quest, -1},
        {ItemMagic::Common, -1},
        {ItemMagic::Magic, 2},
        {ItemMagic::Rare, 8},
        {ItemMagic::Unique, 9},
        {ItemMagic::Set, 8},
        {ItemMagic::Crafted, 8}
    };

    const std::map<ItemMagic, int> attributeSizeMap = {
        {ItemMagic::NoItem, -1},
        {ItemMagic::Quest, -1},
        {ItemMagic::Common, -1},
        {ItemMagic::Magic, 6},
        {ItemMagic::Rare, 6},
        {ItemMagic::Unique, 5},
        {ItemMagic::Set, 6},
        {ItemMagic::Crafted, 6}
    };

    struct AttributeValue {
        int attributeType = 65535;
        int value1 = 0;
        int value2 = 0;
        int uvalue1 = 0;
        int uvalue2 = 0;
        AttributeData attributeData;
        bool isNotUsed = false;
        bool isUnknown = false;
    };
}

#endif // BELZEBUBMAGIC_H
