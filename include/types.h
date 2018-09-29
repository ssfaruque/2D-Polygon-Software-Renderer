#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

using uint = unsigned int;

using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8  = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;


struct Color
{
    union
    {
        u32 color;

        struct
        {
            u8 r;
            u8 g;
            u8 b;
            u8 a;
        };
    };

    Color(u32 pColor) {color = pColor;}
    Color(u8 pr, u8 pg, u8 pb, u8 pa) {r = pr; g = pg; b = pb; a = pa;}
};


#endif  // TYPES_H