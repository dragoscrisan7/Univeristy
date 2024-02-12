package com.example.pain.exception;

public class MyException extends RuntimeException {
    public MyException(String message){
        super(message);
    }
    public MyException(){
        super();
    }
}