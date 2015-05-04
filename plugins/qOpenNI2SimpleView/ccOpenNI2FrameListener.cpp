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

#include "ccOpenNI2FrameListener.h"
#include "ccMainAppInterface.h"

#include <QLabel>

ccOpenNI2FrameListener::ccOpenNI2FrameListener(ccMainAppInterface &app)
: m_app(&app)
, m_label(0)
{}
ccOpenNI2FrameListener::~ccOpenNI2FrameListener(){}
void ccOpenNI2FrameListener::onNewFrame(openni::VideoStream &vs){
  vs.readFrame(&m_frame);
  int width = m_frame.getWidth();
  int height = m_frame.getHeight();
  const openni::VideoMode mode = m_frame.getVideoMode();

  if(m_label){
    switch (mode.getPixelFormat()) {
    case openni::PIXEL_FORMAT_DEPTH_1_MM:
    case openni::PIXEL_FORMAT_DEPTH_100_UM:
      {
        // calculateHistogram(m_depth_histogram, MAX_DEPTH, m_frame);
      }
    case openni::PIXEL_FORMAT_SHIFT_9_2:
    case openni::PIXEL_FORMAT_SHIFT_9_3:
      {
      }
      break;
    case openni::PIXEL_FORMAT_RGB888:
      {
        const unsigned char *data = (const unsigned char*)m_frame.getData();
        QImage img(data, width, height, QImage::Format_RGB888);
        m_label->setPixmap(QPixmap::fromImage(img));
      }
      break;
    case openni::PIXEL_FORMAT_YUV422:
      break;
    case openni::PIXEL_FORMAT_GRAY8:
      break;
    case openni::PIXEL_FORMAT_GRAY16:
      break;
    case openni::PIXEL_FORMAT_JPEG:
      break;
    case openni::PIXEL_FORMAT_YUYV:
      break;
    default:
      break;
    }
  }
}
void ccOpenNI2FrameListener::setLabel(QLabel *label){
  m_label = label;
}
