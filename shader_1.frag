#version 150

in vec3 transformed_normal_vector;
in vec4 view_vector;
in vec4 transformed_light_source_pos_array[8];
in vec2 texture_coordinate;

//uniform bool have_texture;
//uniform Sampler2D texture_id;
//uniform float texture_specular_exponent;
uniform vec3 light_sources_color_array[8];
uniform float light_sources_lux_array[8];
uniform int light_counter;

out vec4 outColor;

void main(void)
{
    vec3 total_shade = vec3(0.0, 0.0, 0.0);
	
    // if no texture is used, full color component should be used!
//    vec4 texture_total_color = vec4(1.0);
//    if (have_texture) {
//        texture_total_color = texture(texture_id, texture_coordinate);
//    }
    
    vec3 N = normalize(transformed_normal_vector);
    float Iamb = 0.1;
    total_shade += vec3( Iamb );
    
    int counter = light_counter;
    if (counter > 8) counter = 8;
    for (int i = 0; i < counter; ++i)
    {
        vec4 light_travel_vector = transformed_light_source_pos_array[i] - view_vector;
        float light_travel_distance =
            sqrt(
            light_travel_vector[1] * light_travel_vector[1] +
            light_travel_vector[2] * light_travel_vector[2] +
            light_travel_vector[3] * light_travel_vector[3] );
        
        vec3 L = vec3( normalize(light_travel_vector) );
        vec3 R = normalize(-reflect(L,N));
		vec3 V = vec3(normalize(-view_vector));
        
        float Idiff = max(dot(N, L), 0.0);
        Idiff = clamp(Idiff, 0.0, 1.0);
        Idiff *= light_sources_lux_array[i];
        //Idiff /= light_travel_distance * light_travel_distance;
		
//        float Ispec = 0.0;
//        if (have_texture) {
//            Ispec = pow( max(dot(R,V),0.0), texture_specular_exponent );
//            Ispec = clamp(Ispec, 0.0, 1.0);
//            Ispec *= light_sources_lux_array[i];
//        }
        
        total_shade += vec3(Idiff * light_sources_color_array[i]);
//        total_shade += vec3(Ispec * light_sources_color_array[i]);
    }

	outColor = vec4(total_shade, 1.0);// * texture_total_color;
}
