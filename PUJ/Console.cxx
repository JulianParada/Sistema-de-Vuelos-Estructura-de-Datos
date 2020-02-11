// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include "Console.h"

// -------------------------------------------------------------------------
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#  include <conio.h>
#  include <Windows.h>
const char PUJ::Console::KEY_CTRL1   = -32;
const char PUJ::Console::BACKSPACE   =   8;
const char PUJ::Console::UP_ARROW    =  72;
const char PUJ::Console::DOWN_ARROW  =  80;
const char PUJ::Console::RIGHT_ARROW =  77;
const char PUJ::Console::LEFT_ARROW  =  75;
const char PUJ::Console::NEWLINE     = '\r';

#else
#  include <termios.h>
#  include <unistd.h>
const char PUJ::Console::KEY_CTRL1   =  17;
const char PUJ::Console::BACKSPACE   = 127;
const char PUJ::Console::UP_ARROW    =  65;
const char PUJ::Console::DOWN_ARROW  =  66;
const char PUJ::Console::RIGHT_ARROW =  67;
const char PUJ::Console::LEFT_ARROW  =  68;
const char PUJ::Console::NEWLINE     = '\n';

int getch( )
{
  struct termios oldt, newt;
  int ch;
  tcgetattr( STDIN_FILENO, &oldt );
  newt = oldt;
  newt.c_lflag &= ~( ICANON | ECHO );
  tcsetattr( STDIN_FILENO, TCSANOW, &newt );

  ch = getchar( );
  if( ch == PUJ::Console::ESC )
  {
    ch = getchar( );
    if( ch == 91 )
      ch = PUJ::Console::KEY_CTRL1;
  }
  tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
  return( ch );
}
#endif // defined(WIN32) || defined(_WIN32) || defined(__WIN32)

// -------------------------------------------------------------------------
const unsigned long PUJ::Console::MAX_HISTORY = 500;
const char PUJ::Console::TAB =  9;
const char PUJ::Console::ESC = 27;
const char PUJ::Console::DEL = 51;
const short PUJ::Console::M_LINE     = 0;
const short PUJ::Console::M_PASSWORD = 1;

// -------------------------------------------------------------------------
PUJ::Console::
Console( )
{
  this->m_MaxHistory = Self::MAX_HISTORY;
  this->m_Quit = false;
  this->m_Pos = -1;
  this->m_LinePos = 0;
  this->m_SkipOut = false;
}

// -------------------------------------------------------------------------
PUJ::Console::
Console( const std::string& prompt )
{
  this->m_MaxHistory = Self::MAX_HISTORY;
  this->m_Quit = false;
  this->m_Prompt = prompt;
  this->m_Pos = -1;
  this->m_LinePos = 0;
  this->m_SkipOut = false;
}

// -------------------------------------------------------------------------
PUJ::Console::
~Console( )
{
}

