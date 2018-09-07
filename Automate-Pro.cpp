#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__) || defined(__TOS_WIN__)

  #include <windows.h>

  inline void delay( unsigned long ms )
    {
    Sleep( ms );
    }

#else  /* presume POSIX */

  #include <unistd.h>


  inline void delay( unsigned long ms )
    {
    usleep( ms * 1000 );
  }
    
#endif 

#include <iostream>
#include <fstream>
#include <csignal>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include <vector>

#include <sqlite3.h> 

#include <tesseract/baseapi.h>
#include <tesseract/strngs.h>
#include <leptonica/allheaders.h>

#include <wand/MagickWand.h>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>

#include <wx/aboutdlg.h>
#include <wx/app.h>
#include <wx/event.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/font.h>
#include <wx/fontutil.h>
#include <wx/msgdlg.h>
#include <wx/filedlg.h>
#include <wx/wfstream.h>
#include <wx/textfile.h>
#include <wx/textdlg.h>
#include <wx/url.h>

#include "Automate.h"

 extern "C" {
    #include <xdo.h>
  }
  
#define ON True
#define OFF False

#define main_icon_xpm "mainicon.ico"

cv::Point MatchingMethod( int, void* );
void click_mouse(Window window_id, int button);

using namespace tesseract;
using namespace std;
using namespace cv;
using std::size_t;
using std::vector;

std::string panel;
std::stringstream stringstream1;
std::stringstream stringstream2;
std::string listboxline = "";

bool boolt = true;
bool boolf = false;

int match_method;
int listcount = 0;
int SSNum=0;
int Executed=0;
int Saved=0;
	
wxString file;
wxTextFile tfile; 

Mat img; Mat templ; Mat result;

unsigned int mainicon_ico_len = 4286;

unsigned char mainicon_ico[] = {
  0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x20, 0x20, 0x00, 0x00, 0x01, 0x00,
  0x20, 0x00, 0xa8, 0x10, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x28, 0x00,
  0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x01, 0x00,
  0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0,
  0xc0, 0xff, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80,
  0x80, 0xff, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80,
  0x80, 0xff, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80,
  0x80, 0xff, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80,
  0x80, 0xff, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80,
  0x80, 0xff, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80,
  0x80, 0xff, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80,
  0x80, 0xff, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80,
  0x80, 0xff, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80,
  0x80, 0xff, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80,
  0x80, 0xff, 0x80, 0x80, 0x80, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x80,
  0x80, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xf9, 0xf3, 0xe0, 0xff, 0xf5, 0xe9, 0xc5, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x80, 0x80, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xea, 0xd2,
  0x83, 0xff, 0xe7, 0xcb, 0x70, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0x80, 0x80, 0x80, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xfd, 0xfb, 0xf7, 0xff, 0xdd, 0xb3, 0x2e, 0xff, 0xdc, 0xb0,
  0x27, 0xff, 0xfc, 0xfa, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x80,
  0x80, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf1, 0xe0,
  0xaa, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xf0, 0xdf,
  0xa8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x80, 0x80, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe2, 0xbe, 0x4d, 0xff, 0xdb, 0xaf,
  0x21, 0xff, 0xf0, 0xde, 0xa5, 0xff, 0xe2, 0xc0, 0x51, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0x80, 0x80, 0x80, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xee,
  0xd2, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xe7, 0xca, 0x6c, 0xff, 0xfe, 0xfd,
  0xfd, 0xff, 0xde, 0xb6, 0x36, 0xff, 0xf8, 0xf1, 0xdb, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x80,
  0x80, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe8, 0xcb, 0x72, 0xff, 0xdb, 0xae,
  0x1e, 0xff, 0xf6, 0xed, 0xcd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xec, 0xd4,
  0x8a, 0xff, 0xea, 0xd1, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x80, 0x80, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xf7,
  0xeb, 0xff, 0xdb, 0xaf, 0x23, 0xff, 0xe1, 0xbe, 0x4c, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xf4, 0xe1, 0xff, 0xdc, 0xb2,
  0x2b, 0xff, 0xfc, 0xfa, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0x80, 0x80, 0x80, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xed, 0xd7, 0x91, 0xff, 0xdb, 0xae,
  0x1e, 0xff, 0xf1, 0xe1, 0xad, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0xc2, 0x57, 0xff, 0xef, 0xdc,
  0xa0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x80,
  0x80, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xfd,
  0xfb, 0xff, 0xde, 0xb6, 0x35, 0xff, 0xdd, 0xb4, 0x30, 0xff, 0xfd, 0xfc,
  0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xf1, 0xe1, 0xaf, 0xff, 0xdf, 0xb9, 0x3e, 0xff, 0xfe, 0xfd,
  0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x80, 0x80, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf2, 0xe3, 0xb2, 0xff, 0xdb, 0xae,
  0x1e, 0xff, 0xeb, 0xd3, 0x88, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xfb,
  0xf7, 0xff, 0xdc, 0xb2, 0x2b, 0xff, 0xf3, 0xe4, 0xb7, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0x80, 0x80, 0x80, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xe2, 0xbf, 0x50, 0xff, 0xda, 0xae, 0x1f, 0xff, 0xfa, 0xf4,
  0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe9, 0xcf,
  0x7b, 0xff, 0xe1, 0xbc, 0x47, 0xff, 0xfe, 0xfd, 0xfc, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x80,
  0x80, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xfe, 0xfd, 0xfd, 0xff, 0xee, 0xdb, 0x9c, 0xff, 0xda, 0xad,
  0x1e, 0xff, 0xe4, 0xc5, 0x5e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xee, 0xd3, 0xff, 0xdb, 0xae,
  0x1e, 0xff, 0xeb, 0xd3, 0x88, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x80, 0x80, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0x80, 0x80, 0x80, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0x80, 0x80,
  0x80, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80,
  0x80, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0x80, 0x80,
  0x80, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0x80, 0x80, 0x80, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80, 0x80, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0x80, 0x80, 0x80, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0x80, 0x80,
  0x80, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0x80, 0x80, 0x80, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0,
  0xc0, 0xff, 0x80, 0x80, 0x80, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae,
  0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae,
  0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae,
  0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae,
  0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae,
  0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae,
  0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae,
  0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae,
  0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae,
  0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae,
  0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae,
  0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae,
  0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae,
  0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae,
  0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae,
  0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae,
  0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae,
  0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae,
  0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae,
  0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae,
  0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae,
  0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0xdb, 0xae, 0x1e, 0xff, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff
};

char* itoa(int value, char* result, int base) {
		// check that the base is valid
		if (base < 2 || base > 36) { *result = '\0'; return result; }

		char* ptr = result, *ptr1 = result, tmp_char;
		int tmp_value;

		do {
			tmp_value = value;
			value /= base;
			*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
		} while ( value );

		*ptr-- = '\0';
		while(ptr1 < ptr) {
			tmp_char = *ptr;
			*ptr--= *ptr1;
			*ptr1++ = tmp_char;
		}
		return result;
}

bool FileExists(string strFilename)
	{
	struct stat stFileInfo;
	bool blnReturn;
	int intStat;
	intStat = stat(strFilename.c_str(),&stFileInfo);
	if(intStat == 0) { blnReturn = true; } else { blnReturn = false; }
	return(blnReturn);
}

int write_png(string filename, unsigned char* data, unsigned int length)
{
        unsigned int i=0;
        fstream file(filename.c_str(), ios::out | ios::binary);
        if (file){
            while ( i <= length )
                {
                file << data[i];
                i++;
            }
        file.close();
        } else {return 0;}
    return 1;
}

int MyX11ErrorHandler(Display *, XErrorEvent *error_event)
	{
	return 0;
}

std::string get_one_line_from_file(std::string fileName)
	{
	ifstream file;
	string lineread;
	string line;

	file.open(fileName.c_str());
	      if (!file){ return "exit"; }
		std::getline(file, lineread); // Read 1 line
		file.close();
		return lineread;
}

std::string read_db_by_id(string wid)
    {
       sqlite3 *db;
       sqlite3_stmt *stmt;
       
       std::string sql;
       std::string select;
       std::string sqlend = "\";";
       std::string widname;
       //const unsigned char *widname;
       char *zErrMsg = 0;
       int rc;

       rc = sqlite3_open("automate.db", &db);
       if( rc ){
          fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
          return(0);
       }else{
       select = "SELECT WINDOWNAME from VIXIV where WID = \"";
       sql = select + wid + sqlend;
       //std::cout << "SQL: " << sql << "\n";
       
       rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
        if (rc != SQLITE_OK) {
            std::cout << "Error: "; //<< sqlite3_errmsg(db);
            return "0";
        }
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            widname =  (const char*) sqlite3_column_text(stmt, 0);
            //std::cout << "\nWindow Name: " << widname << "\n";
        }
        sqlite3_free(zErrMsg);
        
        if (rc != SQLITE_DONE) {
            fprintf(stderr, sqlite3_errmsg(db));
        }else{
            sqlite3_finalize(stmt);
            return widname;

        }
        sqlite3_close(db);
        return widname;
        }
    }

std::string read_db_by_name(string windowname)
    {
       sqlite3 *db;
       char *zErrMsg = 0;
       std::string sql;
       std::string select;
       //const char* data;
       int rc;

       rc = sqlite3_open("automate.db", &db);
       if( rc ){
          fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
          return(0);
       }else{
       select = "SELECT WID from VIXIV where WINDOWNAME = ";
       sql = select + windowname;
       //std::cout << "SQL: " << sql << "\n";
       rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &zErrMsg);
       if( rc != SQLITE_OK ){
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
        }
        sqlite3_close(db);
        return 0;
        }
    }

