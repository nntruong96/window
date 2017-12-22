#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include<QMouseEvent>
#include<QDebug>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


private slots:

    void on_vd_released();

    void on_pushButton_clicked();

    void on_vc_clicked();

    void on_xoa_clicked();

    int timdinh(QPoint a);

    void luudothi();

    void floyd();
    void floyd2();
    void delay();
    void induongdi();
    void nhapst();

    void on_matran_clicked();

    void on_runall_clicked();

    void on_runstep_clicked();
    void inmtkhoancach(int u,int v,int k);
    void inmtduongdi();

    void on_horizontalSlider_valueChanged(int value);


    void on_checkBox_clicked(bool checked);

private:
 int ms=2000,ms2;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
