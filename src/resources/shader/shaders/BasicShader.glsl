#shader vertex

#version 410 core

layout(location = 0) in vec2 position;

uniform float u_time;
uniform float u_width;
uniform float u_height;

void main()
{
    vec2 pos = position;
    pos.y += sin(u_time + pos.x * 8.0)/8.0;
    gl_Position = vec4(pos, 0.0, 1.0);
}


#shader fragment
#version 410 core

layout(location = 0) out vec4 color;

uniform float u_time;
uniform float u_width;
uniform float u_height;

void main() {
    vec4 color1 = vec4(255., 95., 0., 1.);
    vec4 color2 = vec4(255., 255., 0., 1.);
    color = mix(color1, color2, gl_FragCoord.x / u_width);
}