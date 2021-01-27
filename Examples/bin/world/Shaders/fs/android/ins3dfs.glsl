#ifdef GL_ES
//Seta Precisao default para medio
precision mediump int;
precision mediump float;
#endif

uniform sampler2D texture;
uniform sampler2D detalhe;
uniform int       multitextura;//0-nao 1-nao
uniform int       pixeloper;   //0-normal 1-alphareject
uniform vec4      color_reject   ;
uniform vec4      color_ambient  ;
uniform vec4      color_diffuse  ;
uniform vec4      color_specular ;
uniform float     shininess      ;
uniform vec3      light_position ;

varying vec2      t_texcoord;
varying vec3      t_position;
varying vec3      t_normal;

vec4 CalculaIluminacao()
{
    //Reproduz o mesmo sistema de iluminacao da pipeline Fixa
    vec3   light_direction = normalize(light_position - t_position);
    vec3   normal          = normalize(t_normal);
    vec3   half_vector     = normalize(light_direction + normalize(t_position));
    float  diffuse         = max(0.0, dot(normal, light_direction));
    float  specular        = pow(max(0.0, dot(t_normal, half_vector)), shininess);
    vec4   color           = (color_ambient + diffuse) * (color_diffuse + specular) * color_specular;
    return color;
}

bool ChecaRejeicao()
{
    if(pixeloper==1)
    {
       if(texture2D(texture, t_texcoord) == color_reject)
       {
          return true;
       }
       return false;
    }
    return false;
}

void main()
{
    //Rejeixa Pixels da cor escolhida?
    if(ChecaRejeicao())
    {
        discard;
    }
    else
    {
       //Aplica no fragmento a iluminacao + Fragmento resultante das texturas
       if(multitextura==0)
       {
          //como ainda nao temos a posicao da luz nao aplicamos
          //gl_FragColor = CalculaIluminacao() + texture2D(texture, t_texcoord);
            gl_FragColor = texture2D(texture, t_texcoord);
       }
       else
       {
          gl_FragColor = CalculaIluminacao() +
                        (texture2D(texture, t_texcoord) - texture2D(detalhe, t_texcoord * vec2(100.0,100.0)));
       }
    }
}

