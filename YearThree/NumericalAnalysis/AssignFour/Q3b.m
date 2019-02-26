%AssignFour - Ryan Lebeau - 104535367
%Q3b
X=[0;1;2];
Y=[5;5;3];

lgPoly1=@(x) Y(1)*(((x-X(2))*(x-X(3)))/((X(1)-X(2))*(X(1)-X(3))));
lgPoly2=@(x) Y(2)*(((x-X(1))*(x-X(3)))/((X(2)-X(1))*(X(2)-X(3))));
lgPoly3=@(x) Y(3)*(((x-X(1))*(x-X(2)))/((X(3)-X(1))*(X(3)-X(2))));
lgPolyFinal=@(x) lgPoly1(x) + lgPoly2(x) + lgPoly3(x);