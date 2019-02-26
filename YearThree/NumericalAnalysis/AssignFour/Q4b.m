%AssignFour - Ryan Lebeau - 104535367
%Q4b
fx=@(x) e^(-1)*x;
X=[-2 -1 0 1 2];
Y=[fx(X(1)) fx(X(2)) fx(X(3)) fx(X(4)) fx(X(5))];

lgPoly1=@(x) Y(1)*(((x-X(2))*(x-X(3))*(x-X(4))*(x-X(5)))/((X(1)-X(2))*(X(1)-X(3))*(X(1)-X(4))*(X(1)-X(5))));
lgPoly2=@(x) Y(2)*(((x-X(1))*(x-X(3))*(x-X(4))*(x-X(5)))/((X(2)-X(1))*(X(2)-X(3))*(X(2)-X(4))*(X(2)-X(5))));
lgPoly3=@(x) Y(3)*(((x-X(1))*(x-X(2))*(x-X(4))*(x-X(5)))/((X(3)-X(1))*(X(3)-X(2))*(X(3)-X(4))*(X(3)-X(5))));
lgPoly4=@(x) Y(4)*(((x-X(1))*(x-X(2))*(x-X(3))*(x-X(5)))/((X(4)-X(1))*(X(4)-X(2))*(X(4)-X(3))*(X(4)-X(5))));
lgPoly5=@(x) Y(4)*(((x-X(1))*(x-X(2))*(x-X(3))*(x-X(4)))/((X(5)-X(1))*(X(5)-X(2))*(X(5)-X(3))*(X(5)-X(4))));
lgPolyFinal=@(x) lgPoly1(x) + lgPoly2(x) + lgPoly3(x) + lgPoly4(x) + lgPoly5(x);
lgPolyFinal(0.5)