grammar Idb;
import Common;

root 
    :   images
    ;

images
    :   Images '{' image* '}'
    ;

image 
    :   Image imageName '{' imageProperty* '}'
    ;

imageName
    :   StringLiteral
    ;

imageProperty
    :   colorImageProperty
    |   singleValueKeywords
    ;

colorImageProperty
    :   colorImagePropertyKeyword IntegerConstant IntegerConstant IntegerConstant
    ;

colorImagePropertyKeyword
    :   ChromaKey
    |   Tint
    ;

singleValueKeywords
    :   FlipVertical
    |   Bmp
    |   Tga
    ;

Images: 'images';
Image: 'image';
FlipVertical: 'flipVertical';
Bmp: 'bmp';
Tga: 'tga';
ChromaKey : 'chromaKey';
Tint : 'tint';
