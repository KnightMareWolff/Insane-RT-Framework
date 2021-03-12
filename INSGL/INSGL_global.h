/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef INSGL_GLOBAL_H
#define INSGL_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QtOpenGL>
#include <QOpenGLShaderProgram>
#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>
#include <vector>
using namespace std;

#include "INSMT.h"

#if defined(INSGL_LIBRARY)
#  define INSGL_EXPORT Q_DECL_EXPORT
#else
#  define INSGL_EXPORT Q_DECL_IMPORT
#endif

/***********************************/
/*internal OpenGL version mappings */
/***********************************/
#define IGL_OGL_V10 10
#define IGL_OGL_V11 11
#define IGL_OGL_V12 12
#define IGL_OGL_V13 13
#define IGL_OGL_V14 14
#define IGL_OGL_V15 15
#define IGL_OGL_V20 20
#define IGL_OGL_V21 21
#define IGL_OGL_V30 30
#define IGL_OGL_V31 31
#define IGL_OGL_V32 32
#define IGL_OGL_V33 33
#define IGL_OGL_V40 40
#define IGL_OGL_V41 41
#define IGL_OGL_V42 42
#define IGL_OGL_V43 43
#define IGL_OGL_V44 44
#define IGL_OGL_V45 45
#define IGL_OGL_C99 99

#define IGL_SH_BUFFERINIT        201
#define IGL_SH_DELBUFFERS        202
#define IGL_SH_RENDERBUFFERS     203
#define IGL_SH_PERSPECTIVE       204
#define IGL_SH_LOOKAT            205
#define IGL_SH_MODELMTX          206
#define IGL_SH_ENABLESTATES      207
#define IGL_SH_DISABLESTATES     208
#define IGL_SH_ACTIVETEXTURE     209
#define IGL_SH_DISACTTEXTURE     210
#define IGL_SH_UNIINT            211
#define IGL_SH_ORTHO             212
#define IGL_SH_LIGHT_POINT       213
#define IGL_SH_LIGHT_SPOT        214
#define IGL_SH_LIGHT_DIRECTIONAL 215
#define IGL_SH_MATERIAL          216
#define IGL_SH_UNIVEC3FLOAT      217
#define IGL_SH_UNIVEC4FLOAT      218
#define IGL_SH_ENABLE            219
#define IGL_SH_DISABLE           220
#define IGL_SH_COLORMATERIAL     221
#define IGL_SH_TEXTUREDMATERIAL  222
#define IGL_SH_MIXEDMATERIAL     223
#define IGL_SH_NMAPMATERIAL      224
#define IGL_SH_REFLMATERIAL      225
#define IGL_SH_REFRMATERIAL      226
#define IGL_SH_CUBEMAPMATERIAL   227
#define IGL_SH_FINISH            228
#define IGL_SH_DELTEXTURE        229

/***********************************/
/*external OpenGL version mappings */
/***********************************/
#define IGL_RENDER_TRIANGLES            1
#define IGL_RENDER_TRIANGLE_STRIP       2
#define IGL_RENDER_TRIANGLE_FAN         3
#define IGL_RENDER_TRIANGLES_ARRAY      4
#define IGL_RENDER_TRIANGLE_STRIP_ARRAY 5
#define IGL_RENDER_TRIANGLE_FAN_ARRAY   6
#define IGL_RENDER_POLYGON              7
#define IGL_RENDER_QUADS                8
#define IGL_RENDER_POINTS               9

#define IGL_POLYGON_INDEXED             1
#define IGL_POLYGON_NONINDEXED          2
#define IGL_POLYGON_AUTOTEXTURE         3

#define IGL_PROJECTION_PERSP            1
#define IGL_PROJECTION_ORTHO            2

#define IGL_GEOMETRY_DINAMIC            0
#define IGL_GEOMETRY_STATIC             1
#define IGL_GEOMETRY_PHYSICS            3

#define IGL_MATERIAL_COLOR              1
#define IGL_MATERIAL_TEXTURE            2
#define IGL_MATERIAL_LIGHT              3
#define IGL_MATERIAL_MIXED              4
#define IGL_MATERIAL_NORMALMAP          5
#define IGL_MATERIAL_REFLEXIVE          6
#define IGL_MATERIAL_REFRATIVE          7
#define IGL_MATERIAL_RENDERTOTEXTURE    8
#define IGL_MATERIAL_CUBEMAP            9

//Since the Windingmode are being altered at the same function of Material we mantain the same value sequence
#define IGL_WINMODE_CW                  10
#define IGL_WINMODE_CCW                 11

//RightHand or LeftHand geometry construction?
#define IGL_POLYMODE_LEFT         0
#define IGL_POLYMODE_RIGHT        1

//To identify skinned meshs and terrains from the classic mesh type
//This will disapear when we implement generic 3D Object Types...
#define IGL_MESH_CLASSIC          1
#define IGL_MESH_SKINNED          2
#define IGL_MESH_HEIGHTMAP        3

