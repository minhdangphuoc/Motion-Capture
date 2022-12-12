#version 410 core
#define NR_POINT_LIGHTS 256
#define NR_SPOT_LIGHTS 256

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
}; 

struct DirLight {
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 viewPos;

// LIGHTING
uniform bool hasDirLight;
uniform int NumberOfPointLight;
uniform int NumberOfSpotLight;

uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLights[NR_SPOT_LIGHTS];

uniform bool hasTexture;
uniform Material inMaterial;
uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;
uniform sampler2D texture_normal;
uniform float material_shininess;

vec3 CalcDirLight(DirLight light, vec3 ambient, vec3 diffuse, vec3 specular, float shininess, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 ambient, vec3 diffuse, vec3 specular, float shininess, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 ambient, vec3 diffuse, vec3 specular, float shininess, vec3 normal, vec3 fragPos, vec3 viewDir);

float near = 0.1; 
float far  = 100.0; 
vec3 norm;
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{
    Material material;
    if (hasTexture == true)
    {
        material.ambient = vec3(texture(texture_diffuse, TexCoords));
        material.diffuse = vec3(texture(texture_diffuse, TexCoords));
        material.specular = vec3(texture(texture_specular, TexCoords));
        material.shininess = material_shininess;
        norm = vec3(texture(texture_normal, TexCoords)).rgb;
        norm = normalize(norm);
    } else {
        material = inMaterial;
        norm = normalize(Normal);
    }

    vec4 textureColour = texture(texture_diffuse, TexCoords);
    if(textureColour.a < 0.5) {
        discard;
    }

    // Properties
    vec3 result = vec3(0.0);//needs an initial value or else the model won't render correctly
    vec3 viewDir = normalize(viewPos - FragPos);
    
    
    // Directional lighting
    if (hasDirLight==true)
        result = CalcDirLight(dirLight, material.ambient, material.diffuse, material.specular, material.shininess, norm, viewDir);

    //Point lights
    if (NumberOfPointLight>0)
    {
        for(int i = 0; i < NumberOfPointLight; i++)
        result += CalcPointLight(pointLights[i], material.ambient, material.diffuse, material.specular, material.shininess, norm, FragPos, viewDir);
    }
    
    // Spot lights
    if (NumberOfSpotLight>0)
    {
        for(int i = 0; i < NumberOfSpotLight; i++)
        result += CalcSpotLight(spotLights[i], material.ambient, material.diffuse, material.specular, material.shininess, norm, FragPos, viewDir);
    } 

    float depth = LinearizeDepth(gl_FragCoord.z) / far;
    // FragColor = vec4(vec3(depth), 1.0);

    FragColor = vec4(result, 1.0);
    // FragColor = texture(texture_diffuse, TexCoords);
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 ambient, vec3 diffuse, vec3 specular, float shininess, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    // Combine results
    ambient = light.ambient * ambient;
    diffuse = light.diffuse * diff * diffuse;
    specular = light.specular * spec * specular;

    return (ambient + diffuse + specular);
}

// Calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 ambient, vec3 diffuse, vec3 specular, float shininess, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    
    // Combine results
    ambient = light.ambient * ambient;
    diffuse = light.diffuse * diff * diffuse;
    specular = light.specular * spec * specular;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 ambient, vec3 diffuse, vec3 specular, float shininess, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    ambient = light.ambient * ambient;
    diffuse = light.diffuse * diff * diffuse;
    specular = light.specular * spec * specular;
    
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}