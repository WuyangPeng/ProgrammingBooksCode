#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

#include "ccc_win.h"
#include "ccc_time.h"

const double PI = 3.141592653589793;

/**
   A clock that can draw its face.
*/
class Clock
{
public:
   /**
      Constructs a clock with a given center and radius.
      @param c the center of the clock
      @param r the radius of the clock
   */              
   Clock(Point c, double r);

   /**
      Sets the current time.
      @param t the time to set
   */
   void set_time(Time t);

   /**
      Draws the clock face, with tick marks and hands.
   */
   void draw() const;
private:
   /**
      Draw a tick mark (hour or minute mark).
      @param angle the angle in minutes (0...59, 0 = top)
      @param length the length of the tick mark
   */
   void draw_tick(double angle, double length) const;

   /**
      Draw a hand, starting from the center.
      @param angle the angle in minutes (0...59, 0 = top)
      @param length the length of the hand
   */
   void draw_hand(double angle, double length) const;

   Time current_time;
   Point center;
   double radius;
};

/**
   The player of the clock game.
*/
class Player
{
public:
   /**
      Constructs a player with no name, level 1, and score 0.
   */
   Player();

   /**
      Constructs a player with given name and level.
      @param player_name the player name
      @param initial_level the player's level (1...4)
   */            
   Player(string player_name, int initial_level);

   /**
      Increments the score. Moves to next level if current 
      level complete
   */
   void increment_score();

   /**
      Gets the current level.
      @return the level
   */
   int get_level() const;

   /**
      Gets the player's name.
      @return the name
   */
   string get_name() const;
private:
   string name;
   int score;
   int level;
};

/**
   The clock game.
*/
class Game
{
public:
   /**
      Constructs the game with a default player.
   */
   Game();

   /**
      Plays the game while the player wants to continue.
   */
   void play();

   /**
      Reads player name and level.
   */
   void read_player_information();

   /**
      Plays a round, with up to two guesses.
   */
   void play_round();
private:
   /**
      Makes a random time, depending on the level
      @return the random time
   */
   Time random_time();

   /**   
      Gets a time input from the user
      @return  the time guessed by the user
   */
   Time get_guess();

   Player player;
};

/**
   Sets the seed of the random number generator.
*/
void rand_seed()
{  
   int seed = static_cast<int>(time(0));
   srand(seed);
}

/**
   Returns a random integer in a range.
   @param a the bottom of the range
   @param b the top of the range
   @return a random number x, a <= x and x <= b
*/
int rand_int(int a, int b)
{  
   return a + rand() % (b - a + 1);
}

Clock::Clock(Point c, double r)
{  
   center = c;
   radius = r;
}

void Clock::set_time(Time t)
{  
   current_time = t;
}

void Clock::draw_tick(double angle, double length) const
{  
   double alpha = PI / 2 - 6 * angle * PI / 180;
   Point from(
      center.get_x() + cos(alpha) * radius * (1 - length),
      center.get_y() + sin(alpha) * radius * (1 - length));
   Point to(center.get_x() + cos(alpha) * radius,
      center.get_y() + sin(alpha) * radius);
   cwin << Line(from, to);
}

void Clock::draw_hand(double angle, double length) const
{  
   double alpha = PI / 2 - 6 * angle * PI / 180;
   Point from = center;
   Point to(center.get_x() + cos(alpha) * radius * length,
      center.get_y() + sin(alpha) * radius * length);
   cwin << Line(from, to);
}

void Clock::draw() const
{  
   cwin << Circle(center, radius);
   const double HOUR_TICK_LENGTH = 0.2;
   const double MINUTE_TICK_LENGTH = 0.1;
   const double HOUR_HAND_LENGTH = 0.6;
   const double MINUTE_HAND_LENGTH = 0.75;
   for (int i = 0; i < 12; i++)
   {  
      draw_tick(i * 5, HOUR_TICK_LENGTH);
      int j;
      for (j = 1; j <= 4; j++)
         draw_tick(i * 5 + j, MINUTE_TICK_LENGTH);
   }
   draw_hand(current_time.get_minutes(), MINUTE_HAND_LENGTH);
   draw_hand((current_time.get_hours() +
      current_time.get_minutes() / 60.0) * 5, HOUR_HAND_LENGTH);
}

Player::Player()
{  
   level = 1;
   score = 0;
}

Player::Player(string player_name, int initial_level)
{  
   name = player_name;
   level = initial_level;
   score = 0;
}

int Player::get_level() const
{  
   return level;
}

string Player::get_name() const
{  
   return name;
}

void Player::increment_score()
{  
   score++;
   if (score % 5 == 0 && level < 4)
      level++;
}

Game::Game()
{  
}

void Game::play()
{  
   rand_seed();
   read_player_information();
   string response;
   do
   {  
      play_round();
      response = cwin.get_string(
         "Do you want to play again? (y/n)");
   } 
   while (response == "y");
}

void Game::read_player_information()
{  
   string name = cwin.get_string("What is your name?");
   int initial_level;
   do
   {  
      initial_level = cwin.get_int(
         "At what level do you want to start? (1-4)");
   } 
   while (initial_level < 1 || initial_level > 4);
   player = Player(name, initial_level);
}

Time Game::random_time()
{  
   int level = player.get_level();
   int minutes;
   if (level == 1) minutes = 0;
   else if (level == 2) minutes = 15 * rand_int(0, 3);
   else if (level == 3) minutes = 5 * rand_int(0, 11);
   else minutes = rand_int(0, 59);
   int hours = rand_int(1, 12);
   return Time(hours, minutes, 0);
}

Time Game::get_guess()
{  
   int hours;
   do
   {  
      hours = cwin.get_int("Please enter hours: (1-12)");
   } 
   while (hours < 1 || hours > 12);
   int minutes;
   do
   {  
      minutes = cwin.get_int("Please enter minutes: (0-59)");
   } 
   while (minutes < 0 || minutes > 59);

   return Time(hours, minutes, 0);
}

void Game::play_round()
{  
   cwin.clear();
   Time t = random_time();
   const double CLOCK_RADIUS = 5;
   Clock clock(Point(0, 0), CLOCK_RADIUS);
   clock.set_time(t);
   clock.draw();

   Time guess = get_guess();
   if (t.seconds_from(guess) != 0)
      guess = get_guess();

   string text;
   if (t.seconds_from(guess) == 0)
   {  
      text = "Congratulations, " + player.get_name()
         + "! That is correct.";
      player.increment_score();
   }
   else
      text = "Sorry, " + player.get_name()
         + "! That is not correct.";
   cwin << Message(Point(-CLOCK_RADIUS, CLOCK_RADIUS + 1), text);
}

int ccc_win_main()
{  
   Game clock_game;
   clock_game.play();

   return 0;
}
