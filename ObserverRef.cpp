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
