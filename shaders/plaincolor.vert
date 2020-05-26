#version 330 core
layout (location = 0) in vec3 pos;
uniform mat4 projection;
//uniform mat4 view; // View matrix is integrated in model mat for now.
uniform mat4 model;
out vec3 FragPos;

void main()
{
    gl_Position = projection * model * vec4(pos, 1.0);
    FragPos = vec3(model * vec4(pos, 1.0));
}
