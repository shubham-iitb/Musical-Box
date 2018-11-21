//#version 130

#version 400

uniform sampler2D texture1;

in vec3 normal;
in vec4 eye;
in vec4 color;
in vec2 tex;

uniform mat4 viewMatrix;


out vec4 frag_color;

void main () 
{



	// if(tex.x==0) frag_color = color;
	// else frag_color = texture(texture1,tex);


	vec4 diffuse = vec4(0.9,0.9,0.45,1.0);
	vec4 ambient = vec4(0.0,0.1,0.0,1.0);
	vec4 specular = vec4(0.3,0.3,0.3,1.0);
	float shininess = 0.05;
	vec4 spec = vec4(0.5);

	vec4 lightpos = vec4(7.0,5.0,-150.0,1.0);
	vec3 lightdir = vec3(viewMatrix*lightpos);
	lightdir = normalize(lightdir);


	vec3 n = normalize(vec3(normal));

	float dotProduct = dot(n, lightdir);
    float intensity =  max( dotProduct, 0.0);

    // Compute specular component only if light falls on vertex

    if(intensity > 0.0) {
        vec3 e = normalize(vec3(eye));
        vec3 h = normalize(lightdir + e );
        float intSpec = max(dot(h,n), 0.0);
        spec = specular * pow(intSpec, shininess);
    }



	vec4 color1 = vec4(0.0);

	//color1 = texture2D(texture1,tex);
	if(tex.x==0) color1 = color;
	else color1 = texture(texture1,tex);

    frag_color = max((intensity * diffuse  + spec)*color1, ambient);
    // frag_color = color1;


}
