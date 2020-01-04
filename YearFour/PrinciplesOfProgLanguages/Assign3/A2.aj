import java.util.*;

public aspect A2 {
  int exprNum = 0;
  public Hashtable<String, Expr> varTable;
  
  String getTabs(int tabs) 
  {
    String res = "";
    for (int i = 0; i < tabs; ++i) 
	{
      res += "   "; }
    return res; }
	
  Integer preformOp(String op, Integer right, Integer left) 
  {
    if (op.equals("+")) {
      return new Integer(right.intValue() + left.intValue());
    }
    if (op == "*") {
      return new Integer(right.intValue() * left.intValue());
    }
    System.out.println("--" + op + "--");
    return null; }

  Integer evalExpr(int tabLevel, Expr e) 
  {
    if (e.isPrimitive()) {
      if (e.getValue() != null) 
	  {
        System.out.print(getTabs(tabLevel) + e.getValue() + " ==> ?\n" +
					getTabs(tabLevel) + e.getValue() + " ==> " + e.getValue() + "\n");
        return e.getValue(); } 
	  else 
	  {
        System.out.print(getTabs(tabLevel) +  e.getID() + " ==> ?\n");
        Integer res = evalExpr(tabLevel+1, varTable.get(e.getID()));
        System.out.print(getTabs(tabLevel) +  e.getID() + " ==> " + res.intValue() + "\n");
        e.setValue(res);
        return res; } } 
	else 
	{
      System.out.print(getTabs(tabLevel) + getPlainStringFromExpr(e, false) + " ==> ?\n");
	  Integer left = evalExpr(tabLevel+1, e.getRight());
      Integer right = evalExpr(tabLevel+1, e.getLeft());
      Integer res = preformOp(e.getOp(), right, left);
      System.out.print(getTabs(tabLevel) + getPlainStringFromExpr(e, false) + " ==> " + res.intValue() + "\n");
      return res; } }

  String getPlainStringFromExpr(Expr e, boolean count) 
  {
    String res;
    if (count) 
      exprNum++;
    
    if (e.isPrimitive()) 
	{
      if (e.getValue() == null) 
	  {
        return e.getID(); } 
		else 
		{
        return e.getValue().toString(); } }
    res = "(" + getPlainStringFromExpr(e.getLeft(), count) + " " + e.getOp() + " " + getPlainStringFromExpr(e.getRight(), count) + ")";
    return res; }
	
  void around() : call(* *.print*(..)) && !within(A2) {}
  before(Program prog) : execution(String Program.toString()) && target(prog) && !within(A2) {
    varTable = prog.varTable;
    int i = 0;
    for (int j = prog.getStatements().size()-1; j >= 0; j--) {
      Statement s = prog.getStatements().get(j);
      if (s instanceof Assignment) {
        Assignment a = (Assignment)s;
        System.out.println("\nAssignment " + (i++) + " is: " +
        a.getLHS() + " = " + getPlainStringFromExpr(a.getRHS(), true) + ";");
        evalExpr(1, a.getRHS());
      }
    }
    System.out.println("\n" + exprNum + " expressions.");
  }

}