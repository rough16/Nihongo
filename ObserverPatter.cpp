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
