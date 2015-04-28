//##########################################################################
//#                                                                        #
//#                       CLOUDCOMPARE PLUGIN: qOpenNI2                      #
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
//#                             COPYRIGHT: XXX                             #
//#                                                                        #
//##########################################################################

//First: replace all occurences of 'qOpenNI2Plugin' by your own plugin class name in this file!
#include "qOpenNI2Plugin.h"

//Qt
#include <QtGui>

/* OpenNI2 */
#include <OpenNI.h>
#include "OniSampleUtilities.h"

using namespace openni;
#define SAMPLE_READ_WAIT_TIMEOUT 2000 //2000ms

void qOpenNI2Plugin::console(const char *arg1){
	m_app->dispToConsole(QString("[qOpenNI2Plugin] Warning: %1").arg(arg1));

}

void qOpenNI2Plugin::console(const char *arg1, const char *arg2){
	m_app->dispToConsole(QString("[qOpenNI2Plugin] Warning: %1\n%2").arg(arg1, arg2));

}

//Default constructor: should mainly be used to initialize
//actions (pointers) and other members
qOpenNI2Plugin::qOpenNI2Plugin(QObject* parent/*=0*/)
	: QObject(parent)
	, m_action(0)
{
}

//This method should enable or disable each plugin action
//depending on the currently selected entities ('selectedEntities').
//For example: if none of the selected entities is a cloud, and your
//plugin deals only with clouds, call 'm_action->setEnabled(false)'
void qOpenNI2Plugin::onNewSelection(const ccHObject::Container& selectedEntities)
{
	//if (m_action)
	//	m_action->setEnabled(!selectedEntities.empty());
}

//This method returns all 'actions' of your plugin.
//It will be called only once, when plugin is loaded.
void qOpenNI2Plugin::getActions(QActionGroup& group)
{
	//default action (if it has not been already created, it's the moment to do it)
	if (!m_action)
	{
		//here we use the default plugin name, description and icon,
		//but each action can have its own!
		m_action = new QAction(getName(),this);
		m_action->setToolTip(getDescription());
		m_action->setIcon(getIcon());
		//connect appropriate signal
		connect(m_action, SIGNAL(triggered()), this, SLOT(doAction()));
	}

	group.addAction(m_action);
}

//This is an example of an action's slot called when the corresponding action
//is triggered (i.e. the corresponding icon or menu entry is clicked in CC
//main's interface). You can access to most of CC components (database,
//3D views, console, etc.) via the 'm_app' attribute (ccMainAppInterface
//object).
void qOpenNI2Plugin::doAction()
{
	//m_app should have already been initialized by CC when plugin is loaded!
	//(--> pure internal check)
	assert(m_app);
	if (!m_app)
		return;

	/*** HERE STARTS THE ACTION ***/

	//put your code here
	//--> you may want to start by asking parameters (with a custom dialog, etc.)

	//This is how you can output messages
	//m_app->dispToConsole("[qOpenNI2Plugin] Hello world!",ccMainAppInterface::STD_CONSOLE_MESSAGE); //a standard message is displayed in the console
	//m_app->dispToConsole("[qOpenNI2Plugin] Warning: OpenNI2 plugin shouldn't be used as is!",ccMainAppInterface::WRN_CONSOLE_MESSAGE); //a warning message is displayed in the console
	//m_app->dispToConsole("OpenNI2 plugin shouldn't be used as is!",ccMainAppInterface::ERR_CONSOLE_MESSAGE); //an error message is displayed in the console AND an error box will pop-up!
	console("Hello world!", "(from console.)"); //a standard message is displayed in the console


	Status rc = OpenNI::initialize();
	if (rc != STATUS_OK)
	{
		// printf("Initialize failed\n%s\n", OpenNI::getExtendedError());
		console("Initialize failed:", OpenNI::getExtendedError());
		return;
	}

	Device device;
	rc = device.open(ANY_DEVICE);
	if (rc != STATUS_OK)
	{
		// printf("Couldn't open device\n%s\n", OpenNI::getExtendedError());
		console("Couldn't open device:", OpenNI::getExtendedError());
		return;
	}

	VideoStream depth;

	if (device.getSensorInfo(SENSOR_DEPTH) != NULL)
	{
		rc = depth.create(device, SENSOR_DEPTH);
		if (rc != STATUS_OK)
		{
			// printf("Couldn't create depth stream\n%s\n", OpenNI::getExtendedError());
			console("Couldn't create depth stream:", OpenNI::getExtendedError());
			return;
		}
	}

	rc = depth.start();
	if (rc != STATUS_OK)
	{
		// printf("Couldn't start the depth stream\n%s\n", OpenNI::getExtendedError());
		console("Couldn't start the depth stream:", OpenNI::getExtendedError());
		return;
	}

	VideoFrameRef frame;

	console("Entering stream-read loop...\n");
	//while (!wasKeyboardHit())
	int frames_to_read = 150;
	for (int i = 0; i < frames_to_read; i++)
	{
		int changedStreamDummy;
		VideoStream* pStream = &depth;
		rc = OpenNI::waitForAnyStream(&pStream, 1, &changedStreamDummy, SAMPLE_READ_WAIT_TIMEOUT);
		if (rc != STATUS_OK)
		{
			printf("Wait failed! (timeout is %d ms)\n%s\n", SAMPLE_READ_WAIT_TIMEOUT, OpenNI::getExtendedError());
			//console("Wait failed:", OpenNI::getExtendedError());
			continue;
		}

		rc = depth.readFrame(&frame);
		if (rc != STATUS_OK)
		{
			printf("Read failed!\n%s\n", OpenNI::getExtendedError());
			//console("Read failed:", OpenNI::getExtendedError());
			continue;
		}

		if (frame.getVideoMode().getPixelFormat() != PIXEL_FORMAT_DEPTH_1_MM && frame.getVideoMode().getPixelFormat() != PIXEL_FORMAT_DEPTH_100_UM)
		{
			printf("Unexpected frame format\n");
			//console("Unexpected frame format.");
			continue;
		}

		DepthPixel* pDepth = (DepthPixel*)frame.getData();

		int middleIndex = (frame.getHeight() + 1)*frame.getWidth() / 2;

		//printf("[%08llu] %8d\n", (long long)frame.getTimestamp(), pDepth[middleIndex]);
		m_app->dispToConsole(QString("[qOpenNI2Plugin] %1").arg(pDepth[middleIndex]));
	}

	depth.stop();
	depth.destroy();
	device.close();
	OpenNI::shutdown();

	/*** HERE ENDS THE ACTION ***/

}

//This method should return the plugin icon (it will be used mainly
//if your plugin as several actions in which case CC will create a
//dedicated sub-menu entry with this icon.
QIcon qOpenNI2Plugin::getIcon() const
{
	//open qOpenNI2Plugin.qrc (text file), update the "prefix" and the
	//icon(s) filename(s). Then save it with the right name (yourPlugin.qrc).
	//(eventually, remove the original qOpenNI2Plugin.qrc file!)
	return QIcon(":/CC/plugin/qOpenNI2Plugin/icon.png");
}

#ifndef CC_QT5
//Don't forget to replace 'qOpenNI2Plugin' by your own plugin class name here also!
Q_EXPORT_PLUGIN2(qOpenNI2Plugin,qOpenNI2Plugin);
#endif
