#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

//layout (lines_adjacency) in;
layout (triangles) in;
layout (triangle_strip, max_vertices = 6) out;

void main(void)
{
    //for(int i=0; i<3; i++)
    //{
    //    gl_Position = gl_in[i].gl_Position;
    //    EmitVertex();
    //}
    //EndPrimitive();

    //gl_Position = gl_in[0].gl_Position;
    //EmitVertex();

    //gl_Position = gl_in[1].gl_Position;
    //EmitVertex();

    //gl_Position = gl_in[2].gl_Position;
    //EmitVertex();

    //gl_Position = gl_in[2].gl_Position;
    //EmitVertex();

    //gl_Position = gl_in[3].gl_Position;
    //EmitVertex();

    //gl_Position = gl_in[1].gl_Position;
    //EmitVertex();

    //EndPrimitive();

}
