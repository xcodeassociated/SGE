#version 330 core

layout(location = 0) in vec2 spritePos;
layout(location = 1) in vec2 spriteScale;
layout(location = 2) in float spriteRot;
layout(location = 3) in float spriteLayer;
layout(location = 4) in vec2 verPos1;
layout(location = 5) in vec2 verPos2;
layout(location = 6) in vec2 verPos3;
layout(location = 7) in vec2 verPos4;

out vec2 fragUV;

const float inv = 1.0/64.0;

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
	vec2 verPos[4] = vec2[](verPos1, verPos2, verPos3, verPos4);
    int Corner = int(mod(gl_VertexID, 4));
    gl_Position.xy = (Matrix.PV * vec4(rotate(verPos[Corner] * spriteScale, spriteRot) + spritePos, 0.0, 1.0)).xy;
    gl_Position.z = spriteLayer;
    gl_Position.w = 1.0;
    fragUV = rotate(inv * verPos[Corner] * spriteScale, spriteRot) + (inv * spritePos);
}
