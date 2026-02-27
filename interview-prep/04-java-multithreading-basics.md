# ⚡ Java Multithreading Basics — Interview Questions

> Multithreading is one of the most asked Java interview topics, especially for backend roles.

---

## 1. Creating Threads

### Two Ways
```java
// Method 1: Extend Thread
class MyThread extends Thread {
    public void run() { System.out.println("Thread: " + getName()); }
}

// Method 2: Implement Runnable (PREFERRED — allows extending another class)
class MyTask implements Runnable {
    public void run() { System.out.println("Task running"); }
}

// Usage
new MyThread().start();
new Thread(new MyTask()).start();
new Thread(() -> System.out.println("Lambda thread")).start();  // Java 8+
```

### 📌 Interview Tip
> Always prefer `Runnable` (or `Callable`) over extending `Thread`. Java doesn't support multiple inheritance — extending Thread wastes your single inheritance slot.

### ⚠️ Trap
> `thread.run()` does NOT start a new thread — it runs on the current thread! Always use `thread.start()`.

---

## 2. Thread Lifecycle

```
NEW → (start()) → RUNNABLE → (scheduled) → RUNNING
                                ↕ (wait/sleep/block)
                            BLOCKED/WAITING
RUNNING → (run() completes) → TERMINATED
```

---

## 3. Synchronization

### Problem: Race Condition
```java
class Counter {
    int count = 0;
    void increment() { count++; }  // Not atomic! Read-modify-write
}
```

### Fix: `synchronized`
```java
class Counter {
    int count = 0;
    synchronized void increment() { count++; }  // One thread at a time
}

// Or synchronized block (finer granularity)
void increment() {
    synchronized (this) { count++; }
}
```

### 📌 Interview Tip
> `synchronized` acquires a **monitor lock**. Only one thread can hold a monitor at a time. Method-level sync locks `this`; block-level lets you choose the lock object.

---

## 4. `volatile` Keyword

```java
volatile boolean flag = false;

// Thread 1
flag = true;

// Thread 2
while (!flag) { /* spin */ }  // Without volatile, compiler may cache flag
```

### Key Insight
> `volatile` ensures **visibility** (changes are seen by all threads immediately) but NOT **atomicity**. `count++` on a volatile int is still a race condition!

---

## 5. Deadlock

### What: Two threads waiting for each other's lock forever.

```java
Object lockA = new Object(), lockB = new Object();

// Thread 1
synchronized(lockA) {
    synchronized(lockB) { /* work */ }  // Holds A, waits for B
}

// Thread 2
synchronized(lockB) {
    synchronized(lockA) { /* work */ }  // Holds B, waits for A → DEADLOCK!
}
```

### Fix: Always acquire locks in the **same order**.

### 📌 Interview Tip
> Four conditions for deadlock (all must hold): **Mutual Exclusion, Hold & Wait, No Preemption, Circular Wait**. Break any one to prevent deadlock.

---

## 6. `wait()`, `notify()`, `notifyAll()`

```java
class ProducerConsumer {
    Queue<Integer> queue = new LinkedList<>();
    int capacity = 5;
    
    synchronized void produce(int item) throws InterruptedException {
        while (queue.size() == capacity) wait();  // Wait until space available
        queue.add(item);
        notifyAll();  // Notify consumers
    }
    
    synchronized int consume() throws InterruptedException {
        while (queue.isEmpty()) wait();  // Wait until item available
        int item = queue.poll();
        notifyAll();  // Notify producers
        return item;
    }
}
```

### ⚠️ Trap
> Always use `while` (not `if`) before `wait()` — the condition may change between notify and wakeup (**spurious wakeup**).

---

## 7. Thread Pool (ExecutorService)

```java
import java.util.concurrent.*;

ExecutorService pool = Executors.newFixedThreadPool(4);

// Submit tasks
pool.submit(() -> System.out.println("Task 1"));
pool.submit(() -> System.out.println("Task 2"));

// Submit with return value
Future<Integer> future = pool.submit(() -> { return 42; });
System.out.println(future.get());  // Blocks until result ready

pool.shutdown();
```

### 📌 Interview Tip
> Never create threads manually in production. Always use a thread pool. Creating threads is expensive (~1MB stack allocation each).

---

## Quick Reference

| Concept | Purpose |
|---------|---------|
| `synchronized` | Mutual exclusion (atomicity + visibility) |
| `volatile` | Visibility only (no atomicity) |
| `wait()/notify()` | Thread coordination |
| `ReentrantLock` | More flexible locking (tryLock, fairness) |
| `ExecutorService` | Thread pool management |
| `Future/Callable` | Async computation with return values |
| `AtomicInteger` | Lock-free atomic operations |
