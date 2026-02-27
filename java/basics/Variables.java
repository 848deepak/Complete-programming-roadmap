/**
 * MODULE 01 | BASICS → Variables & Data Types (Java)
 * Compile: javac Variables.java && java Variables
 */
public class Variables {
    public static void main(String[] args) {

        System.out.println("=== PRIMITIVE TYPES ===");
        byte b = 127;
        short sh = 32767;
        int i = 2147483647;
        long l = 9223372036854775807L;
        float f = 3.14f;
        double d = 3.141592653589793;
        char c = 'A';
        boolean flag = true;

        System.out.printf("%-12s %d%n", "byte:", b);
        System.out.printf("%-12s %d%n", "short:", sh);
        System.out.printf("%-12s %d%n", "int:", i);
        System.out.printf("%-12s %d%n", "long:", l);
        System.out.printf("%-12s %.2f%n", "float:", f);
        System.out.printf("%-12s %.15f%n", "double:", d);
        System.out.printf("%-12s %c (ASCII %d)%n", "char:", c, (int) c);
        System.out.printf("%-12s %b%n", "boolean:", flag);

        System.out.println("\n=== WRAPPER CLASSES ===");
        System.out.println("Integer.MAX_VALUE  = " + Integer.MAX_VALUE);
        System.out.println("Integer.MIN_VALUE  = " + Integer.MIN_VALUE);
        System.out.println("Integer.parseInt   = " + Integer.parseInt("123"));
        System.out.println("Integer.toBinaryString(10) = " + Integer.toBinaryString(10));
        System.out.println("Double.MAX_VALUE   = " + Double.MAX_VALUE);

        System.out.println("\n=== TYPE CASTING ===");
        double pi = 3.999;
        System.out.println("(int)3.999 = " + (int) pi); // 3, truncates
        int num = 9;
        System.out.println("9/2 (int) = " + num / 2); // 4
        System.out.println("9/(double)2 = " + num / 2.0); // 4.5

        System.out.println("\n=== var (Java 10+) ===");
        var x = 100;
        var s = "World";
        var dd = 2.718;
        System.out.println("var x=" + x + " s=" + s + " dd=" + dd);

        System.out.println("\n=== CONSTANTS ===");
        final double PI = 3.14159265358979;
        System.out.println("PI = " + PI);

        System.out.println("\n=== STRINGS ===");
        String str = "Java Programming";
        System.out.println("length:    " + str.length());
        System.out.println("upper:     " + str.toUpperCase());
        System.out.println("lower:     " + str.toLowerCase());
        System.out.println("charAt(0): " + str.charAt(0));
        System.out.println("indexOf('P'): " + str.indexOf('P'));
        System.out.println("substring(5,9): " + str.substring(5, 9));
        System.out.println("contains Java: " + str.contains("Java"));
        System.out.println("replace:   " + str.replace("Java", "C++"));

        // StringBuilder (mutable string):
        StringBuilder sb = new StringBuilder("Hello");
        sb.append(" World");
        sb.insert(5, ",");
        sb.reverse();
        System.out.println("StringBuilder: " + sb);
    }
}
