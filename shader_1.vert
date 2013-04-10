#version 150

in vec3 vertex_coordinate;
//in  vec3 vertex_normal_vector;
//in vec2 inTexCoord;
//out vec2 texCoord;

uniform mat4 model_transformation;
uniform mat4 camera_transformation;
uniform mat4 projection_transformation;
//uniform vec3 lightSourcesDirPosArr[4];

//out vec3 normal;
//out vec4 viewVector;
//out vec4 lightSourcePos[4];

void main(void)
{
	//normal = mat3(camMatrix) * mat3(mdlMatrix) * inNormal;
	//viewVector = camMatrix*mdlMatrix*vec4(inPosition,1.0);
	//for (int i=0; i<4; i++) {
	//	lightSourcePos[i] = camMatrix*vec4(lightSourcesDirPosArr[i], 1.0);
	//}
	//texCoord = inTexCoord;
    
    gl_Position =
        projection_transformation *
        camera_transformation *
        model_transformation *
        vec4(vertex_coordinate, 1.0);
}