int write_db(string windowname, string wid)
    {
       sqlite3 *db;
       char *zErrMsg = 0;
       std::string sql;
       std::string insert;
       std::string sqlclose;
       int rc;

       rc = sqlite3_open("automate.db", &db);
       if( rc ){
          fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
          return(0);
       }else{
           //if(!select count(type) from sqlite_master where type='table' and name='VIXIV') {
               sql = "CREATE TABLE IF NOT EXISTS VIXIV(ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, WINDOWNAME TEXT NOT NULL, WID INT NOT NULL);";
               rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
               if( rc != SQLITE_OK ){
                    //fprintf(stderr, "SQL error: %s\n", zErrMsg);
                    sqlite3_free(zErrMsg);
               }
            //}
            
           insert = "INSERT INTO VIXIV (WINDOWNAME,WID) VALUES (";
        // << windowname.c_str() << ", " << wid.c_str() << ");";
           sqlclose = ");";
           sql = insert + windowname + ", " + wid + sqlclose;
           rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
           
           if( rc != SQLITE_OK ){
              fprintf(stderr, "\nSQL error: %s\n", zErrMsg);
              sqlite3_free(zErrMsg);
           }//else{
            //  fprintf(stdout, "\nRecord created successfully!\n");
           //}

        }
        sqlite3_close(db);
        return 0;
    }

std::string wid_search_by_id(std::string wid)
    {
        remove("widsearch.sh");
        fstream file("widsearch.sh",ios::out);
        if (file){
        file << "#!/usr/bin/env bash\n";
        file << "rm widsearch 2>/dev/null\n";
        file << "known_windows=$(xwininfo -int -id " << wid << " 2>/dev/null |sed -e \'s/^ *//\'|grep -E \"id:\" |awk \'{ print $4 }\') 2>/dev/null\n";
        file << "echo \"$known_windows\" > widsearch\n";
        file.close();
    } else {return 0;}
	if(FileExists("widsearch.sh")){
		system("bash widsearch.sh");
        } else {
            std::cout << "Error Executing X Window ID Script!";
            return "ERROR";
        }
    if(FileExists("widsearch")){
      wid = get_one_line_from_file("widsearch");
      return wid;
    }
    return "NULL";
}

std::string wid_search_by_name(std::string windowname)
    {
        std::string wid;
        remove("widsearch.sh");
        fstream file("widsearch.sh",ios::out);
        if (file){
        file << "#!/usr/bin/env bash\n";
        file << "rm widsearch 2>/dev/null\n";
        file << "known_windows=$(xwininfo -int -name \"" << windowname << "\" 2>/dev/null |sed -e \'s/^ *//\'|grep -E \"id:\" |awk \'{ print $4 }\') 2>/dev/null\n";
        file << "echo \"$known_windows\" > widsearch\n";
        file.close();
    } else {return 0;}
	if(FileExists("widsearch.sh")){
		system("bash widsearch.sh");
        } else {
            std::cout << "Error Executing X Window ID Script!";
            return "ERROR";
        }
    if(FileExists("widsearch")){
      wid = get_one_line_from_file("widsearch");
      return wid;
    }
    return "NULL";
}

int getwids ()
    {
		std::cout << "\nPlease Select the target window to grab Window ID...\n" << std::flush;
        remove("wid.sh");
        fstream file("wid.sh",ios::out);
        if (file){
        file << "#!/usr/bin/env bash\n";
        file << "rm wid widname 2>/dev/null\n";
        //file << "known_window=$(xwininfo -all -int 2>/dev/null |sed -e \'s/^ *//\'|grep -E \"Parent window id:\" |awk \'{ print $4 }\') 2>/dev/null\n";
        //file << "echo \"$known_window\" > wid\n";
        //file << "known_windows=$(xwininfo -int 2>/dev/null |sed -e \'s/^ *//\'|grep -E \"id:\" |awk \'{ print $4 }\') 2>/dev/null\n";
        //file << "echo \"$known_windows\" > wid\n";
        file << "widname=\"\"\n";
        file << "xwin=$(xwininfo -int 2>/dev/null | sed -e 's/^ *//' | grep -E \"id:\") 2>/dev/null\n";
        file << "win=( $xwin )\n";
        file << "n=0\n";
        file << "for i in \"${win[@]}\"\n";
        file << "do\n";
        file << "n=$((n+1))\n";
        file << "   if [ \"$n\" = 4 ]; then\n";
        file << "		echo $i > wid\n";
        file << "	fi\n";
        file << "	if [ \"$n\" -gt 4 ]; then\n";
        file << "		 widname=\"$widname $i\"\n";
        file << "	fi\n";
        file << "done\n";
        file << "echo $widname > widname\n";
        file.close();
    } else {return 0;}
	if(FileExists("wid.sh")){
		system("bash wid.sh");
        //remove("wid.sh");
        } else {
            std::cout << "Error Executing X Window ID Script!";
            return 0;
        }
	return 1;
}

string screenshot_window(string wid)
{
        std::string filename = wid.c_str();
        wid.insert (0, "x:");
   	 	MagickWandGenesis();
   		MagickWand *wand = NULL;
   	 	wand = NewMagickWand();
   		MagickReadImage(wand, wid.c_str()); // <-- Invoke ImportImageCommand
        filename.append(".png");
   		MagickWriteImage(wand,filename.c_str());
   	 	if(wand)wand = DestroyMagickWand(wand);
   	 	MagickWandTerminus();
    return filename;
}

cv::Point Matching_Method( int, void* )
	{

	int result_cols = img.cols - templ.cols + 1;
	int result_rows = img.rows - templ.rows + 1;
	result.create( result_rows, result_cols, CV_32FC1 );
	match_method = 5; 		//0: SQDIFF 1: SQDIFF NORMED 2: TM CCORR 3: TM CCORR NORMED 4: TM COEFF 5: TM COEFF NORMED

	matchTemplate( img, templ, result, match_method );
	normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

	double minVal; double maxVal; Point minLoc; Point maxLoc; Point matchLoc;

	minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

	if( match_method == 0 || match_method == 1)
	{ matchLoc = minLoc; }
	else
	{ matchLoc = maxLoc; }

	return matchLoc;
}

cv::Point match_screenshot(std::string image, std::string templateimg)
	{

	img = cv::imread( image, 1 ); 			/// Load image
	templ = cv::imread( templateimg, 1 ); 			/// Load template

	cv::Point Matched = Matching_Method( 0, 0 );
    return Matched;
}

void raw_key_press(KeyCode code)
	{
	Display *display = XOpenDisplay(NULL);

		XTestFakeKeyEvent(display, code, ON, CurrentTime);
		usleep(5000);
		XTestFakeKeyEvent(display, code, OFF, CurrentTime);

	XFlush(display);
	XCloseDisplay(display);
}


void key_press(string keycodes, int shiftenabled)
	{
	Display *display = XOpenDisplay(NULL);
//  keycode = XKeysymToKeycode(display, keycode);
    string capsl = "Caps_Lock";
    string shiftl = "Shift_R";
    string atsign = "at";

    KeyCode shift = XKeysymToKeycode(display, XStringToKeysym(shiftl.c_str()));
    //KeyCode caps = XKeysymToKeycode(display, XStringToKeysym(capsl.c_str()));
    KeyCode At = XKeysymToKeycode(display, XStringToKeysym(atsign.c_str()));
    KeyCode code = XKeysymToKeycode(display, XStringToKeysym(keycodes.c_str()));

	if (shiftenabled == 1 ){
		XTestFakeKeyEvent(display, shift, ON, CurrentTime);
		//XTestFakeKeyEvent(display, shift, OFF, CurrentTime);
		XFlush(display);
        usleep(900);
        if (keycodes == "@"){
            XTestFakeKeyEvent(display, At, ON, CurrentTime);
            usleep(900);
            XTestFakeKeyEvent(display, At, OFF, CurrentTime);
        } else {
            XTestFakeKeyEvent(display, code, ON, CurrentTime);
            XFlush(display);
            usleep(900);
            XTestFakeKeyEvent(display, code, OFF, CurrentTime);
		}
		XFlush(display);
        usleep(900);
		//XTestFakeKeyEvent(display, shift, ON, CurrentTime);
		XTestFakeKeyEvent(display, shift, OFF, CurrentTime);
		XFlush(display);
	} else {
        usleep(900);
        XTestFakeKeyEvent(display, code, ON, CurrentTime);
        usleep(900);
        XTestFakeKeyEvent(display, code, OFF, CurrentTime);
	}
	XFlush(display);
	XCloseDisplay(display);
}

void click_mouse(int button)
	{
    Display *disp = XOpenDisplay(NULL);
    xdo_t * xdo_0;
    xdo_0 = xdo_new_with_opened_display(disp,NULL,1);
    
    //xdo_click_window(xdo_0, NULL, button);
    xdo_mouse_down(xdo_0,NULL,button);
    usleep(5000);
    xdo_mouse_up(xdo_0,NULL,button);
    
    XFlush(disp);
    xdo_0 = NULL;
    disp = NULL;
    xdo_free(xdo_0);   
    
    /*
    fstream file("click.sh",ios::out);
        if (file){
		    file << "#!/usr/bin/env bash\n";
		 	file << "xdotool click " << button;
        }
        file.close();
        system("bash click.sh");
        
        //remove("click.sh");
    */   
        
	/*Display *display = XOpenDisplay(NULL);
	XEvent event;
	if(display == NULL)
	{
		exit(EXIT_FAILURE);
	}

	memset(&event, 0x00, sizeof(event));

	event.type = ButtonPress;
	event.xbutton.button = button;
	event.xbutton.same_screen = True;

	XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

	event.xbutton.subwindow = event.xbutton.window;

	while(event.xbutton.subwindow)
	{
		event.xbutton.window = event.xbutton.subwindow;
		XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
	}

	if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stdout, "Error Sending Event !!!\n");

	XFlush(display);

	usleep(1000);

    event.type = ButtonRelease;
	event.xbutton.state = 0x100;

	if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stdout, "Error Sending Event !!!\n");

	XFlush(display);

	XCloseDisplay(display);
     */
     
}

