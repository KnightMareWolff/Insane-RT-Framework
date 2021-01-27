#version 430 core
#ifdef GL_ES
//Seta Precisao default para medio
precision mediump int;
precision mediump float;
#endif

uniform sampler2D texture     ;
uniform sampler2D detalhe     ;
uniform int       multitextura;//0-nao 1-nao
uniform int       pixeloper   ;//0-normal 1-alphareject
uniform int       seloper     ;//0-normal 1-pixelselection
uniform int       colorcode   ;//pixel selecao
uniform vec4      color_reject   = vec4(  0.0,  0.0,  0.0, 1.0);
uniform vec4      color_ambient  = vec4(  0.1,  0.1,  0.1, 1.0);
uniform vec4      color_diffuse  = vec4(  0.0,  0.0,  0.0, 1.0);
uniform vec4      color_specular = vec4(  0.0,  0.0,  0.0, 1.0);
uniform float     shininess      = 77.0f;
uniform vec3      light_position = vec3(12.0f, 32.0f, 560.0f);

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
    vec4   color           = color_ambient + diffuse * color_diffuse + specular * color_specular;
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

bool ChecaSelecao()
{
    if(seloper==1)
    {
       return false;
    }
    return true;
}

void main()
{
    if(ChecaSelecao())
    {
       if(ChecaRejeicao())
       {
           discard;
       }
       else
       {
          //Aplica no fragmento a iluminacao + Fragmento resultante das texturas
          if(multitextura==0)
          {
             gl_FragColor = CalculaIluminacao() + texture2D(texture, t_texcoord);
          }
          else
          {
             gl_FragColor = CalculaIluminacao() +
                           (texture2D(texture, t_texcoord) - texture2D(detalhe, t_texcoord*100));
          }
       }
    }
    else
    {
        gl_FragColor = vec4(colorcode/255.0, 0, 0, 0);
    }
}

