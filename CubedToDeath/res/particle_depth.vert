#version 450 core

layout (location = 0) in vec3 aPos;

uniform mat4 transform_matrix;
uniform mat4 model;

uniform float time;

const vec3[] velocities = {
vec3( 0.367762471534022 , 0.6189936211813832 , 0.7155674471620916 ),
vec3( 0.8910258339328887 , 0.5098443233631995 , 0.8088098374748414 ),
vec3( 0.6913155357025038 , 0.43254371551284065 , -0.6564747008822525 ),
vec3( -0.598788279051574 , 0.21266665499136006 , -0.1566878157145517 ),
vec3( -0.17494594583136158 , 0.21266538827416437 , 0.05326301029832625 ),
vec3( 0.21578981816654252 , 0.32459997661229034 , -0.5050015487952106 ),
vec3( -0.7626750833178195 , 0.8440699456975141 , 0.08513332555614306 ),
vec3( 0.11614551136553497 , 0.4059272159673659 , -0.2636830693595049 ),
vec3( -0.357777491391698 , 0.5282474050938228 , -0.5315220960374851 ),
vec3( 0.17445819131760265 , 0.9648901540173864 , -0.5887106990654707 ),
vec3( -0.45567885588989876 , 0.3529675820519146 , 0.263370331619011 ),
vec3( -0.3350398260515033 , 0.9787242644774093 , 0.5698077258469543 ),
vec3( 0.8026421951381897 , 0.970966620053604 , -0.45070359080871714 ),
vec3( 0.7900352268044457 , 0.8758348897726261 , 0.4445202059440425 ),
vec3( 0.008442257541862785 , 0.24267883242642818 , -0.4817213790138697 ),
vec3( 0.6604179184759877 , 0.6696358653733889 , 0.9787559700085255 ),
vec3( -0.08788981531518614 , 0.44743252763322483 , 0.958370406134625 ),
vec3( -0.21063604443462247 , 0.7543696317659703 , -0.8148966881041599 ),
vec3( 0.3791098563720332 , 0.6402536821080672 , 0.836415478373516 ),
vec3( 0.45375075464077597 , 0.7024386665387989 , 0.42161937304399144 )};

void main()
{
	int grid = 6;
	vec3 initial_offset = vec3(gl_InstanceID % grid, (gl_InstanceID/grid)%grid, gl_InstanceID/(grid * grid));
	vec3 initial_velocity = 5.7f * velocities[gl_InstanceID%20] + 10* ((model * vec4(initial_offset, 1)).xyz - (model * vec4(grid/2,grid/2,grid/2, 1)).xyz);
	initial_velocity.y += 8;
	vec4 position = model * vec4(max(0.45 - time, 0) * aPos + initial_offset + initial_velocity * time + vec3(0, -50, 0) * time * time, 1);

    gl_Position = transform_matrix * position;
}
