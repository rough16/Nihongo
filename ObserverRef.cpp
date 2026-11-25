class ISubscriber
{
public:
    virtual ~ISubscriber() = default;
    virtual void registerSubscription(IPublisher& publisher) = 0;
    virtual void notification() = 0;
};

class IPublisher
{
public:
    virtual ~IPublisher() = default;
    virtual void subscribe(ISubscriber& subscriber) = 0;
    virtual void unsubscribe(ISubscriber& subscriber) = 0;
    virtual void notify() = 0;
};

class Publisher : public IPublisher
{
    std::vector<ISubscriber*> subscribers; // non-owning

public:
    void subscribe(ISubscriber& subscriber) override
    {
        subscribers.push_back(&subscriber);
    }

    void unsubscribe(ISubscriber& subscriber) override
    {
        subscribers.erase(
            std::remove(subscribers.begin(), subscribers.end(), &subscriber),
            subscribers.end()
        );
    }

    void notify() override
    {
        for (ISubscriber* subscriber : subscribers)
            subscriber->notification();
    }
};

class Subscriber1 : public ISubscriber
{
public:
    void registerSubscription(IPublisher& publisher) override
    {
        publisher.subscribe(*this);
    }

    void notification() override
    {
        std::cout << "Receive Notification 1\n";
    }
};

//-----------------------

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Event {
    std::string message;
};

class IObserver {
public:
    virtual void update(const Event& event) = 0;
    virtual ~IObserver() = default;
};

class Subject {
private:
    std::vector<IObserver*> observers;

public:
    void subscribe(IObserver& observer) {
        const auto it = std::find(observers.begin(), observers.end(), &observer);
        if (it == observers.end()) {
            observers.push_back(&observer);
        }
    }

    void unsubscribe(IObserver& observer) {
        std::erase(observers, &observer); // C++20
    }

    void notify(const Event& event) {
        // Snapshot lets observers subscribe/unsubscribe during callbacks
        // without invalidating this iteration.
        const auto currentObservers = observers;
        for (IObserver* observer : currentObservers) {
            observer->update(event);
        }
    }
};

class EmailAlert : public IObserver {
public:
    void update(const Event& event) override {
        std::cout << "Email alert: " << event.message << '\n';
    }
};

class AuditLog : public IObserver {
public:
    void update(const Event& event) override {
        std::cout << "Audit log: " << event.message << '\n';
    }
};

int main() {
    Subject subject;
    EmailAlert emailAlert;
    AuditLog auditLog;

    subject.subscribe(emailAlert);
    subject.subscribe(auditLog);

    subject.notify({"Order shipped"});
}


