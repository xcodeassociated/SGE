#version 330

layout(location = 0) in vec2 spritePos;
layout(location = 1) in vec2 spriteScale;
layout(location = 2) in float spriteRot;
layout(location = 3) in float spriteLayer;

out vec2 fragUV;

const vec2 UV[4] = vec2[4](vec2(0.0, 0.0), vec2(0.0, 1.0), vec2(1.0, 1.0), vec2(1.0, 0.0));
const vec2 Ver[4] = vec2[4](vec2(-32.0, 32.0), vec2(-32.0, -32.0), vec2(32.0, -32.0), vec2(32.0, 32.0));

layout(std140) uniform uMatrix
{
    mat4 PV;
} Matrix;

vec2 rotate(vec2 vec, float radian)
{
    return vec2(cos(radian) * vec.x - sin(radian) * vec.y,
                sin(radian) * vec.x + cos(radian) * vec.y);
}

void main()
{
    int Corner = int(mod(gl_VertexID, 4));

    gl_Position.xy = (Matrix.PV * vec4(rotate(Ver[Corner]*spriteScale, spriteRot) + spritePos, 0.0, 1.0)).xy;
    gl_Position.z = spriteLayer;
    gl_Position.w = 1.0;
    
    fragUV = UV[Corner] * spriteScale;
}
