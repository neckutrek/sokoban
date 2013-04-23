#version 150

in vec3 transformed_normal_vector;
in vec4 view_vector;
in vec4 transformed_light_source_pos_array[8];

uniform vec3 light_sources_color_array[8];
uniform float light_sources_lux_array[8];
uniform int light_counter;

out vec4 outColor;

void main(void)
{
    vec4 diffuse_total_color = vec4(0.0, 0.0, 0.0, 0.0);
    
    int counter = light_counter;
    if (counter > 8) counter = 8;
    for (int i = 0; i < counter; ++i)
    {
        vec4 light_travel_vector = transformed_light_source_pos_array[i] - view_vector;
        //float light_travel_distance = sqrt( light_travel_vector[0]*light_travel_vector[0] +
        //                                light_travel_vector[1]*light_travel_vector[1] +
        //                                   light_travel_vector[2]*light_travel_vector[2] );
        
        vec3 N = normalize(transformed_normal_vector);
        vec3 L = vec3( normalize(light_travel_vector) );
        
        float Idiff = max(dot(N, L), 0.0);
        Idiff = clamp(Idiff, 0.0, 1.0);
        Idiff *= light_sources_lux_array[i];
        
        diffuse_total_color += vec4(vec3( Idiff * light_sources_color_array[i] ),
                                    1.0);
    }

	outColor = //vec4(0.5, 0.6, 0.9, 1.0) +
        diffuse_total_color;
}
