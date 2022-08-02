#include <wx/wx.h>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

const double PI = 3.141592653589793;

const int ID_GUESS = 1000;
const int ID_PLAYER_NAME = 1001;
const int ID_PLAYER_LEVEL = 1002;

/**
   A clock that can draw its face.
*/
class Clock
{
public:
   /**
      Constructs a clock with a given center and radius.
      @param x the x-coordinate of the center
      @param y the y-coordinate of the center
      @param r the radius of the clock
   */              
   Clock(int x, int y, int r);

   /**
      Sets the current time.
      @param h the hours to set
      @param m the minutes to set
   */
   void set_time(int h, int m);

   /**
      Draws the clock face, with tick marks and hands.
      @param dc the device context to draw on
   */
   void draw(wxDC& dc) const;
private:
   /**
      Draw a tick mark (hour or minute mark).
      @param dc the device context to draw on
      @param angle the angle in minutes (0...59, 0 = top)
      @param length the length of the tick mark, as a fraction
      of the radius (between 0.0 and 1.0)
   */
   void draw_tick(wxDC& dc, double angle, double length) const;

   /**
      Draw a hand, starting from the center.
      @param dc the device context to draw on
      @param angle the angle in minutes (0...59, 0 = top)
      @param length the length of the hand, as a fraction
      of the radius (between 0.0 and 1.0)
   */
   void draw_hand(wxDC& dc, double angle, double length) const;

   int hours;
   int minutes;
   int centerx;
   int centery;
   int radius;
};

/**
   The player of the clock game.
*/
class Player
{
public:
   /**
      Constructs a player with name "Player", 
      level 1, and score 0.
   */
   Player();

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

   /**
      Sets the player's level.
      @param l the level
   */
   void set_level(int l);

   /**
      Sets the player's name.
      @param n the name
   */
   void set_name(string n);
private:
   string name;
   int score;
   int level;
};

/**
   The window that shows the clock.
*/
class ClockWindow : public wxWindow
{
public:
   /**
      Constructs a clock window.
      @param parent the parent window
   */
   ClockWindow(wxWindow* parent);
   /**
      Sets the time of the clock and repaints it.
      @param h the hours
      @param m the minutes
   */
   void set_time(int h, int m);
   /**
      Paints the clock.
      @param event the event descriptor
   */      
   void OnPaint(wxPaintEvent& event);
private:
   Clock clock;
   DECLARE_EVENT_TABLE()
};

/**
   The frame that contains the clock window and the
   fields for entering a guess.
*/
class GameFrame : public wxFrame
{
public:
   /**
      Constructs the game frame.
   */
   GameFrame();

   /**
      Starts a new round, with a new clock time.
   */
   void new_round();
   /**
      Processes the player's guess.
      @param event the event descriptor
   */         
   void OnGuess(wxCommandEvent& event);
   /**
      Prompts the player to enter a name.
      @param event the event descriptor
   */         
   void OnPlayerName(wxCommandEvent& event);
   /**
      Prompts the player to enter a level.
      @param event the event descriptor
   */         
   void OnPlayerLevel(wxCommandEvent& event);
private:
   ClockWindow* window;
   wxTextCtrl* hour_text;
   wxTextCtrl* minute_text;
   Player player;
   int current_hours;
   int current_minutes;
   int tries;
   DECLARE_EVENT_TABLE()
};

/**
   The clock game application.
*/
class GameApp : public wxApp
{
public:
   /**
      Constructs the application.
   */
   GameApp();
   virtual bool OnInit();
private:
   GameFrame* frame;
};

DECLARE_APP(GameApp)

IMPLEMENT_APP(GameApp)

BEGIN_EVENT_TABLE(ClockWindow, wxWindow)
   EVT_PAINT(ClockWindow::OnPaint)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(GameFrame, wxFrame)
   EVT_BUTTON(ID_GUESS, GameFrame::OnGuess)
   EVT_MENU(ID_PLAYER_NAME, GameFrame::OnPlayerName)
   EVT_MENU(ID_PLAYER_LEVEL, GameFrame::OnPlayerLevel) 
END_EVENT_TABLE()

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

Clock::Clock(int x, int y, int r)
{  
   centerx = x;
   centery = y;
   radius = r;
}

void Clock::set_time(int h, int m)
{  
   hours = h;
   minutes = m;
}

void Clock::draw_tick(wxDC& dc, double angle, 
   double length) const
{  
   double alpha = -PI / 2 + 6 * angle * PI / 180;
   dc.DrawLine(
      centerx + static_cast<int>(
         cos(alpha) * radius * (1 - length)),
      centery + static_cast<int>(
         sin(alpha) * radius * (1 - length)),
      centerx + static_cast<int>(cos(alpha) * radius),
      centery + static_cast<int>(sin(alpha) * radius));
}

void Clock::draw_hand(wxDC& dc, double angle, 
   double length) const
{  
   double alpha = -PI / 2 + 6 * angle * PI / 180;
   dc.DrawLine(centerx, centery,
      centerx + static_cast<int>(cos(alpha) * radius * length),
      centery + static_cast<int>(sin(alpha) * radius * length));
}

