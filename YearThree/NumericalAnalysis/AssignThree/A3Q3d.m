%AssignThree - Ryan Lebeau - 104535367
%Q3d
func=@(x) cosd(x)-(2*x);
A=0;
B=1;
tol=0.00001;
i=0;
sol=false;

while i<20
  c=(A+B)/2;
  if(func(c)==0 || (B-A)<tol)
    text=['Iteration ',num2str(i+1),': Convergence at c=',num2str(c)];
    disp(text);
    sol=true;
    break;
  elseif(func(c)<0)
    A=c;
  elseif(func(c)>0)
    B=c;
  end
  text=['Iteration ',num2str(i+1),': c=',num2str(c),' new interval [',num2str(A),',',num2str(B),']'];
  disp(text);
  i=i+1;
end

if(sol==false)
  output='20 iterations complete.'
end