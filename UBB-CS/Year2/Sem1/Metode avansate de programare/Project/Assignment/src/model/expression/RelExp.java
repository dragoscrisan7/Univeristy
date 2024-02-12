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

public class RelExp implements Exp{
    Exp e1;
    Exp e2;
    int op;

    public RelExp(String  c, Exp e1, Exp e2) {
        if(Objects.equals(c, "<")){
            this.op = 1;
        } else if (Objects.equals(c, ">")) {
            this.op = 2;
        }else if (Objects.equals(c, "<=")) {
            this.op = 3;
        }else if (Objects.equals(c, ">=")) {
            this.op = 4;
        }else if (Objects.equals(c, "==")) {
            this.op = 5;
        }else if (Objects.equals(c, "!=")) {
            this.op = 6;
        }
        this.e1 = e1;
        this.e2 = e2;
    }

    public Exp getE1() {
        return e1;
    }

    public Exp getE2() {
        return e2;
    }

    public int getOp() {
        return op;
    }

    public void setE1(Exp e1) {
        this.e1 = e1;
    }

    public void setE2(Exp e2) {
        this.e2 = e2;
    }

    public void setOp(int op) {
        this.op = op;
    }

    @Override
    public Value eval(MyIDictionary<String, Value> tbl, MyIHeap<Integer,Value> heap) throws MyException {
        Value v1,v2;
        v1 = e1.eval(tbl, heap);
        if(v1.getType().equals(new IntType())){
            v2 = e2.eval(tbl, heap);
            if(v2.getType().equals(new IntType())){
                IntValue iv1 = (IntValue) v1;
                IntValue iv2 = (IntValue) v2;
                int i1 = iv1.getVal(), i2 = iv2.getVal();
                switch (op){
                    case 1:
                        return new BoolValue(i1 < i2);
                    case 2:
                        return new BoolValue(i1 > i2);
                    case 3:
                        return new BoolValue(i1 <= i2);
                    case 4:
                        return new BoolValue(i1 >= i2);
                    case 5:
                        return new BoolValue(i1 == i2);
                    case 6:
                        return new BoolValue(i1 != i2);
                }

            }
            else {
                throw new MyException("Second operand is not an int.");
            }
        }
        else {
            throw new MyException("First operand is not an int.");
        }
        return null;
    }

    public String toString() {
        return e1 + " " + convertOperation(op) + " " + e2;
    }

    String convertOperation(int op){
        if(op == 1) return "<";
        if(op == 2) return ">";
        if(op == 3) return "<=";
        if(op == 4) return ">=";
        if(op == 5) return "==";
        if(op == 6) return "!=";

        return " ";
    }

    @Override
    public Exp deepCopy() {
        return new RelExp(convertOperation(op),e1.deepCopy(),e2.deepCopy());
    }

    public Type typecheck(MyIDictionary<String,Type> typeEnv) throws MyException{
        Type typ1, typ2;
        typ1=e1.typecheck(typeEnv);
        typ2=e2.typecheck(typeEnv);
        if(typ1.equals(new IntType())) {
            if(typ2.equals(new IntType())) {
                return new BoolType();
            }
            else
                throw new MyException("second operand is not an integer");
        }else
            throw new MyException("first operand is not an integer");
    }
}
