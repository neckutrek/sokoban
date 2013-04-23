#version 150

in vec3 in_vertex_coordinate;
//in vec3 in_vertex_normal_vector;
//in vec2 in_texture_coordinate;
//out vec2 texCoord;

uniform mat4 model_transformation;
uniform mat4 camera_transformation;
uniform mat4 projection_transformation;
uniform vec3 light_sources_pos_array[8];
uniform vec3 light_sources_color_array[8];
uniform float light_sources_lux_array[8];
uniform int light_counter;

out vec3 transformed_normal_vector;
out vec4 view_vector;

out vec4 transformed_light_source_pos_array[8];

void main(void)
{
    view_vector =
        camera_transformation *
        model_transformation *
        vec4(in_vertex_coordinate, 1.0);
    
    transformed_normal_vector =
        mat3(camera_transformation) *
        mat3(model_transformation) *
        in_vertex_normal_vector;
    
    gl_Position =
        projection_transformation *
        camera_transformation *
        model_transformation *
        vec4(in_vertex_coordinate, 1.0);
    
    for (int i = 0; i < light_counter; ++i) {
		transformed_light_source_pos_array[i] =
            camera_transformation *
            vec4(light_sources_pos_array[i], 1.0);
	}
    
    //texCoord = inTexCoord;
}
