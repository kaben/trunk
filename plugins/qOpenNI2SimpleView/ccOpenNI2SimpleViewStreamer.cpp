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


/*
Typical use:

m_streamer = new ccOpenNI2SimpleViewStreamer(*m_app);
if (!m_streamer){
  console("Couldn't create streamer. Exiting.");
  return;
}
openni::Status rc = m_streamer->setupAll(uri);
if (rc != openni::STATUS_OK) {
  console("Couldn't setup streamer:", openni::OpenNI::getExtendedError());
}

delete m_streamer;

*/


#include "ccOpenNI2SimpleViewStreamer.h"
#include "ccMainAppInterface.h"

ccOpenNI2SimpleViewStreamer::ccOpenNI2SimpleViewStreamer(ccMainAppInterface &app)
: m_app(&app)
, m_depth_frame_listener(app)
, m_color_frame_listener(app)
{
  openni::Status rc = openni::OpenNI::initialize();
  console("After OpenNI2 initialization:", openni::OpenNI::getExtendedError());
}

ccOpenNI2SimpleViewStreamer::~ccOpenNI2SimpleViewStreamer(){
  teardownAll();
  openni::OpenNI::shutdown();
}

openni::Status ccOpenNI2SimpleViewStreamer::setupAll(const char *uri){
  openni::Status rc = openni::STATUS_OK;
  if (rc == openni::STATUS_OK)
  { rc = setupDevice(m_dev, uri); }
  if (rc == openni::STATUS_OK){
    rc = setupVideoStream(m_depth, openni::SENSOR_DEPTH, m_dev, m_depth_frame_listener);
  }
  if (rc == openni::STATUS_OK){
    rc = setupVideoStream(m_color, openni::SENSOR_COLOR, m_dev, m_color_frame_listener);
  }
  return rc;
}

openni::Status ccOpenNI2SimpleViewStreamer::setupDevice(
  openni::Device &dev,
  const char *uri
){
  openni::Status rc = dev.open(uri);
  if (rc != openni::STATUS_OK)
  { console("Couldn't open device:", openni::OpenNI::getExtendedError()); }
  return rc;
}

openni::Status ccOpenNI2SimpleViewStreamer::setupVideoStream(
  openni::VideoStream &vs,
  openni::SensorType typ,
  openni::Device &dev,
  ccOpenNI2SimpleViewFrameListener &fl
){
  openni::Status rc = vs.create(dev, typ);
  if (rc == openni::STATUS_OK) {
    rc = vs.addNewFrameListener(&fl);
    if (rc == openni::STATUS_OK) {
      rc = vs.start();
    } else {
      console("Couldn't add new-frame listener:", openni::OpenNI::getExtendedError());
    }
    if (rc != openni::STATUS_OK) {
      console("Couldn't start stream:", openni::OpenNI::getExtendedError());
      vs.destroy();
    }
  } else
  { console("Couldn't find stream:", openni::OpenNI::getExtendedError()); }
  return rc;
}

void ccOpenNI2SimpleViewStreamer::teardownAll(){
  teardownVideoStream(m_color, m_color_frame_listener);
  teardownVideoStream(m_depth, m_depth_frame_listener);
  teardownDevice(m_dev);
}

void ccOpenNI2SimpleViewStreamer::teardownVideoStream(
  openni::VideoStream &vs,
  ccOpenNI2SimpleViewFrameListener &fl
){
  vs.removeNewFrameListener(&fl);
  vs.stop();
  vs.destroy();
}

void ccOpenNI2SimpleViewStreamer::teardownDevice(openni::Device &dev){
  dev.close();
}

/* These are for logging messages to the CloudCompare console. */
void ccOpenNI2SimpleViewStreamer::console(const char *arg1){
  m_app->dispToConsole(QString("[ccOpenNI2SimpleViewStreamer] %1").arg(arg1));
}

void ccOpenNI2SimpleViewStreamer::console(const char *arg1, const char *arg2){
  m_app->dispToConsole(QString("[ccOpenNI2SimpleViewStreamer] %1\n%2").arg(arg1, arg2));
}
