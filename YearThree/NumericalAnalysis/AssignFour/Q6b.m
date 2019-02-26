%AssignFour - Ryan Lebeau - 104535367
%Q6b
Fx=@(x) A/x;
Xk=[0.5 1 1.5 2];
Yk=[7.1 3.7 2.6 2];
A=0;
B=0;
for i=1:1:4
  if(i<=4)
    A=A+Yk(i)/Xk(i);
    B=B+Xk(i)^(-2);
  endif
endfor
A=A/B;
text=['f(x)=',num2str(A),'/x'];
disp(text);