void Clock::draw(wxDC& dc) const
{  
   dc.DrawEllipse(centerx - radius, centery - radius, 
      2 * radius, 2 * radius);
   const double HOUR_TICK_LENGTH = 0.2;
   const double MINUTE_TICK_LENGTH = 0.1;
   const double HOUR_HAND_LENGTH = 0.6;
   const double MINUTE_HAND_LENGTH = 0.75;
   for (int i = 0; i < 12; i++)
   {  
      draw_tick(dc, i * 5, HOUR_TICK_LENGTH);
      int j;
      for (j = 1; j <= 4; j++)
         draw_tick(dc, i * 5 + j, MINUTE_TICK_LENGTH);
   }
   draw_hand(dc, minutes, MINUTE_HAND_LENGTH);
   draw_hand(dc, (hours + minutes / 60.0) * 5, HOUR_HAND_LENGTH);
}

Player::Player()
{
   name = "Player";
   level = 1;
   score = 0;
}

void Player::set_level(int l)
{  
   level = l;
}

void Player::set_name(string n)
{  
   name = n;
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

ClockWindow::ClockWindow(wxWindow* parent)
   : wxWindow(parent, -1),
   clock(200, 200, 200)
{
}

void ClockWindow::OnPaint(wxPaintEvent& event)
{
   wxPaintDC dc(this);
   dc.SetBrush(*wxTRANSPARENT_BRUSH);
   clock.draw(dc);
}

void ClockWindow::set_time(int h, int m)
{
   clock.set_time(h, m);
   Refresh();
}

GameFrame::GameFrame() 
   : wxFrame(NULL, -1, "GameFrame")
{
   // initialize menu
   wxMenu* menu = new wxMenu();
   menu->Append(ID_PLAYER_NAME, "Name");
   menu->Append(ID_PLAYER_LEVEL, "Level");

   // add menu to menu bar
   wxMenuBar* menu_bar = new wxMenuBar();
   SetMenuBar(menu_bar);
   menu_bar->Append(menu, "Player");   

   window = new ClockWindow(this);

   hour_text = new wxTextCtrl(this, -1);
   minute_text = new wxTextCtrl(this, -1);

   wxButton* guess_button = new wxButton(this, 
      ID_GUESS, "Guess");

   wxBoxSizer* bottom_sizer = new wxBoxSizer(wxHORIZONTAL);
   bottom_sizer->Add(new wxStaticText(this, -1, "Hours"));
   bottom_sizer->Add(hour_text);
   bottom_sizer->Add(new wxStaticText(this, -1, "Minutes"));
   bottom_sizer->Add(minute_text);
   bottom_sizer->Add(guess_button);

   wxBoxSizer* frame_sizer = new wxBoxSizer(wxVERTICAL);
   frame_sizer->Add(window, 1, wxGROW);
   frame_sizer->Add(bottom_sizer, 0, wxALIGN_CENTER);

   SetAutoLayout(true);
   SetSizer(frame_sizer);

   new_round();
}

void GameFrame::OnGuess(wxCommandEvent& event)
{
   tries++;
   int hours = atoi(hour_text->GetValue().c_str());
   int minutes = atoi(minute_text->GetValue().c_str());
   if (hours < 1 || hours > 12)
   {
      wxMessageDialog* dialog = new wxMessageDialog(this,
         "Hours must be between 1 and 12");
      dialog->ShowModal();      
      dialog->Destroy();
      return;
   }
   if (minutes < 0 || minutes > 59)
   {
      wxMessageDialog* dialog = new wxMessageDialog(this,
         "Hours must be between 1 and 12");
      dialog->ShowModal();      
      dialog->Destroy();
      return;
   }
   if (current_hours == hours && current_minutes == minutes)
   {
      string text = "Congratulations, " + player.get_name()
         + "! That is correct.";     
      wxMessageDialog* dialog = new wxMessageDialog(this,
         text.c_str());
      dialog->ShowModal();
      dialog->Destroy();
      player.increment_score();
      new_round();
   }
   else
   {
      string text = "Sorry, " + player.get_name()
         + "! That is not correct.";
      wxMessageDialog* dialog = new wxMessageDialog(this,
         text.c_str());
      dialog->ShowModal();
      dialog->Destroy();
      if (tries == 2) new_round();   
   }
}

void GameFrame::new_round()
{
   tries = 0;
   int level = player.get_level();
   if (level == 1) current_minutes = 0;
   else if (level == 2) current_minutes = 15 * rand_int(0, 3);
   else if (level == 3) current_minutes = 5 * rand_int(0, 11);
   else current_minutes = rand_int(0, 59);
   current_hours = rand_int(1, 12);
   window->set_time(current_hours, current_minutes);
}

void GameFrame::OnPlayerName(wxCommandEvent& event)
{
   wxTextEntryDialog* dialog = new wxTextEntryDialog(this,
      "What is your name?");
   dialog->ShowModal();
   player.set_name(dialog->GetValue().c_str());
   dialog->Destroy();
}

void GameFrame::OnPlayerLevel(wxCommandEvent& event)
{
   wxTextEntryDialog* dialog = new wxTextEntryDialog(this,
      "At what level do you want to play? (1-4)");
   dialog->ShowModal();
   int level = atoi(dialog->GetValue().c_str());
   dialog->Destroy();
   if (level < 1 || level > 4)
   {
      wxMessageDialog* dialog = new wxMessageDialog(this,
         "The level must be between 1 and 4");
      dialog->ShowModal();      
      dialog->Destroy();
      return;
   }
   player.set_level(level);
}

GameApp::GameApp()
{
   rand_seed();
   frame = new GameFrame();
}

bool GameApp::OnInit()
{
   frame->Show(true);
   return true;
}

