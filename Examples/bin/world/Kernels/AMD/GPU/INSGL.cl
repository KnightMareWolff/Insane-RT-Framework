typedef struct ICLVertexBuffer
{
   float  position  [3];
   float  texCoord  [2];
   float  normal    [3];
   float  smooth    [3];
   float  tangente  [3];
   float  bitangente[3];
} ICLVertexBuffer;

inline float4 MultiplyMatrixVector(float16 m , float x , float y , float z)
{
   float   rhw, _x, _y, _z;
   float4  resultado;

   rhw = (x * m.s3 + y * m.s7 + z * m.sb + m.sf);

   if (fabs(rhw) < 0.00001)
   {
      resultado.s0 = 0;
      resultado.s1 = 0;
      resultado.s2 = 0;

      return resultado;
   }

   rhw = 1.0f / rhw;

   _x = rhw * (x * m.s0 + y * m.s4 + z * m.s8 + m.sc);
   _y = rhw * (x * m.s1 + y * m.s5 + z * m.s9 + m.sd);
   _z = rhw * (x * m.s2 + y * m.s6 + z * m.sa + m.se);

   resultado.s0 = _x;
   resultado.s1 = _y;
   resultado.s2 = _z;

   return resultado;
}

__kernel void TransformGLBuffer( __global  ICLVertexBuffer* ICLBufferIn ,
                                 float16                    TransfMatrix)
{
   local float4 vert;
   local float4 vert1;

   int index = get_global_id(0);

   vert1.x = ICLBufferIn[index].position[0];
   vert1.y = ICLBufferIn[index].position[1];
   vert1.z = ICLBufferIn[index].position[2];

   vert =   MultiplyMatrixVector( TransfMatrix , vert1.x,
                                                 vert1.y,
                                                 vert1.z);

   ICLBufferIn[index].position[0]=vert.x;
   ICLBufferIn[index].position[1]=vert.y;
   ICLBufferIn[index].position[2]=vert.z;

   ICLBufferIn[index].texCoord[0]-=0.1;
   ICLBufferIn[index].texCoord[1]+=0.1;


}
