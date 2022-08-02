/*

    Copyright David Abrahams 2003-2004
    Copyright Aleksey Gurtovoy 2003-2004

    Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at 
    http://www.boost.org/LICENSE_1_0.txt)
            
    This file was automatically extracted from the source of 
    "C++ Template Metaprogramming", by David Abrahams and 
    Aleksey Gurtovoy.

    It was built successfully with GCC 3.4.2 on Windows using
    the following command: 

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-chapter11-example12.o example12.cpp
        

*/
#include <vector>
#include <ctime>
#include <boost/mpl/vector.hpp>

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/static_assert.hpp>
namespace mpl = boost::mpl;
using namespace mpl::placeholders;

#include <cassert>


    template<class Table, class Event>
    struct generate_dispatcher;

template<class Derived>
class state_machine
{
    // ...
 protected:
    template<
        int CurrentState
      , class Event
      , int NextState
      , void (Derived::*action)(Event const&)
    >
    struct row
    {
        // for later use by our metaprogram
        static int const current_state = CurrentState;
        static int const next_state = NextState;
        typedef Event event;
        typedef Derived fsm_t;

        // do the transition action.
        static void execute(Derived& fsm, Event const& e)
        {
            (fsm.*action)(e);
        }
    };

    ////
    protected:
    int state;
    template <class E>
    static int no_transition(int, E const&);
    ////
  };



  struct play {};
  struct open_close {};
  struct cd_detected { 
    cd_detected(char const*, std::vector<std::clock_t> const&) {}
  };
  #ifdef __GNUC__ // in which pause seems to have a predefined meaning
  # define pause pause_
  #endif
  struct pause {};
  struct stop {};
  

// concrete FSM implementation 
class player : public state_machine<player>
{
 private:
    // the list of FSM states
    enum states {
        Empty, Open, Stopped, Playing, Paused
      , initial_state = Empty
    };

    
    #ifdef __MWERKS__
     public: // Codewarrior bug workaround.  Tested at 0x3202
    #endif
    
    void start_playback(play const&);
    void open_drawer(open_close const&);
    void close_drawer(open_close const&);
    void store_cd_info(cd_detected const&);
    void stop_playback(stop const&);
    void pause_playback(pause const&);
    void resume_playback(play const&);
    void stop_and_open(open_close const&);

    
    #ifdef __MWERKS__
       private:
    #endif 
          friend class state_machine<player>;
    typedef player p; // makes transition table cleaner

    // transition table
    struct transition_table : mpl::vector11<

    //    Start     Event         Next      Action
    //  +---------+-------------+---------+---------------------+
    row < Stopped , play        , Playing , &p::start_playback  >,
    row < Stopped , open_close  , Open    , &p::open_drawer     >,
    //  +---------+-------------+---------+---------------------+
    row < Open    , open_close  , Empty   , &p::close_drawer    >,
    //  +---------+-------------+---------+---------------------+
    row < Empty   , open_close  , Open    , &p::open_drawer     >,
    row < Empty   , cd_detected , Stopped , &p::store_cd_info   >,
    //  +---------+-------------+---------+---------------------+
    row < Playing , stop        , Stopped , &p::stop_playback   >,
    row < Playing , pause       , Paused  , &p::pause_playback  >,
    row < Playing , open_close  , Open    , &p::stop_and_open   >,
    //  +---------+-------------+---------+---------------------+
    row < Paused  , play        , Playing , &p::resume_playback >,
    row < Paused  , stop        , Stopped , &p::stop_playback   >,
    row < Paused  , open_close  , Open    , &p::stop_and_open   >
    //  +---------+-------------+---------+---------------------+

    > {};
////

// "play" event processor
void process_event(play const& e)
{
    switch (this->state)
    {
     case Stopped:        
        this->start_playback(e);
        this->state = Playing;
        break;
     case Paused:        
        this->resume_playback(e);
        this->state = Playing;
        break;
     default:
        this->state = no_transition(this->state, e);
    }
}

// "stop" event processor
void process_event(stop const& e)
{
    // ...
}

// etc...
};

  void player::start_playback(play const&){}
  void player::open_drawer(open_close const&){}
  void player::close_drawer(open_close const&){}
  void player::store_cd_info(cd_detected const&){}
  void player::stop_playback(stop const&){}
  void player::pause_playback(pause const&){}
  void player::resume_playback(play const&){}
  void player::stop_and_open(open_close const&){}
  

