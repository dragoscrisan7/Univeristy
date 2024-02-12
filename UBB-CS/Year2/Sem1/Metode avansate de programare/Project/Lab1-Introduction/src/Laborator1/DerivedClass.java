package Laborator1;

public class DerivedClass extends BaseClass{
    String name;
    public DerivedClass(String name) {
        super(name);
    }

    @Override
    public String toString() {
        return "DC: " + super.toString();
    }
}