int move_mouse(int X, int Y, string id)
{
	std::stringstream ss1;
    std::stringstream ss2;
    ss1 = std::stringstream();
    ss2 = std::stringstream();
    ss1.clear();
    ss2.clear();
    
    Window wid=0;

    ss2 << id;
    ss2 >> wid;
	//std::cout << endl << "Mouse Move Wid: " << wid << endl;
    Display *displayMain = XOpenDisplay(NULL);
    	XWarpPointer(displayMain, None, wid, 0, 0, 0, 0, X, Y+10);
	XFlush(displayMain);
	return 1;
}

int process_keys(std::string keys)
    {
    std::locale loc;
    //std::size_t len = keys.size();
    std::string schar;
    char c;
        for (std::string::size_type i=0; i<keys.length(); ++i)
            {
			usleep(1000);
            c=keys[i];
            if (std::isalpha(c,loc)){
                if (std::isupper(c,loc))
                    {
                       if(c == 'A') { key_press("A", 1); }
                       if(c == 'B') { key_press("B", 1); }
                       if(c == 'C') { key_press("C", 1); }
                       if(c == 'D') { key_press("D", 1); }
                       if(c == 'E') { key_press("E", 1); }
                       if(c == 'F') { key_press("F", 1); }
                       if(c == 'G') { key_press("G", 1); }
                       if(c == 'H') { key_press("H", 1); }
                       if(c == 'I') { key_press("I", 1); }
                       if(c == 'J') { key_press("J", 1); }
                       if(c == 'K') { key_press("K", 1); }
                       if(c == 'L') { key_press("L", 1); }
                       if(c == 'M') { key_press("M", 1); }
                       if(c == 'N') { key_press("N", 1); }
                       if(c == 'O') { key_press("O", 1); }
                       if(c == 'P') { key_press("P", 1); }
                       if(c == 'Q') { key_press("Q", 1); }
                       if(c == 'R') { key_press("R", 1); }
                       if(c == 'S') { key_press("S", 1); }
                       if(c == 'T') { key_press("T", 1); }
                       if(c == 'U') { key_press("U", 1); }
                       if(c == 'V') { key_press("V", 1); }
                       if(c == 'W') { key_press("W", 1); }
                       if(c == 'X') { key_press("X", 1); }
                       if(c == 'Y') { key_press("Y", 1); }
                       if(c == 'Z') { key_press("Z", 1); }

                    } else {

                       if(c == 'a') { key_press("a", 0); }
                       if(c == 'b') { key_press("b", 0); }
                       if(c == 'c') { key_press("c", 0); }
                       if(c == 'd') { key_press("d", 0); }
                       if(c == 'e') { key_press("e", 0); }
                       if(c == 'f') { key_press("f", 0); }
                       if(c == 'g') { key_press("g", 0); }
                       if(c == 'h') { key_press("h", 0); }
                       if(c == 'i') { key_press("i", 0); }
                       if(c == 'j') { key_press("j", 0); }
                       if(c == 'k') { key_press("k", 0); }
                       if(c == 'l') { key_press("l", 0); }
                       if(c == 'm') { key_press("m", 0); }
                       if(c == 'n') { key_press("n", 0); }
                       if(c == 'o') { key_press("o", 0); }
                       if(c == 'p') { key_press("p", 0); }
                       if(c == 'q') { key_press("q", 0); }
                       if(c == 'r') { key_press("r", 0); }
                       if(c == 's') { key_press("s", 0); }
                       if(c == 't') { key_press("t", 0); }
                       if(c == 'u') { key_press("u", 0); }
                       if(c == 'v') { key_press("v", 0); }
                       if(c == 'w') { key_press("w", 0); }
                       if(c == 'x') { key_press("x", 0); }
                       if(c == 'y') { key_press("y", 0); }
                       if(c == 'z') { key_press("z", 0); }

                    }

            } else {
                        if(c == '@') { key_press("@",1); } // Shift
                        if(c == '0') { key_press("0",0);}
                        if(c == '1') { key_press("1",0); }
                        if(c == '2') { key_press("2",0); }
                        if(c == '3') { key_press("3",0); }
                        if(c == '4') { key_press("4",0); }
                        if(c == '5') { key_press("5",0); }
                        if(c == '6') { key_press("6",0); }
                        if(c == '7') { key_press("7",0); }
                        if(c == '8') { key_press("8",0); }
                        if(c == '9') { key_press("9",0); }
                        if(c == '.') { key_press("period",0); }
                        if(c == ' ') { key_press("space",0); }
                        
                }

        }
return 1;
}

int ViXiVFrame::save_script(){
	
	std::string BaseFileName = "script";
	std::string FileName = "";
	std::string FileExt = ".vix";
	std::string FileExistsName = "";
	std::stringstream ss;

	int n = 0;
	int filenumber = 0;
	bool Exists = true;
	
	listcount = ViXiVFrame::wx_listbox->GetCount();
	if(listcount != 0)
		{
		ss << filenumber;
		FileName = BaseFileName+ss.str()+FileExt;
		
		while(Exists == true){
			filenumber++;
			ss.str("");
			ss << filenumber;

			FileName = BaseFileName+ss.str()+FileExt;
			Exists = FileExists(FileName);
		}
		FileName = BaseFileName+ss.str()+FileExt;
		//std::cout <<std::endl<< FileName<<std::endl << std::flush;
		//////////////////////
		fstream scriptfile(FileName.c_str(), ios::out);
		if(scriptfile){
			std::cout << "Writing " << FileName << std::endl;
			while(n < listcount)
			{
				listboxline = ViXiVFrame::wx_listbox->GetString(n);
				//std::cout << "Instruction: " << listboxline << std::endl;
				if(!listboxline.empty()){
					scriptfile << listboxline;
					scriptfile << "\n";
				}
				n++;
			}
		scriptfile.close();
		Saved=1;
		return 1;
		} else { wxMessageBox(_("Couldn't Open File:" + FileName), _("Problem"), wxICON_EXCLAMATION | wxOK, this); return 0; }
		
	} else {
		//wxMessageDialog *dial1 = new wxMessageDialog(NULL, wxT("No Contents to Write!"), wxT("Alert"), wxOK | wxICON_EXCLAMATION); dial1->ShowModal();
		wxMessageBox(_("No Contents to Write!"), _("Problem"), wxICON_EXCLAMATION | wxOK, this);
		}
return 0;
}

std::string execute_screenshot(std::string method, std::string FileName)
	{

	fstream file("screenshot.sh",ios::out);
        if (file){
		if (method == "select"){
			//std::cout << std::endl << FileName << std::endl << std::flush;
		    file << "#!/usr/bin/env bash\n";
		 	file << "gnome-screenshot -a -f 2>/dev/null " << FileName;
		}
		if (method == "main"){
			file << "#!/usr/bin/env bash\n";
		 	file << "gnome-screenshot -f 2>/dev/null " << FileName;
		}
    file.close();
    } else {return "";}
	if(FileExists("screenshot.sh"));
    {
		system("sh screenshot.sh");
    }
	if(FileExists(FileName))
    {
		return FileName;
	} else{
		return "";
    }
}
    

std::vector<std::string> process_script(std::string FileName)
	{
	ifstream file;
	std::string lineread;
	std::string line;
	std::stringstream SS;
    std::vector<std::string> ScriptArray;

	int i = 0;
    //std::cout << FileName << std::endl;
	file.open(FileName.c_str());
      if (file){
		while (std::getline(file, line))
			++i;
		file.clear();
		file.seekg(0, ios::beg);

		//std::cout << "i:" << i << std::endl;
		//std::cout << "Size: " << sizeof(ScriptArray);

		i=0;
	    while (std::getline(file , line))
			{
			ScriptArray.push_back(line);
			++i;
		}
	file.close();
	//return ScriptArray;
	} else { std::cout << "Error: Could not Open " << FileName << "\n";}
return ScriptArray;
}

int set_focus_wid(string widstring)
    {
    Window wid;
    stringstream ss;
    ss << widstring;
    ss >> wid;
    Display *display = XOpenDisplay(NULL);
    if(display == NULL)
        {
        exit(EXIT_FAILURE);
    }
    std::cout << "\nSetting focus to " << wid << std::endl;
    //XSetInputFocus(display, wid, RevertToNone, CurrentTime);
    if(!XRaiseWindow(display, wid))
        {
        exit(1);
    } else { std::cout << "\nFocus Set\n";}
        	XFlush(display);
        	XCloseDisplay(display);
    return 1;
}



// Declare the bitmap loading function
extern void wxC9ED9InitBitmapResources();

static bool bBitmapLoaded = false;

ViXiVFrame::ViXiVFrame(wxWindow* parent)
    : ViXiVFrameBaseClass(parent)
{
}

ViXiVFrame::~ViXiVFrame()
{
}

void ViXiVFrame::OnSave(wxCommandEvent& event)
    {
    wxUnusedVar(event);
	save_script();
   
}


void ViXiVFrame::OnLoad(wxCommandEvent& event)
    {
	bool empty = ViXiVFrame::wx_listbox->IsEmpty();
    wxUnusedVar(event);
    if (Saved!=1 && empty!=true)
    {
        if (wxMessageBox(_("Current content has not been saved! Proceed?"), _("Please confirm"), wxICON_QUESTION | wxYES_NO, this) == wxNO )
            return;
    }
    ViXiVFrame::wx_listbox->Clear();
	Saved=0;

    wxString		line;	
    wxString        file;
    wxFileDialog    fdlog(this);
    wxTextFile 		tfile; 


    if(fdlog.ShowModal() != wxID_OK) return;
    file.Clear();
    file = fdlog.GetPath();
    tfile.Open(file);

    if (tfile.IsOpened()) 
        {
        line = tfile.GetFirstLine();
        while(!tfile.Eof())
        {
            ViXiVFrame::wx_listbox->Append(line);
            line = tfile.GetNextLine();
        }			
        Saved = 1;
        int Count = wx_listbox->GetCount();
        
        ViXiVFrame::wx_save->Enable(true);
        ViXiVFrame::wx_execute->Enable(true);
        ViXiVFrame::wx_textbox->Enable(true);
        ViXiVFrame::wx_optionnon->Enable(false);
        ViXiVFrame::wx_optionleft->Enable(false);
        ViXiVFrame::wx_optionright->Enable(false);
        ViXiVFrame::wx_optiontop->Enable(false);
        ViXiVFrame::wx_optionbot->Enable(false);
        ViXiVFrame::wx_textadj->Enable(false);
        ViXiVFrame::wx_add->Enable(false);
        ViXiVFrame::wx_remove->Enable(false);
        ViXiVFrame::wx_run->Enable(false);

        if(Count >= 2){
            ViXiVFrame::wx_up->Enable(true);
            ViXiVFrame::wx_down->Enable(true);
            }                
        } else {wxMessageBox(_("File Contents UnAvailable!"), _("Problem"), wxICON_ERROR | wxOK, this);}
}

