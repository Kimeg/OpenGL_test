#version 330 core

in vec2 texCoords;

const vec3 gamma = vec3(2.2);
const vec3 inv_gamma = 1/gamma;

uniform sampler2D cubemap;

void main()
{
    //gl_FragColor = vec4(vec3(1.0)-texture(cubemap, texCoords).xyz, 1.0);

    vec3 tex_col = texture(cubemap, texCoords).rgb;
    tex_col = pow(tex_col, gamma);
    tex_col = pow(tex_col, inv_gamma);

    float fog_dist = gl_FragCoord.z / gl_FragCoord.w;
    float alpha = mix(0.5, 0.0, 1.0-exp(-0.000002*fog_dist*fog_dist));

    gl_FragColor = vec4(tex_col, alpha);

    //gl_FragColor = vec4(0.5f);
}