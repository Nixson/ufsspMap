#ifndef MAINMAP_H
#define MAINMAP_H

#include <QMainWindow>
#include <QDateTime>
#include <QMenu>
#include <QAction>
#include "upointer.h"
#include "scenetypes.h"
#include "adminform.h"
#include <QMouseEvent>

namespace Ui {
class MainMap;
}

class MainMap : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMap(QWidget *parent = 0);
    ~MainMap();
protected:
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *mouse) override;

public slots:
    void slotDisplay(QPointF point);

private slots:
    void on_btnRG_clicked();
    void setDateTime();
private:
    Ui::MainMap *ui;
    UPointer *upointer;
    AdminForm *admin;
    void setSubButtonStYle();
    QMenu * createStaticMenu();
};

#endif // MAINMAP_H
