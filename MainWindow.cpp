#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "osg/Node"
#include "osgDB/ReadFile"
#include "QtOsgView.h"
#include "osgGA/TrackballManipulator"
#include "osgViewer/ViewerEventHandlers"
#include "osgDB/WriteFile"
#include <QDir>
#include <QDebug>
#include "osg/ProxyNode"
#include <QFileDialog>
#include "osg/PositionAttitudeTransform"
#include "osg/ShapeDrawable"
#include <QUuid>
#include <QRunnable>
#include <mutex>
#include <QThreadPool>
#include <QTimer>
#include <QProgressBar>


std::atomic_int64_t g_num_max=1000000;
QtOsgView* m_ptrView=nullptr;
QThreadPool* g_threadPool=nullptr;
osg::ref_ptr<osg::Group> g_root;
osg::ref_ptr<osg::ProxyNode> g_proxyNode;
std::mutex g_mtx;
unsigned int g_sqrtNum=0;
QPointF getPoint(){
    static float offset=50.0f;
    static std::atomic_uint g_i = 0;
    static std::atomic_uint g_j = 0;
    g_j++;
    if(g_j>g_sqrtNum){
        g_i++;
        g_j=0;
    }

    return QPoint(g_i*offset,g_j*offset);
}
osg::ref_ptr<osg::Geode> createBox(const osg::Vec3& center, float width)
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(new osg::ShapeDrawable(new osg::Box(center, width)));
    return geode.release();
}
osg::ref_ptr<osg::Group> createPagedLOD(int row, int col)
{
    float offsets=50.0f;
    osg::ref_ptr<osg::Group> root = new osg::Group;
    for (int i = 0; i<row; i++)
    {
        for (int j = 0; j<col; j++)
        {
            osg::ref_ptr<osg::PagedLOD> lod = new osg::PagedLOD;
            lod->setCenter(osg::Vec3(i * offsets, j * offsets, 0.0));
            //lod->addChild(createBox(osg::Vec3(i * offsets, j * offsets, 0.0), 1), 300.0, 1000.0f);
            osg::ref_ptr<osg::PositionAttitudeTransform> posNode=new osg::PositionAttitudeTransform;
            posNode->addChild(g_proxyNode);
            posNode->setPosition(osg::Vec3(i * offsets, j * offsets, 0.0));
            lod->addChild(posNode,300.0,1000.0);
            root->addChild(lod.get());
        }
    }
    return root.release();
}

CreateTree::CreateTree(osg::Group* group):_root(group) {
}

void CreateTree::run() {
    while (--g_num_max >= 0) {
        QPointF pt=getPoint();
        osg::ref_ptr<osg::PagedLOD> lod = new osg::PagedLOD;
        lod->setCenter(osg::Vec3(pt.x(),pt.y(), 0.0));
        //lod->addChild(createBox(osg::Vec3(pt.x(),pt.y(), 0.0), 1), 300.0, 1000.0f);
        osg::ref_ptr<osg::PositionAttitudeTransform> posNode = new osg::PositionAttitudeTransform;
        posNode->addChild(g_proxyNode);
        posNode->setPosition(osg::Vec3(pt.x(),pt.y(), 0.0));
        lod->addChild(posNode, 200.0, 1000.0);
        _root->addChild(lod);
    }
    emit createFinished(_root);
}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qRegisterMetaType<osg::ref_ptr<osg::Group>>("osg::ref_ptr<osg::Group>");

    m_ptrView =new QtOsgView(this);
    m_ptrView->setCameraManipulator(new osgGA::TrackballManipulator);
    m_ptrView->addEventHandler(new osgViewer::WindowSizeHandler);
    m_ptrView->addEventHandler(new osgViewer::StatsHandler);

    this->setCentralWidget(m_ptrView);

    g_sqrtNum=sqrt(g_num_max.load());
    g_threadPool=new QThreadPool();
    g_threadPool->setMaxThreadCount(12);
    g_root = new osg::Group;

    osg::ref_ptr<osgDB::Options> options =  new osgDB::Options();
    options->setOptionString("noTriStripPolygons");
    options->setOptionString("inlineExternalReferencesInIVEFile");
    options->setOptionString("OutputTextureFiles");

    const std::string filename("F:/OSG/Test/TestPageLod/trees11/Group3.3ds");
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile(filename,options);
    g_proxyNode=new osg::ProxyNode;
    g_proxyNode->addChild(node,filename);

    initUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initUI()
{
    pProgressBar = new QProgressBar();
    ui->statusbar->addPermanentWidget(pProgressBar);
}


