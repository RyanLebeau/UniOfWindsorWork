%AssignThree - Ryan Lebeau - 104535367
%Q3g
func=@(x) cosd(x)-(2*x);
funcd=@(x) -1*sind(x)-2;
Pi_1=0;
tol=0.0001;
i=0;
epsilon=0.0000001;
sol=false;

while i<10
  Pi=Pi_1-(func(Pi_1)/funcd(Pi_1));
  %text=[num2str(Pi),' ',num2str(Pi_1)];
  %disp(text);
  if(abs(Pi-Pi_1)<tol)
    text=['Iteration ',num2str(i+1),': Convergence at P=',num2str(Pi)];
    disp(text);
    sol=true;
    break;
  elseif(abs(func(Pi))<epsilon)
    break;
  else
    Pi_1=Pi;
  end
  text=['Iteration ',num2str(i+1),': P=',num2str(Pi)];
  disp(text);
  i=i+1;
end

if(sol==false)
  disp('Solution not found.');
end