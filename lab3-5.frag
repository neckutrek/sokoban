#version 150

in vec2 texCoord;
in vec3 normal;
in vec4 viewVector;

uniform sampler2D tex[48];
uniform int nTextures;

in vec4 lightSourcePos[4];
uniform vec3 lightSourcesColorArr[4];
uniform float specularExponent[4];
uniform bool isDirectional[4];

out vec4 out_Color;

void main(void)
{   
	vec3 N = normalize(normal);
	vec3 finalShade = vec3(0.0, 0.0, 0.0);
	float Iamb = 0.5;

	vec4 finalTexture = vec4(0.0);
	float n = nTextures;
	float f = 1.0/n;
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

	if (nTextures > 1) {
		totalSpecIntensity += 0.1618;
		for (int i=0; i<nTextures; i++) {
			if (i%2 == 0) {
				finalTexture += totalSpecIntensity*f*texture(tex[i], texCoord);
			} else if ((i+1)%2 == 0) {
				finalTexture += (1-totalSpecIntensity)*f*texture(tex[i], texCoord);
			}
		}
	} else {
		finalTexture += texture(tex[0], texCoord);
	}
	

	out_Color = vec4(finalShade, 1.0) * finalTexture;
}