// -------------------------------------------------------------------------
void PUJ::Console::
run( )
{
  std::cout << this->m_Prompt;

  bool ok = true;
  while( ok )
  {
    this->m_Char = getch( );
    if( this->hotkeys( this->m_Char ) == 0 )
    {
      switch( this->m_Char )
      {
      case Self::ESC:
      {
      } // end case
      break;
      case Self::KEY_CTRL1:
      {
        char c = getch( );
        switch( c )
        {
        case Self::UP_ARROW:
        {
          if( this->m_History.size( ) > 0 )
          {
            if( this->m_Pos == -1 )
            {
              // store current command
              this->m_Unused = "";
              this->m_Unused.assign(
                this->m_Buffer.begin( ), this->m_Buffer.end( )
                );
            } // end if

            // clear line
            for( int i = 0; i < this->m_LinePos; ++i )
              std::cout << "\b \b";

            // clean buffer
            this->m_Buffer.clear( );

            this->m_Pos++;
            if( this->m_Pos > ( this->m_History.size( ) - 1 ) )
              this->m_Pos = this->m_History.size( ) - 1;

            // store in buffer
            for( int i = 0; i < this->m_History[ this->m_Pos ].size( ); ++i )
              this->m_Buffer.push_back( this->m_History[ this->m_Pos ][ i ] );
            this->m_LinePos = this->m_Buffer.size( );
            std::cout << this->m_History[ this->m_Pos ];
          } // end if
        } // end case
        break;
      case Self::DOWN_ARROW:
        {
          if( this->m_History.size( ) > 0 )
          {
            // clear line
            for( int i = 0; i < this->m_LinePos; ++i )
              std::cout << "\b \b";

            // clean buffer
            this->m_Buffer.clear( );

            this->m_Pos--;
            if( this->m_Pos < -1 )
              this->m_Pos = -1;
            if( this->m_Pos >= 0 )
            {
              std::cout << this->m_History[ this->m_Pos ];
              // store in buffer
              for( int i = 0; i < this->m_History[ this->m_Pos ].size( ); ++i )
                this->m_Buffer.push_back(
                  this->m_History[ this->m_Pos ][ i ]
                  );
            }
            else
            {
              if( this->m_Buffer.size( ) > 0 )
              {
                std::cout << this->m_Unused;

                // store in buffer
                for( int i = 0; i < this->m_Unused.size( ); ++i )
                  this->m_Buffer.push_back( this->m_Unused[ i ] );
              } // end if
            } // end if
            this->m_LinePos = this->m_Buffer.size( );
          } // end if
        } // end case
        break;
        case Self::LEFT_ARROW:
        {
          // if there are characters to move left over, do so
          if( this->m_LinePos > 0 )
          {
            std::cout << "\b";
            this->m_LinePos--;
          } // end if
        } // end case
        break;
        case Self::RIGHT_ARROW:
        {
          // if there are characters to move right over, do so
          if( this->m_LinePos < this->m_Buffer.size( ) )
          {
            std::cout << this->m_Buffer[ this->m_LinePos ];
            this->m_LinePos++;
          } // end if
        } // end case
        break;
        case Self::DEL:
        {
          if( this->m_LinePos < this->m_Buffer.size( ) )
          {
            this->m_SkipOut = true;
            this->m_Buffer.erase( this->m_Buffer.begin( ) + this->m_LinePos );
            // update screen after current position
            for( int i = this->m_LinePos; i < this->m_Buffer.size( ); ++i )
              std::cout << this->m_Buffer[ i ];
            // erase last char
            std::cout << " ";
            for( int i = this->m_LinePos; i < this->m_Buffer.size( ); ++i )
              std::cout << "\b";
            // make-up for erase position
            std::cout << "\b";
          } // end if
        } // end case
        break;
        default:
        {
          this->m_SkipOut = true;
        } // end case
        break;
        } // end switch
      } // end case
      break;
      case Self::BACKSPACE:
      {
        if( this->m_LinePos > 0 )
        {
          // move cursor back, blank char, and move cursor back again
          std::cout << "\b \b";
          // don't forget to clean the buffer and update line position
          if( this->m_LinePos == this->m_Buffer.size( ) )
          {
            this->m_Buffer.pop_back( );
            this->m_LinePos--;
          }
          else
          {
            this->m_LinePos--;
            this->m_Buffer.erase( this->m_Buffer.begin( ) + this->m_LinePos );
            // update screen after current position
            for( int i = this->m_LinePos; i < this->m_Buffer.size( ); ++i )
              std::cout << this->m_Buffer[ i ];
            // erase last char
            std::cout << " ";
            for( int i = this->m_LinePos + 1; i < this->m_Buffer.size( ); ++i )
              std::cout << "\b";
            // make-up for erase position and go to new position
            std::cout << "\b\b";
          } // end if
        } // end if
      } // end case
      break;
      case Self::TAB:
      {
      } // end case
      break;
      case Self::NEWLINE:
      {
        // store in string
        this->m_String.assign(
          this->m_Buffer.begin( ), this->m_Buffer.end( )
          );

        // save command to history
        // trimming of command should be done in callback function
        if( this->m_String.length( ) > 0 ) 
          this->m_History.push_front( this->m_String );

        // run command
        std::cout << std::endl;
        this->trigger( this->m_String );
                                
        // check for exit command
        ok = !( this->m_Quit );
        if( ok )
        {
          if( this->m_History.size( ) > this->m_MaxHistory )
            this->m_History.pop_back( );

          // clean buffer
          this->m_Buffer.clear( );

          // print prompt. new line should be added from callback function
          std::cout << this->m_Prompt;

          // reset position
          this->m_Pos = -1;
          this->m_LinePos = 0;
        } // end if
      } // end case
      break;
      default:
      {
        if( !( this->m_SkipOut ) )
        {
          std::cout << this->m_Char;
          if( this->m_LinePos != this->m_Buffer.size( ) )
          {
            // line position is not at end. Insert new char
            this->m_Buffer.insert(
              this->m_Buffer.begin( ) + this->m_LinePos, this->m_Char
              );
            // update screen after current position
            for( int i = this->m_LinePos + 1; i < this->m_Buffer.size( ); ++i )
              std::cout << this->m_Buffer[ i ];
            for( int i = this->m_LinePos + 1; i < this->m_Buffer.size( ); ++i )
              std::cout << "\b";
          }
          else
            this->m_Buffer.push_back( this->m_Char );
          this->m_LinePos++;
        }
        else
          this->m_SkipOut = false;
      } // end case
      break;
      } // end switch
    } // end if
  } // end while
}

