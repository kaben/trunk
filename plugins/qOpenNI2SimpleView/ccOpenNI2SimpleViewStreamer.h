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

#ifndef CC_OPENNI2_SIMPLE_VIEW_STREAMER_HEADER
#define CC_OPENNI2_SIMPLE_VIEW_STREAMER_HEADER

#ifndef CC_OPENNI2_FRAME_LISTENER_HEADER
#include "ccOpenNI2FrameListener.h"
#endif

#ifndef _OPENNI_H_
#include  <OpenNI.h>
#endif

class ccMainAppInterface;

class ccOpenNI2SimpleViewStreamer
{
public:
  openni::Device m_dev;
  openni::VideoStream m_depth, m_color;
  ccMainAppInterface* m_app;
  ccOpenNI2FrameListener m_depth_frame_listener, m_color_frame_listener;

public:
  ccOpenNI2SimpleViewStreamer(ccMainAppInterface &);
  virtual ~ccOpenNI2SimpleViewStreamer();

  openni::Status setupAll(const char *uri);
  openni::Status setupDevice(openni::Device &, const char *uri);
  openni::Status setupVideoStream(openni::VideoStream &, openni::SensorType, openni::Device &, ccOpenNI2FrameListener &);

  void teardownAll();
  void teardownVideoStream(openni::VideoStream &, ccOpenNI2FrameListener &);
  void teardownDevice(openni::Device &);

  void console(const char *);
  void console(const char *, const char *);
};

#endif
