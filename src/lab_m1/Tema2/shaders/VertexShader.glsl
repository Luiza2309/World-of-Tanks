#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// Output values to fragment shader
out vec3 world_position;
out vec3 world_normal;
uniform int hp;

void main() {
    // Deform the object using a sine wave
    world_position = (Model * vec4(v_position, 1)).xyz;
    world_normal = normalize(mat3(Model) * v_normal);

    vec3 deformedPosition = v_position;
    if (hp < 3) {
        float deformationAmount = sin(v_position.x + v_position.z) * 0.07 * (3 - hp); // Adjust parameters as needed
         deformedPosition = deformedPosition + deformedPosition * deformationAmount;
    }

    // Transform the vertex position using model, view, and projection matrices
    gl_Position = Projection * View * Model * vec4(deformedPosition, 1.0);

    // You can pass other attributes to the fragment shader if needed
    //fragColor = vec4(1.0, 0.0, 0.0, 1.0); // Red color for simplicity
}
