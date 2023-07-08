#include "rdb.h"
#include<iostream>

using namespace std;

bool integerAttribute::operator==(const Attr &right) { 
    return columnData == static_cast<const integerAttribute &>(right).columnData;
}
bool integerAttribute::operator!=(const Attr &right) { 
    return columnData != static_cast<const integerAttribute &>(right).columnData;
}
bool integerAttribute::operator>=(const Attr &right) { 
    return columnData >= static_cast<const integerAttribute &>(right).columnData;
}
bool integerAttribute::operator<=(const Attr &right) { 
    return columnData <= static_cast<const integerAttribute &>(right).columnData;
}
bool integerAttribute::operator>(const Attr &right) { 
    return columnData > static_cast<const integerAttribute &>(right).columnData;
}
bool integerAttribute::operator<(const Attr &right) { 
    return columnData < static_cast<const integerAttribute &>(right).columnData;
}

bool floatAttribute::operator==(const Attr &right) { 
    return columnData == static_cast<const floatAttribute &>(right).columnData;
}
bool floatAttribute::operator!=(const Attr &right) { 
    return columnData != static_cast<const floatAttribute &>(right).columnData;
}
bool floatAttribute::operator>=(const Attr &right) { 
    return columnData >= static_cast<const floatAttribute &>(right).columnData;
}
bool floatAttribute::operator<=(const Attr &right) { 
    return columnData <= static_cast<const floatAttribute &>(right).columnData;
}
bool floatAttribute::operator>(const Attr &right) { 
    return columnData > static_cast<const floatAttribute &>(right).columnData;
}
bool floatAttribute::operator<(const Attr &right) { 
    return columnData < static_cast<const floatAttribute &>(right).columnData;
}

bool stringAttribute::operator==(const Attr &right) { 
    return columnData == static_cast<const stringAttribute &>(right).columnData;
} 
bool stringAttribute::operator!=(const Attr &right) { 
    return columnData != static_cast<const stringAttribute &>(right).columnData;
}
bool stringAttribute::operator>=(const Attr &right) { 
    return columnData >= static_cast<const stringAttribute &>(right).columnData;
}
bool stringAttribute::operator<=(const Attr &right) { 
    return columnData <= static_cast<const stringAttribute &>(right).columnData;
}
bool stringAttribute::operator>(const Attr &right) { 
    return columnData >  static_cast<const stringAttribute &>(right).columnData;
}
bool stringAttribute::operator<(const Attr &right) { 
    return columnData < static_cast<const stringAttribute &>(right).columnData;
}