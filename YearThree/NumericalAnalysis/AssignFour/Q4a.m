%AssignFour - Ryan Lebeau - 104535367
%Q4a
fx=@(x) e^(-1)*x;
Xk=[-2;-1;0;1;2];
B=[fx(Xk(1));fx(Xk(2));fx(Xk(3));fx(Xk(4));fx(Xk(5))];
A=[1 -2 4 -8 16;1 -1 1 -1 1;1 0 0 0 0;1 1 1 1 1;1 2 4 8 16];
X=A\B;
P=@(x) X(1)+X(2)*x+X(3)*x+X(4)*x+X(5)*x;
P(0.5)
