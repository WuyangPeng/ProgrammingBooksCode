#ifndef observer_h
#define observer_h

namespace ObserverPattern
{
    using namespace std;

    static const int SURFACE_BRIDGE = 0;

    class Entity
    {
    public:
        bool isHero() const
        {
            return false;
        }

        bool isStandingOn([[maybe_unused]] int surface) const
        {
            return false;
        }

        bool isOnSurface()
        {
            return true;
        }

        void accelerate([[maybe_unused]] int force)
        {
        }

        void update()
        {
        }
    };

    enum Event
    {
        EVENT_ENTITY_FELL
    };

    enum Achievement
    {
        ACHIEVEMENT_FELL_OFF_BRIDGE
    };

    static const int GRAVITY = 1;
    static const int EVENT_START_FALL = 1;

    namespace Motivation
    {
        class Physics
        {
        public:
            void updateEntity(Entity& entity);

            void notify([[maybe_unused]] Entity& entity, [[maybe_unused]] int event)
            {
            }
        };

        //^physics-update
        void Physics::updateEntity(Entity& entity)
        {
            bool wasOnSurface = entity.isOnSurface();
            entity.accelerate(GRAVITY);
            entity.update();
            if (wasOnSurface && !entity.isOnSurface())
            {
                notify(entity, EVENT_START_FALL);
            }
        }
        //^physics-update
    }

    namespace Pattern
    {
        //^observer
        class Observer
        {
        public:
            virtual ~Observer()
            {
            }
            virtual void onNotify(const Entity& entity, Event event) = 0;
        };
        //^observer

        //^achievement-observer
        class Achievements : public Observer
        {
        public:
            virtual void onNotify(const Entity& entity, Event event)
            {
                switch (event)
                {
                case EVENT_ENTITY_FELL:
                    if (entity.isHero() && heroIsOnBridge_)
                    {
                        unlock(ACHIEVEMENT_FELL_OFF_BRIDGE);
                    }
                    break;

                    // Handle other events, and update heroIsOnBridge_...
                    // 处理其他事件，并更新heroIsOnBridge_...
                }
            }

        private:
            void unlock([[maybe_unused]] Achievement achievement)
            {
                // Unlock if not already unlocked...
                // 如果尚未解锁，请解锁...
            }

            bool heroIsOnBridge_;
        };
        //^achievement-observer

        static const int MAX_OBSERVERS = 10;

        //^subject-list
        //^subject-register
        //^subject-notify
        class Subject
        {
            //^omit subject-list
            //^omit subject-notify
        public:
            void addObserver(Observer* observer)
            {
                // Add to array...
                //^omit
                observers_[numObservers_++] = observer;
                //^omit
            }

            void removeObserver(Observer* observer)
            {
                // Remove from array...
                //^omit
                int index;
                for (index = 0; index < MAX_OBSERVERS; index++)
                {
                    if (observers_[index] == observer)
                        break;
                }

                if (index < numObservers_)
                {
                    // Shift the following ones up.
                    // 向上移动以下内容。
                    for (; index < numObservers_ - 1; index++)
                    {
                        observers_[index] = observers_[index + 1];
                    }

                    numObservers_--;
                }
                //^omit
            }

            // Other stuff...
            //^omit subject-notify
            //^omit subject-register
        protected:
            void notify(const Entity& entity, Event event)
            {
                for (int i = 0; i < numObservers_; i++)
                {
                    observers_[i]->onNotify(entity, event);
                }
            }

            // Other stuff...
            //^omit subject-notify

            //^omit subject-list
        private:
            Observer* observers_[MAX_OBSERVERS];
            int numObservers_;
            //^omit subject-register
            //^omit subject-notify
        };
        //^subject-list
        //^subject-register
        //^subject-notify

        //^physics-inherit
        class Physics : public Subject
        {
        public:
            void updateEntity(Entity& entity);
        };
        //^physics-inherit

        class PhysicsEvent : public Observer
        {
            Subject entityFell_;
            Subject& entityFell()
            {
                return entityFell_;
            }

            virtual void onNotify([[maybe_unused]] const Entity& entity, [[maybe_unused]] Event event)
            {
            }

