#version 150
in vec2 pos;
in float ang;
in float spd;
in float hue;
in int shp;
in int tme;

out float angle;
out float speed;
out float tint;
out int shape;
out int time;


uniform mat4 projection;

void main() 
{
	angle = ang;
	speed = spd;
	shape = shp;
	time = tme;
	tint = hue;
	
	gl_Position = projection * vec4(pos, 0.0, 1.0);
}