

#version 330 core
out vec4 FragColor;
uniform vec3 color;
uniform vec3 lightColor;
uniform vec3 lightPos;  
uniform vec3 viewPos;
uniform int reflectivness;
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

   float specularStrength = 1.0;
   vec3 viewDir = normalize(viewPos - FragPos);
   vec3 reflectDir = reflect(-lightDir, norm);  
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), reflectivness);
   vec3 specular = specularStrength * spec * lightColor;  


   vec3 result = (ambient + diffuse + specular) * color;


   FragColor = vec4(result,1.0f)*texture(ourTexture, TexCoord);
}

