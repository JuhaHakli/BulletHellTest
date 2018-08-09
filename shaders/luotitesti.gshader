#version 150 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

in float angle[];
in float speed[];
in float tint[];
in int shape[];
in int time[];

out float angle[];
out float speed[];
out float fTint;
flat out int fTime;



out vec2 texCoord;

#define M_PI 3.1415926535897932384626433832795

mat4 rotationMatrix(vec3 axis, float angle)
{
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;
    
    return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}

//S-Palloluoti
void build_ballS(vec4 position)
{    
	//Lasketaan luodin leveys/2 ja korkeus/2 ja sovitetaan se -1, 1 koordinaatteihin
	float width = 2.0f/576.0f*16.0f;
	float height = 2.0f/672.0f*16.0f;
	
	//Luodaan keskipisteen avulla nurkat käyttäen hyväksi äsken laskettuja leveyttä ja korkeutta
    gl_Position = position + vec4(-width, -height, 0.0f, 0.0f);    // 1:bottom-left
	texCoord = vec2(0.0f, 0.03125f);
    EmitVertex();   
    gl_Position = position + vec4( width, -height, 0.0f, 0.0f);    // 2:bottom-right
	texCoord = vec2(0.03125f, 0.03125f);
    EmitVertex();
    gl_Position = position + vec4(-width,  height, 0.0f, 0.0f);    // 3:top-left
	texCoord = vec2(0.0f, 0.0f);
    EmitVertex();
    gl_Position = position + vec4( width,  height, 0.0f, 0.0f);    // 4:top-right
	texCoord = vec2(0.03125f, 0.0f);
    EmitVertex();
    EndPrimitive();
}

//S-Palloluoti
void build_ballSTEST(vec4 position)
{    
	float width = 2.0f/576.0f*16.0f;
	float height = 2.0f/672.0f*24.0f;
	
	float angRad = M_PI/2 - angle[0] * M_PI/180.0f;
	
	mat4 rotZ = rotationMatrix(vec3(0, 0, 1), angRad);
	
	//Asetetaan pisteet origoon:
    gl_Position = position + vec4(-width, -height, 0.0f, 0.0f) * rotZ;    // 1:bottom-left
	texCoord = vec2(0.0f, 0.078125f);
    EmitVertex();   
    gl_Position = position + vec4( width, -height, 0.0f, 0.0f) * rotZ;    // 2:bottom-right
	texCoord = vec2(0.03125f, 0.078125f);
    EmitVertex();
    gl_Position = position + vec4(-width,  height, 0.0f, 0.0f) * rotZ;    // 3:top-left
	texCoord = vec2(0.0f, 0.03125f);
    EmitVertex();
    gl_Position = position + vec4( width,  height, 0.0f, 0.0f) * rotZ;    // 4:top-right
	texCoord = vec2(0.03125f, 0.03125f);
    EmitVertex();
    EndPrimitive();
}

//M-Palloluoti
void build_ballM(vec4 position)
{    
	//Lasketaan luodin leveys/2 ja korkeus/2 ja sovitetaan se -1, 1 koordinaatteihin
	float width = 2.0f/576.0f*24.0f;
	float height = 2.0f/672.0f*24.0f;
	
	//Luodaan keskipisteen avulla nurkat käyttäen hyväksi äsken laskettuja leveyttä ja korkeutta
    gl_Position = position + vec4(-width, -height, 0.0f, 0.0f);    // 1:bottom-left
	texCoord = vec2(0.03125f, 0.046875f);
    EmitVertex();   
    gl_Position = position + vec4( width, -height, 0.0f, 0.0f);    // 2:bottom-right
	texCoord = vec2(0.078125f, 0.046875f);
    EmitVertex();
    gl_Position = position + vec4(-width,  height, 0.0f, 0.0f);    // 3:top-left
	texCoord = vec2(0.03125f, 0.0f);
    EmitVertex();
    gl_Position = position + vec4( width,  height, 0.0f, 0.0f);    // 4:top-right
	texCoord = vec2(0.078125f, 0.0f);
    EmitVertex();
    EndPrimitive();
}

