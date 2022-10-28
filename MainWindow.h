#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfo>
#include <QList>
#include <qrunnable.h>
#include <osg/Group>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class CreateTree :public QObject, public QRunnable {
    Q_OBJECT
public:
    CreateTree(osg::Group* group);
    void run();
signals:
    void createFinished(osg::ref_ptr<osg::Group>);
private:
    osg::ref_ptr<osg::Group> _root;
};
class QProgressBar;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionLoad_Model_triggered();

    void on_actionOpen_File_triggered();

    void on_actionSave_As_File_triggered();

    void on_actionCreate_Model_triggered();

    void on_actionBig_Scene_triggered();
    void createFinished(osg::ref_ptr<osg::Group>);
private:
    void getModelPath(QList<QFileInfo>& outList, const QString& path, const QString& filter);
    void initUI();
    Ui::MainWindow* ui;
    QProgressBar * pProgressBar;
};
#endif // MAINWINDOW_H
