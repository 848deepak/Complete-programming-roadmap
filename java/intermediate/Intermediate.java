/**
 * MODULE 06-09 | INTERMEDIATE → References, Exceptions, Files, Collections (Java)
 * Compile: javac Intermediate.java && java Intermediate
 */
import java.util.*;
import java.util.stream.*;
import java.io.*;
import java.nio.file.*;
import java.nio.charset.StandardCharsets;

// ---- Custom exception ----
class InsufficientFundsException extends Exception {
    InsufficientFundsException(double a,double b){
        super(String.format("Cannot withdraw %.2f: balance=%.2f",a,b));
    }
}

// ---- AutoCloseable resource ----
class ManagedResource implements AutoCloseable {
    private final String name;
    ManagedResource(String n){System.out.println("[Open] "+n);name=n;}
    void doWork(){System.out.println("[Work] "+name);}
    @Override public void close(){System.out.println("[Close] "+name);}
}

public class Intermediate {

    // ---- REFERENCES ----
    static class Box { int value; Box(int v){value=v;} @Override public String toString(){return "Box("+value+")";} }
    static void incrementBox(Box b){b.value++;}
    static void reassignBox(Box b){b=new Box(0);}  // no effect outside

    public static void main(String[] args) throws Exception {

        // MODULE 06 - REFERENCES:
        System.out.println("=== M06: REFERENCES ===");
        int x=10, y=x; y=99;
        System.out.println("primitives: x="+x+" y="+y);  // x still 10

        Box b1=new Box(42), b2=b1; b2.value=999;
        System.out.println("same object: b1="+b1);  // Box(999)

        Box myBox=new Box(10); incrementBox(myBox);  reassignBox(myBox);
        System.out.println("after inc+reassign: "+myBox);  // Box(11)

        String s1="hello", s2="hello", s3=new String("hello");
        System.out.println("pool: s1==s2 "+(s1==s2)+"  s1==s3 "+(s1==s3)+"  equals: "+s1.equals(s3));

        // MODULE 07 - EXCEPTIONS:
        System.out.println("\n=== M07: EXCEPTIONS ===");
        // Basic:
        try{int[]arr=new int[3];arr[10]=1;}
        catch(ArrayIndexOutOfBoundsException e){System.out.println("Caught: "+e.getMessage());}
        finally{System.out.println("finally always runs!");}

        // Custom:
        var acc=new Object(){
            double balance=1000;
            void withdraw(double amt) throws InsufficientFundsException {
                if(amt<0)throw new IllegalArgumentException("negative");
                if(amt>balance)throw new InsufficientFundsException(amt,balance);
                balance-=amt; System.out.printf("Withdrew %.2f%n",amt);
            }
        };
        try{acc.withdraw(500);acc.withdraw(800);}
        catch(InsufficientFundsException e){System.out.println(e.getMessage());}

        // try-with-resources:
        System.out.println("try-with-resources:");
        try(ManagedResource r1=new ManagedResource("DB");ManagedResource r2=new ManagedResource("File")){
            r1.doWork();r2.doWork();
        }

        // MODULE 08 - FILE HANDLING:
        System.out.println("\n=== M08: FILE HANDLING ===");
        Path p=Path.of("tmp_demo.txt");
        Files.write(p,List.of("Name,Age","Alice,20","Bob,21"),StandardCharsets.UTF_8);
        List<String>lines=Files.readAllLines(p);
        lines.forEach(l->System.out.println("  "+l));
        Files.deleteIfExists(p);
        System.out.println("File written, read, deleted.");

        // MODULE 09 - COLLECTIONS:
        System.out.println("\n=== M09: COLLECTIONS ===");
        List<Integer>list=new ArrayList<>(Arrays.asList(5,3,8,1,9,2));
        Collections.sort(list); System.out.println("Sorted: "+list);
        Map<String,Integer>map=new HashMap<>();map.put("Alice",95);map.put("Bob",87);
        System.out.println("Map: "+new TreeMap<>(map));
        Set<Integer>set=new HashSet<>(Set.of(5,3,8,1,5,3));
        System.out.println("Set (unique): "+new TreeSet<>(set));
        Deque<Integer>stk=new ArrayDeque<>();stk.push(10);stk.push(20);stk.push(30);
        System.out.print("Stack: "); while(!stk.isEmpty())System.out.print(stk.pop()+" "); System.out.println();
        PriorityQueue<Integer>minH=new PriorityQueue<>(list); System.out.println("Min-heap top: "+minH.peek());

        // STREAMS:
        System.out.println("\n=== STREAMS ===");
        List<Integer>nums=List.of(1,2,3,4,5,6,7,8,9,10);
        List<Integer>evenSq=nums.stream().filter(n->n%2==0).map(n->n*n).collect(Collectors.toList());
        System.out.println("Even squares: "+evenSq);
        Map<Boolean,List<Integer>>part=nums.stream().collect(Collectors.partitioningBy(n->n%2==0));
        System.out.println("Even: "+part.get(true)+"  Odd: "+part.get(false));
        String joined=List.of("Java","is","awesome").stream().collect(Collectors.joining(" "));
        System.out.println("Joined: "+joined);
    }
}
