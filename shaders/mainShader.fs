

#version 330 core
out vec4 FragColor;
uniform vec3 color;
uniform vec3 lightColor;
uniform vec3 lightPos;  
in vec2 TexCoord;
in vec3 Normal;  
in vec3 FragPos;  
uniform sampler2D ourTexture;
void main()
{
   float ambientStrength = 0.3;
   vec3 ambient = ambientStrength * lightColor;



   vec3 norm = normalize(Normal);
   vec3 lightDir = normalize(lightPos - FragPos);  
   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = diff * lightColor;

   vec3 result = (ambient + diffuse) * color;


   FragColor = vec4(result,1.0f)*texture(ourTexture, TexCoord);
}

