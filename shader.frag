#version 150 core

in vec3 Color;
out vec4 outColor;
in vec2 TexCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;	
uniform sampler2D texture3;

void main() {
	//outColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), texture(texture3, TexCoord), 0.33);
	//outColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5);
	//outColor = texture(texture1, TexCoord)*texture(texture2, TexCoord)*texture(texture3, TexCoord);
	//outColor = vec4(Color, 1.0);
	outColor = vec4(1.0, 1.0, 1.0, 1.0);
}