//Defines for 3D Objects selection
#define IGL_MODE_RENDER           1
#define IGL_MODE_SELECTION_PRIMI  2
#define IGL_MODE_SELECTION_MESHS  3
#define IGL_MODE_SELECTION_FACES  4

#define IGL_COR_R                 1
#define IGL_COR_G                 2
#define IGL_COR_B                 3
#define IGL_COR_A                 4

#define IGL_LIGHT_COLOR_AMB       1
#define IGL_LIGHT_COLOR_SPEC      2
#define IGL_LIGHT_COLOR_DIF       3

#define IGL_SHADING_MODE_FLAT     0
#define IGL_SHADING_MODE_SMOOTH   1
#define IGL_SHADING_MODE_DIFLAT   2
#define IGL_SHADING_MODE_DIFOTH   3
#define IGL_SHADING_MODE_NOONE    4

#define IGL_LIGHT_CHANNEL_01      0
#define IGL_LIGHT_CHANNEL_02      1
#define IGL_LIGHT_CHANNEL_03      2
#define IGL_LIGHT_CHANNEL_04      3
#define IGL_LIGHT_CHANNEL_05      4
#define IGL_LIGHT_CHANNEL_06      5
#define IGL_LIGHT_CHANNEL_07      6
#define IGL_LIGHT_CHANNEL_08      7
#define IGL_LIGHT_CHANNEL_09      8
#define IGL_LIGHT_CHANNEL_10      9

#define IGL_FACE_TRIANGLES        0
#define IGL_FACE_QUADS            1
#define IGL_FACE_POLYGON          2

#define IGL_FRAMEBUFFER_PIXEL     0

#define IGL_PLANO_TOPO            0
#define IGL_PLANO_ABAIXO          1
#define IGL_PLANO_ESQUERDO        2
#define IGL_PLANO_DIREITO         3
#define IGL_PLANO_FRENTE          4
#define IGL_PLANO_ATRAS           5

#define IGL_TRANSF_ROT            1
#define IGL_TRANSF_SCL            2
#define IGL_TRANSF_TRL            3

#define IGL_TEXTURE_CLAMP         1
#define IGL_TEXTURE_LINEAR        2
#define IGL_TEXTURE_GEN_ST        3
#define IGL_TEXTURE_CREATE        4
#define IGL_TEXTURE_PREP          5
#define IGL_TEXTURE_RENDER        6
#define IGL_TEXTURE_CUBEMAP       7


#define IGL_PAINEL_DEFAULT        1
#define IGL_PAINEL_FACES          2
#define IGL_PAINEL_RELEVO         3

//Shader Defines
#define IGL_VERTEX_SHADER_TYPE   0
#define IGL_FRAGMENT_SHADER_TYPE 1
#define IGL_GEOMETRY_SHADER_TYPE 2
#define IGL_TESSCTRL_SHADER_TYPE 3
#define IGL_TESSEVAL_SHADER_TYPE 4
#define IGL_COMPUTE_SHADER_TYPE  5

//Video Defines
#define IGL_VIDEO_SOURCE_CAMERA 0
#define IGL_VIDEO_SOURCE_FILE   1
#define IGL_VIDEO_SOURCE_IMAGES 2

#define IGL_VIDEO_STATUS_OPENERROR  0
#define IGL_VIDEO_STATUS_OPENOK     1
#define IGL_VIDEO_STATUS_PROCESSING 2
#define IGL_VIDEO_STATUS_FINISH     3

#define IGL_VIDEO_EXEC_ONESHOT      1
#define IGL_VIDEO_EXEC_LOOP         2
#define IGL_VIDEO_EXEC_FOREVER      3

//Material , Light and Textures Defines
#define IGL_ADD_MATERIAL  100
#define IGL_ADD_TEXTURA   101
#define IGL_PREP_MATERIAL 102

#define IGL_LAYER_CHN_DETAIL 0
#define IGL_LAYER_CHN_NMAP   1
#define IGL_LAYER_CHN_CBMAP  2
#define IGL_LAYER_CHN_LTMAP  3
#define IGL_LAYER_CHN_CLMAP  4

#define IGL_LIST_TYPE_SHADERS   0
#define IGL_LIST_TYPE_MATERIALS 1
#define IGL_LIST_TYPE_TEXTURES  2
#define IGL_LIST_TYPE_LIGHTS    3
#define IGL_LIST_TYPE_VIDEOS    4
#define IGL_LIST_TYPE_CAMERAS   5
#define IGL_LIST_TYPE_OBJECTS   6

enum IGLLIGHTTYPE
{
    LIGHTTYPE_POINT,
    LIGHTTYPE_SPOT,
    LIGHTTYPE_DIRECTIONAL,
    LIGHTTYPE_AMBIENT,
};

/*
struct IGLVertexBuffer
{
    CIMTVector  position;
    CIMTVector2 texCoord;
    CIMTVector  normal;
    CIMTVector  smooth;
    CIMTVector  tangente;
    CIMTVector  bitangente;
};
*/

struct FeedBackData
{
    CIMTVector  position;
};

//static const char * tf_varyings[] =
//{
//  "f_position"
//};

#endif // INSGL_GLOBAL_H
