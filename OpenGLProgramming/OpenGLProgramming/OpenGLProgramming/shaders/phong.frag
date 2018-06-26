#version 410

in vec4 vPosition; 
in vec3 vNormal;

uniform vec3 Ka; // ambient material colour 
uniform vec3 Kd; // diffuse material colour 
uniform vec3 Ks; // specular material colour 

uniform float specularPower; // material specular power 

uniform vec3 Ia; // ambient light colour 

uniform vec3 Id; // diffuse light colour 
uniform vec3 Id2; // diffuse light colour 

uniform vec3 Is; // specular light colour 
uniform vec3 Is2; // specular light colour 

uniform vec3 lightDirection; 
uniform vec3 lightDirection2;
uniform vec3 cameraPosition;

out vec4 FragColour; 

void main() 
{ 
	// ensure normal and light direction are normalised 
	vec3 N = normalize(vNormal); 
	vec3 L = normalize(lightDirection); 
	vec3 L2 = normalize(lightDirection2); 

	// calculate lambert term (negate light direction)
	float lambertTerm = max( 0, min( 1, dot( N, -L ) ) );
	float lambertTerm2 = max( 0, min( 1, dot( N, -L2 ) ) );

	// calculate view vector and reflection vector 
	vec3 V = normalize(cameraPosition - vPosition.xyz); 
	vec3 R = reflect( L, N ); // calculate specular term 
	vec3 R2 = reflect( L2, N ); // calculate specular term 

	// calculate each colour property 
	float specularTerm = pow( max( 0, dot( R, V ) ), specularPower ); 
	float specularTerm2 = pow( max( 0, dot( R2, V ) ), specularPower ); 

	//calculate specular term
	vec3 ambient = Ia * Ka; 
	vec3 diffuse = Id * Kd * lambertTerm;
	vec3 diffuse2 = Id2 * Kd * lambertTerm2; 
	vec3 specular = Is * Ks * specularTerm;
	vec3 specular2 = Is2 * Ks * specularTerm2;

	FragColour = vec4( ambient + diffuse + diffuse2 + specular + specular2, 1); 
}