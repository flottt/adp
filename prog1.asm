LDK 1  //ADP Vorlesung 2 Seite 16
STA 1  //int eins = 1

LDK 0
STA 3  //int sum = 0           //&sum = 3 

INP 2 //int i = readEingabe(); //&i = 2
LDA 2
STA 4 //int n = i              //&n = 4

//for (int i = n; i > 0; i--) 
:ForSprung1 
LDA 2 // x = i
MUL 2 // x *= i
ADD 3 // x += sum 
STA 3 // gesamt: sum += i * i 

LDA 2 
SUB 1 
STA 2 //i--

JGZ ForSprung1  //if (i > 0) then continue; 

OUT 3 //print sum
HLT 99