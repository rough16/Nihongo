# Nihongo
For JapanesePreparation

1. Singleton Pattern

Ensures only one instance of a class exists.
text

       Singleton
    ----------------
    - instance
    ----------------
    + getInstance()
    + operation()
          |
          |
     Single Object

2. Factory Method Pattern

Creates one product through a factory method.
text

           IProduct
              |
       ---------------
       |             |
    Product1      Product2


           IFactory
              |
       ---------------
       |             |
    Factory1      Factory2
       |             |
       v             v
    Product1      Product2

3. Abstract Factory Pattern

Creates families of related products.
text

                IFactory
                   |
           -----------------
           |               |
        Factory1        Factory2
           |               |
       ----------      ----------
       |        |      |        |
    ProductA1 ProductB1 ProductA2 ProductB2


       IProductA       IProductB
           |               |
       ----------      ----------
       |        |      |        |
      PA1      PA2    PB1      PB2

4. Builder Pattern

Separates the construction of a complex object from its representation.
text

             Director
                |
                v
           IBuilder
                |
          -------------
          |           |
       Builder1    Builder2
          |           |
          v           v
        Product     Product

5. Prototype Pattern

Creates new objects by cloning existing objects.
text

          IPrototype
               |
        ----------------
        |              |
    Prototype1     Prototype2
        |              |
        | clone()      | clone()
        v              v
      Object         Object

2. Structural Design Patterns
6. Adapter Pattern

Allows incompatible interfaces to work together.
text

          Client
             |
             v
        ITarget
             |
             v
         Adapter
             |
             v
        Adaptee

7. Bridge Pattern

Separates abstraction from implementation.
text

        Abstraction
             |
             | has-a
             v
        IImplementor
             |
       --------------
       |            |
   Impl1          Impl2

8. Composite Pattern

Treats individual objects and groups of objects uniformly.
text

          Component
              |
       ----------------
       |              |
      Leaf        Composite
                       |
                       |
                  Components
                       |
                 -------------
                 |           |
                Leaf        Leaf

9. Decorator Pattern

Adds additional responsibilities dynamically.
text

          Component
              |
       ----------------
       |              |
    Concrete       Decorator
    Component          |
                       |
                  Component
                       |
                 ConcreteDecorator

10. Facade Pattern

Provides a simplified interface to a complex subsystem.
text

          Client
             |
             v
           Facade
             |
      -----------------
      |       |       |
   System1 System2 System3

11. Proxy Pattern

Provides a substitute or placeholder for another object.
text

           ISubject
               |
        ----------------
        |              |
       Proxy       RealSubject
        |
        | has-a
        v
    RealSubject

12. Flyweight Pattern

Shares common object state to reduce memory consumption.
text

            Client
               |
               v
         FlyweightFactory
               |
               v
          IFlyweight
               |
        ----------------
        |              |
    Flyweight1     Flyweight2

3. Behavioral Design Patterns
13. Observer Pattern

One-to-many relationship between publisher and subscribers.
text

          IPublisher
               |
               v
           Publisher
               |
        Subscriber List
               |
       -----------------
       |       |       |
      Sub1    Sub2    Sub3
       |       |       |
       v       v       v
   notification()

14. Strategy Pattern

Encapsulates interchangeable algorithms.
text

           Context
              |
              | has-a
              v
          IStrategy
              |
       ----------------
       |              |
    Strategy1      Strategy2

15. State Pattern

Changes object behavior based on its internal state.
text

            Context
               |
               | has-a
               v
            IState
               |
        ----------------
        |              |
      State1         State2

16. Command Pattern

Encapsulates a request as an object.
text

          Client
             |
             v
         ICommand
             |
       --------------
       |            |
   Command1      Command2
       |            |
       v            v
    Receiver     Receiver

17. Template Method Pattern

Defines the skeleton of an algorithm in a base class.
text

          AbstractClass
                |
         templateMethod()
                |
         ----------------
         |              |
      Class1           Class2
         |              |
     step1()         step1()
     step2()         step2()

18. Chain of Responsibility Pattern

Passes a request through a chain of handlers.
text

       Client
          |
          v
       Handler1
          |
          v
       Handler2
          |
          v
       Handler3

19. Iterator Pattern

Provides sequential access to elements without exposing the underlying representation.
text

          IIterator
              |
       ----------------
       |              |
    Iterator1     Iterator2


          Aggregate
              |
       ----------------
       |              |
    Collection1   Collection2

20. Mediator Pattern

Centralizes communication between objects.
text

          IMediator
              |
           Mediator
          /   |   \
         /    |    \
      Obj1   Obj2   Obj3

21. Memento Pattern

Captures and restores an object's previous state.
text

          Originator
              |
              v
           Memento
              ^
              |
          Caretaker

22. Visitor Pattern

Separates operations from the objects on which they operate.
text

           IVisitor
               |
        ----------------
        |              |
     Visitor1       Visitor2


          IElement
              |
        ----------------
        |              |
     Element1       Element2

23. Interpreter Pattern

Defines a grammar and provides an interpreter for expressions.
text

       AbstractExpression
                |
         ----------------
         |              |
    TerminalExpr   NonTerminalExpr

