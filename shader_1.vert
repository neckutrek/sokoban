#version 150

in vec3 in_vertex_coordinate;
//in vec3 in_vertex_normal_vector;
//in vec2 in_texture_coordinate;
//out vec2 texCoord;

uniform mat4 model_transformation;
uniform mat4 camera_transformation;
uniform mat4 projection_transformation;
//uniform vec3 lightSourcesDirPosArr[4];

//out vec3 tranformed_normal_vector;
//out vec4 view_vector;
//out vec4 lightSourcePos[4];

void main(void)
{
	//normal = mat3(camMatrix) * mat3(mdlMatrix) * inNormal;
	//viewVector = camMatrix*mdlMatrix*vec4(inPosition,1.0);
	//for (int i=0; i<4; i++) {
	//	lightSourcePos[i] = camMatrix*vec4(lightSourcesDirPosArr[i], 1.0);
	//}
	//texCoord = inTexCoord;
    
//    view_vector =
//        camera_transformation *
//        model_transformation *
//        vec4(in_vertex_coordinate, 1.0);
//    
//    tranformed_normal_vector =
//        mat3(camera_transformation) *
//        mat3(model_transformation) *
//        in_vertex_normal_vector;
	
    
    gl_Position =
        projection_transformation *
        camera_transformation *
        model_transformation *
        vec4(in_vertex_coordinate, 1.0);
}
