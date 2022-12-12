#version 410 core
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoords;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;
layout(location = 5) in uvec4 inBoneIds; 
layout(location = 6) in vec4 inWeights;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 finalBonesMatrices[MAX_BONES];
uniform bool hasAnimated;
void main()
{
    TexCoords = inTexCoords;
    
    if (hasAnimated) {
        mat4 BoneTransform = mat4(0.0f);
        for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++)
        {
            BoneTransform += finalBonesMatrices[inBoneIds[i]] * inWeights[i];
        }
        
        FragPos = (model * BoneTransform * vec4(inPos,1.0f)).xyz;
        
        vec4 NormalL = BoneTransform * vec4(inNormal, 0.0f);
        Normal = (model * NormalL).xyz;   

        gl_Position = projection * view *  BoneTransform * vec4(inPos, 1.0);
    }
    else {
        FragPos = vec3(model * vec4(inPos, 1.0));
        Normal = mat3(transpose(inverse(model))) * inNormal;  

        gl_Position = projection * view * vec4(FragPos, 1.0);
    }
}