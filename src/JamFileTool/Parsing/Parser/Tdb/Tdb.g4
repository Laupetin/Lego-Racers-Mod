grammar Tdb;
import Common;

root 
    :   textures
    ;

textures
    :   Textures '{' texture* '}'
    ;

texture 
    :   Texture textureName '{' textureProperty* '}'
    ;

textureName
    :   StringLiteral
    ;

textureProperty
    :   colorTextureProperty
    |   intTextureProperty
    |   singleValueKeywords
    ;

colorTextureProperty
    :   colorTexturePropertyKeyword IntegerConstant IntegerConstant IntegerConstant
    ;

colorTexturePropertyKeyword
    :   ChromaKey
    ;

intTextureProperty
    :   intTexturePropertyKeyword IntegerConstant
    ;

intTexturePropertyKeyword
    :   Keyword29
    ;

singleValueKeywords
    :   FlipVertically
    |   Bmp
    |   Tga
    |   Keyword2D
    |   Keyword2E
    ;

Textures: 'textures';
Texture: 'texture';
FlipVertically: 'flipVertically';
Keyword29: 'keyword29';
Bmp: 'bmp';
Tga: 'tga';
ChromaKey: 'chromaKey';
Keyword2D: 'keyword2D';
Keyword2E: 'keyword2E';
