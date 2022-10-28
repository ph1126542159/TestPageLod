#ifndef ADAPTERWIDGET_H
#define ADAPTERWIDGET_H

#include <QOpenGLWidget>
#include "osgViewer/Viewer"
class AdapterWidget : public QOpenGLWidget
{
public:
    explicit AdapterWidget(QWidget *parent = nullptr);
    osgViewer::GraphicsWindow* getGraphicsWindow();
    const osgViewer::GraphicsWindow* getGraphicsWindow()const;
protected:
    virtual void resizeGL(int width, int height);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void keyReleaseEvent(QKeyEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void wheelEvent(QWheelEvent* event);
    osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> m_ptrGw;
};

#endif // ADAPTERWIDGET_H
