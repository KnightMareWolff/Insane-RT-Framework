#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

//uniform mat4 mvp_matrix;
uniform mat4 modl_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

//Variaveis de Controle de Operacao
uniform vec3  posicao_camera;
uniform vec3  view_camera;
uniform vec3  up_camera;
uniform float indice_refracao;

//Vertex Buffer Data
attribute vec3 a_position;
attribute vec2 a_texcoord;
attribute vec3 a_normal;
attribute vec3 a_smooth;
attribute vec3 a_tangente;
attribute vec3 a_bitangente;

//Variaveis de transicao
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

void main()
{
    //Calcula a posição transformada do vertice PVM Matriz
    vec4 pos    = (proj_matrix * view_matrix) * modl_matrix * vec4(a_position,1.0);
    //prove para a OGL a pos transf
    gl_Position = pos;
    // Transfere a coordenadas de textura e vertice para o fragment shader
    // O valor sera automaticamente interpolado para fragmentos dentro das faces
    // do poligono bem como usano no fs para iluminacao
    t_texcoord       = a_texcoord;
    t_position       = pos.xyz;
    t_position_world = vec3(modl_matrix  * vec4(a_position,1.0) );

    t_view_world     = normalize( posicao_camera - t_position_world );

    t_normal         = mat3(modl_matrix) * a_normal;
    t_smooth         = mat3(modl_matrix) * a_smooth;
    t_tangente       = mat3(modl_matrix) * a_tangente;
    t_bitangente     = mat3(modl_matrix) * a_bitangente;
    t_eyecoord       = (modl_matrix * view_matrix) * vec4(a_position,1.0);

    // Matriz para transformação do espaço tangente.
    t_bumpmatrix = mat3(
            t_tangente.x, t_bitangente.x, t_smooth.x,
            t_tangente.y, t_bitangente.y, t_smooth.y,
            t_tangente.z, t_bitangente.z, t_smooth.z ) ;

    //Calcula a direção da reflexão
    t_dir_reflexao = reflect(-t_view_world, t_normal );
    t_dir_refracao = refract(-t_view_world, t_normal, indice_refracao );

}
