package Laborator1;

public class BaseClass {
    String name;
    private static Integer nr = 0;
    //constructor
    public BaseClass(String name) {
        this.name = name;
    }

    public String toString() {
        return this.name + " " + nr;
    }
    public static void increment() {
        nr += 1;
    }
}
