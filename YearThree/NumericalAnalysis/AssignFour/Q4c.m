%AssignFour - Ryan Lebeau - 104535367
%Q4c
fx=@(x) e^(-1)*x;
X=[-2 -1 0 1 2];
Y=[fx(X(1)) fx(X(2)) fx(X(3)) fx(X(4)) fx(X(5))];
c=[];d=[];
[c,d]=DNfunc(X,Y);
text=['The divided difference table is'];disp(text);disp(d);
text=['The Newton polynomial coefficients are'];disp(text);disp(c);
%P=@(x) c(5)+c(4)*(x-X(1))+c(3)*(x-X(1))*(x-X(2))+c(2)*(x-X(1))*(x-X(2))*(x-X(3))+c(1)*(x-X(1))*(x-X(2))*(x-X(3))*(x-X(4));
P=@(x) (c(1)*x^4)+(c(2)*x^3)+(c(3)*x^2)+(c(4)*x)+c(5);
P(0.5)