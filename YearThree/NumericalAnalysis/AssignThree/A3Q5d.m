%AssignThree - Ryan Lebeau - 104535367
%Q5d
funcy=@(x) (3-2*x)/2;
funcx=@(y) sqrt((4-2*y)/3);
y=0;x=0;i=0;
tol=0.0001;
sol=false;

while i<10
  xPrev=x;
  yPrev=y;
  x=funcx(y);
  y=funcy(x);
  if(abs(x-xPrev)<tol || abs(y-yPrev)<tol)
    text=['Iteration ',num2str(i+1),': Convergence x=',num2str(x),' y=',num2str(y)];
    disp(text);
    sol=true;
    break;
  end
  text=['Iteration ',num2str(i+1),': x=',num2str(x),' y=',num2str(y)];
  disp(text);
  i=i+1;
endwhile
if (sol==false)
  disp('No convergence');
endif
