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
    :   metaVertices
    |   metaFaces
    |   keyword2F
    |   keyword30
    |   metaBone
    |   metaObject
    ;

metaVertices
    :   Vertices IntegerConstant IntegerConstant IntegerConstant
    ;

metaFaces
    :   Faces IntegerConstant IntegerConstant
    ;

keyword2F
    :   Keyword2F IntegerConstant
    ;

keyword30
    :   Keyword30
    ;

metaBone
    :  Bone IntegerConstant
    ;

metaObject
    : Object IntegerConstant
    ;
    
Materials: 'materials';
Scale: 'scale';
Vertices: 'vertices';
Faces: 'faces';
Meta: 'meta';
Object: 'object';
Vertex : 'v';
Uv : 'uv';
Color: 'clr';
Normal: 'vn';
Texture: 'texture';
Face: 'f';
Keyword2F: 'keyword2F';
Keyword30: 'keyword30';
Bone: 'bone';
