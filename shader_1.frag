#version 150

//in vec3 tranformed_normal_vector;
//in vec3 view_vector;

out vec4 outColor;


void main(void)
{
//    vec3 constant_light_source = vec3(0.5, 0.5, 0.5);
//    
//    vec3 N = normalize(tranformed_normal_vector);
//    vec3 L = vec3(normalize(constant_light_source - viewVector));
//    
//    float Idiff = max(dot(N, L), 0.0);
//    Idiff = clamp(Idiff, 0.0, 1.0);
    
	outColor = vec4(0.9, 0.9, 0.0, 1.0);// + vec4(Idiff, 1.0);
}