void ViXiVFrame::OnExit(wxCommandEvent& event)
{
    wxUnusedVar(event);
    Close();
}

void ViXiVFrame::OnAbout(wxCommandEvent& event)
{
    

    wxUnusedVar(event);
    
    wxURI wxURL_CV = wxURL("http://opencv.org/license.html");
    wxURI wxURL_XL = wxURL("http://opensource.org/licenses/MIT");
    wxURI wxURL_IM = wxURL("http://imagemagick.org/script/license.php");
    wxURI wxURL_WX = wxURL("http://wxwidgets.org/about/licence/");
    wxURI wxURL_SQ = wxURL("http://sqlite.org/copyright.html");
    wxURI wxURL_TA = wxURL("http://github.com/tesseract-ocr/tesseract/blob/master/LICENSE");
    wxURI wxURL_XD = wxURL("http://www.semicomplete.com/files/xdotool/docs/html/");
    
    wxArrayString wxDevs;
    wxAboutDialogInfo info;
    info.AddDeveloper(_("David I. Jones"));
	info.SetIcon(wxICON(main_icon));
    info.SetVersion(_("v3.33"));
    info.SetWebSite(_("https://www.vixiv.net"));
    info.SetCopyright(_("Copyright 2017 ViXiV Technologies"));
    info.SetLicence(_("Copyright 2017 ViXiV Technologies"
    "\nSoftware Libraries used in this product fall under various licenses:"
    "\n\nX11 ( " + wxURL_XL.BuildURI() + " ):\n"    
    "\nPermission is hereby granted, free of charge, to any person obtaining a copy"
    "\nof this software and associated documentation files (the \"Software\"), to deal"
    "\nin the Software without restriction, including without limitation the rights"
    "\nto use, copy, modify, merge, publish, distribute, sublicense, and/or sell"
    "\ncopies of the Software, and to permit persons to whom the Software is"
    "\nfurnished to do so, subject to the following conditions:\n\n"
    "\nThe above copyright notice and this permission notice shall be included in all"
    "\ncopies or substantial portions of the Software.\n\n"
    "\nTHE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR"
    "\nIMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,"
    "\nFITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE"
    "\nAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER"
    "\nLIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,"
    "\nOUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE"
    "\nSOFTWARE." 
    "\n\nOpenCV ( " + wxURL_CV.BuildURI() + " ):\n"
    "\nBy downloading, copying, installing or using the software you agree to this license."
    "\nIf you do not agree to this license, do not download, install, copy or use the software."
    "\nLicense Agreement"
    "\n\nFor Open Source Computer Vision Library"
    "\n(3-clause BSD License)"
    "\n\nRedistribution and use in source and binary forms, with or without modification,"
    "\nare permitted provided that the following conditions are met:"
    "\nRedistributions of source code must retain the above copyright notice, "
    "this list of conditions and the following disclaimer."
    "\nRedistributions in binary form must reproduce the above copyright notice, "
    "this list of conditions and the following disclaimer in the documentation"
    "and/or other materials provided with the distribution."
    "\nNeither the names of the copyright holders nor the names of the contributors may be used "
    "\nto endorse or promote products derived from this software without specific prior written permission."
    "\nThis software is provided by the copyright holders and contributors \"AS IS\" and any express or"
    "\nimplied warranties, including, but not limited to, implied warranties of merchantability "
    "\nand fitness for a particular purpose are disclaimed. "
    "\nIn no event shall copyright holders or contributors be liable for any direct,"
    "\nindirect, incidental, special, exemplary, or consequential damages (including,"
    "\nbut not limited to, procurement of substitute goods or services;"
    "\nloss of use, data, or profits; or business interruption) however caused and on"
    "\nany theory of liability, whether in contract, strict liability, or tort"
    "\n(including negligence or otherwise) arising in any way out of the use of this software, "
    "\neven if advised of the possibility of such damage."
    "\n\n\nTesseract OCR ( " + wxURL_TA.BuildURI() + " )"
    "\n\nImageMagick ( " + wxURL_IM.BuildURI() + " ):\n"
    "\nLicensed under the ImageMagick License (the \"License\"); you may not use"
    "\nthis file except in compliance with the License.  You may obtain a copy"
    "\nof the License at " + wxURL_IM.BuildURI() + "\n\n"
    "\nUnless required by applicable law or agreed to in writing, software"
    "\ndistributed under the License is distributed on an \"AS IS\" BASIS, WITHOUT"
    "\nWARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the"
    "\nLicense for the specific language governing permissions and limitations"
    "\nunder the License."
    "\n\n\nwxWidgets ( " + wxURL_WX.BuildURI() + " ):\n"
    "\nwxWindows Library Licence, Version 3.1"
    "\n\n          ======================================"
    "\n\nCopyright (c) 1998-2005 Julian Smart, Robert Roebling et al"
    "\nEveryone is permitted to copy and distribute verbatim copies"
    "\nof this licence document, but changing it is not allowed."
    "\n                     WXWINDOWS LIBRARY LICENCE"
    "\n  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION"
    "\nThis library is free software; you can redistribute it and/or modify it"
    "\nunder the terms of the GNU Library General Public Licence as published by"
    "\nthe Free Software Foundation; either version 2 of the Licence, or (at your"
    "\noption) any later version."
    "\nThis library is distributed in the hope that it will be useful, but WITHOUT"
    "\nANY WARRANTY; without even the implied warranty of MERCHANTABILITY or"
    "\nFITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public"
    "\nLicence for more details."
    "\nYou should have received a copy of the GNU Library General Public Licence"
    "\nalong with this software, usually in a file named COPYING.LIB.  If not,"
    "\nwrite to the Free Software Foundation, Inc., 51 Franklin Street, Fifth"
    "\nFloor, Boston, MA 02110-1301 USA."
    "\n\nEXCEPTION NOTICE"
    "\n\n1. As a special exception, the copyright holders of this library give"
    "\npermission for additional uses of the text contained in this release of the"
    "\nlibrary as licenced under the wxWindows Library Licence, applying either"
    "\nversion 3.1 of the Licence, or (at your option) any later version of the"
    "\nLicence as published by the copyright holders of version 3.1 of the Licence"
    "\ndocument."
    "\n\n2. The exception is that you may use, copy, link, modify and distribute"
    "\nunder your own terms, binary object code versions of works based on the"
    "\nLibrary."
    "\n\n3. If you copy code from files distributed under the terms of the GNU"
    "\nGeneral Public Licence or the GNU Library General Public Licence into a"
    "\ncopy of this library, as this licence permits, the exception does not apply"
    "\nto the code that you add in this way.  To avoid misleading anyone as to the"
    "\nstatus of such modified files, you must delete this exception notice from"
    "\nsuch code and/or adjust the licensing conditions notice accordingly."
    "\n\n4. If you write modifications of your own for this library, it is your"
    "\nchoice whether to permit this exception to apply to your modifications. If"
    "\nyou do not wish that, you must delete the exception notice from such code"
    "\nand/or adjust the licensing conditions notice accordingly."
    "\n\n\nSQLite3: ( " + wxURL_SQ.BuildURI() + " )\n"));

    
    info.SetDescription(_("ViXiV Automate Pro uses multiple Open Source libraries and tools under Various Licenses:\n OpenCV, Tesseract OCR, ImageMagick, SQLite, wxWidgets, XwinInfo, XDO and libxdo / X11 / Xtst / XLibs"));
    ::wxAboutBox(info);
}

