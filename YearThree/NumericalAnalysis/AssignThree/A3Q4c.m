%AssignThree - Ryan Lebeau - 104535367
%Q4c
func=@(x) x^3-6*x^2+9*x;
funcd=@(x) 3*x^2-12*x+9;
Pi_1=2.5;i=0;
tol=0.00001;
epsilon=0.00000001;
sol=false;

while i<15
  Pi=Pi_1-(2*func(Pi_1)/funcd(Pi_1));
  %text=[num2str(Pi),' ',num2str(Pi_1),' ',num2str(abs(Pi-Pi_1))];
  %disp(text);
  if(abs(Pi-Pi_1)<=tol || abs(func(Pi))<epsilon)
    text=['Iteration ',num2str(i+1),': Convergence at P=',num2str(Pi)];
    disp(text);
    sol=true;
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
Using the order of the root(2) drastically increases the rate
of convergence. Instead of the previous 13 iterations, it now
takes 3 iterations.
%}