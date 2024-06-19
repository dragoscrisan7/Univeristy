package model.expression;

import exception.MyException;
import model.adt.MyIDictionary;
import model.adt.MyIHeap;
import model.type.IntType;
import model.type.Type;
import model.value.IntValue;
import model.value.Value;

public class ArithExp implements Exp{
    Exp e1;
    Exp e2;
    int op; //1-plus, 2-minus, 3-star, 4-divide

    public ArithExp(char c, Exp e1, Exp e2) {
        if(c == '+'){
            this.op = 1;
        } else if (c == '-') {
            this.op = 2;
        } else if (c == '*') {
            this.op = 3;
        } else if (c == '/') {
            this.op = 4;
        }
        this.e1 = e1;
        this.e2 = e2;
    }
    public Value eval(MyIDictionary<String, Value> tbl, MyIHeap<Integer,Value> heap) throws MyException {
        Value v1, v2;
        v1 = e1.eval(tbl, heap);
        if (v1.getType().equals(new IntType())) {
            v2 = e2.eval(tbl, heap);
            if (v2.getType().equals(new IntType())) {
                IntValue i1 = (IntValue) v1;
                IntValue i2 = (IntValue) v2;
                int n1, n2;
                n1 = i1.getVal();
                n2 = i2.getVal();
                if (op == 1) return new IntValue(n1 + n2);
                if (op == 2) return new IntValue(n1 - n2);
                if (op == 3) return new IntValue(n1 * n2);
                if (op == 4)
                    if (n2 == 0) throw new MyException("division by zero");
                    else return new IntValue(n1 / n2);
            }
            else
                throw new MyException("second operand is not an integer");
        }
        else
            throw new MyException("first operand is not an integer");
        return null;
    }

    public String toString() {
        return e1 + " " + convertOperation(op) + " " + e2 ;
    }

    char convertOperation(int op){
        if(op == 1) return '+';
        if(op == 2) return '-';
        if(op == 3) return '*';
        if(op == 4) return '/';

        return ' ';
    }

    public Exp deepCopy() {
        return new ArithExp(convertOperation(op), e1.deepCopy(), e2.deepCopy());
    }

    public Type typecheck(MyIDictionary<String,Type> typeEnv) throws MyException{
        Type typ1, typ2;
        typ1=e1.typecheck(typeEnv);
        typ2=e2.typecheck(typeEnv);
        if(typ1.equals(new IntType())) {
            if(typ2.equals(new IntType())) {
                return new IntType();
            }
            else
                throw new MyException("second operand is not an integer");
        }else
            throw new MyException("first operand is not an integer");
    }
}