void ViXiVFrame::OnClickExecute(wxCommandEvent& event)
{
	wxUnusedVar(event);
	listcount = ViXiVFrame::wx_listbox->GetCount();
	if(listcount != 0)
		{
			srand ( time(NULL) );
			std::string ifexb = "/usr/bin/";
			std::string ifexs = "/usr/sbin/";
			std::string ifexl = "/usr/lib/";
			std::string xwin = ifexb.append("xwininfo");
			std::string widstring = "";
            std::string widname = "";
			std::string wid = "";
			std::string uwidstring = "";
			std::string FileName = "";
			std::string SSFileName = "";
			std::string SSNumStr = "";
			std::string instruction = "";
			std::string ins_base = "";
			std::string ins_arg = "";
            std::string var_arg = "";
			std::string	arg_ss_main = "";
			std::string arg_ss_wind = "";
			std::string SSFileNameRtrn = "";
			std::string MainSSFileNameRtrn = "";

			std::stringstream ss1;
            std::stringstream ss2;
			std::vector<std::string> ScriptArray;

			cv::Point tbloc;

            //execute_screenshot();
            int i=0; int n = 0;
			int ArraySize = 0;
            int Button = 0;
            int Sleep = 0;
            
			size_t pos;
			size_t endpos;

			//Display *d;
			//XSetWindowAttributes attributes;
			//Window w; Window wp;
			//XEvent e;

			//FileName = file;
			//if(FileExists(FileName)) { ScriptArray = process_script(FileName); }
			while(n < listcount)
			{
				listboxline = ViXiVFrame::wx_listbox->GetString(n);
				//std::cout << "Instruction: " << listboxline << std::endl;
				if(!listboxline.empty()){
					ScriptArray.push_back(listboxline);
				}
				n++;
			}

			ArraySize = ScriptArray.size();
			while (i<ArraySize)
				{
				//std::cout << std::endl << "i: " << i << std::endl << std::flush;
				instruction = ScriptArray[i];

				++i; pos=string::npos; endpos=string::npos;

				pos = instruction.find(" ");
				endpos = instruction.find(";");

				ins_base = "";
				ins_arg = "";

				if(pos != string::npos){

					ins_base = instruction.substr(0, pos);
					ins_arg = instruction.substr(pos+1);
					endpos = ins_arg.find(";");
					ins_arg = ins_arg.substr(0, endpos);
					std::cout << "\nBase Ins: " << ins_base;
					std::cout << "\nArgument: " << ins_arg << std::endl;
				} else {
					endpos = instruction.find(";");
					if(endpos != string::npos){
						ins_base = instruction.substr(0, endpos);
						std::cout << "\nBase Ins: " << ins_base << std::endl;
					}
				}

				if (ins_base == "Type" || ins_base == "TYPE" || ins_base == "type") {
					if (ins_arg != "" )
						{
						if (ins_arg == "UP" || ins_arg == "Up" || ins_arg == "up")
							{ raw_key_press(111);
							} else {
							if (ins_arg == "DOWN" || ins_arg == "Down" || ins_arg == "down")
								{ raw_key_press(116);
								} else {
								if (ins_arg == "LEFT" || ins_arg == "Left" || ins_arg == "left")
									{ raw_key_press(113);
									} else {
									if (ins_arg == "RIGHT" || ins_arg == "Right" || ins_arg == "Right")
										{ raw_key_press(114);
										} else {
										if (ins_arg == "ENTER" || ins_arg == "Enter" || ins_arg == "enter")
											{ raw_key_press(36);
											} else { process_keys(ins_arg); }
										}
									}
								}
							}
						}

				}

				if (ins_base == "Click" || ins_base == "CLICK" || ins_base == "click"){
					if (ins_arg != "")
						{
						int Button;
						ss1 << ins_arg;
						ss1 >> Button;
						click_mouse(Button);
					}
				}
                
                if (ins_base == "Sleep" || ins_base == "SLEEP" || ins_base == "sleep"){
					if (ins_arg != "")
						{
						Sleep = 0;
						ss2 << ins_arg;
						ss2 >> Sleep;
                        std::cout << "\nSleeping for " << Sleep << " seconds...";
                        delay(Sleep * 1000);
                        ins_arg = "";
                        //std::stringstream().swap(m);
                        ss2 = std::stringstream();
                        ss2.clear();
					}
				}
                
				if (ins_base == "Find" || ins_base == "FIND" || ins_base == "find"){
					
                int padding_up = 0;
                int padding_down = 0;
                int padding_left = 0;
                int padding_right = 0;
                int padding = 0;
                
                pos = ins_arg.find(" ");
                endpos = ins_arg.find(";");
                if(pos != string::npos){
                    arg_ss_main = ins_arg.substr(0, pos);
                    ins_arg = ins_arg.substr(pos+1);
                    pos = ins_arg.find(" ");
                    arg_ss_wind = ins_arg;  
                    
                    endpos = arg_ss_wind.find(".png");
                    arg_ss_wind = arg_ss_wind.substr(0, endpos+4);
                    //arg_ss_wind = arg_ss_wind.substr(0, endpos+5);
                    
                    std::cout << "\nMain SS: \"" << arg_ss_main << "\"\n";
                    std::cout << "\nWindow SS: \"" << arg_ss_wind << "\"\n";
                } else {
                    std::cout << "\nIncorrect Format! " << ins_arg << std::endl;
                }
                
                std::size_t widpos = arg_ss_wind.find(".png");
                widstring = arg_ss_wind.substr(0,widpos);
                
                std::cout << "\nWindow String: " << widstring << std::endl;
                std::string searchresults = wid_search_by_id(widstring);
                
                std::cout << "Search Results: " << searchresults << std::endl;
                if(widstring != "" && searchresults != "" && searchresults != "ERROR" && searchresults != "NULL")
                    {
                    set_focus_wid(widstring);
                    tbloc = match_screenshot(arg_ss_wind, arg_ss_main);
                    } else {
                        widname = read_db_by_id(widstring);
                    //    std::cout << "WIDNAME DB READ: " << widname << "\n";
                        if(widname != "" && widname != "ERROR" && widname != "NULL"){
                            widstring = wid_search_by_name(widname);
                      //      std::cout << "WID xwin search: " << widstring << "\n";
                            if(widstring != "" && widstring != "ERROR" && widstring != "NULL"){
                                set_focus_wid(widstring);
                                tbloc = match_screenshot(arg_ss_wind, arg_ss_main);
                            }
                        }    
                    }
                    
                    std::size_t adjustpos = ins_arg.find("adjust "); 
                    if (adjustpos != string::npos)
                        {
                        ins_arg = ins_arg.substr(adjustpos);
                        std::cout << std::endl << ins_arg << std::endl;
                        std::size_t adjuppos = string::npos;
                        adjuppos = ins_arg.find("up by ");
                        std::size_t adjdownpos = string::npos;
                        adjdownpos = ins_arg.find("down by ");
                        std::size_t adjleftpos = string::npos;
                        adjleftpos = ins_arg.find("left by ");
                        std::size_t adjrightpos = string::npos;
                        adjrightpos = ins_arg.find("right by ");
                        pos = ins_arg.find("by ");
                        
                        ss1 = std::stringstream();
                        ss1.clear();
                        
                        if(adjuppos != string::npos)
                            { 
                            var_arg = ins_arg.substr(pos+3);
                            std::cout << std::endl << var_arg << std::endl;
                            ss1 << var_arg;
                            ss1 >> padding_up;
                            tbloc.y=tbloc.y-padding_up;
                        }
                        if(adjdownpos != string::npos)
                            { 
                            var_arg = ins_arg.substr(pos+3);
                            std::cout << std::endl << ins_arg << std::endl;
                            ss1 << var_arg;
                            ss1 >> padding_down;
                            tbloc.y=tbloc.y+padding_down;
                        }
                        if(adjleftpos != string::npos)
                            { 
                            var_arg = ins_arg.substr(pos+3);
                            std::cout << std::endl << ins_arg << std::endl;
                            ss1 << var_arg;
                            ss1 >> padding_left;
                            tbloc.x=tbloc.x-padding_left;
                        }
                        if(adjrightpos != string::npos)
                            { 
                            var_arg = ins_arg.substr(pos+3);
                            std::cout << std::endl << ins_arg << std::endl;
                            ss1 << var_arg;
                            ss1 >> padding_right;
                            tbloc.x=tbloc.x+padding_right;
                        }
                        
                        ss1 = std::stringstream();
                        ss1.clear(); 
                    } else {
                        tbloc.x=tbloc.x+5; 
                        tbloc.y=tbloc.y+5;
                    }
                    
                    move_mouse(tbloc.x, tbloc.y, widstring );
                }
			
                if (ins_base == "TAB" || ins_base == "Tab" || ins_base == "tab"){ raw_key_press(23); }
                if (ins_base == "Enter" || ins_base == "ENTER" || ins_base == "enter"){ raw_key_press(36); }
            }
			usleep(300);
			Executed = 1;
		} else {
			wxMessageBox(_("Nothing to Execute!"), _("HuH?"), wxICON_EXCLAMATION | wxCANCEL, this);
    }
}

void ViXiVFrame::OnClickRun(wxCommandEvent& event)
{
	Execute_Find();	
}
void ViXiVFrame::OnClickSave(wxCommandEvent& event)
{
	wxUnusedVar(event);
	save_script();
}

