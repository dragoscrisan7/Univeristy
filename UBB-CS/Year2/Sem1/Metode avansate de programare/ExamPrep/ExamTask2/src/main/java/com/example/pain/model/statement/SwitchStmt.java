package com.example.pain.model.statement;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyIDictionary;
import com.example.pain.model.adt.MyIStack;
import com.example.pain.model.adt.PrgState;
import com.example.pain.model.expression.Exp;
import com.example.pain.model.expression.RelExp;
import com.example.pain.model.type.Type;

public class SwitchStmt implements IStmt{
    private final Exp mainExpression;
    private final Exp expression1;
    private final IStmt statement1;
    private final Exp expression2;
    private final IStmt statement2;
    private final IStmt defaultStatement;

    public SwitchStmt(Exp mainExpression, Exp expression1, IStmt statement1, Exp expression2, IStmt statement2, IStmt defaultStatement) {
        this.mainExpression = mainExpression;
        this.expression1 = expression1;
        this.statement1 = statement1;
        this.expression2 = expression2;
        this.statement2 = statement2;
        this.defaultStatement = defaultStatement;
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> exeStack = state.getStk();
        IStmt converted = new IfStmt(new RelExp("==", mainExpression, expression1),
                statement1, new IfStmt(new RelExp("==", mainExpression, expression2), statement2, defaultStatement));
        exeStack.push(converted);
        state.setExeStack(exeStack);
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type mainType = mainExpression.typecheck(typeEnv);
        Type type1 = expression1.typecheck(typeEnv);
        Type type2 = expression2.typecheck(typeEnv);
        if (mainType.equals(type1) && mainType.equals(type2)) {
            statement1.typecheck(typeEnv.deepCopy());
            statement2.typecheck(typeEnv.deepCopy());
            defaultStatement.typecheck(typeEnv.deepCopy());
            return typeEnv;
        } else {
            throw new MyException("The expression types don't match in the switch statement!");
        }
    }

    @Override
    public IStmt deepCopy() {
        return new SwitchStmt(mainExpression.deepCopy(), expression1.deepCopy(), statement1.deepCopy(), expression2.deepCopy(), statement2.deepCopy(), defaultStatement.deepCopy());
    }

    @Override
    public String toString() {
        return String.format("switch(%s){(case(%s): %s)(case(%s): %s)(default: %s)}", mainExpression, expression1, statement1, expression2, statement2, defaultStatement);
    }
}
