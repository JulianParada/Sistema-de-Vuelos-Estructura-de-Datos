// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================
#ifndef __PUJ__Console__h__
#define __PUJ__Console__h__

#include <deque>
#include <iostream>
#include <string>

namespace PUJ
{
  /**
   */
  class Console
  {
  public:
    typedef Console Self;

  public:
    Console( );
    Console( const std::string& prompt );
    virtual ~Console( );

    void run( );
    void setPrompt( const std::string& prompt );
    virtual int trigger( const std::string& cmd );
    virtual int hotkeys( char c );
    void pause( );
    void quit( );
    std::string getLine( );
    std::string getLine( int mode, const std::string& delimiter = " " );
    void setMaxHistory( int count );
    void setBuffer( const std::string& buffer );
    std::string getBuffer( ) const;

  public:
    static const unsigned long MAX_HISTORY;
    static const char KEY_CTRL1;
    static const char BACKSPACE;
    static const char UP_ARROW;
    static const char DOWN_ARROW;
    static const char RIGHT_ARROW;
    static const char LEFT_ARROW;
    static const char TAB;
    static const char ESC;
    static const char DEL;
    static const char NEWLINE;
    static const short M_LINE;
    static const short M_PASSWORD;

  protected:
    bool m_Quit;
    int m_MaxHistory;
    std::string m_Prompt;

    int m_Pos;
    int m_LinePos;
    bool m_SkipOut;
    char m_Char;
    std::string m_String;
    std::string m_Unused;
    std::deque< char > m_Buffer;
    std::deque< std::string > m_History;
  };
} // end namespace

#endif // __PUJ__Console__h__

// eof - Console.h
