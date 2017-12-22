#ifndef SOVLE_H
#define SOVLE_H

#include <QObject>
#include <QWidget>
#include<QMouseEvent>
#include <QDebug>
#include<QPaintEvent>
#include<QVector>

class sovle : public QWidget
{
    Q_OBJECT
public:
    explicit sovle(QWidget *parent = 0);

    void paintEvent(QPaintEvent *ev);

    void vedinh(QPainter& painter);
    void vecanh(QPainter& painter);
    void vedothi(QPainter& painter);
    void vemuiten(QPainter& painter);
    void xoadothi(QPainter& painter);
    void runall(QPainter& painter);
    bool checkdinh(int x);
    bool checkdinh2(int u, int v);
     bool checkdinh3(int u, int v);
    int x,y,k=0;
    int mode =0,mode2 = 0;
    int timdinh(QPoint a);

   QVector<int> duongdi;
    QPolygon toadodinh,toadocanh1,toadocanh2;
    int mang[1000],dothi[100][100],pi[100][100],next[100][100],s,t,kk=0;

signals:

public slots:
};

#endif // SOVLE_H
