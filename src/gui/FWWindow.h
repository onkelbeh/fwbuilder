/* 

                          Firewall Builder

                 Copyright (C) 2003 NetCitadel, LLC

  Author:  Vadim Kurland     vadim@fwbuilder.org

  $Id$

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


#ifndef  __FWWINDOW_H_
#define  __FWWINDOW_H_

//#include <ui_FWBMainWindow_q.h>
//#include <ui_pagesetupdialog_q.h>

#include "RCS.h"
#include "HttpGet.h"
#include "printerStream.h"
#include "ObjectEditor.h"

#include <QString>
#include <QShowEvent>
#include <QHideEvent>
#include <QMainWindow>

#include <vector>
#include <list>
#include <set>

class ObjectManipulator;
class ObjectTreeView;
class ProjectPanel;

class QMdiArea;
class QMdiSubWindow;
class QPrinter;
class QTabWidget;
class QTextEdit;
class QTimer;
class QTreeWidgetItem;
class QDockWidget;

class RuleSetView;
class findDialog;
class FindObjectWidget;
class FindWhereUsedWidget;

namespace Ui {
    class FWBMainWindow_q;
    class pageSetupDialog_q;
};

namespace libfwbuilder {
    class FWObjectDatabase;
    class Firewall;
    class PolicyRule;
    class RuleSet;
    class Rule;
    class FWObject;
    class FWReference;
};


#define MAXRECENTFILES 5
#define EDITOR_PANEL_SEARCH_TAB 0
#define EDITOR_PANEL_EDITOR_TAB 1


class FWWindow : public QMainWindow {

    Q_OBJECT;

    Ui::pageSetupDialog_q *psd;
        
    QMdiArea *m_space;
    QMdiSubWindow *previous_subwindow;
    QWidget *instd;
    HttpGet *current_version_http_getter;
    
    QTimer *instDialogOnScreenTimer;
    QString noFirewalls;

    QWidget *editorOwner;

    QPrinter *printer;
    libfwbuilder::FWObject *searchObject;
    libfwbuilder::FWObject *replaceObject;
    //int                                    lastFirewallIdx;
    QStringList openDocFiles;
    bool auto_load_from_rcs_head_revision;
    QAction *recentFileActs[MAXRECENTFILES];
    QAction *openRecentSeparatorAct;

    void clearFirewallTabs();
    ProjectPanel *newProjectPanel();
    void showSub(ProjectPanel *projectW);
    void attachEditorToProjectPanel(ProjectPanel *pp);
    
public:
    QVector <QString> windowsTitles;
    QVector <QMdiSubWindow*> windowsPainters;

    ObjectEditor *oe;
    FindObjectWidget *findObjectWidget;
    FindWhereUsedWidget *findWhereUsedWidget;

    ProjectPanel* activeProject();
    void updateWindowTitle();
    void updateTreeFont();
    void updateRecentFileActions();
    void updateOpenRecentMenu(const QString &fileName);

    void enableBackAction();

    
public slots:
    void selectActiveSubWindow (/*const QString & text*/);
    void subWindowActivated(QMdiSubWindow*);

    void editorPanelTabChanged(int);
    
    void minimize();
    void maximize();
    virtual void search();

    virtual void restoreRuleSetTab();

    virtual void editFind();
    virtual void editRedo();
    virtual void editUndo();

    virtual void toggleViewObjectTree();
    virtual void toggleViewEditor();

    virtual void helpContents();
    virtual void helpContentsAction();
    virtual void helpIndex();
    virtual void help();
    virtual void showReleaseNotes();

    virtual void fileNew();
    virtual void fileOpen();
    virtual void openRecentFile();
    virtual void clearRecentFilesMenu();
    virtual void fileClose();
    virtual void fileSave();
    virtual void fileSaveAs();
    virtual void fileDiscard();
    virtual void fileCommit();
    virtual void fileImport();
    virtual void fileExport();
    virtual void filePrint();
    virtual void fileExit();
    virtual void fileProp();
    virtual void fileAddToRCS();
    virtual void fileCompare();
    virtual void editCopy();
    virtual void editCut();
    virtual void editDelete();
    virtual void editPaste();
    virtual void editPrefs();
    virtual void importPolicy();

    virtual void startupLoad();

    virtual void helpAbout();
    virtual void debug();
     
    virtual void compile(std::set<libfwbuilder::Firewall * > vf);
    virtual void compile();
    virtual void install(std::set<libfwbuilder::Firewall * > vf);
    virtual void install();
    virtual void transferfw(std::set<libfwbuilder::Firewall * > vf);
    virtual void transferfw();

    virtual void insertRule();
    virtual void addRuleAfterCurrent();
    virtual void moveRule();
    virtual void moveRuleUp();
    virtual void moveRuleDown();
    virtual void removeRule(); 

    virtual void copyRule();
    virtual void cutRule();
    virtual void pasteRuleAbove();
    virtual void pasteRuleBelow();

    virtual void back();
    virtual void newObject();
    virtual void lockObject();
    virtual void unlockObject();

    virtual void prepareEditMenu();
    virtual void prepareViewMenu();
    virtual void prepareObjectMenu();
    virtual void prepareFileMenu();
    virtual void prepareToolsMenu();
    virtual void prepareWindowsMenu();
    virtual void prepareFileOpenRecentMenu();

    virtual void toolsDiscoveryDruid();

    virtual void killInstDialog();

    virtual void checkForUpgrade(const QString&);

    virtual void projectWindowClosed();

    void tableResolutionSettingChanged(int );

    virtual void rollBackSelectionSameWidget();
    virtual void rollBackSelectionDifferentWidget();
    void activateRule(QString, QString, int);
    
 public:
    Ui::FWBMainWindow_q *m_mainWindow;
     
    FWWindow();
    ~FWWindow();


    RCS * getRCS(); 

    void registerAutoOpenDocFile(const QString &file_name,
                                 bool load_from_rcs_head);
    void load(QWidget *dialogs_parent,RCS *rcs);
    void load(QWidget *dialogs_parent);
    void loadLibrary(const std::string &libfpath);
    bool loadFile(const QString &filename, bool load_rcs_head);
    void save();
    bool checkin(bool unlock);
    int  findFirewallInList(libfwbuilder::FWObject *f);

    bool editingLibrary();

    QString chooseNewFileName(const QString &fname, const QString &title);
    void setFileName(const QString &fname);
    
    bool saveIfModified();
    
    /**
     * selects whatever is current in rules
     */
    void selectRules();
    void disableActions(bool havePolicies);
    void setActionsEnabled(bool en);
    void setEnabledAfterRF();

    QString getCurrentFileName();
    
    void setupAutoSave();

    void findObject(libfwbuilder::FWObject *);
    void findWhereUsed(libfwbuilder::FWObject *obj, ProjectPanel *pp);
    
    bool exportLibraryTest(std::list<libfwbuilder::FWObject*> &selectedLibs);
    void exportLibraryTo(QString fname,std::list<libfwbuilder::FWObject*> &selectedLibs, bool rof);

    void findExternalRefs(libfwbuilder::FWObject *lib,
                       libfwbuilder::FWObject *root,
                       std::list<libfwbuilder::FWReference*> &extRefs);
    
    void setSafeMode(bool f);
    void setStartupFileName(const QString &fn);

    // semi-intelligent way to guess most appropriate
    // destination directory for various file save or file open
    // operations. If working directory is configured in
    // preferences, then getDestDir returns that. If it is not
    // configured and file name is given on the command line,
    // directory where that file is located is returned. If
    // parameter filename is empty, then current directory
    // is returned (however on windows and mac userDataDir is returned)

    QString getDestDir(const QString &filename);
    
    libfwbuilder::FWObject*  getCurrentLib();

    void insertObjectInTree(libfwbuilder::FWObject *parent,
                            libfwbuilder::FWObject *obj);

    libfwbuilder::FWObject* createObject(const QString &objType,
                                          const QString &objName,
                                          libfwbuilder::FWObject *copyFrom=NULL);

    libfwbuilder::FWObject* createObject(libfwbuilder::FWObject *parent,
                                          const QString &objType,
                                          const QString &objName,
                                          libfwbuilder::FWObject *copyFrom=NULL);

    void moveObject(libfwbuilder::FWObject *target,
                    libfwbuilder::FWObject *obj);

    void moveObject(const QString &targetLibName,
                    libfwbuilder::FWObject *obj);

    void loadDataFromFw(libfwbuilder::Firewall *fw);

    void delObj(libfwbuilder::FWObject *obj,bool openobj=true);
    ObjectTreeView* getCurrentObjectTree();

    void findAllFirewalls (std::list<libfwbuilder::Firewall *> &fws);

    libfwbuilder::FWObject* duplicateObject(libfwbuilder::FWObject *target,
                                            libfwbuilder::FWObject *obj,
                                            const QString &name = QString::null,
                                            bool  askForAutorename=true);
    void showDeletedObjects(bool f);

