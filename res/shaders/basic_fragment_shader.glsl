#version 450 core 

layout(location = 0) out vec4 out_color;

in vec4 fragmentcolor;
in vec2 textureuv;

uniform sampler2D texture1;

void main()
{
//	out_color = texture(texture1, textureuv);

	out_color = vec4(1.0, 1.0, 0.0, 1.0);
}
