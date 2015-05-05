//##########################################################################
//#                                                                        #
//#                       CLOUDCOMPARE PLUGIN: qOpenNI2                    #
//#                                                                        #
//#  This program is free software; you can redistribute it and/or modify  #
//#  it under the terms of the GNU General Public License as published by  #
//#  the Free Software Foundation; version 2 of the License.               #
//#                                                                        #
//#  This program is distributed in the hope that it will be useful,       #
//#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
//#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
//#  GNU General Public License for more details.                          #
//#                                                                        #
//#                             COPYRIGHT: EntreScan 2015                  #
//#                                                                        #
//##########################################################################

#ifndef Q_OPENNI2_PLUGIN_HEADER
#define Q_OPENNI2_PLUGIN_HEADER

// qCC
#ifndef CC_STD_PLUGIN_INTERFACE_HEADER
#include "../ccStdPluginInterface.h"
#endif

// Qt
#ifndef QOBJECT_H
#include <QObject>
#endif

// OpenNI2
#ifndef _OPENNI_H_
#include  <OpenNI.h>
#endif
class ccOpenNI2SimpleViewDlg;
class ccOpenNI2SimpleViewStreamer;
class QActions;

//! OpenNI2 qCC plugin
/**
Look at the ccStdPluginInterface::m_app attribute to get access to
most of CC components (database, 3D views, console, etc.).
**/

class qOpenNI2SimpleViewPlugin : public QObject, public ccStdPluginInterface
{
  Q_OBJECT
  Q_INTERFACES(ccStdPluginInterface)
#ifdef CC_QT5
  Q_PLUGIN_METADATA(IID "scandyco.cloudcompare.plugin.qOpenNI2SimpleView")
#endif

public:
  qOpenNI2SimpleViewPlugin(QObject* parent=0);
  virtual ~qOpenNI2SimpleViewPlugin();

  /* Inherited from ccPluginInterface */
  virtual QString getName() const { return "qOpenNI2SimpleViewPlugin"; }
  virtual QString getDescription() const { return "OpenNI2 Simple-View demo  capture"; }
  virtual QIcon getIcon() const;

  /* Inherited from ccStdPluginInterface */
  void onNewSelection(const ccHObject::Container& selectedEntities);
  /*
  Return all actions (QAction objects). CloudCompare will automatically
  add them to an icon in the plugin toolbar and to an entry in the
  plugin menu (when several actions are returned, CC will create a
  dedicated toolbar and sub-menu).
  These actions must be connected to custom slots of this plugin.
  */
  virtual void getActions(QActionGroup& group);

  void setupStreamer(const char *uri);
  void teardownStreamer();

protected slots:
  /*** ACTIONS' SLOTS ***/
  //! Starts actions
  void doStartGrabbing();
  //! Grab cloud
  void grabCloud();
  //! On dialog end
  void dialogClosed(int);

protected:
  //! Actions
  /** Add as many actions as you want.
    Each will correspond to an icon in the dedicated
    toolbar and an entry in the plugin menu.
  **/
  QAction* m_action;

  //! Associated dialog
  ccOpenNI2SimpleViewDlg* m_dlg;

  /* OpenNI2 */
  ccOpenNI2SimpleViewStreamer *m_streamer;
  int m_frame_ct;

protected:
  void console(const char *);
  void console(const char *, const char *);
};

#endif
