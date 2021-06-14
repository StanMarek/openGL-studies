#version 150 core

in vec3 Color;
out vec4 outColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
uniform vec3 camPos;
uniform vec3 lightPos;
uniform sampler2D texture1;
uniform sampler2D texture2;	
uniform sampler2D texture3;

void main() {
	//outColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), texture(texture3, TexCoord), 0.33);
	//outColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5);
	//outColor = texture(texture1, TexCoord)*texture(texture2, TexCoord)*texture(texture3, TexCoord);
	//outColor = vec4(Color, 1.0);
	//outColor = vec4(1.0, 1.0, 1.0, 1.0);
	//outColor = texture(texture1, TexCoord);

	float ambientStrength = 0.1;
	vec3 ambientlightColor = vec3(1.0, 1.0, 1.0);
	vec4 ambient = ambientStrength*vec4(ambientlightColor, 1.0);

	float diffuseStrength = 1.0;
	vec3 diffuselightColor = vec3(1.0, 1.0, 1.0);
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos- FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffvec = diff * diffuselightColor * diffuseStrength;
	vec4 diffuse = vec4(diffvec, 1.0);

	float specularStrength = 1.0;
	vec3 sepcularlightColor = vec3(1.0, 1.0, 1.0);
	vec3 viewDir = normalize(camPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 200);
	vec4 specular = specularStrength * spec * vec4(sepcularlightColor, 1.0);

	float dist = distance(lightPos, FragPos);
	dist = (50-dist)/50;
	dist = max(dist, 0.0); 

	outColor = (ambient + dist*diffuse +dist*spec) * texture(texture1, TexCoord);
}
