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

//First: replace all occurences of 'qOpenNI2SimpleViewPlugin' by your own plugin class name in this file!
#include "qOpenNI2SimpleViewPlugin.h"

//dialog
#include "ccOpenNI2Dlg.h"

#include <iostream>

//Qt
#include <QElapsedTimer>
#include <QMainWindow>
#include <QtGui>

/* OpenNI2 */
#include <OpenNI.h>
#include "OniSampleUtilities.h"
#include "ccOpenNI2SimpleViewStreamer.h"

#define SAMPLE_READ_WAIT_TIMEOUT 2000 //2000ms

void qOpenNI2SimpleViewPlugin::console(const char *arg1){
  m_app->dispToConsole(QString("[qOpenNI2SimpleViewPlugin] Warning: %1").arg(arg1));

}
void qOpenNI2SimpleViewPlugin::console(const char *arg1, const char *arg2){
  m_app->dispToConsole(QString("[qOpenNI2SimpleViewPlugin] Warning: %1\n%2").arg(arg1, arg2));

}

//Default constructor: should mainly be used to initialize
//actions (pointers) and other members
qOpenNI2SimpleViewPlugin::qOpenNI2SimpleViewPlugin(QObject* parent/*=0*/)
  : QObject(parent)
  , ccStdPluginInterface()
  , m_action(0)
  , m_dlg(0)
  , m_timer(0)
  // , m_device(0)
  , m_streamer(0)
  , m_frame_ct(0)
{}
qOpenNI2SimpleViewPlugin::~qOpenNI2SimpleViewPlugin() {
  if (m_dlg){ delete m_dlg; }
  teardownStreamer();
}

void qOpenNI2SimpleViewPlugin::setupStreamer(const char *uri){
  teardownStreamer();
  m_streamer = new ccOpenNI2SimpleViewStreamer(*m_app);
  if (!m_streamer){
    console("Couldn't create streamer. Exiting.");
    return;
  }
  openni::Status rc = m_streamer->setupAll(uri);
  if (rc != openni::STATUS_OK) {
    console("Couldn't setup streamer:", openni::OpenNI::getExtendedError());
  }
}

void qOpenNI2SimpleViewPlugin::teardownStreamer(){
  if (m_streamer){
    // m_streamer->teardownAll();
    delete m_streamer;
    m_streamer = 0;
  }
}

//This method should enable or disable each plugin action
//depending on the currently selected entities ('selectedEntities').
//For example: if none of the selected entities is a cloud, and your
//plugin deals only with clouds, call 'm_action->setEnabled(false)'
void qOpenNI2SimpleViewPlugin::onNewSelection(const ccHObject::Container& selectedEntities) {
  //if (m_action)
  //  m_action->setEnabled(!selectedEntities.empty());
}

//This method returns all 'actions' of your plugin.
//It will be called only once, when plugin is loaded.
void qOpenNI2SimpleViewPlugin::getActions(QActionGroup& group) {
  //default action (if it has not been already created, it's the moment to do it)
  if (!m_action) {
    //here we use the default plugin name, description and icon,
    //but each action can have its own!
    m_action = new QAction(getName(),this);
    m_action->setToolTip(getDescription());
    m_action->setIcon(getIcon());
    //connect appropriate signal
    //connect(m_action, SIGNAL(triggered()), this, SLOT(doAction()));
    connect(m_action, SIGNAL(triggered()), this, SLOT(doStartGrabbing()));
  }

  group.addAction(m_action);
}

void qOpenNI2SimpleViewPlugin::onNewFrame(openni::VideoStream &vstream){
  console("got new frame.");
}

void qOpenNI2SimpleViewPlugin::doStartGrabbing() {
  assert(m_app);
  if (!m_app){ return; }

  const char* device_uri = openni::ANY_DEVICE;
  setupStreamer(device_uri);

  m_dlg = new ccOpenNI2Dlg(m_app->getMainWindow());
  m_dlg->grabRGBCheckBox->setChecked(false);
  m_dlg->grabPushButton->setEnabled(true);

  connect(m_dlg->grabPushButton, SIGNAL(clicked()), this, SLOT(grabCloud()));
  connect(m_dlg, SIGNAL(finished(int)), this, SLOT(dialogClosed(int)));

  //m_dlg->setModal(false);
  //m_dlg->setWindowModality(Qt::NonModal);
  m_dlg->show();

  if (!m_timer) {
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateRTView()));
  }
  m_timer->start(0);
}
void qOpenNI2SimpleViewPlugin::grabCloud()
{}
void qOpenNI2SimpleViewPlugin::dialogClosed(int){
  teardownStreamer();
}
void qOpenNI2SimpleViewPlugin::updateRTView()
{}

//This method should return the plugin icon (it will be used mainly
//if your plugin as several actions in which case CC will create a
//dedicated sub-menu entry with this icon.
QIcon qOpenNI2SimpleViewPlugin::getIcon() const {
  //open qOpenNI2SimpleViewPlugin.qrc (text file), update the "prefix" and the
  //icon(s) filename(s). Then save it with the right name (yourPlugin.qrc).
  //(eventually, remove the original qOpenNI2SimpleViewPlugin.qrc file!)
  return QIcon(":/CC/plugin/qOpenNI2SimpleViewPlugin/icon.png");
}

#ifndef CC_QT5
//Don't forget to replace 'qOpenNI2SimpleViewPlugin' by your own plugin class name here also!
Q_EXPORT_PLUGIN2(qOpenNI2SimpleViewPlugin,qOpenNI2SimpleViewPlugin);
#endif
