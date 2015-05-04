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

#include "ccOpenNI2Dlg.h"

#include <ccOctree.h>

ccOpenNI2Dlg::ccOpenNI2Dlg(QWidget* parent) : QDialog(parent), Ui::OpenNI2Dialog()
{
  setupUi(this);

  setWindowFlags(Qt::Tool/*Qt::Dialog | Qt::WindowStaysOnTopHint*/);
}

QString ccOpenNI2Dlg::getCloudName() const
{
  return cloudNameLineEdit->text();
}

bool ccOpenNI2Dlg::grabRGBInfo()
{
  return grabRGBCheckBox->isChecked();
}

void ccOpenNI2Dlg::addMode(const QString& mode)
{
  resolutionComboBox->addItem(mode);
}

unsigned char ccOpenNI2Dlg::getFrameAveragingCount() const
{
  return (unsigned char)std::min(frameAvgSpinBox->value(),255);
}
