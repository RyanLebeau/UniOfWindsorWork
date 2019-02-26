%AssignThree - Ryan Lebeau - 104535367
%Q3e
func=@(x) cosd(x)-(2*x);
A=0;
B=1;
tol=0.0001;
i=0;
epsilon=0.0000001;
sol=false;

while i<10
  c=B-((func(B)*(B-A))/(func(B)-func(A)));
  %disp(func(c));
  if(func(c)==0 || (B-A)<tol)
    text=['Iteration ',num2str(i+1),': Convergence at c=',num2str(c)];
    disp(text);
    sol=true;
    break;
  elseif(abs(func(A))<epsilon || abs(func(B))<epsilon)
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
  output='Solution not found.'
end