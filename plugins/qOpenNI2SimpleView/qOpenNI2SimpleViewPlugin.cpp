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

qOpenNI2SimpleViewPlugin::qOpenNI2SimpleViewPlugin(QObject* parent/*=0*/)
  : QObject(parent)
  , ccStdPluginInterface()
  , m_action(0)
  , m_dlg(0)
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
    delete m_streamer;
    m_streamer = 0;
  }
}

/*
Enable or disable each plugin action depending on currently selected entities
('selectedEntities'). E.g.: if none of the selected entities is a cloud,
and plugin deals only with clouds, call 'm_action->setEnabled(false)'.
*/
void qOpenNI2SimpleViewPlugin::onNewSelection(const ccHObject::Container& selectedEntities) {
  //if (m_action)
  //  m_action->setEnabled(!selectedEntities.empty());
}

/* Returns all plugin 'actions'; called once when plugin is loaded. */
void qOpenNI2SimpleViewPlugin::getActions(QActionGroup& group) {
  if (!m_action) {
    /* Each action can have its own plugin name, description and icon. */
    m_action = new QAction(getName(),this);
    m_action->setToolTip(getDescription());
    m_action->setIcon(getIcon());
    connect(m_action, SIGNAL(triggered()), this, SLOT(doStartGrabbing()));
  }
  group.addAction(m_action);
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
}
void qOpenNI2SimpleViewPlugin::grabCloud()
{}
void qOpenNI2SimpleViewPlugin::dialogClosed(int){
  teardownStreamer();
}

/*
Plugin icon (it will be used mainly if plugin has several actions,
in which case CC will create a dedicated sub-menu entry with this icon.
*/
QIcon qOpenNI2SimpleViewPlugin::getIcon() const {
  return QIcon(":/CC/plugin/qOpenNI2SimpleViewPlugin/icon.png");
}

#ifndef CC_QT5
Q_EXPORT_PLUGIN2(qOpenNI2SimpleViewPlugin, qOpenNI2SimpleViewPlugin);
#endif
