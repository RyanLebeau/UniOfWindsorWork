%AssignThree - Ryan Lebeau - 104535367
%Q4b
func=@(x) x^3-6*x^2+9*x;
funcd=@(x) 3*x^2-12*x+9;
Pi_1=2.5;i=0;
tol=0.0001;
epsilon=0.00000001;
sol=false;

while i<15
  Pi=Pi_1-(func(Pi_1)/funcd(Pi_1));
  %text=[num2str(Pi),' ',num2str(Pi_1),' ',num2str(abs(Pi-Pi_1))];
  %disp(text);
  if(abs(Pi-Pi_1)<=tol)
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
%{
This convergence is linear since it takes over 10 iterations
to reach an accurate convergence at not nearly a quadratic increase.
Increasing by 10^-4 for 7 iterations is slow and linear.
%}