package model.expression;

import exception.MyException;
import model.adt.MyIDictionary;
import model.adt.MyIHeap;
import model.type.BoolType;
import model.type.IntType;
import model.type.Type;
import model.value.BoolValue;
import model.value.IntValue;
import model.value.Value;

import java.util.Objects;

public class LogicExp implements Exp{
    Exp e1;
    Exp e2;
    int op;

    public LogicExp(String  c, Exp e1, Exp e2) {
        if(Objects.equals(c, "&&")){
            this.op = 1;
        } else if (Objects.equals(c, "||")) {
            this.op = 2;
        }
        this.e1 = e1;
        this.e2 = e2;
    }

    public Value eval(MyIDictionary<String, Value> tbl, MyIHeap<Integer,Value> heap) throws MyException {
        Value v1,v2;
        v1 = e1.eval(tbl, heap);
        if(v1.getType().equals(new IntType())){
            v2 = e2.eval(tbl, heap);
            if(v2.getType().equals(new IntType())){
                BoolValue bool1 = (BoolValue) v1;
                BoolValue bool2 = (BoolValue) v2;
                boolean b1,b2;
                b1 = bool1.getVal();
                b2 = bool2.getVal();
                if(Objects.equals(this.op, "&&"))
                    return new BoolValue(b1 && b2);
                else if (Objects.equals(this.op, "||"))
                    return new BoolValue(b1 || b2);
            }
            else {
                throw new MyException("Second operand is not a boolean.");
            }
        }
        else {
            throw new MyException("First operand is not a boolean.");
        }
        return null;
    }

    public Exp getE1() {
        return e1;
    }

    public void setE1(Exp e1) {
        this.e1 = e1;
    }

    public Exp getE2() {
        return e2;
    }

    public void setE2(Exp e2) {
        this.e2 = e2;
    }

    public int getOp() {
        return op;
    }

    public void setOp(int op) {
        this.op = op;
    }

    public String toString() {
        return e1 + " " + convertOperation(op) + " " + op;
    }
    String convertOperation(int op){
        if(op == 1) return "&&";
        if(op == 2) return "||";

        return " ";
    }

    public Exp deepCopy() {
        return new LogicExp(convertOperation(op), e1.deepCopy(), e2.deepCopy());
    }

    public Type typecheck(MyIDictionary<String,Type> typeEnv) throws MyException{
        Type typ1, typ2;
        typ1=e1.typecheck(typeEnv);
        typ2=e2.typecheck(typeEnv);
        if(typ1.equals(new BoolType())) {
            if(typ2.equals(new BoolType())) {
                return new BoolType();
            }
            else
                throw new MyException("second operand is not a boolean");
        }else
            throw new MyException("first operand is not a boolean");
    }
}
