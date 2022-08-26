#version 450

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragViewDir;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main(){
	
	const vec3 diffColor = texture(texSampler, fragTexCoord).rgb;
	const vec3 specColor = vec3(1.0f, 1.0f, 1.0f);

	const float specPower = 160.0f;

	const vec3 L0 = vec3(-0.4830f, 0.8365f, -0.2588f);
	const vec3 L1 = vec3(0.4830f, 0.8365f, 0.2588f);

	vec3 N = normalize(fragNorm);
	vec3 V = normalize(fragViewDir);
	
	vec3 HemiDir = vec3(0.0f, 1.0f, 0.0f);

	vec3 ambColor = vec3(0.3f, 0.3f, 0.3f);
	vec3 topColor = vec3(0.1f, 0.15f, 0.3f);

	vec3 diffuse0 = diffColor * max(dot(N, L0), 0.0f);
	vec3 diffuse1 = diffColor * max(dot(N, L1), 0.0f);

	vec3 first = (dot(N, HemiDir) + 1) / 2 * topColor;
	vec3 second = (1 - dot(N, HemiDir)) / 2 * ambColor;
	vec3 hemispheric = first + second;

	vec3 CompColor = diffuse0 + diffuse1 + (hemispheric * diffColor);
		
	outColor = vec4(CompColor, 1.0f);
}