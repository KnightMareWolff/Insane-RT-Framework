#version 430

//Canais de Textura Disponiveis
uniform sampler2D   textura_base;
uniform sampler2D   textura_detalhe;
uniform sampler2D   textura_normal_map;
uniform samplerCube textura_cube_map;

//Variaveis de Controle de Operacao
uniform int       multitextura       ;//0-nao 1-nao
uniform int       pixeloper          ;//0-normal 1-color reject
uniform int       modo_material      ;//0-cores  1-texturizada 2-Mixed 3-NormalMap 4-Reflexao 5-Refração.
uniform int       modo_iluminacao    ;//0-flat   1-phong 2-difusaFLAT 3-difusaSmooth 4-Nenhum
uniform int       modo_renderizacao  ;//0-normal 1-selection
uniform int       color_pick         ;//valor inteiro representando a cor de seleção
uniform vec4      color_reject       ;//cor a ser usada para rejeicao de pixel.

//Dados de uma Luz
struct DadosLuz
{
   vec4      cor_ambiente_luz   ;//cor ambiente da luz
   vec4      cor_diffusa_luz    ;//cor difusa da luz
   vec4      cor_specular_luz   ;//cor specular da luz

   vec3      posicao_luz        ;//posicao  da luz
   vec3      direcao_luz        ;//direcao  da luz

   float     expoente_luz           ;
   float     cutoff_luz             ;
   float     atenuacaoconstante_luz ;
   float     atenuacaolinear_luz    ;
   float     atenuacaoquadratica_luz;
};

//São 10 Canais de luzes em shaders.
uniform DadosLuz Luzes[10];

//Dados de um Material
uniform vec4      cor_diffusa_mat  ;
uniform vec4      cor_ambiente_mat ;
uniform vec4      cor_emissiva_mat ;
uniform vec4      cor_specular_mat ;
uniform float     opacidade_mat    ;//Fator de Opeacidade do Material
uniform float     brilho_mat       ;//Fator de Brilho do Material
uniform float     reflexao_mat     ;//Fator de Reflexão do Material

//Dados Do Vertex Shader
varying   vec2 t_texcoord;
varying   vec3 t_position;
varying   vec3 t_position_world;
varying   vec3 t_view_world;
varying   vec3 t_normal;
varying   vec3 t_smooth;
varying   vec3 t_tangente;
varying   vec3 t_bitangente;
varying   vec4 t_eyecoord;
varying   mat3 t_bumpmatrix;
varying   vec3 t_dir_reflexao;
varying   vec3 t_dir_refracao;

vec3 IluminacaoPhong(int IdLuz,vec3 s_normal)
{
    vec3 l_eyecoord;

    l_eyecoord.x = t_eyecoord.x;
    l_eyecoord.y = t_eyecoord.y;
    l_eyecoord.z = t_eyecoord.z;

    vec3 s = normalize(Luzes[IdLuz].posicao_luz - l_eyecoord);
    vec3 v = normalize( - l_eyecoord );
    vec3 r = reflect  ( -s, s_normal );

    float sDotN = max( dot(s,s_normal), 0.0 );

    vec3 ambient = (Luzes[IdLuz].cor_ambiente_luz * cor_ambiente_mat).xyz;
    vec3 diffuse = (Luzes[IdLuz].cor_diffusa_luz  * cor_diffusa_mat ).xyz * sDotN;
    vec3 spec    = vec3(0.0);

    if( sDotN > 0.0 )
    {
       spec = (Luzes[IdLuz].cor_specular_luz *
                           cor_specular_mat *
                           pow( max( dot(r,v), 0.0 ), brilho_mat )).xyz;
    }

    vec3   IntensidadeLuz = ambient + diffuse + spec;
    return IntensidadeLuz;
}

vec3 IluminacaoDifusa(int IdLuz,vec3 s_normal)
{
    vec3 l_eyecoord;

    l_eyecoord.x = t_eyecoord.x;
    l_eyecoord.y = t_eyecoord.y;
    l_eyecoord.z = t_eyecoord.z;

    vec3 s = normalize(Luzes[IdLuz].posicao_luz - l_eyecoord);

    vec3   IntensidadeLuz = (Luzes[IdLuz].cor_diffusa_luz *
                                          cor_diffusa_mat *
                             max( dot( s, s_normal ), 0.0 )).xyz;
    return IntensidadeLuz;
}

vec3 IluminacaoNula(int IdLuz,vec3 s_normal)
{
    //Retorna Intensidade Nula de Shading
    vec3   IntensidadeLuz  =  vec3(0.0) ;
    return IntensidadeLuz;
}

vec3 IluminacaoNormalMap(int IdLuz,vec3 normalmapcoord , vec3 cortextura)
{
    // Transform light direction and view direction to tangent space
    vec3 bumplightdir    = normalize( t_bumpmatrix * (Luzes[IdLuz].posicao_luz.xyz - t_position) );
    vec3 bumpviewdir     = t_bumpmatrix * normalize(-t_position);
    vec3 IntensidadeLuz  = vec3(Luzes[IdLuz].expoente_luz,
                                Luzes[IdLuz].expoente_luz,
                                Luzes[IdLuz].expoente_luz);

    vec3  r = reflect( -bumplightdir, normalmapcoord );
    vec3  ambient = IntensidadeLuz * cor_ambiente_mat.rgb;
    float sDotN   = max( dot(bumplightdir, normalmapcoord), 0.0 );
    vec3  diffuse = IntensidadeLuz * cortextura * sDotN;

        vec3 spec = vec3(0.0);
        if( sDotN > 0.0 )
            spec = IntensidadeLuz       *
                   cor_specular_mat.rgb *
                   pow( max( dot(r,bumpviewdir), 0.0 ), brilho_mat );

     return ambient + diffuse + spec;
}

