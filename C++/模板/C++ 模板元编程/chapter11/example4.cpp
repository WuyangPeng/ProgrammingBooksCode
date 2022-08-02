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

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-chapter11-example4.o example4.cpp
        

*/

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/static_assert.hpp>
namespace mpl = boost::mpl;
using namespace mpl::placeholders;


    struct tag {};

    template <class T>
    tag operator,(tag,T);

    template <class T>
    tag operator|(tag,T);

    struct transition_table
    {
        transition_table& operator[](tag);
    };
    struct fsm
    {
        typedef tag play;
typedef tag open_close;
typedef tag cd_detected;
typedef tag stop;
typedef tag pause;
        void start_playback(play const&);
        void open_drawer(open_close const&);
        void close_drawer(open_close const&);
        void store_cd_info(cd_detected const&);
        void stop_playback(stop const&);
        void pause_playback(pause const&);
        void resume_playback(play const&);
        void stop_and_open(open_close const&);
    };
    tag Stopped, Playing, Open, Empty, Paused;
    
namespace {typedef tag play;
typedef tag open_close;
typedef tag cd_detected;
typedef tag stop;
typedef tag pause;}


transition_table STT;

// provided by the FSM framework
template <class Event>
struct on
{
    typedef Event type;
};
void test() {

  // Current   Event             Next     Action
  //  State                      State             
STT[ Stopped |on<play>()      | Playing |&fsm::start_playback ]
   [ Stopped |on<open_close>()| Open    |&fsm::open_drawer    ]

;}

