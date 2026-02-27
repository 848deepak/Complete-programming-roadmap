# ⚡ Modern Java Features (Java 8 → Java 17+)

> Essential modern Java features every developer and interviewee must know.

---

## Java 8 — The Collection Revolution

### 1. Lambda Expressions
```java
// Before Java 8
Comparator<String> comp = new Comparator<String>() {
    public int compare(String a, String b) { return a.compareTo(b); }
};

// With lambdas
Comparator<String> comp = (a, b) -> a.compareTo(b);

// Method reference
Comparator<String> comp = String::compareTo;

// Common uses
list.forEach(System.out::println);
list.sort(Comparator.comparingInt(String::length));
```

### 2. Stream API
```java
List<Integer> numbers = List.of(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

// Filter, map, collect
List<Integer> evenSquares = numbers.stream()
    .filter(n -> n % 2 == 0)
    .map(n -> n * n)
    .collect(Collectors.toList());
// [4, 16, 36, 64, 100]

// Reduce
int sum = numbers.stream().reduce(0, Integer::sum);

// Grouping
Map<Integer, List<String>> byLength = words.stream()
    .collect(Collectors.groupingBy(String::length));

// Parallel streams
long count = numbers.parallelStream()
    .filter(n -> isPrime(n))
    .count();
```

### 3. Optional
```java
// Avoid NullPointerException
Optional<String> opt = Optional.ofNullable(getValue());

// Safe access
String result = opt.orElse("default");
String result2 = opt.orElseThrow(() -> new RuntimeException("Missing!"));

// Chaining
Optional<String> upper = opt
    .filter(s -> s.length() > 3)
    .map(String::toUpperCase);
```

### 4. Functional Interfaces
```java
// Built-in functional interfaces
Function<String, Integer> toLen = String::length;
Predicate<Integer> isEven = n -> n % 2 == 0;
Consumer<String> printer = System.out::println;
Supplier<List<String>> listFactory = ArrayList::new;

// Composing
Predicate<Integer> isEvenAndPositive = isEven.and(n -> n > 0);
Function<String, String> shout = String::toUpperCase;
Function<String, String> shoutAndTrim = shout.andThen(String::trim);
```

---

## Java 11 — Utility Improvements

### String Methods
```java
"  hello  ".strip();          // "hello" (Unicode-aware trim)
"  hello  ".stripLeading();   // "hello  "
"hello".repeat(3);            // "hellohellohello"
"hello\nworld".lines().count(); // 2
"  ".isBlank();               // true
```

### var (Local Variable Type Inference — Java 10)
```java
var list = new ArrayList<String>();  // Inferred as ArrayList<String>
var map = Map.of("a", 1, "b", 2);   // Inferred as Map<String, Integer>

// With lambdas (Java 11)
list.stream()
    .map((var s) -> s.toUpperCase())
    .forEach(System.out::println);
```

---

## Java 14-16 — Pattern Matching & Records

### Records (Java 16)
```java
// Before: 50+ lines of boilerplate (constructor, getters, equals, hashCode, toString)
// After: 1 line!
record Point(int x, int y) {}

Point p = new Point(3, 4);
System.out.println(p.x());  // 3
System.out.println(p);      // Point[x=3, y=4]
```

### Switch Expressions (Java 14)
```java
// Old
String result;
switch (day) {
    case MONDAY: case FRIDAY: result = "Work"; break;
    case SATURDAY: case SUNDAY: result = "Rest"; break;
    default: result = "Midweek"; break;
}

// New — expression with arrow labels
String result = switch (day) {
    case MONDAY, FRIDAY -> "Work";
    case SATURDAY, SUNDAY -> "Rest";
    default -> "Midweek";
};
```

### Pattern Matching for instanceof (Java 16)
```java
// Old
if (obj instanceof String) {
    String s = (String) obj;
    System.out.println(s.length());
}

// New — binding variable
if (obj instanceof String s) {
    System.out.println(s.length());  // s already cast!
}
```

### Text Blocks (Java 15)
```java
String json = """
    {
        "name": "Alice",
        "age": 30,
        "city": "London"
    }
    """;
```

---

## Java 17+ — Sealed Classes

### Sealed Classes
```java
// Restrict which classes can extend
sealed interface Shape permits Circle, Rectangle, Triangle {}
record Circle(double radius) implements Shape {}
record Rectangle(double w, double h) implements Shape {}
record Triangle(double a, double b, double c) implements Shape {}

// Exhaustive switch (compiler checks all cases)
double area(Shape shape) {
    return switch (shape) {
        case Circle c -> Math.PI * c.radius() * c.radius();
        case Rectangle r -> r.w() * r.h();
        case Triangle t -> { /* Heron's formula */ yield 0; }
    };
}
```

---

## Interview Quick Reference

| Feature | Version | Key Use Case |
|---------|---------|-------------|
| Lambdas | Java 8 | Inline functions, callbacks |
| Streams | Java 8 | Declarative data processing |
| Optional | Java 8 | Null safety |
| `var` | Java 10 | Local type inference |
| Text Blocks | Java 15 | Multi-line strings |
| Records | Java 16 | Immutable data classes |
| Pattern Matching | Java 16 | Safer type checks |
| Sealed Classes | Java 17 | Controlled inheritance |
| Switch Expressions | Java 14 | Cleaner branching |
