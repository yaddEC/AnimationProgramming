/////////////////////
// INPUT VARIABLES //
/////////////////////
in lowp vec3 inputPosition;
in lowp vec3 normal;
in lowp vec4 boneIndices;
in lowp vec4 boneWeights;

//////////////////////
// OUTPUT VARIABLES //
//////////////////////
smooth out vec2 texCoord;
smooth out vec3 outNormal;

uniform SceneMatrices
{
	uniform mat4 projectionMatrix;
} sm;

uniform mat4 modelViewMatrix;

uniform SkinningMatrices
{
	uniform mat4 mat[64];
} skin;

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
void main(void)
{
	vec4 pos = vec4(inputPosition, 1.0f);
	vec4 skinnedPosition = vec4(0, 0, 0, 1);
	vec3 norm = normal;
	vec3 skinnedNormal = vec3(0, 0, 0);

	for (int i = 0; i < 4; i++) 
	{
		skinnedPosition += boneWeights[i] * (skin.mat[int(boneIndices[i])] * pos);
		skinnedNormal += boneWeights[i] * (mat3(skin.mat[int(boneIndices[0])]) * norm);
    }

	gl_Position = sm.projectionMatrix * (modelViewMatrix * vec4(skinnedPosition.xyz, 1.0));
	outNormal = mat3(modelViewMatrix) * skinnedNormal;

	outNormal = normalize(outNormal);
}