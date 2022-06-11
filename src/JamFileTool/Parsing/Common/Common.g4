grammar Common;

IntegerConstant
    :   DecimalConstant
    |   HexadecimalConstant
    |   Zero
    ;

fragment
DecimalConstant
    :   IntegerSign? NonzeroDigit Digit*
    ;

fragment
HexadecimalConstant
    :   IntegerSign? HexadecimalPrefix HexadecimalDigit+
    ;

fragment
HexadecimalPrefix
    :   '0' [xX]
    ;

fragment
NonzeroDigit
    :   [1-9]
    ;

fragment
Digit
    :   [0-9]
    ;

fragment
HexadecimalDigit
    :   [0-9a-fA-F]
    ;

fragment
Zero
    :   IntegerSign? '0'
    ;

fragment
IntegerSign
    :   '+'
    |   '-'
    ;

StringLiteral
    :   '"' SCharSequence? '"'
    ;

fragment
SCharSequence
    :   SChar+
    ;

fragment
SChar
    :   ~["\\\r\n]
    |   EscapeSequence
    |   '\\\n'   // Added line
    |   '\\\r\n' // Added line
    ;

fragment
EscapeSequence
    :   '\\' ['"?abfnrtv\\]
    ;

Whitespace
    :   [ \t]+
        -> skip
    ;

Newline
    :   (   '\r' '\n'?
        |   '\n'
        )
        -> skip
    ;

BlockComment
    :   '/*' .*? '*/'
        -> skip
    ;

LineComment
    :   '//' ~[\r\n]*
        -> skip
    ;