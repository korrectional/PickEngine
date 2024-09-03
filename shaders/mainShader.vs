#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 rotation;
uniform mat4 scale;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
void main()
{
   gl_Position = projection*view*model*scale*vec4(aPos,1.0f);
   FragPos = vec3(model * vec4(aPos, 1.0));
   Normal = aNormal;
   TexCoord = aTexCoord;
}
