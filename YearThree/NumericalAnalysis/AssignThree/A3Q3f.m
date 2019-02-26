%AssignThree - Ryan Lebeau - 104535367
%Q3f
func=@(x) cosd(x)-(2*x);
Pi_2=0;
Pi_1=1;
tol=0.0001;
i=0;
epsilon=0.0000001;
sol=false;

while i<10
  Pi=Pi_1-((func(Pi_1)*(Pi_1-Pi_2))/(func(Pi_1)-func(Pi_2)));
  %text=[num2str(Pi),num2str(Pi_1),num2str(Pi_2)];
  %disp(text);
  if(abs(Pi-Pi_1)<tol)
    text=['Iteration ',num2str(i+1),': Convergence at P=',num2str(Pi)];
    disp(text);
    sol=true;
    break;
  elseif(abs(func(Pi))<epsilon)
    break;
  else
    Pi_2=Pi_1;
    Pi_1=Pi;
  end
  text=['Iteration ',num2str(i+1),': P=',num2str(Pi)];
  disp(text);
  i=i+1;
end

if(sol==false)
  disp('Solution not found.');
end