#include "mainmap.h"
#include "ui_mainmap.h"
#include <QCoreApplication>
#include <QDesktopWidget>
#include <QDir>

MainMap::MainMap(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMap)
{
    ui->setupUi(this);
    QString confDir = QCoreApplication::applicationDirPath()+"/conf/";
    QDir dir(confDir);
    if(!dir.exists() && !dir.mkdir(confDir)){
        //error
    }
    upointer = new UPointer(confDir);
//    upointer->setConfDir();
    ui->graphicsView->setScene(upointer->getScene());
    upointer->reWrite(ui->graphicsView->width(),ui->graphicsView->height());
    admin = new AdminForm();
    admin->setPointer(upointer);
}
void MainMap::resizeEvent(QResizeEvent* event) {
    Q_UNUSED(event);
    upointer->reWrite(ui->graphicsView->width(),ui->graphicsView->height());
}

void MainMap::mousePressEvent(QMouseEvent *mouse){
    QPoint pf = mouse->pos();
    upointer->setPoint(pf);
}

MainMap::~MainMap()
{
    delete ui;
}

void MainMap::on_btnRG_clicked()
{
    admin->setGeometry(QStyle::alignedRect(
                        Qt::LeftToRight,
                        Qt::AlignCenter,
                        admin->size(),
                        qApp->desktop()->availableGeometry()
                    ));
    admin->show();
}