Category	Design Pattern	Main Purpose
Creational	Singleton	Single instance
Creational	Factory Method	Create products
Creational	Abstract Factory	Create product families
Creational	Builder	Build complex objects
Creational	Prototype	Clone objects
Structural	Adapter	Interface compatibility
Structural	Bridge	Separate abstraction and implementation
Structural	Composite	Tree structures
Structural	Decorator	Add responsibilities
Structural	Facade	Simplify subsystem
Structural	Proxy	Control object access
Structural	Flyweight	Share objects
Behavioral	Observer	Notify subscribers
Behavioral	Strategy	Interchange algorithms
Behavioral	State	State-dependent behavior
Behavioral	Command	Encapsulate requests
Behavioral	Template Method	Algorithm skeleton
Behavioral	Chain of Responsibility	Pass requests through handlers
Behavioral	Iterator	Traverse collections
Behavioral	Mediator	Centralize communication
Behavioral	Memento	Restore previous state
Behavioral	Visitor	Separate operations
Behavioral	Interpreter	Interpret grammar


<img width="696" height="447" alt="image" src="https://github.com/user-attachments/assets/666a7084-caa6-4a78-9e3f-df1a7eea4797" />



<img width="789" height="479" alt="image" src="https://github.com/user-attachments/assets/c9255749-bdf9-4288-b974-da666f9ee9e2" />


cpp
// Observer Pattern

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Both Publisher and Subscriber depend on abstractions rather than concrete implementations.
This is an application of the Dependency Inversion Principle (DIP).

Your design also demonstrates:
    1. Interface-based programming.
    2. Runtime polymorphism.
    3. Loose coupling.
    4. One-to-many relationships.
    5. Separation of responsibilities.
*/

class IPublisher;

class ISubscriber
{
public:
    virtual void registerSubcribtion(IPublisher *publsiher) = 0;
    virtual void notification() = 0;
};

class IPublisher
{
public:
    virtual void subscribe(ISubscriber *subcriber) = 0;
    virtual void unsubscribe(ISubscriber *subcriber) = 0;
    virtual void notify() = 0;
};

class Publisher : public IPublisher
{
    std::vector<ISubscriber *> subcriberlist;

public:
    void subscribe(ISubscriber *subcriber)
    {
        subcriberlist.emplace_back(subcriber);
    }

    void notify()
    {
        for (auto subs : subcriberlist)
        {
            subs->notification();
        }
    }

    void unsubscribe(ISubscriber *subscriber)
    {
        subcriberlist.erase(
            std::remove(
                subcriberlist.begin(),
                subcriberlist.end(),
                subscriber
            ),
            subcriberlist.end()
        );
    }
};

class Subscriber1 : public ISubscriber
{
public:
    void registerSubcribtion(IPublisher *publsiher)
    {
        publsiher->subscribe(this);
    }

    void notification()
    {
        std::cout << "Receive Notification 1" << "\n";
    }
};

class Subscriber2 : public ISubscriber
{
public:
    void registerSubcribtion(IPublisher *publsiher)
    {
        publsiher->subscribe(this);
    }

    void notification()
    {
        std::cout << "Receive Notification 2" << "\n";
    }
};

class Subscriber3 : public ISubscriber
{
public:
    void registerSubcribtion(IPublisher *publsiher)
    {
        publsiher->subscribe(this);
    }

    void notification()
    {
        std::cout << "Receive Notification 3" << "\n";
    }
};

int main()
{
    ISubscriber *subs1 = new Subscriber1();
    ISubscriber *subs2 = new Subscriber2();
    ISubscriber *subs3 = new Subscriber3();

    IPublisher *pubs = new Publisher();

    subs1->registerSubcribtion(pubs);
    subs2->registerSubcribtion(pubs);
    subs3->registerSubcribtion(pubs);

    pubs->notify();

    return 0;
}

𝗥𝗼𝘂𝗻𝗱 1 – 𝗧𝗲𝗰𝗵𝗻𝗶𝗰𝗮𝗹 𝗥𝗼𝘂𝗻𝗱:

𝗤𝘂𝗲𝘀𝘁𝗶𝗼𝗻: 𝗗𝗲𝘀𝗶𝗴𝗻 𝗮 𝗛𝗶𝘁 𝗖𝗼𝘂𝗻𝘁𝗲𝗿.
Focus: Ability to handle high-concurrency write requests and memory-efficient data storage. Discussion involved using circular buffers or buckets to manage time-based counts within a specific window.
Follow-up: Scaling the counter to handle millions of requests per second and ensuring accuracy in a distributed environment.

𝗥𝗼𝘂𝗻𝗱 2 – 𝗖𝗼𝗻𝗰𝘂𝗿𝗿𝗲𝗻𝗰𝘆 & 𝗣𝗿𝗼𝗯𝗹𝗲𝗺 𝗦𝗼𝗹𝘃𝗶𝗻𝗴:
Technical Deep Dive: Basic questions on concurrency, thread lifecycle, and race conditions.
Implementation: Design and implement a word auto-complete suggestion feature for keyboards.
Approach: Utilized a Trie (Prefix Tree) data structure to store words and provided an efficient search algorithm for prefix matching.
Follow-up: Optimizing the Trie for memory and adding weightage/frequency to suggestions.

𝗥𝗼𝘂𝗻𝗱 3 – 𝗔𝗹𝗴𝗼𝗿𝗶𝘁𝗵𝗺𝘀 & 𝗦𝘆𝘀𝘁𝗲𝗺𝘀 𝗟𝗼𝗴𝗶𝗰:
DSA Question: Find the median of two sorted arrays.
System Logic: Strategy for zero-downtime key rotation in a Master-Slave architecture.
Problem Scenario: Master nodes SSH into slave nodes using a private key; slave nodes verify using a public key.

𝗥𝗼𝘂𝗻𝗱 4 – 𝗕𝗲𝗵𝗮𝘃𝗶𝗼𝗿𝗮𝗹 𝗥𝗼𝘂𝗻𝗱:
Discussion: Deep dive into past projects and technical challenges faced in the last 4 years.
Focus: Conflict resolution within a team, handling tight deadlines, and the rationale behind choosing Yugabyte.
