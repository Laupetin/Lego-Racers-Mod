grammar Gdb;
import Common;

root 
    :   sections
    ;

sections
    :   materialSection scaleSection? (vertexSection faceSection)? metaSection?
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
    :   Scale floatOrIntConstant
    ;

vertexSection
    :   Vertices '{' vertexList? '}'
    ;

vertexList
    :   vertexDefPositionUvColor+
    |   vertexDefPositionUvNormal+
    |   vertexDefPositionUv+
    |   vertexDefPosition+
    ;

vertexDefPosition
    : vertexPosition
    ;

vertexDefPositionUv
    :   vertexPosition
        vertexUv
    ;

vertexDefPositionUvColor
    :   vertexPosition
        vertexUv
        vertexColor
    ;

vertexDefPositionUvNormal
    :   vertexPosition
        vertexUv
        vertexNormal
    ;

vertexPosition
    :   Vertex floatOrIntConstant floatOrIntConstant floatOrIntConstant
    ;

vertexUv
    :   Uv floatOrIntConstant floatOrIntConstant
    ;

vertexColor
    :   Color IntegerConstant IntegerConstant IntegerConstant IntegerConstant
    ;

vertexNormal
    :   Normal floatOrIntConstant floatOrIntConstant floatOrIntConstant
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
