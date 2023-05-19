#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform int posX;
uniform int posY;

void main()
{
   gl_Position = vec4(posX, posY, aPos.z, 1.0f);
   ourColor = aColor;
   TexCoord = vec2(aTexCoord.x, aTexCoord.y);
};