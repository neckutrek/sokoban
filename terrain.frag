#version 150

in vec2 texCoord;
in vec3 normal;
in vec4 lightSourcePos[4];
in vec4 viewVector;

uniform sampler2D tex;
uniform vec3 lightSourcesColorArr[4];
uniform float specularExponent[4];
uniform bool isDirectional[4];

out vec4 outColor;

void main(void)
{
	vec3 N = normalize(normal);
	vec3 finalShade = vec3(0.0, 0.0, 0.0);
	float Iamb = 0.2;

	vec4 finalTexture = vec4(0.0);
	float totalSpecIntensity = 0.0;	

	finalShade += vec3(Iamb);
	
	for (int i=0; i<4; i++) {
		vec3 L = vec3(normalize(lightSourcePos[i] - viewVector));
		vec3 R = normalize(-reflect(L,N));
		vec3 V = vec3(normalize(-viewVector));

		float Idiff = max(dot(N, L), 0.0);
		Idiff = clamp(Idiff, 0.0, 1.0);
	   
		float Ispec = 0.0;
		if (isDirectional[i]) {
			Ispec = pow( max(dot(R,V),0.0), specularExponent[i] );
			Ispec = clamp(Ispec, 0.0, 1.0);
		}
		totalSpecIntensity += Ispec;

		finalShade += Idiff * lightSourcesColorArr[i];
		finalShade += Ispec * lightSourcesColorArr[i];
	}
	
	finalShade = clamp(finalShade, 0.0, 1.0);

	finalTexture += texture(tex, texCoord);
	

	outColor = vec4(finalShade, 1.0) * finalTexture;
}
