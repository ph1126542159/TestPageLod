#ifndef QTOSGVIEW_H
#define QTOSGVIEW_H

#include "AdapterWidget.h"
#include "osgViewer/Viewer"
class QtOsgView : public osgViewer::Viewer,public AdapterWidget
{
public:
    explicit QtOsgView(QWidget *parent = nullptr);

    virtual void paintGL();
private:
    osg::Timer m_Timer;
    double m_dStrTime;
    double m_dEndTime;
    double m_dSleepTime;
    int m_nNum;
};

#endif // QTOSGVIEW_H
