#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

//uniform mat4 mvp_matrix;
uniform mat4 modl_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

//Vertex Buffer Data
attribute vec3 a_position;
attribute vec2 a_texcoord;
attribute vec3 a_normal;

//Variaveis de transicao
varying   vec2 t_texcoord;
varying   vec3 t_position;
varying   vec3 t_normal;

void main()
{
    //Calcula a posição transformada do vertice PVM Matriz
    vec4 pos    = (proj_matrix * view_matrix) * modl_matrix * vec4(a_position,1.0);
    //prove para a OGL a pos transf
    gl_Position = pos;
    // Transfere a coordenadas de textura e vertice para o fragment shader
    // O valor sera automaticamente interpolado para fragmentos dentro das faces
    // do poligono bem como usano no fs para iluminacao
    t_texcoord  = a_texcoord;
    t_position  = pos.xyz;
    t_normal    = a_normal;
}
