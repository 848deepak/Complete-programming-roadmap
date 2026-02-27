/**
 * MODULE 02 | BASICS → Control Flow (Java)
 * Compile: javac ControlFlow.java && java ControlFlow
 */
import java.util.*;

public class ControlFlow {
    public static void main(String[] args) {

        System.out.println("=== IF-ELSE ===");
        int marks = 72;
        if      (marks >= 90) System.out.println("A");
        else if (marks >= 80) System.out.println("B");
        else if (marks >= 70) System.out.println("C");   // prints
        else                  System.out.println("F");

        // Ternary:
        int n = 15;
        System.out.println(n + " is " + (n%2==0 ? "even" : "odd"));

        // Leap year:
        int year = 2024;
        boolean leap = (year%400==0) || (year%4==0 && year%100!=0);
        System.out.println(year + (leap?" is":" is NOT") + " a leap year");

        System.out.println("\n=== SWITCH (traditional) ===");
        int day = 5;
        switch (day) {
            case 1: System.out.println("Mon"); break;
            case 2: System.out.println("Tue"); break;
            case 3: System.out.println("Wed"); break;
            case 4: System.out.println("Thu"); break;
            case 5: System.out.println("Fri"); break;
            case 6: System.out.println("Sat"); break;
            case 7: System.out.println("Sun"); break;
            default: System.out.println("Invalid");
        }

        System.out.println("\n=== SWITCH EXPRESSION (Java 14+) ===");
        String dayName = switch (day) {
            case 1 -> "Monday";    case 2 -> "Tuesday"; case 3 -> "Wednesday";
            case 4 -> "Thursday";  case 5 -> "Friday";  case 6 -> "Saturday";
            case 7 -> "Sunday";    default -> "?";
        };
        System.out.println("Day " + day + " = " + dayName);

        System.out.println("\n=== FOR LOOP ===");
        int sum=0; for(int i=1;i<=100;i++) sum+=i;
        System.out.println("Sum 1-100 = " + sum);  // 5050

        List<String> langs = List.of("Java","C++","Python");
        for (String lang : langs) System.out.print(lang + " ");
        System.out.println();

        System.out.println("\n=== WHILE ===");
        int pw=1; while(pw<1024){System.out.print(pw+" ");pw*=2;} System.out.println();

        System.out.println("\n=== DO-WHILE ===");
        int x=1; do{System.out.print(x+" ");x++;}while(x<=5); System.out.println();

        System.out.println("\n=== BREAK / CONTINUE ===");
        for(int i=1;i<=100;i++){if(i%21==0){System.out.println("First mult of 21: "+i);break;}}
        System.out.print("Odds 1-15: ");
        for(int i=1;i<=15;i++){if(i%2==0)continue;System.out.print(i+" ");}
        System.out.println();

        System.out.println("\n=== PATTERN ===");
        int rows=5;
        for(int i=1;i<=rows;i++){
            for(int j=1;j<=rows-i;j++) System.out.print("  ");
            for(int j=1;j<=i;j++) System.out.print("* ");
            System.out.println();
        }
    }
}
