#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform vec3 object_color;

uniform int hp;

// Output
layout(location = 0) out vec4 out_color;

vec4 point_light_contribution(vec3 light_pos, vec3 light_color);

void main()
{
    if (hp < 3) {
        out_color = point_light_contribution(light_position, light_direction) * 1.0 / 4 * hp;
    }
    else
    {
        out_color = point_light_contribution(light_position, light_direction);
    }
}

vec4 point_light_contribution(vec3 light_pos, vec3 light_color) {
    vec3 L = normalize(light_pos - world_position);
    vec3 V = normalize(world_position);
    vec3 H = normalize(L + V);
    vec3 R = reflect(-L, world_normal);

    float ambient_light = 0.4;
    float diffuse_light = material_kd * max(dot(world_normal, L), 0);
    float specular_light = 0;
    if (diffuse_light > 0)
    {
        specular_light = material_ks * pow(max(dot(V, R), 0), material_shininess);
    }

    float total_light = ambient_light;

    total_light = ambient_light + diffuse_light + specular_light;

	return vec4(object_color, 1) * total_light;
}