void ViXiVFrame::OnClickAdd(wxCommandEvent& event)
{
	wxUnusedVar(event);
	int location = -1;
	int CurrentSelection = -1;
	bool Compare1;
	bool Compare2;
	bool Compare3;
	
	wxString listboxstr = "";
	std::string textbox = "";
	
//	Close();
//////////////////////////////////////////////////////
/////////////////////////////////////////////////////
	CurrentSelection = wx_choice->GetSelection();
	//std::cout << CurrentSelection << std::endl << std::flush;
    if(CurrentSelection == 0)
        {
        Execute_Find();
        wx_remove->Enable(true);
        int Count = wx_listbox->GetCount();
        if(Count >= 2){
            ViXiVFrame::wx_up->Enable(true);
            ViXiVFrame::wx_down->Enable(true);
        }
    }
    
	if(CurrentSelection == 1)
		{
		listboxstr = "Click ";
		textbox = ViXiVFrame::wx_textbox->GetValue();
		
		Compare1 = textbox.compare("1");
		Compare2 = textbox.compare("2");
		Compare3 = textbox.compare("3");
		if(Compare1 == 1 && Compare2 == 1 && Compare3 == 1)
			{
			//wxMessageDialog *dial1 = new wxMessageDialog(NULL, wxT("Invalid Argument!"), wxT("Alert"), wxOK | wxICON_EXCLAMATION);
			//dial1->ShowModal();
			wxMessageBox(_("Invalid Argument!"), _("Problem"), wxICON_EXCLAMATION | wxOK, this);

		} else {
			listboxstr = listboxstr + textbox + ";";			
			//ViXiVFrame::wx_listbox->InsertItems(1, listboxconst, location);
			//ViXiVFrame::wx_listbox->InsertItems(listboxstr, location);
			//ViXiVFrame::wx_listbox->InsertItems(listboxstr, location);
			location = ViXiVFrame::wx_listbox->GetSelection();
			//std::cout << "Location: " << location << std::endl;
			if(location != -1){
			ViXiVFrame::wx_listbox->InsertItems(1, &listboxstr, location+1);
			} else {
                ViXiVFrame::wx_listbox->Append(listboxstr); 
            }
            wx_remove->Enable(true); 
            wx_execute->Enable(true);
            wx_save->Enable(true);
            
            int Count = wx_listbox->GetCount();
            if(Count >= 2){
                ViXiVFrame::wx_up->Enable(true);
                ViXiVFrame::wx_down->Enable(true);
            }
		}
	}
    if(CurrentSelection == 2)
		{
		textbox = ViXiVFrame::wx_textbox->GetValue();
		if(textbox == "")
			{
			//wxMessageDialog *dial1 = new wxMessageDialog(NULL, wxT("Invalid Argument!"), wxT("Alert"), wxOK | wxICON_EXCLAMATION);
			//dial1->ShowModal();
			wxMessageBox(_("Invalid Argument!"), _("Problem"), wxICON_EXCLAMATION | wxOK, this);

		} else {
			listboxstr = "Sleep ";
			textbox = ViXiVFrame::wx_textbox->GetValue();
			listboxstr = listboxstr + textbox + ";";
			
			location = ViXiVFrame::wx_listbox->GetSelection();
			//std::cout << "Location: " << location << std::endl;
			if(location != -1){
			ViXiVFrame::wx_listbox->InsertItems(1, &listboxstr, location+1);
			} else { 
                ViXiVFrame::wx_listbox->Append(listboxstr); 
            }
            wx_remove->Enable(true);
            wx_execute->Enable(true);
            wx_save->Enable(true);
            
            int Count = wx_listbox->GetCount();
            if(Count >= 2){
                ViXiVFrame::wx_up->Enable(true);
                ViXiVFrame::wx_down->Enable(true);
            }
		}
	}
    
	if(CurrentSelection == 3)
		{
		textbox = ViXiVFrame::wx_textbox->GetValue();	
		if(textbox == "")
			{
			//wxMessageDialog *dial1 = new wxMessageDialog(NULL, wxT("Invalid Argument!"), wxT("Alert"), wxOK | wxICON_EXCLAMATION);
			//dial1->ShowModal();
			wxMessageBox(_("Invalid Argument!"), _("Problem"), wxICON_EXCLAMATION | wxOK, this);

		} else {
			listboxstr = "Type ";
			textbox = ViXiVFrame::wx_textbox->GetValue();
			listboxstr = listboxstr + textbox + ";";
			
			location = ViXiVFrame::wx_listbox->GetSelection();
			//std::cout << "Location: " << location << std::endl;
			if(location != -1){
			ViXiVFrame::wx_listbox->InsertItems(1, &listboxstr, location+1);
			} else { 
                ViXiVFrame::wx_listbox->Append(listboxstr);
            }
            wx_remove->Enable(true); 
            wx_execute->Enable(true);
            wx_save->Enable(true);
            
            int Count = wx_listbox->GetCount();
            if(Count >= 2){
                ViXiVFrame::wx_up->Enable(true);
                ViXiVFrame::wx_down->Enable(true);
            }
		}	
	}
	
	if(CurrentSelection == 4)
		{
		wxString Tab = "Tab;";
		location = ViXiVFrame::wx_listbox->GetSelection();
			//std::cout << "Location: " << location << std::endl;
			if(location != -1){
			ViXiVFrame::wx_listbox->InsertItems(1, &Tab, location+1);
			} else { 
                ViXiVFrame::wx_listbox->Append(Tab);
            }
            wx_remove->Enable(true); 
            wx_execute->Enable(true);
            wx_save->Enable(true);
            int Count = wx_listbox->GetCount();
            if(Count >= 2){
                ViXiVFrame::wx_up->Enable(true);
                ViXiVFrame::wx_down->Enable(true);
            }
        }
	
	if(CurrentSelection == 5)
		{
		wxString Enter = "Enter;";
		location = ViXiVFrame::wx_listbox->GetSelection();
			//std::cout << "Location: " << location << std::endl;
			if(location != -1){
			ViXiVFrame::wx_listbox->InsertItems(1, &Enter, location+1);
			} else { 
                ViXiVFrame::wx_listbox->Append(Enter); 
            }
            wx_remove->Enable(true);
            wx_execute->Enable(true);
            wx_save->Enable(true);
            
            int Count = wx_listbox->GetCount();
            if(Count >= 2){
                ViXiVFrame::wx_up->Enable(true);
                ViXiVFrame::wx_down->Enable(true);
            }
        }
        
    location = ViXiVFrame::wx_listbox->GetCount();
    ViXiVFrame::wx_listbox->SetSelection(location-1);
}

void ViXiVFrame::OnNew(wxCommandEvent& event)
{
	wxUnusedVar(event);
	bool empty= ViXiVFrame::wx_listbox->IsEmpty();
	if (Saved!=1 && empty!=true)
	{
		if (wxMessageBox(_("Current content has not been saved! Proceed?"), _("Please Confirm!"), wxICON_QUESTION | wxYES_NO, this) == wxNO )
			return;
    }
    ViXiVFrame::wx_save->Enable(false);
    ViXiVFrame::wx_execute->Enable(false);
    ViXiVFrame::wx_textbox->Enable(true);
    ViXiVFrame::wx_optionnon->Enable(false);
    ViXiVFrame::wx_optionleft->Enable(false);
    ViXiVFrame::wx_optionright->Enable(false);
    ViXiVFrame::wx_optiontop->Enable(false);
    ViXiVFrame::wx_optionbot->Enable(false);
    ViXiVFrame::wx_textadj->Enable(false);
    ViXiVFrame::wx_up->Enable(false);
    ViXiVFrame::wx_add->Enable(false);
    ViXiVFrame::wx_remove->Enable(false);
    ViXiVFrame::wx_run->Enable(false);
    ViXiVFrame::wx_down->Enable(false);
	ViXiVFrame::wx_listbox->Clear();
	Saved=0;
}

void ViXiVFrame::OnClickUp(wxCommandEvent& event)
{
    int location = -1;
    int listcount = 0;
    
	wxUnusedVar(event);
    bool empty = ViXiVFrame::wx_listbox->IsEmpty();
    if (empty!=true){
        location = ViXiVFrame::wx_listbox->GetSelection();
        if(location != -1){
            listcount = ViXiVFrame::wx_listbox->GetCount();
            if(listcount == 1){
                //ViXiVFrame::wx_listbox->SetSelection(0);
            }
            if(listcount >= 2){
                if(location-1 != -1){
                    ViXiVFrame::wx_listbox->SetSelection(location-1);
                    wxString CurrString = wx_listbox->GetString(location);
                    ViXiVFrame::wx_listbox->Delete(location);
                    ViXiVFrame::wx_listbox->Insert(CurrString, location-1);
                } else {
                    //wx_listbox->Move
                    ViXiVFrame::wx_listbox->SetSelection(location-1);
                }
                
            }
            location = ViXiVFrame::wx_listbox->GetSelection();
            if(location == 0){
                wx_up->Enable(false);
            }
            if(location == wx_listbox->GetCount()-2){
                wx_down->Enable(true);
            }
        }

    } else {
		wxMessageBox(_("Nothing to Move!"), _("HuH?"), wxICON_INFORMATION | wxOK_DEFAULT, this);
    }
}

void ViXiVFrame::OnClickDown(wxCommandEvent& event)
{
    int location = -1;
    int listcount = 0;
    
	wxUnusedVar(event);
    bool empty = ViXiVFrame::wx_listbox->IsEmpty();
    if (empty!=true){
        location = ViXiVFrame::wx_listbox->GetSelection();
        if(location != -1){
            listcount = ViXiVFrame::wx_listbox->GetCount();
            if(listcount == 1){
                //ViXiVFrame::wx_listbox->SetSelection(0);
            }
            if(listcount >= 2){
                if(location+1 != listcount){
                    ViXiVFrame::wx_listbox->SetSelection(location+1);
                    wxString CurrString = wx_listbox->GetString(location);
                    ViXiVFrame::wx_listbox->Delete(location);
                    ViXiVFrame::wx_listbox->Insert(CurrString, location+1);
                } else {
                    //wx_listbox->Move
                    
                    ViXiVFrame::wx_listbox->SetSelection(location+1);
                }
                
            }
            location = ViXiVFrame::wx_listbox->GetSelection();
            listcount = ViXiVFrame::wx_listbox->GetCount();
            if(location+1 == listcount){
                wx_down->Enable(false);
            }
            if(location == 1){
                wx_up->Enable(true);
            }
            
        }
        
    } else {
		wxMessageBox(_("Nothing to Move!"), _("HuH?"), wxICON_INFORMATION | wxOK_DEFAULT, this);
    }
}

void ViXiVFrame::OnClickRemove(wxCommandEvent& event)
{
    int location = -1;
    int listcount = 0;
    
	wxUnusedVar(event);
    bool empty = ViXiVFrame::wx_listbox->IsEmpty();
    if (empty!=true){
        location = ViXiVFrame::wx_listbox->GetSelection();
        if(location != -1){
            ViXiVFrame::wx_listbox->Delete(location);
            listcount = ViXiVFrame::wx_listbox->GetCount();
            if(listcount == 1){
                ViXiVFrame::wx_listbox->SetSelection(0);
            }
            if(listcount >= 2){
                if(location-1 != -1){
                    ViXiVFrame::wx_listbox->SetSelection(location-1);
                } else {
                    ViXiVFrame::wx_listbox->SetSelection(location-1);
                }
                
            }
            bool empty = ViXiVFrame::wx_listbox->IsEmpty();
            if (empty!=true){
                wx_up->Enable(false);
                wx_down->Enable(false);
            }
        }
        location = ViXiVFrame::wx_listbox->GetSelection();
        if(location == -1){
            wx_remove->Enable(false);
            wx_execute->Enable(false);
            wx_save->Enable(false);
        }
        listcount = ViXiVFrame::wx_listbox->GetCount();
        if(listcount >= 2){
            wx_up->Enable(true);
            wx_down->Enable(true);
        } else {
            wx_up->Enable(false);
            wx_down->Enable(false);
        } 
    } else {
		wxMessageBox(_("Nothing to Remove!"), _("HuH?"), wxICON_INFORMATION | wxOK_DEFAULT, this);
    }
}


void ViXiVFrame::OnSelectListBox(wxCommandEvent& event)
{
	wxUnusedVar(event);
    int Selection = wx_listbox->GetSelection();
    int Count = wx_listbox->GetCount();
    
    wx_add->Enable(true);
    wx_remove->Enable(true);
    
    if(Selection != 0 && Selection != -1 && Selection != Count){
        wx_up->Enable(true);
        wx_down->Enable(true);
    } 
    if(Selection == -1)
    {
        wx_up->Enable(true);
        wx_down->Enable(true);
    } 
    if(Selection == 0)
    {
        wx_up->Enable(false);
        wx_down->Enable(true);
    }
    if(Selection == Count-1)
    {
        wx_up->Enable(true);
        wx_down->Enable(false);
        
    }
}

