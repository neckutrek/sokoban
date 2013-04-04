#version 150

in  vec3 inPosition;
in  vec3 inNormal;
in vec2 inTexCoord;
out vec2 texCoord;

// NY
uniform mat4 projMatrix;
uniform mat4 mdlMatrix;
uniform mat4 camMatrix;
uniform vec3 lightSourcesDirPosArr[4];

out vec3 normal;
out vec4 viewVector;
out vec4 lightSourcePos[4];

void main(void)
{
	normal = mat3(camMatrix) * mat3(mdlMatrix) * inNormal;
	viewVector = camMatrix*mdlMatrix*vec4(inPosition,1.0);
	for (int i=0; i<4; i++) {
		lightSourcePos[i] = camMatrix*vec4(lightSourcesDirPosArr[i], 1.0);
	}
	texCoord = inTexCoord;
	gl_Position = projMatrix * camMatrix * mdlMatrix * vec4(inPosition, 1.0);
}
