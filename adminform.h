#ifndef ADMINFORM_H
#define ADMINFORM_H

#include <QWidget>
#include <string>
#include "upointer.h"

using namespace  std;
namespace Ui {
class AdminForm;
}

class AdminForm : public QWidget
{
    Q_OBJECT

public:
    explicit AdminForm(QWidget *parent = 0);
    ~AdminForm();
    void setPointer(UPointer *up);
    void parseValueToInt(string s);

private slots:
    void reloadNumberPathPoint();

    void onNumberPathPointSelect(int i);

    void setOGP(int i);

    void setTypeAirObject(int i);

    void onDrawAirPoint(int i);

    void parseValueToInt(QString s);

    void on_bgImg_clicked();

    void on_addLine_clicked();

    void on_x0_valueChanged(double arg1);

    void on_y0_valueChanged(double arg1);

    void on_x1_valueChanged(double arg1);

    void on_y1_valueChanged(double arg1);

    void on_newPath_clicked();

    void on_deletePath_clicked();

    void on_saveNewPath_clicked();

private:
    Ui::AdminForm *ui;
    UPointer *upointer;
    bool lockPoint;
    flightRoute path;
    int countTargetNumber;
    void installOGP();
    void installTypeAirObject();
    void isActiveComboBox(bool isActive);
    void instalSettingsPath();
};

#endif // ADMINFORM_H
