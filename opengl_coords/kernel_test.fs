#version 330 core

in vec3 fragPos;
in vec2 texCoords;
in vec3 normals;

out vec4 FragColor;

struct Light
{
    vec3 pos;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material 
{
    sampler2D diffuse;
    sampler2D specular;
    int shininess;
};

uniform Light light;
uniform Material material;

uniform vec3 camPos;

const float offset = 1.0/300.0;

void main()
{
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset),
        vec2( 0.0f,    offset),
        vec2( offset,  offset),
        vec2(-offset,  0.0f),
        vec2( 0.0f,    0.0f),
        vec2( offset,  0.0f),
        vec2(-offset, -offset),
        vec2( 0.0f,   -offset),
        vec2( offset, -offset)
    );

    float kernel[9] = float[](
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
    );

    float kernel2[9] = float[](
        1,  1,  1,
        1, -8,  1,
        1,  1,  1
    );

    vec3 sampleTex[9];

    for (int i=0;i<9; i++)
    {
        sampleTex[i] = vec3(texture(material.diffuse, texCoords.st + offsets[i]));
    }

    vec3 col = vec3(0.0);
    for (int i=0; i<9; i++)
        col += sampleTex[i] * kernel2[i];

    FragColor = vec4(col, 1.0);

    // ambient lighting
    //vec3 ambient = light.ambient * texture(material.diffuse, texCoords).rgb;

    // diffuse lighting
    //vec3 lightDir = normalize(light.pos-fragPos);
    //vec3 norm = normalize(normals);

    //float diff = max(dot(lightDir, norm), 0.0f);
    //vec3 diffuse = light.diffuse * diff * texture(material.diffuse, texCoords).rgb;

    // specular lighting
    //vec3 viewDir = normalize(camPos-fragPos); 
    //vec3 reflectDir = reflect(-lightDir, norm);

    //float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    //vec3 specular = light.specular * spec * texture(material.specular, texCoords).rgb;

    //FragColor = vec4(ambient+diffuse+specular, 1.0f);
    //FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
