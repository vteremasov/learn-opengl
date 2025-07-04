#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform float hOffset;
out vec3 ourColor;
void main()
{
   vec2 xy = aPos.xy * -1.0f;
   xy.x += hOffset;
   gl_Position = vec4(xy, aPos.z, 1.0);
   ourColor = vec3(xy, aPos.z);
}