void ViXiVFrame::OnSelectListBoxDClick(wxCommandEvent& event)
{
    wxString EditString = "";
    wxString OrigString = "";
    wxString AltString = "";
    std::size_t pos;
    std::size_t npos = string::npos;
    
    int Selection = wx_listbox->GetSelection();
    
    OrigString = ViXiVFrame::wx_listbox->GetString(Selection);
    wxTextEntryDialog Dialog(this, _("Original: " + OrigString), _("Advanced Edit!"), _(EditString), wxOK, wxDefaultPosition);
    Dialog.SetValue(_(OrigString));
    if ( Dialog.ShowModal() == wxID_OK )
        {
            EditString = Dialog.GetValue();
        }
    pos = EditString.find(";");
    if(pos == string::npos)
    {
        std::cout << "\nAppending Missing Semi-Colon!\n";
        EditString.append(";");
    } else {
        if(pos != EditString.Len()-1)
        {
            std::cout << "\nSemi-Colon in Wrong Location!!! Fixing!\n";
            AltString = "";
            AltString = EditString.Mid(0, pos);
            AltString.Append(EditString.Mid(pos+1));
            AltString.Append(";");
            EditString = AltString;
        }
    }
    
    ViXiVFrame::wx_listbox->Delete(Selection);
    ViXiVFrame::wx_listbox->Insert(EditString,Selection);
	
}

void ViXiVFrame::OnSelect(wxCommandEvent& event)
{
	wxUnusedVar(event);
	wx_textbox->SetValue("");
	
	int CurrentSelection = wx_choice->GetSelection();
	if(CurrentSelection == 0)
		{
		wxSafeYield();
        wx_optionnon->Enable(true);
		wx_optionleft->Enable(true);
        wx_optionright->Enable(true);
		wx_optiontop->Enable(true);
        wx_optionbot->Enable(true);
        wx_textadj->Enable(true);
		wx_textbox->Enable(false);
		wx_add->Enable(true);
		wx_remove->Enable(false);
		wx_run->Enable(true);
		
	}
	
	if(CurrentSelection == 1 || CurrentSelection == 2 || CurrentSelection == 3)
	{
        wx_optionnon->Enable(false);
		wx_optionleft->Enable(false);
		wx_optionright->Enable(false);
		wx_optiontop->Enable(false);
		wx_optionbot->Enable(false);
        wx_textadj->Enable(false);
		wx_textbox->Enable(true);
		wx_add->Enable(true);
		wx_remove->Enable(false);
		wx_run->Enable(false);
	}
	
	if(CurrentSelection == 4 || CurrentSelection == 5)
	{
        wx_optionnon->Enable(false);
		wx_optionleft->Enable(false);
        wx_optionright->Enable(false);
		wx_optiontop->Enable(false);
        wx_optionbot->Enable(false);
        wx_textadj->Enable(false);
		wx_textbox->Enable(false);
		wx_add->Enable(true);
		wx_remove->Enable(false);
		wx_run->Enable(false);
		
	}
}

int ViXiVFrame::Execute_Find()
{
		int location = -1;
        
        wxString listboxstr = "Find ";
        
        std::string AdjustStr = "";
		std::string SSFileName = "";
		std::string SSFileNameRtrn = "";
		std::string MainSSFileNameRtrn = "";
		std::string SSNumStr = "";
		std::string wid = "";
        std::string widname = "";
        std::string widfile = "wid";
        std::string widnamefile = "widname";
		//std::string listboxstr = "Find ";
		//std::coutstd::cout << "\nGetting OptionIB";
		
        bool optionnon   =    ViXiVFrame::wx_optionnon ->GetValue();
		bool optiontop   =    ViXiVFrame::wx_optiontop ->GetValue();
        bool optionbot   =    ViXiVFrame::wx_optionbot ->GetValue();
		bool optionleft  =    ViXiVFrame::wx_optionleft ->GetValue();
		bool optionright =    ViXiVFrame::wx_optionright ->GetValue();
		
        wxString optionadj   =    ViXiVFrame::wx_textadj ->GetValue();

	    std::stringstream ss;
        ss = std::stringstream();
		ss.clear();
        
		SSNum++;
		ss << SSNum;
		ss >> SSNumStr;
        
        ss = std::stringstream();
        ss.clear();
		SSFileName = "SS"+SSNumStr+".png";
		
		wxMessageBox(_("Please Select the target window with the +"), _("Problem"), wxICON_INFORMATION | wxOK_DEFAULT, this);
		//wxMessageDialog *dial1 = new wxMessageDialog(NULL, wxT("Please Select the target window to grab the window ID."), wxT("Alert"), wxOK | wxICON_EXCLAMATION);
		//dial1->ShowModal();
		
		//ViXiVFrameBaseClass::ViXiVFrameBaseClass::vixivsizer->SetMinSize(16,16);
		//vixivsizer-> SetMinSize(16,16);
		//this->SetMinSize(16,16);
		//vixivsizer->SetItemBounds(420,600,420,600);
		SetSize(wxSize(16,16));
		wxSafeYield();
        
        remove("wid");
        remove("widname");

		if(getwids() != 0)
			{
			wid = get_one_line_from_file(widfile);
            widname = get_one_line_from_file(widnamefile);
            
            if(wid != "" && widname != ""){
            write_db(widname, wid);
			set_focus_wid(wid);
            } //else {
              //  wid = read_db_by_name(widname);
              //  widsearch
            //}
			//std::cout << "WID: " << wid;
		} else { wxMessageBox(_("Couldn't Grab Window ID!"), _("Please Try Again?"), wxICON_EXCLAMATION | wxOK, this); }
 
		wxSafeYield();
		wxMessageBox(_("Please Select the area to capture for WID:"+wid+"\nCapture will not work in interrupter if it is not large enough or there is too much white space!"), _("Please Select Area"), wxICON_INFORMATION | wxOK, this);
		//wxMessageDialog *dial2 = new wxMessageDialog(NULL, wxT("Please Select the area to capture for WID:" + wid + ".\nCapture will not work if it is not large enough or there is too much white space!\n"), wxT("Alert"), wxOK | wxICON_EXCLAMATION);
		//dial2->ShowModal();
		
		std::cout << "\nPlease Select the area to capture...\n" << std::flush;
		std::cout << "Capture will not work if it is not large enough or too much white space!" << std::flush;
	
		wxSafeYield();
		
		SSFileNameRtrn = execute_screenshot("select", SSFileName);
		MainSSFileNameRtrn = screenshot_window(wid);

		listboxstr = listboxstr + SSFileNameRtrn + " " + MainSSFileNameRtrn;
        
        if(!optionnon) {
            if(optiontop || optionbot || optionleft || optionright){
                listboxstr.append(" adjust");
                
                if(optiontop)
                    listboxstr.append(" up by ");
                    
                if(optionbot)
                    listboxstr.append(" down by ");
                    
                if(optionleft)
                    listboxstr.append(" left by ");
                    
                if(optionright)
                    listboxstr.append(" right by ");
            }
            AdjustStr = wx_textadj->GetValue();
            listboxstr.append(AdjustStr);
        }
        listboxstr.append(";");
        
		location = ViXiVFrame::wx_listbox->GetSelection();
		//std::cout << "Location: " << location << std::endl;
		if(location != -1){
		ViXiVFrame::wx_listbox->InsertItems(1, &listboxstr, location+1);
		} else { ViXiVFrame::wx_listbox->Append(listboxstr); }
        wx_execute->Enable(true);
        wx_save->Enable(true);
		return 1;
///////////////////////////////////////////////////		
}

