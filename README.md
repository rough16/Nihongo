# Nihongo
For JapanesePreparation

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