            void physicsEvent()
            {
                PhysicsEvent physics;

                //^physics-event
                physics.entityFell()
                    .addObserver(this);
                //^physics-event
            }
        };
    }

    namespace LinkedObservers
    {
        //^linked-observer
        class Observer
        {
            friend class Subject;

        public:
            Observer()
                : next_(nullptr)
            {
            }

            // Other stuff...
            //^omit
            virtual void onNotify([[maybe_unused]] const Entity& entity, [[maybe_unused]] Event event)
            {
            }
            //^omit
        private:
            Observer* next_;
        };
        //^linked-observer

        //^linked-subject
        class Subject
        {
            Subject()
                : head_(nullptr)
            {
            }

            // Methods...
            //^omit
            void addObserver(Observer* observer);
            void removeObserver(Observer* observer);
            void notify(const Entity& entity, Event event);
            //^omit
        private:
            Observer* head_;
        };
        //^linked-subject

        //^linked-add
        void Subject::addObserver(Observer* observer)
        {
            observer->next_ = head_;
            head_ = observer;
        }
        //^linked-add

        //^linked-remove
        void Subject::removeObserver(Observer* observer)
        {
            if (head_ == observer)
            {
                head_ = observer->next_;
                observer->next_ = nullptr;
                return;
            }

            Observer* current = head_;
            while (current != nullptr)
            {
                if (current->next_ == observer)
                {
                    current->next_ = observer->next_;
                    observer->next_ = nullptr;
                    return;
                }

                current = current->next_;
            }
        }
        //^linked-remove

        //^linked-notify
        void Subject::notify(const Entity& entity, Event event)
        {
            Observer* observer = head_;
            while (observer != nullptr)
            {
                observer->onNotify(entity, event);
                observer = observer->next_;
            }
        }
        //^linked-notify
    }

    namespace One
    {
        class Observable;

        class Observer
        {
            friend class Observable;

        public:
            bool isObserving() const
            {
                return observable_ != nullptr;
            }

            void observe(Observable& observable);
            void detach();

        protected:
            Observer()
                : prev_(this),
                  next_(this)
            {
            }

            virtual ~Observer()
            {
                detach();
            }

            virtual void onNotify(Observable& observable) = 0;

        private:
            // The Observable this Observer is watching.
            // 该观察者正在观察的观察者。
            Observable* observable_ = nullptr;

            // The next and previous nodes in the circular linked list
            // observers of observable_.
            // observable_的循环链接列表观察者中的下一个和上一个节点。
            Observer* prev_;
            Observer* next_;
        };

        class Observable
        {
            friend class Observer;

        public:
            bool hasObserver() const
            {
                return observer_ != nullptr;
            }

        protected:
            Observable()
                : observer_(nullptr)
            {
            }

            virtual ~Observable()
            {
                // Detach all of the observers.
                // 分离所有观察者。
                while (observer_ != nullptr)
                    observer_->detach();
            }

            void notify()
            {
                if (observer_ == nullptr)
                    return;

                Observer* observer = observer_;
                do
                {
                    observer->onNotify(*this);
                    observer = observer->next_;
                } while (observer != observer_);
            }

            // The first in the linked list of observers of this.
            // 观察者的链接列表中的第一个。
            Observer* observer_;
        };

        void Observer::observe(Observable& observable)
        {
            // Stop observing what it was previously observing.
            // 停止观察以前的观察。
            detach();

            if (observable.observer_ == nullptr)
            {
                // The first observer.
                // 第一个观察者。
                observable.observer_ = this;
            }
            else
            {
                // Already have other observers, so link it in at the end of the
                // list.
                // 已经有其他观察者，因此将其链接到列表的末尾。
                prev_ = observable.observer_->prev_;
                next_ = observable.observer_;

                observable.observer_->prev_->next_ = this;
                observable.observer_->prev_ = this;
            }

            observable_ = &observable;
        }

        void Observer::detach()
        {
            if (observable_ == nullptr)
                return;

            // Make sure the observable itself isn't pointing at this node.
            // 确保可观察对象本身没有指向此节点。
            if (observable_->observer_ == this)
            {
                if (next_ == this)
                {
                    // This is the only observer, so just clear it.
                    // 这是唯一的观察者，所以请清除它。
                    observable_->observer_ = nullptr;
                }
                else
                {
                    // Advance the next node.
                    // 前进下一个节点。
                    observable_->observer_ = next_;
                }
            }

            // Unlink this observer from the list.
            // 从列表中取消此观察者的链接。
            prev_->next_ = next_;
            next_->prev_ = prev_;

            prev_ = this;
            next_ = this;
            observable_ = nullptr;
        }

