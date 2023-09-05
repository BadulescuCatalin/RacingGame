#version 330

// Input
// TODO(student): Get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture;
layout(location = 3) in vec3 v_color;

// extension -> manage extension -> glsl la extensii + de restart

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float clock;
uniform vec3 carPos;

// Output
// TODO(student): Output values to fragment shader
out vec3 frag_normal;
out vec2 frag_texture;
out vec3 frag_color;
out vec3 frag_position;

void main()
{
    // TODO(student): Send output to fragment shader
    frag_normal = v_normal;
	frag_texture = v_texture;
	frag_color = v_color;
    
   

    vec3 world_pos = (Model * vec4(v_position,1)).xyz;
    vec3 world_carPos = carPos; 

    //v_position = vpoz;
    world_pos.y = world_pos.y - length((world_carPos - world_pos) * (world_carPos - world_pos)) * 0.02; 
    // de pus poz car cu -0.5
    // TODO(student): Compute gl_Position
    gl_Position = Projection * View *  vec4(world_pos , 1.0f); 
    
}
