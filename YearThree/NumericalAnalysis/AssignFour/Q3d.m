%AssignFour - Ryan Lebeau - 104535367
%Q3d
X=[0;1;2;3;4;5];
Y=[5;5;3;5;17;45];
c=[];d=[];
[c,d]=DNfunc(X,Y);
text=['The divided difference table is'];disp(text);disp(d);
text=['The Newton polynomial coefficients are'];disp(text);disp(c);
