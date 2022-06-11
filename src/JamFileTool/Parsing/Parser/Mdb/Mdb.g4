grammar Mdb;

import Common;

root 
    :   materials
    ;

materials
    :   Materials '{' material* '}'
    ;

material 
    :   Material materialName '{' material_property* '}'
    ;

materialName
    :   StringLiteral
    ;

material_property
    :   colorMaterialProperty
    |   textMaterialProperty
    |   uint8MaterialProperty
    |   intMaterialProperty
    |   singleValueKeywords
    |   keyword2F
    |   keyword38
    ;

colorMaterialProperty
    :   colorMaterialPropertyKeyword IntegerConstant IntegerConstant IntegerConstant IntegerConstant
    ;

colorMaterialPropertyKeyword
    :   Color0
    |   Color1
    ;

textMaterialProperty
    :   textMaterialPropertyKeyword StringLiteral
    ;

textMaterialPropertyKeyword
    :   Texture
    ;

uint8MaterialProperty
    :   uint8MaterialPropertyKeyword IntegerConstant
    ;

uint8MaterialPropertyKeyword
    :   Opacity
    ;

intMaterialProperty
    :   intMaterialPropertyKeyword IntegerConstant
    ;

intMaterialPropertyKeyword
    :   Keyword4D
    |   Keyword4E
    |   Keyword4F
    |   Keyword50
    ;

singleValueKeywords
    :   Keyword2A
    |   Keyword2B
    |   Keyword2D
    |   Keyword2E
    |   Keyword44
    |   Keyword45
    |   Keyword47
    |   Keyword48
    |   Keyword49
    |   Keyword4A
    |   Keyword4B
    |   Keyword4C
    ;

keyword2F
    :   Keyword2F keyword2FSubtoken
    ;

keyword2FSubtoken
    :   Keyword30
    |   Keyword31 IntegerConstant
    |   Keyword32 IntegerConstant
    |   Keyword33 IntegerConstant
    |   Keyword34 IntegerConstant
    |   Keyword35 IntegerConstant
    |   Keyword36
    |   Keyword37 IntegerConstant
    ;

keyword38
    :   Keyword38 keyword38Subtoken keyword38Subtoken
    ;

keyword38Subtoken
    :   Keyword39
    |   Keyword3A
    |   Keyword3B
    |   Keyword3C
    |   Keyword3D
    |   Keyword3E
    |   Keyword3F
    |   Keyword40
    |   Keyword41
    |   Keyword42
    |   Keyword43
    ;

Materials: 'materials';
Material: 'material';
Color1 : 'color1';
Color0 : 'color0';
Keyword2A: 'keyword2A';
Keyword2B: 'keyword2B';
Texture: 'texture';
Keyword2D: 'keyword2D';
Keyword2E: 'keyword2E';
Keyword2F: 'keyword2F';
Keyword30: 'keyword30';
Keyword31: 'keyword31';
Keyword32: 'keyword32';
Keyword33: 'keyword33';
Keyword34: 'keyword34';
Keyword35: 'keyword35';
Keyword36: 'keyword36';
Keyword37: 'keyword37';
Keyword38: 'keyword38';
Keyword39: 'keyword39';
Keyword3A: 'keyword3A';
Keyword3B: 'keyword3B';
Keyword3C: 'keyword3C';
Keyword3D: 'keyword3D';
Keyword3E: 'keyword3E';
Keyword3F: 'keyword3F';
Keyword40: 'keyword40';
Keyword41: 'keyword41';
Keyword42: 'keyword42';
Keyword43: 'keyword43';
Keyword44: 'keyword44';
Keyword45: 'keyword45';
Opacity: 'opacity';
Keyword47: 'keyword47';
Keyword48: 'keyword48';
Keyword49: 'keyword49';
Keyword4A: 'keyword4A';
Keyword4B: 'keyword4B';
Keyword4C: 'keyword4C';
Keyword4D: 'keyword4D';
Keyword4E: 'keyword4E';
Keyword4F: 'keyword4F';
Keyword50: 'keyword50';