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

#ifndef CC_OPENNI2_SIMPLE_VIEW_DLG_HEADER
#define CC_OPENNI2_SIMPLE_VIEW_DLG_HEADER

#ifndef ui_OpenNI2SimpleViewDlg_H
#include "ui_OpenNI2SimpleViewDlg.h"
#endif

//! Dialog for qOpenNI2 plugin
class ccOpenNI2SimpleViewDlg : public QDialog, public Ui::OpenNI2SimpleViewDialog
{
public:

  //! Default constructor
  ccOpenNI2SimpleViewDlg(QWidget* parent = 0);

  //! Returns output clound name
  QString getCloudName() const;

  //! Returns output clound name
  bool grabRGBInfo();

  //! Adds 'resolution mode' string
  void addMode(const QString& mode);

  //! Returns frame averaging
  unsigned char getFrameAveragingCount() const;
};

#endif //CC_OPENNI2_SIMPLE_VIEW_DLG_HEADER