//    void select();
//    void unselect();
    
    QPrinter* getPrinter();
    libfwbuilder::FWObjectDatabase* db();
    QString printHeader();

    static void printFirewallFromFile(QString fileName,
                                      QString firewallName,
                                      QString outputFileName);

    //wrapers for some Object Editor functions
    bool isEditorVisible();
    bool isEditorModified();
    
    void showEditor();
    void hideEditor();
    void closeEditor();
    
    void openEditor(libfwbuilder::FWObject *o);
    void openOptEditor(libfwbuilder::FWObject *, ObjectEditor::OptType t);
    void blankEditor();
    
    libfwbuilder::FWObject* getOpenedEditor();
    ObjectEditor::OptType getOpenedOptEditor();
    
    void selectObjectInEditor(libfwbuilder::FWObject *o);
    void actionChangedEditor(libfwbuilder::FWObject *o);
    bool validateAndSaveEditor();

    virtual void closeEditorPanel();
    virtual void openEditorPanel();
    
    bool requestEditorOwnership(QWidget *w,
                                libfwbuilder::FWObject *o,
                                ObjectEditor::OptType   otype,
                                bool validate = true);
    void releaseEditor();
    void connectEditor(QWidget *w);

    void singleRuleCompile(libfwbuilder::Rule *rule);

    void buildEditorTitleAndIcon(libfwbuilder::FWObject *obj,
                                 ObjectEditor::OptType t,
                                 QString *title_txt,
                                 QPixmap *pm,
                                 bool include_file_name);
    
 protected:

    virtual void showEvent(QShowEvent *ev);
    virtual void hideEvent(QHideEvent *ev);
    virtual void closeEvent(QCloseEvent *ev);
    virtual bool event(QEvent *event);

 protected slots:
    void activatePreviousSubWindow();
 
 signals:
    void restoreSelection_sign(bool same_widget);


};

#endif


