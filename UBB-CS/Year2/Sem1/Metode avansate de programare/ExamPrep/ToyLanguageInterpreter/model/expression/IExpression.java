package model.expression;

import exceptions.ADTException;
import exceptions.ExpressionEvaluationException;
import model.utils.MyIDictionary;
import model.value.Value;

public interface IExpression {
    Value eval(MyIDictionary<String,Value> table) throws ExpressionEvaluationException, ADTException;
    IExpression deepCopy();
}
