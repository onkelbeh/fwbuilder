
#include "../../config.h"
#include "../../build_num"

#include <qglobal.h>

#if defined(Q_OS_MACX) || defined(Q_OS_WIN32)
#  include <qsettings.h>
#  include <QDir>
#  include <QApplication>
//#  include <QCoreApplication>
#else
#  include <limits.h>
#  include <unistd.h>
#endif

#include <QString>
#include <QtDebug>

#ifndef _WIN32
#  include <unistd.h>
#  include <pwd.h>
#else
#  include <direct.h>
#  include <stdlib.h>
#  include <io.h>
#  include <windows.h>
#endif

#include <string>

#include "fwbuilder/libfwbuilder-config.h"
#include "fwbuilder/Tools.h"
#include "fwbuilder/Resources.h"
#include "commoninit.h"

std::string appRootDir;
std::string userDataDir;
std::string respath; 
std::string localepath;
std::string librespath;
std::string sysfname;
std::string tempfname;
std::string argv0;
std::string ee;

QString build_num = QString("").setNum(BUILD_NUM);
QString user_name;

extern int fwbdebug;

using namespace std;
using namespace libfwbuilder;



void init(char * const*)
{


/*
 * Note appRootDir is the path to the directory where fwbuilder binary
 * is installed (on Mac it is <wherever>/fwbuilder3.app/Contents/MacOS.
 * On Windows it is c:\FWBuilder30, on Linux it is something like
 * /usr/bin or /usr/local/bin and so on.
 */
#if defined(Q_OS_WIN32) || defined(Q_OS_MACX)
    if (QCoreApplication::instance()==NULL)
    {
        int ac = 0;
        char **av = { NULL };
        new QApplication( ac, av );
    }
    QDir dir(QApplication::applicationDirPath());
    appRootDir = string(dir.absolutePath().toAscii().constData());

/* On windows and mac we install API resources (DTD etc) in the 
 * dir right above the one where we install resources for the GUI and compilers
 */
    if (respath=="") respath = appRootDir + FS_SEPARATOR + RES_DIR; 
    string::size_type n0 = respath.find_last_of("/\\");
    librespath = respath.substr(0, n0);

#else
    appRootDir = string(PREFIX) + FS_SEPARATOR + "bin";

/* On Unix RES_DIR and LIBFWBUILDER_TEMPLATE_DIR are absolute paths */

    if (respath=="") respath = RES_DIR;
    librespath = LIBFWBUILDER_TEMPLATE_DIR;
#endif


    libfwbuilder::init();


#if defined(Q_OS_WIN32)
    argv0 = appRootDir + FS_SEPARATOR + "fwbuilder.exe";
#else
/* need argv0 for built-in installer on unix and mac */
    argv0 = appRootDir + FS_SEPARATOR + "fwbuilder";
#endif

    sysfname = respath + FS_SEPARATOR  + "objects_init.xml";
    tempfname = respath+ FS_SEPARATOR + "templates.xml";

/* define localepath the same way as we define PKGLOCALEDIR in qmake.inc */
    localepath = respath + "/locale";

/* default directory where the user may want to save files */
#if defined(Q_OS_WIN32)
    userDataDir = string(getenv("USERPROFILE"))+"\\Documents";
#elif defined(Q_OS_MACX)
    userDataDir = string(getenv("HOME"))+"/Documents";
#else
    userDataDir = string(getenv("HOME"));
#endif


#ifdef _WIN32

#define INFO_BUFFER_SIZE 32767

TCHAR  infoBuf[INFO_BUFFER_SIZE];
DWORD  bufCharCount = INFO_BUFFER_SIZE;

  bufCharCount = INFO_BUFFER_SIZE;
  if( GetUserName( infoBuf, &bufCharCount ) )
  {
#ifdef UNICODE
      user_name = QString::fromUtf16((ushort*)infoBuf);
#else
      user_name = QString::fromLocal8Bit(infoBuf);
#endif
  }

  user_name = user_name.replace(' ','_');

#else

    char *lname = getenv("LOGNAME");
    if (lname!=NULL)
        user_name = QString(lname);
    else
    {
        struct passwd *pwd = getpwuid(getuid());
        assert(pwd);
        user_name = QString(pwd->pw_name);
    }
#endif
}
