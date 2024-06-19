package Laborator1;

public class Clasa1 {
    public static void main(String[] args) {
        Integer sum = 0;
        Integer leng = args.length;
        for(int i = 0; i < leng; i++) {
            sum += Integer.parseInt(args[i]);
        }
        System.out.println(sum/leng);

        BaseClass bc = new BaseClass("a");
        System.out.println(bc.toString());

        DerivedClass dc = new DerivedClass("b");
        System.out.println(dc.toString());

        BaseClass bc1 = new BaseClass("c");
        bc1.increment();
        System.out.println(bc1.toString());
        bc.increment();
        BaseClass.increment();
        System.out.println(bc1.toString());

        try {
            int a = 5/0;
        }
        catch(Exception e) {
            System.out.println(e.toString());
        }
    }
}