//MainFrameBaseClass::MainFrameBaseClass(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
//    : wxFrame(parent, id, title, pos, size, style)
ViXiVFrameBaseClass::ViXiVFrameBaseClass( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
    if ( !bBitmapLoaded ) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC9ED9InitBitmapResources();
        bBitmapLoaded = true;
    }

	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	//wxFont font;
	//wxString fontname(wxT("ASSASSIN$"));
	//font.FromString(fontname);
	//SetFont(font);
    if(!FileExists("mainicon.ico")){
        write_png("mainicon.ico", mainicon_ico, mainicon_ico_len);
    }

	SetIcon(wxICON(main_icon));
    m_mainPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(5,5), wxTAB_TRAVERSAL);
    
	wxBoxSizer* boxSizer1 = new wxBoxSizer(wxVERTICAL);
    boxSizer1->Add(m_mainPanel, 1, wxALIGN_CENTER, 5);
    
    wxBoxSizer* boxSizer5 = new wxBoxSizer(wxVERTICAL);
    m_mainPanel->SetSizer(boxSizer5);
    
    m_menuBar = new wxMenuBar(0);
    this->SetMenuBar(m_menuBar);
    
    m_name6 = new wxMenu();
    m_menuBar->Append(m_name6, _("File"));
    
	m_menuItemN = new wxMenuItem(m_name6, wxID_NEW,  _("New		Alt-N"), _("New"), wxITEM_NORMAL);
	m_menuItemS = new wxMenuItem(m_name6, wxID_SAVE, _("Save	Alt-S"), _("Save"), wxITEM_NORMAL);
	m_menuItemL = new wxMenuItem(m_name6, wxID_OPEN, _("Load	Alt-L"), _("Load"), wxITEM_NORMAL);
    m_menuItemQ = new wxMenuItem(m_name6, wxID_EXIT, _("Quit	Alt-X"), _("Quit"), wxITEM_NORMAL);

	m_name6->Append(m_menuItemN);
	m_name6->Append(m_menuItemS);
	m_name6->Append(m_menuItemL);
    m_name6->Append(m_menuItemQ);

    m_name8 = new wxMenu();
    m_menuBar->Append(m_name8, _("Help"));
    
    m_menuItem9 = new wxMenuItem(m_name8, wxID_ABOUT, _("About..."), wxT(""), wxITEM_NORMAL);
    m_name8->Append(m_menuItem9);
    
    m_mainToolbar = this->CreateToolBar(wxTB_FLAT, wxID_ANY);
    m_mainToolbar->SetToolBitmapSize(wxSize(16,16));

    Centre();
    // Connect events
	this->Connect(m_menuItemN->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(ViXiVFrameBaseClass::OnNew), NULL, this);
	this->Connect(m_menuItemS->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(ViXiVFrameBaseClass::OnSave), NULL, this);
    this->Connect(m_menuItemL->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(ViXiVFrameBaseClass::OnLoad), NULL, this);
    this->Connect(m_menuItemQ->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(ViXiVFrameBaseClass::OnExit), NULL, this);
    this->Connect(m_menuItem9->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(ViXiVFrameBaseClass::OnAbout), NULL, this);

	wxFlexGridSizer* vixivsizer;
	vixivsizer = new wxFlexGridSizer( 6, 1, 0, 0 );
	vixivsizer->SetFlexibleDirection( wxVERTICAL );
	vixivsizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	wxFlexGridSizer* fgSizerIns;
	fgSizerIns = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizerIns->SetFlexibleDirection( wxBOTH );
	fgSizerIns->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxString wx_choiceChoices[] = { wxT("Find (Screenshot Area)"), wxT("Mouse Click"),  wxT("Sleep"), wxT("Type"), wxT("Tab"), wxT("Press Enter") };
	int wx_choiceNChoices = sizeof( wx_choiceChoices ) / sizeof( wxString );
	wx_choice = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wx_choiceNChoices, wx_choiceChoices, 0 );
	wx_choice->SetSelection( -1 );
	wx_choice->SetMinSize( wxSize( 200,-1 ) );
	wx_choice->SetMaxSize( wxSize( 200,-1 ) );
	
	fgSizerIns->Add( wx_choice, 0, wxALL, 5 );
	
	wx_textbox = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	wx_textbox->SetMaxLength( 0 ); 
	wx_textbox->SetMinSize( wxSize( 200,-1 ) );
	wx_textbox->SetMaxSize( wxSize( 200,-1 ) );
	
	fgSizerIns->Add( wx_textbox, 0, wxALL, 5 );
	
	vixivsizer->Add( fgSizerIns, 1, wxALIGN_CENTER, 5 );
	
	wxFlexGridSizer* fgSizer11;
	fgSizer11 = new wxFlexGridSizer( 1, 6, 0, 0 );
	fgSizer11->SetFlexibleDirection( wxBOTH );
	fgSizer11->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
    wx_optionnon = new wxRadioButton( this, wxID_ANY, wxT("None"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer11->Add( wx_optionnon, 0, wxALL, 5 );
	//wx_optiontop->Enable(false);
    
	wx_optiontop = new wxRadioButton( this, wxID_ANY, wxT("Up"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer11->Add( wx_optiontop, 0, wxALL, 5 );
	//wx_optiontop->Enable(false);
	
    wx_optionbot = new wxRadioButton( this, wxID_ANY, wxT("Down"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer11->Add( wx_optionbot, 0, wxALL, 5 );
	//wx_optiontop->Enable(false);
    
	wx_optionleft = new wxRadioButton( this, wxID_ANY, wxT("Left"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer11->Add( wx_optionleft, 0, wxALL, 5 );
	//wx_optionleft->Enable(false);
    
    wx_optionright = new wxRadioButton( this, wxID_ANY, wxT("Right"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer11->Add( wx_optionright, 0, wxALL, 5 );
	//wx_optionleft->Enable(false);

	wx_textadj = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	wx_textadj->SetMaxLength( 2 ); 
	wx_textadj->SetMinSize( wxSize( 25,-1 ) );
	wx_textadj->SetMaxSize( wxSize( 25,-1 ) );
	fgSizer11->Add( wx_textadj, 0, wxALL, 5 );

	vixivsizer->Add( fgSizer11, 1, wxALIGN_CENTER, 5 );
	
	wxFlexGridSizer* fgSizerButtons;
	fgSizerButtons = new wxFlexGridSizer( 1, 5, 0, 0 );
	//fgSizerButtons->SetFlexibleDirection( wxBOTH );
	//fgSizerButtons->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
    wx_up = new wxButton( this, wxID_ANY, wxT("/\\"), wxDefaultPosition, wxSize(20,30), 0 );
	fgSizerButtons->Add( wx_up, 0, wxALL, 5 );
        
	wx_add = new wxButton( this, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerButtons->Add( wx_add, 0, wxALL, 5 );
	
	wx_remove = new wxButton( this, wxID_ANY, wxT("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerButtons->Add( wx_remove, 0, wxALL, 5 );
	
	wx_run = new wxButton( this, wxID_ANY, wxT("Run"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerButtons->Add( wx_run, 0, wxALL, 5 );
    
    wx_down = new wxButton( this, wxID_ANY, wxT("\\/"), wxDefaultPosition, wxSize(20,30), 0 );
	fgSizerButtons->Add( wx_down, 0, wxALL, 5 );
    
	vixivsizer->Add( fgSizerButtons, 1, wxALIGN_CENTER_HORIZONTAL, 10 );
	
	wxFlexGridSizer* fgSizerList;
	fgSizerList = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizerList->SetFlexibleDirection( wxBOTH );
	fgSizerList->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wx_listbox = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	wx_listbox->SetMinSize( wxSize( 400,380 ) );
	wx_listbox->SetMaxSize( wxSize( 400,380 ) );
	
	fgSizerList->Add( wx_listbox, 0, wxALIGN_CENTER, 5 );

	vixivsizer->Add( fgSizerList, 1, wxALIGN_CENTER, 5 );
	
	wxFlexGridSizer* fgSizerSave;
	fgSizerSave = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizerSave->SetFlexibleDirection( wxBOTH );
	fgSizerSave->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wx_save = new wxButton( this, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0 );

	wxFlexGridSizer* fgSizerExe;
	fgSizerExe = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizerExe->SetFlexibleDirection( wxBOTH );
	fgSizerExe->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wx_execute = new wxButton( this, wxID_ANY, wxT("Execute"), wxDefaultPosition, wxDefaultSize, 0 );

    wx_execute->Enable(false);
    wx_textbox->Enable(true);
    wx_optionnon->Enable(false);
    wx_optionleft->Enable(false);
    wx_optionright->Enable(false);
    wx_optiontop->Enable(false);
    wx_optionbot->Enable(false);
    wx_textadj->Enable(false);
    wx_up->Enable(false);
    wx_add->Enable(false);
    wx_remove->Enable(false);
    wx_run->Enable(false);
    wx_down->Enable(false);
    wx_save->Enable(false);
 
	this->Connect(wx_choice->GetId(), wxEVT_CHOICE, wxCommandEventHandler(ViXiVFrameBaseClass::OnSelect), NULL, this);
	this->Connect(wx_listbox->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(ViXiVFrameBaseClass::OnSelectListBox), NULL, this);
    this->Connect(wx_listbox->GetId(), wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler(ViXiVFrameBaseClass::OnSelectListBoxDClick), NULL, this);
	this->Connect(wx_execute->GetId(), wxEVT_BUTTON, wxCommandEventHandler(ViXiVFrameBaseClass::OnClickExecute), NULL, this);
	this->Connect(wx_save->GetId(), wxEVT_BUTTON, wxCommandEventHandler(ViXiVFrameBaseClass::OnClickSave), NULL, this);
    this->Connect(wx_up->GetId(), wxEVT_BUTTON, wxCommandEventHandler(ViXiVFrameBaseClass::OnClickUp), NULL, this);
	this->Connect(wx_add->GetId(), wxEVT_BUTTON, wxCommandEventHandler(ViXiVFrameBaseClass::OnClickAdd), NULL, this);
	this->Connect(wx_remove->GetId(), wxEVT_BUTTON, wxCommandEventHandler(ViXiVFrameBaseClass::OnClickRemove), NULL, this);
	this->Connect(wx_run->GetId(), wxEVT_BUTTON, wxCommandEventHandler(ViXiVFrameBaseClass::OnClickRun), NULL, this);
    this->Connect(wx_down->GetId(), wxEVT_BUTTON, wxCommandEventHandler(ViXiVFrameBaseClass::OnClickDown), NULL, this);

	fgSizerExe->Add( wx_save, 0, wxALL, 5 );
	vixivsizer->Add( fgSizerSave, 1, wxALIGN_CENTER, 5 );
	
	fgSizerExe->Add( wx_execute, 0, wxALL, 5 );
	vixivsizer->Add( fgSizerExe, 1, wxALIGN_CENTER, 5 );
	vixivsizer->SetMinSize(420,600);
	//vixivsizer->SetItemBounds(420,600,420,600);
	SetSize(wxSize(420,600));
	
	this->SetSizer( vixivsizer );
	this->Layout();
    
}

ViXiVFrameBaseClass::~ViXiVFrameBaseClass()
{
    this->Disconnect(m_menuItemQ->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(ViXiVFrameBaseClass::OnExit), NULL, this);
    this->Disconnect(m_menuItem9->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(ViXiVFrameBaseClass::OnAbout), NULL, this);
    this->Disconnect(wx_execute->GetId(), wxEVT_BUTTON, wxCommandEventHandler(ViXiVFrameBaseClass::OnClickExecute), NULL, this);
    
}



// Define the ViXiVApp
class ViXiVApp : public wxApp
{
public:
    ViXiVApp() {}
    virtual ~ViXiVApp() {}

    virtual bool OnInit() {
        // Add the common image handlers
        wxImage::AddHandler( new wxPNGHandler );
        wxImage::AddHandler( new wxJPEGHandler );

        ViXiVFrame *vixivFrame = new ViXiVFrame(NULL);
		//SetIcon(wxICON(mainicon));
        SetTopWindow(vixivFrame);
        return GetTopWindow()->Show();
    }
};

DECLARE_APP(ViXiVApp)
IMPLEMENT_APP(ViXiVApp)