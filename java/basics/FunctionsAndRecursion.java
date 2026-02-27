/**
 * MODULE 03 | BASICS → Functions & Recursion (Java)
 * Compile: javac FunctionsAndRecursion.java && java FunctionsAndRecursion
 */
import java.util.*;
import java.util.function.*;

public class FunctionsAndRecursion {

    static int    add(int a, int b)          { return a+b; }
    static double add(double a, double b)    { return a+b; }
    static int    add(int a, int b, int c)   { return a+b+c; }
    static int    sumAll(int... nums)        { int s=0; for(int n:nums) s+=n; return s; }

    static long factorial(int n) { return n<=1?1:(long)n*factorial(n-1); }

    static long[] memo = new long[50];
    static { Arrays.fill(memo,-1L); memo[0]=0; memo[1]=1; }
    static long fib(int n){ return memo[n]!=-1?memo[n]:(memo[n]=fib(n-1)+fib(n-2)); }

    static int gcd(int a,int b){ return b==0?a:gcd(b,a%b); }

    static double fastPow(double x,int n){
        if(n==0)return 1; if(n<0)return 1.0/fastPow(x,-n);
        if(n%2==0){double h=fastPow(x,n/2);return h*h;} return x*fastPow(x,n-1);
    }

    static void hanoi(int n,char from,char to,char aux){
        if(n==1){System.out.println("  Disk 1: "+from+" → "+to);return;}
        hanoi(n-1,from,aux,to);
        System.out.println("  Disk "+n+": "+from+" → "+to);
        hanoi(n-1,aux,to,from);
    }

    static void subsets(int[] arr,int idx,List<Integer> curr){
        if(idx==arr.length){System.out.println(curr);return;}
        subsets(arr,idx+1,curr);
        curr.add(arr[idx]); subsets(arr,idx+1,curr); curr.remove(curr.size()-1);
    }

    public static void main(String[] args) {
        System.out.println("=== OVERLOADING + VARARGS ===");
        System.out.println("add(5,3)="+add(5,3)+" add(2.5,3.1)="+add(2.5,3.1)+" add(1,2,3)="+add(1,2,3));
        System.out.println("sumAll(1..5)="+sumAll(1,2,3,4,5));

        System.out.println("\n=== FACTORIAL ===");
        for(int i=0;i<=10;i++) System.out.print(i+"!="+factorial(i)+"  "); System.out.println();

        System.out.println("\n=== FIBONACCI ===");
        System.out.print("fib(0-9): ");
        for(int i=0;i<10;i++) System.out.print(fib(i)+" ");
        System.out.println("\nfib(40)="+fib(40));

        System.out.println("\n=== GCD ===");
        System.out.println("gcd(48,18)="+gcd(48,18)+"  gcd(100,75)="+gcd(100,75));

        System.out.println("\n=== FAST POWER ===");
        System.out.println("2^10="+(int)fastPow(2,10)+"  3^5="+(int)fastPow(3,5));

        System.out.println("\n=== HANOI (3 disks) ===");
        hanoi(3,'A','C','B');

        System.out.println("\n=== SUBSETS of {1,2,3} ===");
        subsets(new int[]{1,2,3},0,new ArrayList<>());

        System.out.println("\n=== LAMBDAS + HIGHER-ORDER ===");
        Function<Integer,Integer> sq = x->x*x;
        System.out.println("sq(6)="+sq.apply(6));
        Function<Integer,Integer> addTen=x->x+10;
        System.out.println("sq then +10 on 3: "+sq.andThen(addTen).apply(3));  // 19
        Predicate<String> nonEmpty=s->!s.isEmpty(), hasAt=s->s.contains("@");
        System.out.println("isEmail 'a@b.com': "+nonEmpty.and(hasAt).test("a@b.com"));
    }
}
