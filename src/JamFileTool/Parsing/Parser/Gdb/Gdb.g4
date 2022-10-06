grammar Gdb;
import Common;

root 
    :   sections
    ;

sections
    :   materialSection scaleSection? vertexSection faceSection metaSection?
    ;

materialSection
    :   Materials '{' materialNameList? '}'
    ;

materialNameList 
    :   materialName+
    ;

materialName
    :   StringLiteral
    ;

scaleSection
    :   Scale FloatingConstant
    ;

vertexSection
    :   Vertices '{' vertexList? '}'
    ;

vertexList
    :   vertexPosition+
    |   vertexPositionUv+
    |   vertexPositionUvColor+
    |   vertexPositionUvNormal+
    ;

vertexPositionUv
    :   vertexPosition
        vertexUv
    ;

vertexPositionUvColor
    :   vertexPosition
        vertexUv
        vertexColor
    ;

vertexPositionUvNormal
    :   vertexPosition
        vertexUv
        vertexNormal
    ;

vertexPosition
    :   Vertex FloatingConstant FloatingConstant FloatingConstant
    ;

vertexUv
    :   Uv FloatingConstant FloatingConstant
    ;

vertexColor
    :   Color FloatingConstant FloatingConstant FloatingConstant
    ;

vertexNormal
    :   Normal FloatingConstant FloatingConstant FloatingConstant
    ;

faceSection
    :   Faces '{' faceList? '}'
    ;

faceList
    :   face+
    ;

face
    :   Face IntegerConstant IntegerConstant IntegerConstant
    ;

metaSection
    :   Meta '{' metaList? '}'
    ;

metaList
    :   meta+
    ;

meta
    :   keyword31
    |   keyword2D
    |   keyword2F
    |   keyword30
    |   keyword32
    |   keyword27
    ;

keyword31
    :   Keyword31 IntegerConstant IntegerConstant IntegerConstant
    ;

keyword2D
    :   Keyword2D IntegerConstant IntegerConstant
    ;

keyword2F
    :   Keyword2F IntegerConstant
    ;

keyword30
    :   Keyword30
    ;

keyword32
    :  Keyword32 IntegerConstant
    ;

keyword27
    : Keyword27 IntegerConstant
    ;
    
Materials: 'materials';
Scale: 'scale';
Vertices: 'vertices';
Faces: 'faces';
Meta: 'meta';
Vertex : 'v';
Uv : 'uv';
Color: 'clr';
Normal: 'vn';
Texture: 'texture';
Face: 'f';
Keyword27: 'keyword27';
Keyword2D: 'keyword2D';
Keyword2F: 'keyword2F';
Keyword30: 'keyword30';
Keyword31: 'keyword31';
Keyword32: 'keyword32';
