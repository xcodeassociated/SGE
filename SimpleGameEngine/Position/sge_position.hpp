#ifndef sge_position_h
#define sge_position_h

namespace SGE
{
    struct Position
    {
        float x = 0;
        float y = 0;

        Position(float _x, float _y) 
            : x(_x), y(_y) {};
        Position() = default;
    };
}
#endif
