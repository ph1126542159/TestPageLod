#include "QtOsgView.h"
#include <QDebug>
class SysncOperation :public osg::GraphicsOperation
{

public:
    SysncOperation() :osg::GraphicsOperation("SysncOperation", false)
    {

    }
    virtual void operator() (osg::GraphicsContext* context)
    {
        if (context)
        {
            context->makeCurrent();
            if (osgViewer::GraphicsWindow* window = dynamic_cast<osgViewer::GraphicsWindow*>(context))
            {
                // 关闭显卡垂直同步
                window->setSyncToVBlank(false);
            }
        }
    }
};

QtOsgView::QtOsgView(QWidget *parent)
    : AdapterWidget{parent}
{
    getCamera()->setViewport(new osg::Viewport(0,0,width(),height()));
    getCamera()->setProjectionMatrixAsPerspective(30,static_cast<double>(width()) / static_cast<double>(height()), 1.0f, 10000.0f);
    getCamera()->setGraphicsContext(getGraphicsWindow());
    setThreadingModel(osgViewer::Viewer::DrawThreadPerContext);
    setRealizeOperation(new SysncOperation());
    osg::DisplaySettings::instance()->setNumOfDatabaseThreadsHint(4);
    osg::DisplaySettings::instance()->setMaxTexturePoolSize(64000);
    m_dStrTime=0;
    m_dEndTime=0;
    m_dSleepTime=10;

    m_nNum=0;
}

void QtOsgView::paintGL()
{
    m_dStrTime = m_Timer.tick();
    frame();
    m_nNum++;
    m_dEndTime = m_Timer.tick();

    //计算需要睡眠的时间
    m_dSleepTime = 1.0 / 60.0 - m_Timer.delta_s(m_dStrTime, m_dEndTime);

    if (m_dSleepTime < 0)
    {
        m_dSleepTime = 0.0;
    }

    //睡眠
    OpenThreads::Thread::microSleep(m_dSleepTime * 1000000);		//微秒

    //递归调用
    update();
}
