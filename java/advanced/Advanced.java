/**
 * MODULE 12 | ADVANCED → Generics, Patterns, Concurrency (Java)
 * Compile: javac Advanced.java && java Advanced
 */
import java.util.*;
import java.util.stream.*;
import java.util.function.*;
import java.util.concurrent.*;
import java.util.concurrent.atomic.*;

// ---- Generic Pair ----
class Pair<A,B> {
    final A first; final B second;
    Pair(A a,B b){first=a;second=b;}
    @Override public String toString(){return "("+first+", "+second+")";}
}

// ---- Generic Stack ----
class GenStack<T> {
    private final List<T> data=new ArrayList<>();
    void push(T v){data.add(v);}
    T pop(){if(data.isEmpty())throw new EmptyStackException();return data.remove(data.size()-1);}
    T peek(){return data.get(data.size()-1);}
    @Override public String toString(){return data.toString();}
}

// ---- Bounded generic (Comparable) ----
class SortedList<T extends Comparable<T>> {
    private final List<T> items=new ArrayList<>();
    void add(T v){items.add(v);Collections.sort(items);}
    @Override public String toString(){return items.toString();}
}

// ---- SINGLETON ----
final class Config {
    private static Config inst;
    private final String env="production";
    private Config(){}
    static synchronized Config get(){if(inst==null)inst=new Config();return inst;}
    String getEnv(){return env;}
}

// ---- BUILDER ----
class Person {
    final String name,email,phone; final int age;
    private Person(Builder b){name=b.name;email=b.email;phone=b.phone;age=b.age;}
    static class Builder {
        private String name,email="",phone=""; private int age;
        Builder(String n,int a){name=n;age=a;}
        Builder email(String e){email=e;return this;}
        Builder phone(String p){phone=p;return this;}
        Person build(){return new Person(this);}
    }
    @Override public String toString(){return "Person{"+name+",age="+age+",email="+email+"}";}
}

// ---- OBSERVER ----
interface Listener { void onEvent(String event, Object data); }
class EventBus {
    private final Map<String,List<Listener>> map=new HashMap<>();
    void on(String e,Listener l){map.computeIfAbsent(e,k->new ArrayList<>()).add(l);}
    void emit(String e,Object d){map.getOrDefault(e,List.of()).forEach(l->l.onEvent(e,d));}
}

public class Advanced {
    public static void main(String[] args) throws Exception {

        System.out.println("=== GENERICS ===");
        Pair<String,Integer> pair=new Pair<>("Alice",95);
        System.out.println("Pair: "+pair);
        GenStack<Integer> gs=new GenStack<>();
        gs.push(10);gs.push(20);gs.push(30);
        System.out.println("Stack: "+gs+" peek="+gs.peek()+" pop="+gs.pop());
        SortedList<Integer> sl=new SortedList<>();
        sl.add(5);sl.add(1);sl.add(8);sl.add(2);
        System.out.println("SortedList: "+sl);

        System.out.println("\n=== FUNCTIONAL ===");
        Function<Integer,Integer> dbl=x->x*2, addTen=x->x+10;
        System.out.println("dbl then +10 on 5: "+dbl.andThen(addTen).apply(5));  // 20
        System.out.println("dbl compose +10 on 5: "+dbl.compose(addTen).apply(5));  // 30
        Predicate<String> valid=s->s!=null&&!s.isEmpty()&&s.contains("@");
        System.out.println("isEmail 'a@b.com': "+valid.test("a@b.com"));
        System.out.println("isEmail '':        "+valid.test(""));

        System.out.println("\n=== STREAMS (advanced) ===");
        List<String> names=List.of("Alice","Bob","Charlie","Anna","Brian","Adam");
        Map<Character,List<String>> grouped=names.stream()
            .collect(Collectors.groupingBy(s->s.charAt(0)));
        System.out.println("Grouped: "+grouped);
        long primes=LongStream.rangeClosed(2,1000).parallel()
            .filter(n->{for(long d=2;d*d<=n;d++)if(n%d==0)return false;return true;})
            .count();
        System.out.println("Primes 2-1000: "+primes);   // 168

        System.out.println("\n=== DESIGN PATTERNS ===");
        // Singleton:
        Config c1=Config.get(),c2=Config.get();
        System.out.println("singleton same? "+(c1==c2)+"  env="+c1.getEnv());
        // Builder:
        Person p=new Person.Builder("Deepak",22).email("deepak@example.com").phone("+91-999").build();
        System.out.println("Builder: "+p);
        // Observer:
        EventBus bus=new EventBus();
        bus.on("login",(ev,d)->System.out.println("Logger: "+ev+" user="+d));
        bus.on("login",(ev,d)->System.out.println("Analytics: "+ev));
        bus.on("logout",(ev,d)->System.out.println("Session ended: "+d));
        bus.emit("login","deepak"); bus.emit("logout","deepak");

        System.out.println("\n=== CONCURRENCY ===");
        AtomicInteger counter=new AtomicInteger(0);
        ExecutorService exec=Executors.newFixedThreadPool(4);
        List<Future<?>> fs=new ArrayList<>();
        for(int i=0;i<4;i++) fs.add(exec.submit(()->{ for(int j=0;j<250;j++) counter.incrementAndGet(); }));
        for(Future<?>f:fs) f.get();
        exec.shutdown();
        System.out.println("AtomicCounter(expected 1000)="+counter.get());

        CompletableFuture<Integer>f1=CompletableFuture.supplyAsync(()->42);
        CompletableFuture<Integer>f2=CompletableFuture.supplyAsync(()->58);
        System.out.println("Combined futures: "+f1.thenCombine(f2,Integer::sum).get());  // 100
    }
}
