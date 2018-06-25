//A normal map fragment shader
#version 410

in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vTangent;
in vec3 vBiTangent;
in vec4 vPosition;
out vec4 FragColour;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;

uniform vec3 Ka; // material ambient
uniform vec3 Kd; // material diffuse
uniform vec3 Ks; // material specular

uniform float specularPower;
uniform vec3 Ia;  // light ambient

uniform vec3 Id;  // light diffuse
uniform vec3 Id2; // light diffuse
uniform vec3 Id3; // light diffuse

uniform vec3 Is;  // light specular
uniform vec3 Is2; // light specular
uniform vec3 Is3; // light specular

uniform vec3 lightDirection;
uniform vec3 lightDirection2;
uniform vec3 lightDirection3;

uniform vec3 cameraPosition;

//uniform vec4 lightPosition;
//uniform vec4 lightPosition2;

//This implementation is very similar to the lighting in the old fixed-function pipeline of OpenGL.
//There is a maximum number of lights, set in the MAX_LIGHTS constant then we create a uniform variable called allLights
//That holds the number of lights we are actually using called numLights
//Array of lights
//#define MAX_LIGHTS 10
//uniform int numLights;
//uniform struct Light
//{
//	vec3 position;
//	vec3 intensities;
//	float attenuation;
//	float ambientCoefficient;
//	float coneAngle;
//	vec3 coneDirection;
//}
//numLights[MAX_LIGHTS];
//
////The next step is to refactor the GLSL code so that it loops over the array. We extract all the lighting code into a function
////Called ApplyLight, which does the entire lighting calculation for a single light.
//
////The ApplyLight function takes a single light as an argument, but it also takes some arguments that describe the surface that
////Is being lit: surfaceColour, normal, surfacePos and surfaceToCamera.
////Because all the lights are acting upon the same surface, we calculate these surface related variables once, and pass them
////In as arguments for every Light
//
////With all the lighting code extraced into a function we can loop through all the lights. For each light, we call ApplyLight and add all the results together 
////To get the surface colour.
//
//vec3 ApplyLight(Light light, vec3 surfaceColour, vec3 normal, vec3 surfacePos, vec3 surfaceToCamera)
//{
//	vec3 surfaceToLight;
//	float attenuation = 1.0f;
//
//	//We represent the direction of a direction light with a homogeneous coordinate by setting W = 0.
//	//When W = 0 in a 4D coordinate, it represents the direction towards a point that is infinitely far away
//	if(lightPosition.w == 0.0)
//	{
//		//Get the direction by converting to vec3 (ignore W) and negate it
//		surfaceToLight = normalize(light.position.xyz);
//		attenuation = 1.0f;
//	}
//	else
//	{
//		//Point Light
//		surfaceToLight = normalize(light.position.xyz - surfacePos);
//		float distanceToLight = length(light.position.xyz - surfacePos);
//		attenuation = 1.0 / (1.0 + light.attenuation * pow(distanceToLight, 2));
//
//		//First we get the direction for the center of the cone. The Normalize function is called just in case
//		//light.coneDirection is not already a unit vector
//
//		//Second we get the direction of the ray of light. 
//		//This is the opposite of the direction from the surface to the light
//
//		//Third we get the angle between the center of the cone and the ray of light. The combination 
//		//Of acos and dot return the angle in radians, then we convert it into degrees
//
//		//Fourth we check if the angle is outside of the cone. If so, set the attenuation factor to zero
//		//To make the light ray invisible
//		float lightToSurfaceAngle = degrees(acos(dot(-surfaceToLight, normalize(light.coneDirection))));
//		//If the light pixel exits the cone it we set the attenuation to 0 which makes the light ray invisible
//		if(lightToSurfaceAngle > light.coneAngle)
//		{
//			attenuation = 0.0;
//		}
//	}
//
//	vec3 ambient = light.ambientCoefficient * surfaceColour.rgb * light.intensities;
//
//	float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
//	vec3 diffuse = diffuseCoefficient * surfaceColour.rgb * light.intensities;
//
//	float specularCoefficient = 0.0f;
//	if(diffuseCoefficient > 0.0)
//	{
//		//Is a mirror like reflection of waves, such as light
//		specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), specularPower);
//	}
//		vec3 specular = specularCoefficient * Ks * light.intensities;
//
//		return ambient + attenuation * (diffuse + specular);
//}

void main() 
{
	vec3 N = normalize(vNormal);
	vec3 T = normalize(vTangent);
	vec3 B = normalize(vBiTangent);
	vec3 L = normalize(lightDirection);
	vec3 L2 = normalize(lightDirection2);
	vec3 L3 = normalize(lightDirection3);
	
	mat3 TBN = mat3(T,B,N);
	
	vec3 texDiffuse = texture( diffuseTexture, vTexCoord ).rgb;
	vec3 texSpecular = texture( specularTexture, vTexCoord ).rgb;
	vec3 texNormal = texture( normalTexture, vTexCoord ).rgb;
	
	//Calculate lambert term
	float lambertTerm = max( 0,  min( 1, dot( N, -L )) );
	float lambertTerm2 = max( 0,  min( 1, dot( N, -L2)) );
	float lambertTerm3 = max( 0,  min( 1, dot( N, -L3 )) );
	
	//Calculate view vector and reflection vector
	vec3 V = normalize(cameraPosition - vPosition.xyz);
	vec3 R = reflect( L, N );
	vec3 R2 = reflect( L2, N );
	vec3 R3 = reflect( L3, N );
	
	//Calculate specular term
	float specularTerm = pow( max( 0, dot( R, V ) ), specularPower );
	float specularTerm2 = pow( max( 0, dot( R2, V ) ), specularPower );
	float specularTerm3 = pow( max( 0, dot( R3, V ) ), specularPower );
	
	//Sets the default colour to black
	//vec3 linearColor = vec3(0);
	//for(int i = 0; i < numLights; i++)
	//{
	//	//Light light, vec3 surfaceColour, vec3 normal, vec3 surfacePos, vec3 surfaceToCamera
	//	linearColor += ApplyLight(allLights[i], Kd, N, T, Is);
	//}

	//Calculate each light property
	vec3 ambient = Ia * Ka;
	vec3 diffuse = Id * Kd * texDiffuse * lambertTerm;
	vec3 specular = Is * Ks * texSpecular * specularTerm;

	vec3 diffuse2 = Id2 * Kd * texDiffuse * lambertTerm2;
	vec3 specular2 = Is2 * Ks * texSpecular * specularTerm2;

	vec3 diffuse3 = Id3 * Kd * texDiffuse * lambertTerm3;
	vec3 specular3 = Is3 * Ks * texSpecular * specularTerm3;

	FragColour = vec4(ambient + diffuse + specular + diffuse2 + specular2 + diffuse3 + specular3, 1);
}