vec4 CalculaIluminacao()
{
    vec4   cor_luz;

    for( int i = 0; i < 10; i++ )
    {
       //No caso de Normal Maps a Normal do Mesh não é utilizada e quando solicitado pelo
       //programador retorna iluminação Nula
       if(modo_material  == 3 ||
          modo_material  == 4 ||
          modo_material  == 5 ||
          modo_iluminacao== 4  )
       {
           //Iluminação Nula
           cor_luz += vec4(IluminacaoNula(i,t_smooth), 1.0);
       }
       //Phong com Normais Flat gera ADS Flat(Ambiente + difusa + specular)
       if(modo_iluminacao==0)
       {
          cor_luz += vec4(IluminacaoPhong(i,t_normal), 1.0);
       }
       //Phong com Normais Smooth gera ADS Smooth(Ambiente + difusa + specular)
       if(modo_iluminacao==1)
       {
          cor_luz += vec4(IluminacaoPhong(i,t_smooth), 1.0);
       }
       //Difusa com Normais Flat (Difusa Luz + Difusa Material)
       if(modo_iluminacao==2)
       {
          cor_luz += vec4(IluminacaoDifusa(i,t_normal), 1.0);
       }
       //Difusa com Normais Smooth (Difusa Luz + Difusa Material)
       if(modo_iluminacao==3)
       {
          cor_luz += vec4(IluminacaoDifusa(i,t_smooth), 1.0);
       }
    }

    return cor_luz;
}

vec4 CalculaMaterial()
{
    vec4   cor_material;

    //Caso esteja-se requisitando operações Multitextura sem que
    //Multitextura seja suportada...
    if(modo_material > 1 && multitextura==0)
    {
       cor_material = texture2D(textura_base, t_texcoord);
    }
    //Calcula a Intensidade da Luz (algoritmo Phong) Flat ou ADS
    if(modo_material==0)
    {
       //Phong com Normais Flat gera ADS Flat(Ambiente + difusa + specular)
       cor_material = cor_diffusa_mat;
    }
    if(modo_material==1)
    {
       //Repassa a cor da textura
       cor_material = texture2D(textura_base, t_texcoord);
    }
    if(modo_material==2)
    {
       //Faz o Mix da textura com a texturaBase.
       //Obs:Por enquanto esta se considerando Mixed textura detalhe
       //cor_material = mix(texture2D(textura_base, t_texcoord) ,
       //                   texture2D(textura_detalhe, t_texcoord * vec2(100.0,100.0)),
       //                   0.7);
       cor_material = (texture2D(textura_base, t_texcoord) - texture2D(textura_detalhe, t_texcoord * vec2(50.0,50.0)));
    }
    if(modo_material==3)
    {
       //No Caso de NormalMaping a iluminação é refletida no processamento do Material
       //Portanto é aplicado uma Iluminação Nula durante o estagio de junção entre
       //a cor do material e a cor de luz...portanto o loop de luzes tambem e realizado aqui,
       //por enquanto...
       vec4 nrmlMapCoord = 2.0 * texture2D( textura_normal_map , t_texcoord ) - 1.0;
       vec4 cortextura   = texture2D( textura_base , t_texcoord );
       for( int i = 0; i < 10; i++ )
       {
          cor_material += vec4( IluminacaoNormalMap(i,nrmlMapCoord.xyz, cortextura.rgb), 1.0 );
       }
    }
    if(modo_material==4)
    {
       //Realiza a Reflexão
       vec4 correflexao = texture(textura_cube_map, t_dir_reflexao);
       cor_material    = mix( cor_diffusa_mat, correflexao , reflexao_mat);
    }
    if(modo_material==5)
    {
       //Realiza a Refração
       vec4 correflexao = texture(textura_cube_map, t_dir_reflexao);
       vec4 correfracao = texture(textura_cube_map, t_dir_refracao);

       cor_material    = mix( correfracao , correflexao , reflexao_mat);
    }
    if(modo_material==6)
    {
       cor_material    = texture(textura_cube_map, t_position_world);
    }

    return cor_material;
}

bool ChecaRejeicao()
{
    if(pixeloper==1)
    {
       if(texture2D(textura_base, t_texcoord) == color_reject)
       {
          return true;
       }
       return false;
    }
    return false;
}

void main()
{
    if(modo_renderizacao==0)
    {
       if(ChecaRejeicao())
       {
           //Caso seja para rejeitar descarta o Pixel da Operação
           discard;
       }
       else
       {
          //Aplica no fragmento a iluminacao + Fragmento resultante das texturas
          gl_FragColor = CalculaIluminacao() + CalculaMaterial();
       }
    }
    if(modo_renderizacao==1)
    {
        //Aplica aplica a cor de seleção do objeto.
        gl_FragColor = vec4(color_pick/255.0);
    }
}