        class Noise : public Observable
        {
        public:
            Noise(const char* name)
                : name_(name)
            {
            }

            void sound()
            {
                cout << name_ << "!" << endl;
                notify();
            }

        private:
            const char* name_;
        };

        class Ear : public Observer
        {
        public:
            Ear(const char* name)
                : name_(name)
            {
            }

            int numObserved = 0;

        protected:
            virtual void onNotify([[maybe_unused]] Observable& observable)
            {
                numObserved++;
                cout << name_ << " heard it!" << endl;
            }

        private:
            const char* name_;
        };

        void destructSoloObserverTest()
        {
            Ear* ear = new Ear("ear");
            Noise noise("beep");
            ear->observe(noise);

            delete ear;
            ASSERT(!noise.hasObserver());

            noise.sound();
        }

        void destructMultipleObserverTest()
        {
            Ear* ear1 = new Ear("ear1");
            Ear* ear2 = new Ear("ear2");
            Noise noise("beep");
            ear1->observe(noise);
            ear2->observe(noise);

            delete ear2;
            ASSERT(noise.hasObserver());

            delete ear1;
            ASSERT(!noise.hasObserver());

            noise.sound();
        }

        void destructObservableTest()
        {
            Ear ear1("ear1");
            Ear ear2("ear2");
            Noise* noise = new Noise("beep");
            ear1.observe(*noise);
            ear2.observe(*noise);

            delete noise;
            ASSERT(!ear1.isObserving());
            ASSERT(!ear2.isObserving());
        }

        void notifyTest()
        {
            Noise noise1("beep");
            Ear ear1("one");
            Ear ear2("two");
            Ear ear3("three");

            noise1.sound();
            ASSERT(ear1.numObserved == 0);
            ASSERT(ear2.numObserved == 0);
            ASSERT(ear3.numObserved == 0);

            ear1.observe(noise1);
            noise1.sound();
            ASSERT(ear1.numObserved == 1);
            ASSERT(ear2.numObserved == 0);
            ASSERT(ear3.numObserved == 0);

            ear2.observe(noise1);
            noise1.sound();
            ASSERT(ear1.numObserved == 2);
            ASSERT(ear2.numObserved == 1);
            ASSERT(ear3.numObserved == 0);

            ear3.observe(noise1);
            noise1.sound();
            ASSERT(ear1.numObserved == 3);
            ASSERT(ear2.numObserved == 2);
            ASSERT(ear3.numObserved == 1);

            ear2.detach();
            noise1.sound();
            ASSERT(ear1.numObserved == 4);
            ASSERT(ear2.numObserved == 2);
            ASSERT(ear3.numObserved == 2);

            ear1.detach();
            noise1.sound();
            ASSERT(ear1.numObserved == 4);
            ASSERT(ear2.numObserved == 2);
            ASSERT(ear3.numObserved == 3);

            ear3.detach();
            noise1.sound();
            ASSERT(ear1.numObserved == 4);
            ASSERT(ear2.numObserved == 2);
            ASSERT(ear3.numObserved == 3);
        }

        void observeTest()
        {
            Ear ear("ear");
            Noise beep("beep");
            Noise boop("boop");

            ear.observe(beep);
            beep.sound();
            ASSERT(ear.numObserved == 1);
            boop.sound();
            ASSERT(ear.numObserved == 1);

            // Should stop listening to beep.
            // 应该停止听beep。
            ear.observe(boop);
            beep.sound();
            ASSERT(ear.numObserved == 1);
            boop.sound();
            ASSERT(ear.numObserved == 2);
        }

        void test()
        {
            destructSoloObserverTest();
            destructMultipleObserverTest();
            destructObservableTest();
            notifyTest();
            observeTest();
        }
    }

    namespace Pool
    {
        class Binding;
        class BindingPool;
        class Listener;

