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

#ifndef CC_OPENNI2_SIMPLE_VIEW_FRAME_LISTENER_HEADER
#define CC_OPENNI2_SIMPLE_VIEW_FRAME_LISTENER_HEADER

#ifndef _OPENNI_H_
#include  <OpenNI.h>
#endif

#define MAX_DEPTH 10000

class QLabel;
class ccMainAppInterface;

class ccOpenNI2SimpleViewFrameListener : public openni::VideoStream::NewFrameListener
{
public:
  ccMainAppInterface* m_app;
  openni::VideoFrameRef m_frame;
  QLabel *m_label;
  float m_depth_histogram[MAX_DEPTH];
public:
  ccOpenNI2SimpleViewFrameListener(ccMainAppInterface &);
  virtual ~ccOpenNI2SimpleViewFrameListener();
  virtual void onNewFrame(openni::VideoStream &);
  void setLabel(QLabel *);
};

#endif
