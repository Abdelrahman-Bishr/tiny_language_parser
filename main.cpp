#include "mainwindow.h"
#include <QApplication>
// zz IDENTIFIER
// := ASSIGN
// 9 NUMBER
// * MULT
// 10 NUMBER


int main(int argc, char *argv[]){

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}

/*
read , READ
x , IDENTIFIER
; , SEMICOLOMN
if , IF
0 , number
< , LESS THAN
x , IDENTIFIER
then , THEN
fact , FACT
:= , ASSIGN
1 , number
; , SEMICOLOMN
repeat , REPEAT
fact , FACT
:= , ASSIGN
fact , FACT
* , MULTIPLICATION
x , IDENTIFIER
; , SEMICOLOMN
x , IDENTIFIER
:= , ASSIGN
- , MINUS
1 , number
until , UNTIL
x , IDENTIFIER
= , EQUAL
0 , number
; , SEMICOLOMN
write , WRITE
fact , FACT
end , END
*/


/*
X , IDENTIFIER
:= , ASSIGN
5 , NUMBER
* , MULT
( , OPENBRACKET
6,NUMBER
+,PLUS
10,NUMBER
) , CLOSEBRACKET
;,SEMICOLON

*/