        class Event
        {
        public:
            Event(BindingPool& pool)
                : pool_(pool),
                  binding_(nullptr)
            {
            }

            ~Event();

            void addListener(Listener& listener);
            void removeListener(Listener& listener);

            void send(const char* data);

        private:
            BindingPool& pool_;
            Binding* binding_;
        };

        class Listener
        {
        public:
            Listener(const char* name)
                : name_(name), m_NumEvents{ 0 }
            {
            }

            int numEvents() const;

            void receive(const char* data)
            {
                cout << name_ << " received " << data << endl;
            }

            void addEvents()
            {
                ++m_NumEvents;
            }

            void removeEvents()
            {
                --m_NumEvents;
            }

        private:
            const char* name_;
            int m_NumEvents;
        };

        class Binding
        {
            friend class BindingPool;
            friend class Event;

        public:
            Binding()
                : listener_(nullptr),
                  next_(nullptr)
            {
            }

        private:
            Listener* listener_;

            // If the binding is in use, this will point to the binding for the
            // next listener. Otherwise, it will point to the next free binding.
            // 如果正在使用绑定，则它将指向下一个侦听器的绑定。 否则，它将指向下一个自由绑定。
            Binding* next_;
        };

        class BindingPool
        {
        public:
            BindingPool()
            {
                // Build the free list.
                // 建立空闲列表。
                free_ = &bindings_[0];
                for (int i = 0; i < POOL_SIZE - 1; i++)
                {
                    bindings_[i].next_ = &bindings_[i + 1];
                }
            }

            Binding* newBinding()
            {
                // TODO(bob): Make sure there is a free one.
                // Remove the head of the free list.
                // 确保有一个空闲的。 删除空闲列表的头。
                Binding* binding = free_;
                free_ = free_->next_;
                return binding;
            }

        private:
            static const int POOL_SIZE = 100;

            Binding bindings_[POOL_SIZE];

            // Pointer to the first binding in the list of free bindings.
            // 指向空闲绑定列表中的第一个绑定的指针。
            Binding* free_;
        };

        Event::~Event()
        {
            Binding* binding = binding_;
            while (binding != nullptr)
            {
                if (binding->listener_ != nullptr)
                {
                    binding->listener_->removeEvents();
                }

                binding = binding->next_;
            }
        }

        void Event::addListener(Listener& listener)
        {
            // TODO(bob): Add to end of list.
            // 添加到列表末尾。
            Binding* binding = pool_.newBinding();
            binding->listener_ = &listener;
            binding->next_ = binding_;
            binding_ = binding;
            listener.addEvents();
        }

        void Event::removeListener([[maybe_unused]] Listener& listener)
        {
            // TODO(bob): Implement me!
            listener.removeEvents();
        }

        void Event::send(const char* data)
        {
            Binding* binding = binding_;
            while (binding != nullptr)
            {
                binding->listener_->receive(data);
                binding = binding->next_;
            }
        }

        int Listener::numEvents() const
        {
            return m_NumEvents;  // ?
        }

        // TODO(bob): Destructors for all of these types.
        // 所有这些类型的析构函数。

        void destructEventTest()
        {
            BindingPool pool;

            Event* event1 = new Event(pool);
            Event* event2 = new Event(pool);

            Listener listener1("listener 1");
            Listener listener2("listener 2");

            event1->addListener(listener1);
            event1->addListener(listener2);
            event2->addListener(listener1);
            event2->addListener(listener2);

            ASSERT(listener1.numEvents() == 2);
            ASSERT(listener2.numEvents() == 2);

            delete event1;

            ASSERT(listener1.numEvents() == 1);
            ASSERT(listener2.numEvents() == 1);

            delete event2;

            ASSERT(listener1.numEvents() == 0);
            ASSERT(listener2.numEvents() == 0);
        }

        void test()
        {
            destructEventTest();

            BindingPool pool;

            Event event1(pool);
            Event event2(pool);

            Listener listener1("listener 1");
            Listener listener2("listener 2");
            Listener listener3("listener 3");

            event1.addListener(listener1);
            event1.addListener(listener2);
            event2.addListener(listener2);
            event2.addListener(listener3);

            event1.send("first");
            event2.send("second");
        }
    }

    void test()
    {
        One::test();
        Pool::test();
    }
}

#endif
