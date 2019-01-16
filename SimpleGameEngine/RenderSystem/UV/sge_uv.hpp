#ifndef sge_uv_h
#define sge_uv_h

namespace SGE
{
    struct UV
    {
        float u = 0;
        float v = 0;

        UV(float _u, float _v) : u(_u), v(_v) {};
        UV() = default;
        virtual ~UV() = default;
    };
}

#endif
