//============================================================================
//
// Listing 7.3
//
// Mathematics for 3D Game Programming and Computer Graphics, 3rd ed.
// By Eric Lengyel
//
// The code in this file may be freely used in any software. It is provided
// as-is, with no warranty of any kind.
//
//============================================================================


in vec3					view;		// Tangent-space view direction.
in vec3					light;		// Tangent-space light direction.
uniform vec3			diffuse;	// Diffuse material color.
uniform vec3			specular;	// Specular material color.
uniform vec2			range;		// Scale and bias for look-up texture.
uniform sampler2D		microfacetTexture;	// The look-up texture sampler.

void main()
{
	vec2	txtr;
	
	// Normalize V and L.
	vec3 vdir = normalize(view);
	vec3 ldir = normalize(light);
	
	// Calculate H.
	vec3 hdir = normalize(vdir + ldir);
	
	// Scale and bias N*H.
	txtr.x = hdir.z * range.x + range.y;
	
	// Calculate L*H.
	txtr.y = dot(ldir, hdir);
	
	// Look up product F(V,L)D(V,L)/pi and divide by N*V.
	vec3 color = texture2D(microfacetTexture, txtr).xyz / vdir.z;
	
	// Calculate geometrical attenuation (may be omitted).
	color *= saturate(min(vdir.z, ldir.z) * 2.0 * hdir.z / txtr.y);
	
	// Multiply specular by (1-k)C and add kCD(N*L).
	gl_FragColor.xyz = color * specular + diffuse * ldir.z;
}
