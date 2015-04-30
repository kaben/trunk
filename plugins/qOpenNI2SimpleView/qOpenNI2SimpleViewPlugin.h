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

//qCC
#include "../ccStdPluginInterface.h"

//Qt
#include <QObject>

class ccOpenNI2Dlg;
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
	//replace qOpenNI2 by the plugin name (IID should be unique - let's hope your plugin name is unique ;)
	Q_PLUGIN_METADATA(IID "cccorp.cloudcompare.plugin.qOpenNI2")
#endif

public:

	//! Default constructor
	qOpenNI2SimpleViewPlugin(QObject* parent=0);

	//! Destructor
	virtual ~qOpenNI2SimpleViewPlugin();

	//inherited from ccPluginInterface
	virtual QString getName() const { return "qOpenNI2SimpleViewPlugin"; }
	virtual QString getDescription() const { return "OpenNI2 Simple-View demo  capture"; }
	virtual QIcon getIcon() const;

	//inherited from ccStdPluginInterface
	void onNewSelection(const ccHObject::Container& selectedEntities);
	/*
	Return all actions (QAction objects). CloudCompare will automatically
	add them to an icon in the plugin toolbar and to an entry in the
	plugin menu (when several actions are returned, CC will create a
	dedicated toolbar and sub-menu).
	These actions must be connected to custom slots of this	plugin.
  */
	virtual void getActions(QActionGroup& group);

protected slots:

	/*** ADD YOUR CUSTOM ACTIONS' SLOTS HERE ***/
	void doAction();

	//! Starts actions
	void doStartGrabbing();

	//! Grab cloud
	void grabCloud();

	//! On dialog end
	void dialogClosed(int);

	//! Updates real time view
	void updateRTView();

protected:

	//! Actions
	/** Add as many actions as you want.
		Each will correspond to an icon in the dedicated
		toolbar and an entry in the plugin menu.
	**/
	QAction* m_action;

	//! Associated dialog
	ccOpenNI2Dlg* m_dlg;

	//! Timer to update RT view
	QTimer* m_timer;

protected:
	void console(const char *);
	void console(const char *, const char *);
};

#endif