// -------------------------------------------------------------------------
void PUJ::Console::
setPrompt( const std::string& prompt )
{
  this->m_Prompt = prompt;
}

// -------------------------------------------------------------------------
int PUJ::Console::
trigger( const std::string& cmd )
{
  return( ( this->m_Quit )? 1: 0 );
}

// -------------------------------------------------------------------------
int PUJ::Console::
hotkeys( char c )
{
  return( 0 );
}

// -------------------------------------------------------------------------
void PUJ::Console::
pause( )
{
  getch( );
}

// -------------------------------------------------------------------------
void PUJ::Console::
quit( )
{
  this->m_Quit = true;
}

// -------------------------------------------------------------------------
std::string PUJ::Console::
getLine( )
{
  return( this->getLine( Self::M_LINE, "" ) );
}

// -------------------------------------------------------------------------
std::string PUJ::Console::
getLine( int mode, const std::string& delimiter )
{
  std::string line;
  char c;
  bool ok = true;
  while( ok )
  {
    c = getch( );
    if( c == Self::NEWLINE )
    {
      std::cout << std::endl;
      ok = false;
    }
    else if( c == Self::BACKSPACE )
    {
      if( line.length( ) > 0 )
      {
        line = line.substr( 0,line.size( ) - 1 );
        if( mode != Self::M_PASSWORD )
          std::cout << "\b \b";
      } // end if
    }
    else
    {
      line += c;
      if( mode != Self::M_PASSWORD )
        std::cout << c;
    } // end if
  } // end while
  return( line );
}

// -------------------------------------------------------------------------
void PUJ::Console::
setMaxHistory( int count )
{
  this->m_MaxHistory = count;
}

// -------------------------------------------------------------------------
void PUJ::Console::
setBuffer( const std::string& buffer )
{
  this->m_Buffer.assign( buffer.begin( ), buffer.end( ) );
  this->m_LinePos = this->m_Buffer.size( );
}

// -------------------------------------------------------------------------
std::string PUJ::Console::
getBuffer( ) const
{
  return( std::string( this->m_Buffer.begin( ), this->m_Buffer.end( ) ) );
}

// eof - Console.cxx
