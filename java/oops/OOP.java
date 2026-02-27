/**
 * MODULE 05 | OOP → Classes, Inheritance, Polymorphism (Java)
 * Compile: javac OOP.java && java OOP
 */
import java.util.*;

// Abstract base
abstract class Shape {
    protected String color;
    Shape(String c) { this.color=c; }
    abstract double area();
    abstract void draw();
    void describe() { System.out.printf("%-12s color=%-8s area=%.2f%n",getClass().getSimpleName(),color,area()); }
}

class Circle extends Shape {
    double r;
    Circle(double r,String c) { super(c);this.r=r; }
    @Override double area() { return Math.PI*r*r; }
    @Override void draw()   { System.out.println("  O  (circle r="+r+")"); }
}

class Rectangle extends Shape {
    double l,w;
    Rectangle(double l,double w,String c){super(c);this.l=l;this.w=w;}
    @Override double area() { return l*w; }
    @Override void draw()   { System.out.println("  [] (rect "+l+"x"+w+")"); }
}

// Interface with default:
interface Flyable { void fly(); default void land(){ System.out.println("Landing..."); } }
interface Swimmable { void swim(); }

// Animal hierarchy:
class Animal {
    protected String name; protected int age;
    Animal(String n,int a){name=n;age=a;}
    void makeSound(){ System.out.println(name+": ..."); }
}

class Dog extends Animal {
    String breed;
    Dog(String n,int a,String b){super(n,a);breed=b;}
    @Override void makeSound(){ System.out.println(name+" (Dog): Woof!"); }
    void fetch(){ System.out.println(name+" fetches the ball!"); }
}

class Cat extends Animal implements Swimmable {
    Cat(String n,int a){super(n,a);}
    @Override void makeSound(){ System.out.println(name+" (Cat): Meow!"); }
    @Override public void swim(){ System.out.println(name+" swims!"); }
}

class Duck extends Animal implements Flyable,Swimmable {
    Duck(String n){super(n,1);}
    @Override void makeSound()  { System.out.println(name+" (Duck): Quack!"); }
    @Override public void fly() { System.out.println(name+" flies!"); }
    @Override public void swim(){ System.out.println(name+" swims!"); }
}

// Encapsulation:
class BankAccount {
    private double balance; private String owner;
    BankAccount(String o,double b){owner=o;balance=b;}
    double getBalance(){return balance;}
    void deposit(double a){if(a>0)balance+=a;System.out.printf("Deposited %.2f%n",a);}
    boolean withdraw(double a){if(a>balance){System.out.println("Insufficient!");return false;}balance-=a;System.out.printf("Withdrew %.2f%n",a);return true;}
}

// Overloading:
class Calculator {
    int    add(int a,int b)          {return a+b;}
    double add(double a,double b)    {return a+b;}
    int    add(int a,int b,int c)    {return a+b+c;}
}

public class OOP {
    public static void main(String[] args) {
        System.out.println("=== ABSTRACT CLASS + POLYMORPHISM ===");
        Shape[] shapes={new Circle(5,"red"),new Rectangle(4,6,"blue"),new Circle(3,"green")};
        for(Shape s:shapes){s.draw();s.describe();}

        System.out.println("\n=== INHERITANCE + INTERFACES ===");
        Animal[] animals={new Dog("Max",3,"Lab"),new Cat("Luna",2),new Duck("Donald")};
        for(Animal a:animals) a.makeSound();
        if(animals[0] instanceof Dog d) d.fetch();
        if(animals[2] instanceof Duck dk){dk.fly();dk.swim();}

        System.out.println("\n=== ENCAPSULATION ===");
        BankAccount acc=new BankAccount("Deepak",1000);
        System.out.printf("Balance: %.2f%n",acc.getBalance());
        acc.deposit(500); acc.withdraw(300); acc.withdraw(2000);
        System.out.printf("Balance: %.2f%n",acc.getBalance());

        System.out.println("\n=== OVERLOADING ===");
        Calculator calc=new Calculator();
        System.out.println("add(5,3)="+calc.add(5,3)+" add(2.5,3.1)="+calc.add(2.5,3.1)+" add(1,2,3)="+calc.add(1,2,3));
    }
}
