#version 330

// Input
in vec2 texcoord;

// Uniform properties
uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform int mixx;

// TODO(student): Declare various other uniforms

// Output
layout(location = 0) out vec4 out_color;


void main()
{

    // TODO(student): Calculate the out_color using the texture2D() function.
    
    vec4 color1 = texture2D(texture_1, texcoord);
    vec4 color2 = texture2D(texture_2, texcoord);
    vec4 color = color1;

    if(mixx == 1) {
        color = mix(color1, color2, 0.5f);
    }
    if(color.a < 0.5)
        discard;
    out_color = color;

}