//L-Palloluoti
void build_ballL(vec4 position)
{    
	//Lasketaan luodin leveys/2 ja korkeus/2 ja sovitetaan se -1, 1 koordinaatteihin
	float width = 2.0f/576.0f*32.0f;
	float height = 2.0f/672.0f*32.0f;
	
	//Luodaan keskipisteen avulla nurkat käyttäen hyväksi äsken laskettuja leveyttä ja korkeutta
    gl_Position = position + vec4(-width, -height, 0.0f, 0.0f);    // 1:bottom-left
	texCoord = vec2(0.078125f, 0.0625f);
    EmitVertex();   
    gl_Position = position + vec4( width, -height, 0.0f, 0.0f);    // 2:bottom-right
	texCoord = vec2(0.140625, 0.0625f);
    EmitVertex();
    gl_Position = position + vec4(-width,  height, 0.0f, 0.0f);    // 3:top-left
	texCoord = vec2(0.078125f, 0.0f);
    EmitVertex();
    gl_Position = position + vec4( width,  height, 0.0f, 0.0f);    // 4:top-right
	texCoord = vec2(0.140625, 0.0f);
    EmitVertex();
    EndPrimitive();
}

//XL-Palloluoti
void build_ballXL(vec4 position)
{    
	float width = 2.0f/576.0f*40.0f;
	float height = 2.0f/672.0f*40.0f;
	
    gl_Position = position + vec4(-width, -height, 0.0f, 0.0f);    // 1:bottom-left
	texCoord = vec2(0.140625f, 0.078125f);
    EmitVertex();   
    gl_Position = position + vec4( width, -height, 0.0f, 0.0f);    // 2:bottom-right
	texCoord = vec2(0.21875f, 0.078125f);
    EmitVertex();
    gl_Position = position + vec4(-width,  height, 0.0f, 0.0f);    // 3:top-left
	texCoord = vec2(0.140625f, 0.0f);
    EmitVertex();
    gl_Position = position + vec4( width,  height, 0.0f, 0.0f);    // 4:top-right
	texCoord = vec2(0.21875f, 0.0f);
    EmitVertex();
    EndPrimitive();
}

//S-Ovaaliluoti
void build_ovalS(vec4 position)
{    
	float width = 2.0f/576.0f*16.0f;
	float height = 2.0f/672.0f*24.0f;
	
	float angRad = M_PI/2 - angle[0] * M_PI/180.0f;
	
	mat4 rotZ = rotationMatrix(vec3(0, 0, 1), angRad);
	
	//Asetetaan pisteet origoon:
    gl_Position = position + vec4(-width, -height, 0.0f, 0.0f) * rotZ;    // 1:bottom-left
	texCoord = vec2(0.0f, 0.078125f);
    EmitVertex();   
    gl_Position = position + vec4( width, -height, 0.0f, 0.0f) * rotZ;    // 2:bottom-right
	texCoord = vec2(0.03125f, 0.078125f);
    EmitVertex();
    gl_Position = position + vec4(-width,  height, 0.0f, 0.0f) * rotZ;    // 3:top-left
	texCoord = vec2(0.0f, 0.03125f);
    EmitVertex();
    gl_Position = position + vec4( width,  height, 0.0f, 0.0f) * rotZ;    // 4:top-right
	texCoord = vec2(0.03125f, 0.03125f);
    EmitVertex();
    EndPrimitive();
}

void main() 
{
	fTime = time[0];
	fTint = tint[0];
	
	switch(shape[0])
	{
		case 0:
			build_ballS(gl_in[0].gl_Position);
		break;
		case 1:
			build_ballM(gl_in[0].gl_Position);
		break;
		case 2:
			build_ballL(gl_in[0].gl_Position);
		break;
		case 3:
			build_ballXL(gl_in[0].gl_Position);
		break;
		case 4:
			build_ovalS(gl_in[0].gl_Position);
		break;	
	}
}	