void MainWindow::on_actionLoad_Model_triggered()
{
    QString path=QFileDialog::getExistingDirectory(nullptr,QString("选择目录"),"./");
    if(path.isEmpty()) return;
    QList<QFileInfo> list;
    getModelPath(list,path,"obj");

    osg::ref_ptr<osgDB::Options> options = new osgDB::Options;
    options->setOptionString("noTriStripPolygons");
    options->setOptionString("noWriteExternalReferenceFiles");
    options->setOptionString("OutputTextureFiles");
    options->setOptionString("Compressor=zlib");
    options->setOptionString("ForceReadingImage");
    osg::ref_ptr<osg::ProxyNode> proxyNode = new osg::ProxyNode;
    foreach (auto const& it, list) {
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile(it.absoluteFilePath().toStdString(),options);
        osg::ref_ptr<osg::PositionAttitudeTransform> posNode = new osg::PositionAttitudeTransform();
        posNode->addChild(node);
        proxyNode->addChild(posNode, it.absoluteFilePath().toStdString());
    }
    m_ptrView->getSceneData()->asGroup()->addChild(proxyNode);
}
void MainWindow::getModelPath(QList<QFileInfo>& outList,const QString& path,const QString& filter){
    QDir dir(path);
    if(!dir.exists()) return;
    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden);
    dir.setSorting(QDir::DirsFirst);
    foreach(QFileInfo info,dir.entryInfoList())
    {
        if(!info.isFile())
        {
            getModelPath(outList,info.filePath(),filter);
            continue;
        }
        if(!filter.contains(info.completeSuffix().toLower())) continue;
        outList<<info;
    }
}

void MainWindow::on_actionOpen_File_triggered()
{
    QString path=QFileDialog::getOpenFileName(nullptr,QString("选择文件"),"./");
    if(path.isEmpty()) return;

    osg::ref_ptr<osgDB::Options> options =  new osgDB::Options();
    options->setOptionString("noTriStripPolygons");
    options->setOptionString("inlineExternalReferencesInIVEFile");
    options->setOptionString("OutputTextureFiles");

    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile(path.toStdString(),options);
    osg::ref_ptr<osg::ProxyNode> proxyNode=new osg::ProxyNode;
    QUuid id = QUuid::createUuid();
    QString strId = id.toString();
    proxyNode->addChild(node,strId.toStdString());

    osg::ref_ptr<osg::Group> group=new osg::Group;
    group->addChild(proxyNode);
    m_ptrView->setSceneData(group);
}


void MainWindow::on_actionSave_As_File_triggered()
{
    QString path=QFileDialog::getSaveFileName(nullptr,QString("选择文件"),"./","*.ive");
    if(path.isEmpty()) return;
    osg::ref_ptr<osgDB::Options> options = new osgDB::Options;
    options->setOptionString("IncludingHint");
    options->setOptionString("noWriteExternalReferenceFiles");
    options->setOptionString("WriteImageHint=IncludeFile");
    osgDB::writeNodeFile(*m_ptrView->getSceneData(), path.toStdString(), options);
}

void MainWindow::on_actionCreate_Model_triggered()
{
    g_root->addChild(createPagedLOD(100, 100));
    m_ptrView->setSceneData(g_root);
}


void MainWindow::on_actionBig_Scene_triggered()
{
    if(g_threadPool->activeThreadCount()>0) return;
    pProgressBar->setRange(0,g_num_max);
    for(int i=0;i<g_threadPool->maxThreadCount();i++){
        osg::ref_ptr<osg::Group> group=new osg::Group;
        CreateTree* tr=new CreateTree(group);
        connect(tr, SIGNAL(createFinished(osg::ref_ptr<osg::Group>)), this,SLOT(createFinished(osg::ref_ptr<osg::Group>)));
        tr->setAutoDelete(true);
        g_threadPool->start(tr);
    }

    QTimer* time=new QTimer();
    time->setInterval(1000);
    QObject::connect(time,&QTimer::timeout,[=](){
        pProgressBar->setValue(pProgressBar->maximum()-g_num_max);
        if (g_num_max >= 0) return;
        time->stop();
        time->deleteLater();
        m_ptrView->setSceneData(g_root);

        osgDB::DatabasePager* pager = m_ptrView->getDatabasePager();
        pager->setDoPreCompile(true);
        pager->setTargetMaximumNumberOfPageLOD(10);

        pProgressBar->setValue(pProgressBar->maximum());
    });
    time->start();
}

void MainWindow::createFinished(osg::ref_ptr<osg::Group> group) {
    std::lock_guard<std::mutex> lock(g_mtx);
    g_root->addChild(group);
}
