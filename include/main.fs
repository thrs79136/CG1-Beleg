#version 450 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

const uint DIRLIGHT=4;

uniform int isLightSource;
uniform int useSpecularLight;

// Richtungslicht
uniform vec3 lightDir;
uniform vec3 lightPos[4];
uniform vec3 lightColor[5];
uniform vec3 viewPos;
uniform int displayLight[4];

out vec4 FragColor;

uniform sampler2D texSampler;

vec3 calcLight(int lightID){
    // ambientes Licht
    float ambientStrength = 0.1;
    
    vec3 ambient = ambientStrength*lightColor[lightID];

    // diffuses Licht
    vec3 norm = normalize(Normal);
    vec3 lightDirection;
    if (lightID==DIRLIGHT)
        lightDirection = normalize(lightDir);
    else
        lightDirection = normalize(lightPos[lightID]-FragPos);
    // kleinerer Winkel zwischen Normal- und Lichtvektor => diff wird groesser
    // dot(norm, lightDirection) < 0 => Licht faellt nicht auf Flaeche
    float diff = max( dot(norm, lightDirection), 0.0);
    vec3 diffuse = lightColor[lightID] * diff;

    // Glanzlicht (specular light)
    vec3 specular;
    if (useSpecularLight==0){
        specular = vec3(0.0);
    }
    else{
        float specularStrength = 2.5;
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDirection, norm);
        float spec = pow( max( dot(viewDir, reflectDir), 0.0 ), 8);
        specular = specularStrength * spec * lightColor[lightID];
    }
    return (ambient+diffuse+specular)*vec3(texture(texSampler, TexCoord));
}

void main(){
    vec3 result = vec3(0.0);
    if (isLightSource==0){ 
    for (int i=0; i<4;i++)
        if (displayLight[i]!=0) result += 0.6*calcLight(i);
    result +=calcLight(4);
    } else{
        result = lightColor[isLightSource-1] + vec3(0.2);
    }
    FragColor = vec4(result, 1.0);
}