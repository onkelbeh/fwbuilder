/*

                          Firewall Builder

                 Copyright (C) 2010 NetCitadel, LLC

  Author:  Roman Bovsunivskiy     a2k0001@gmail.com

  $Id: main_instDialogInstallTest.cpp 2707 2010-03-10 18:22:19Z a2k $

  This program is free software which we release under the GNU General Public
  License. You may redistribute and/or modify this program under the terms
  of that license as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  To get a copy of the GNU General Public License, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

#include "instDialogInstallTest.h"
#include "FWWindow.h"
#include "FWBSettings.h"
#include "common/commoninit.h"

#include <iostream>

int fwbdebug = 0;
FWWindow *mw = NULL;
FWBSettings *st = NULL;
char** args;
QApplication *app = NULL;

using namespace libfwbuilder;
using namespace std;


int main( int argc, char** argv)
{
    app = new QApplication(argc, argv, 0);
    app->setOrganizationName(QLatin1String("NetCitadel"));
    app->setApplicationName(QLatin1String("Firewall Builder"));
    st = new FWBSettings();
    st->init();
    init(argv);

    //respath = std::string(PREFIX) + "/share/libfwbuilder";
    //std::string full_res_path = std::string(PREFIX) + "/resources/resources.xml";

    string full_res_path = respath + FS_SEPARATOR + "resources.xml";

    try
    {
        new Resources(full_res_path);
    } catch (FWException &e)
    {
        cerr << "Can not read resource file from " << full_res_path << endl;
    }
    instDialogInstallTest tst;
    QTest::qExec(&tst);
}
