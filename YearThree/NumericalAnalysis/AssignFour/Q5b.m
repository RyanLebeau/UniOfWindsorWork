%AssignFour - Ryan Lebeau - 104535367
%Q5b
Xk=[1 2 3 4 5];
Yk=[2 3.1 4 4.8 5.9];
Xmean=mean(Xk);
Ymean=mean(Yk);
sumx2=(Xk-Xmean)*(Xk-Xmean)';
sumxy=(Yk-Ymean)*(Xk-Xmean)';
A=sumxy/sumx2;
B=Ymean-A*Xmean;
Fx=@(x) A*x+B;
text=['F(x)=',num2str(A),'x+',num2str(B)];
disp(text);


