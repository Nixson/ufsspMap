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
    ui->graphicsView->setScene(upointer->getScene());
    upointer->reWrite(ui->graphicsView->width(),ui->graphicsView->height());
    admin = new AdminForm();
    admin->setPointer(upointer);
    // отображение положения курсора на сцене в Дисплее
    connect(upointer->getScene(), SIGNAL(signalCursor(QPointF)), this,SLOT(slotDisplay(QPointF)));
    ui->graphicsView->setMouseTracking(true);
    this->ui->label_2->setStyleSheet("background-color: rgb(56, 235,229)");
    this->setSubButtonStYle();
    QTimer* timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(setDateTime()));
    timer->start(1000);

    ui->pushButtonStatic->setMenu(createStaticMenu());

}
void MainMap::resizeEvent(QResizeEvent* event) {
    Q_UNUSED(event);
    upointer->reWrite(ui->graphicsView->width(),ui->graphicsView->height());
}

void MainMap::mousePressEvent(QMouseEvent *mouse){
    QPoint pf = mouse->pos();
    upointer->setPoint(pf);
}

void MainMap::slotDisplay(QPointF point)
{
    this->ui->displayX->display(point.x());
    this->ui->displayY->display(point.y());
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

void MainMap::setDateTime()
{
    QDateTime DaTi=QDateTime::currentDateTime();
    ui->label->setText(DaTi.date().toString("dd-MM")+
   "  "+DaTi.time().toString("hh:mm:ss"));
}

void MainMap::setSubButtonStYle()
{
    ui->subButton->setStyleSheet("color: rgb(195, 175,8)");
    ui->subButton->setEnabled(false);
    ui->subButton2->setStyleSheet("color: rgb(195, 175,8)");
    ui->subButton2->setEnabled(false);
    ui->subButton3->setStyleSheet("color: rgb(195, 175,8)");
    ui->subButton3->setEnabled(false);

}

QMenu * MainMap::createStaticMenu()
{   QMenu* menu=new QMenu(this);
    QMenu* first=new QMenu(trUtf8("Дислокация"), this);
    QMenu* menu1=new QMenu(trUtf8("Аэродромы"), this);
    QAction* third=new QAction(trUtf8("Сетка"), this);
    QAction* f4=new QAction(trUtf8("Карта"), this);
    QAction* f5=new QAction(trUtf8("Полосы"), this);
    QAction* f6=new QAction(trUtf8("Трассы"), this);
    QAction* f7=new QAction(trUtf8("Гран. ответ."), this);
    QAction* f8=new QAction(trUtf8("зоны и рубежи"), this);
    menu->addMenu(first);
    menu->addMenu(menu1);
    menu1->addAction("Все аэродромы",upointer,SLOT(airfieldAll()));
    menu1->addAction("Свои",upointer,SLOT(airfieldOwn()));
    menu1->addAction("Чужие",upointer,SLOT(airfieldForeign()));
    menu->addAction(third);
    menu->addAction(f4);
    menu->addAction(f5);
    menu->addAction(f6);
    menu->addAction(f7);
    menu->addAction(f8);
    return menu;
}



