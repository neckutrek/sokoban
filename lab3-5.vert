#version 150

in vec3 inPosition;
in vec3 inNormal;
in vec2 inTexCoord;

uniform mat4 mtwMatrix;
uniform mat4 wtcMatrix;
uniform mat4 projMatrix;

uniform vec3 lightSourcesDirPosArr[4];

out vec2 texCoord;
out vec3 normal;
out vec4 viewVector;
out vec4 lightSourcePos[4];

void main(void)
{
	normal = mat3(wtcMatrix)*mat3(mtwMatrix) * inNormal;
	viewVector = wtcMatrix*mtwMatrix*vec4(inPosition,1.0);
	for (int i=0; i<4; i++) {
		lightSourcePos[i] = wtcMatrix*vec4(lightSourcesDirPosArr[i], 1.0);
	}
	texCoord = inTexCoord;

	gl_Position = projMatrix * wtcMatrix * mtwMatrix * vec4(inPosition, 1.0);
}
