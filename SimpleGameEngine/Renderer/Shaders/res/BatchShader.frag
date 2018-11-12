#version 330

in vec2 fragUV;

out vec4 color;

uniform sampler2D mySampler;

void main()
{
    color = texture(mySampler, fragUV);
}
