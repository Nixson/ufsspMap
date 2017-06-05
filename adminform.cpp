#include "adminform.h"
#include "ui_adminform.h"
#include <QFileDialog>
#include <QMessageBox>

AdminForm::AdminForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminForm)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    lockPoint = false;
}

AdminForm::~AdminForm()
{
    delete ui;
}

void AdminForm::on_bgImg_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Файл карты"), upointer->getConfDir(),
                                                    tr("Изображения (*.png);;Все файлы (*.*)"));
    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        file.close();
        QString oldImgPath = upointer->getConfDir()+"mainMap.png";
        ui->bgLine->setText(fileName);
        QFile fileOld(oldImgPath);
        if(fileOld.exists())
            fileOld.remove();
        QFile::copy(fileName,oldImgPath);
        upointer->setBg(oldImgPath);

    }
}
void AdminForm::setPointer(UPointer *up){
    upointer = up;
    lockPoint = true;
    ui->bgLine->setText(upointer->getBg());
    fPoint zPoint = upointer->getzPosition();
    ui->x0->setValue((double)zPoint.x);
    ui->y0->setValue((double)zPoint.y);
    fPoint lastPoint = upointer->getlastPosition();
    ui->x1->setValue((double)lastPoint.x);
    ui->y1->setValue((double)lastPoint.y);
    lockPoint = false;
}

void AdminForm::on_addLine_clicked()
{
    iDataLines dl;
    dl.bold = ui->bold->value();
    dl.color = QColor(ui->red->value(),ui->green->value(),ui->blue->value());
    QList <fPoint> data;
    dl.data = data;
    upointer->createLine(&dl);
}

void AdminForm::on_x0_valueChanged(double arg1)
{
    Q_UNUSED(arg1)
    if(!lockPoint)
        upointer->setPosition((float)ui->x0->value(),(float)ui->y0->value(),(float)ui->x1->value(),(float)ui->y1->value());
}

void AdminForm::on_y0_valueChanged(double arg1)
{
    Q_UNUSED(arg1)
    if(!lockPoint) upointer->setPosition((float)ui->x0->value(),(float)ui->y0->value(),(float)ui->x1->value(),(float)ui->y1->value());
}

void AdminForm::on_x1_valueChanged(double arg1)
{
    Q_UNUSED(arg1)
    if(!lockPoint) upointer->setPosition((float)ui->x0->value(),(float)ui->y0->value(),(float)ui->x1->value(),(float)ui->y1->value());
}

void AdminForm::on_y1_valueChanged(double arg1)
{
    Q_UNUSED(arg1)
    if(!lockPoint) upointer->setPosition((float)ui->x0->value(),(float)ui->y0->value(),(float)ui->x1->value(),(float)ui->y1->value());
}
