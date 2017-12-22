#include "sovle.h"
#include<Qpainter>
#include<QPen>
#include <QtMath>
#include <math.h>
sovle::sovle(QWidget *parent) : QWidget(parent)
{

}

void sovle::paintEvent(QPaintEvent *ev)
{
     QPainter painter(this);
     painter.setRenderHint(QPainter::Antialiasing);
     painter.setPen(Qt::NoPen);
     painter.setBrush(QColor(240,255,255));
     painter.drawRect(0,0,1265,851);
     QPen pen(Qt::black,3,Qt::SolidLine);
     painter.setPen(pen);
     painter.drawRect(2,2,870,495);
     painter.drawRect(2,520,870,80);
     painter.drawRect(880,2,383,597);
     painter.drawText(880,620,QString("Lịch sử thuật toán: Thuật toán Floyd-Warshall còn được gọi là thuật "));
     painter.drawText(880,640,QString("toán Floyd được Robert Floyd tìm ra năm 1962. Thuật toán Floyd "));
     painter.drawText(880,660,QString("còn là một thuật toán giải quyết bài toán đường đi ngắn nhất giữa "));
     painter.drawText(880,680,QString("tất cả các đỉnh trong đồ thị có hướng hoặc vô hướng có cạnh mang "));
     painter.drawText(880,700,QString("trọng số dương dựa trên khái niệm các đỉnh trung gian."));
     if( mode  == 1 || mode ==2  || mode2 == 1 || mode ==4) vedothi(painter);
     if( mode2 == 2 )
         xoadothi(painter);

     if(mode == 3) runall(painter);
}

void sovle::vedinh(QPainter &painter) //Vẽ đỉnh
{
    QPen pen(Qt::black,2,Qt::SolidLine);
    painter.setPen(pen);
    int n=toadodinh.size(),k=0;
    for(int j=0;j<n;j++)
    {
        k++;
        painter.setBrush(QColor(255,248,134));
        painter.drawEllipse(toadodinh.value(j),20,20);
        painter.drawText(toadodinh.value(j).x()-5,toadodinh.value(j).y()+5,QString("%1").arg(k));
    }
}

void sovle::vecanh(QPainter &painter) // Vẽ cạnh
{
    QPen pen(Qt::black,1,Qt::SolidLine);
        painter.setPen(pen);
    int m=toadocanh1.size();

    for(int j=0;j<m;j++)
   {
      painter.drawLine(toadocanh1.value(j),toadocanh2.value(j));
      if(mode2==1)
      {

      }
      painter.drawText((toadocanh1.value(j).x()+toadocanh2.value(j).x())/2+5,(toadocanh1.value(j).y()+toadocanh2.value(j).y())/2,QString("%1").arg(mang[j]));
   }
}

void sovle::vemuiten(QPainter &painter) // ve đầu mũi tên
{
    int m=toadocanh1.size();
    int barb =  15;
    int r=20;
    double phi = 3.141592653589793238462643383279502884/6;
    for(int j=0;j<m;j++)
   {
      double theta = atan2(toadocanh2.value(j).y()-toadocanh1.value(j).y(),toadocanh2.value(j).x()-toadocanh1.value(j).x());
      double  xx = toadocanh2.value(j).x() - r *  cos(theta),yy = toadocanh2.value(j).y() - r * sin(theta);
      double x = xx - barb * cos(theta + phi);
      double y = yy - barb * sin(theta + phi);
      painter.drawLine(xx,yy,x,y);
      x = xx - barb * cos(theta - phi);
      y = yy - barb * sin(theta - phi);
      painter.drawLine(xx,yy,x,y);
    }
}

void sovle::xoadothi(QPainter &painter) //Xóa đữ liệu đã lưu
{
    for(int i=0;i<=toadodinh.size();i++)
        mang[i]=0;

    for(int i=0;i<toadodinh.size();i++)
        for(int j=0;j<toadodinh.size();j++)
            dothi[i][j]=-1;

    while(!toadocanh1.isEmpty())
    {
        toadocanh1.pop_back();
    }
    while(!toadocanh2.isEmpty())
    {
        toadocanh2.pop_back();
    }
    while (!toadodinh.isEmpty())
        toadodinh.pop_back();
    mode = 0; mode2 =0; k=0;
    vedothi(painter);
}

void sovle::runall(QPainter &painter)
{
    int n=toadodinh.size();
//Vẽ lại cạnh
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(dothi[i][j]!=0)
            {
                if(checkdinh3(i,j))
                {
                    QPen pen(Qt::red,1,Qt::SolidLine);
                    painter.setPen(pen);
                    painter.drawLine(toadodinh.value(i-1),toadodinh.value(j-1));
                    painter.drawText((toadodinh.value(i-1).x()+toadodinh.value(j-1).x())/2+5,(toadodinh.value(i-1).y()+toadodinh.value(j-1).y())/2,QString("%1").arg(dothi[i][j]));
                }
                else
                {
                    QPen pen(Qt::black,1,Qt::SolidLine);
                    painter.setPen(pen);
                    painter.drawLine(toadodinh.value(i-1),toadodinh.value(j-1));
                    painter.drawText((toadodinh.value(i-1).x()+toadodinh.value(j-1).x())/2+5,(toadodinh.value(i-1).y()+toadodinh.value(j-1).y())/2,QString("%1").arg(dothi[i][j]));
                }
            }
        }
    }
//Vẽ lại đinh
    for(int i=1;i<=n;i++)
        if(checkdinh(i)==true)
        {
            QPen pen(Qt::black,2,Qt::SolidLine);
            painter.setBrush(Qt::red);
            painter.setPen(pen);
            painter.drawEllipse(toadodinh.value(i-1),20,20);
            painter.setPen(Qt::black);
            painter.drawText(toadodinh.value(i-1).x()-5,toadodinh.value(i-1).y()+5,QString("%1").arg(i));
        }
    else
        {
            QPen pen(Qt::black,2,Qt::SolidLine);
            painter.setBrush(QColor(255,248,134));
            painter.setPen(pen);
            painter.drawEllipse(toadodinh.value(i-1),20,20);
            painter.drawText(toadodinh.value(i-1).x()-5,toadodinh.value(i-1).y()+5,QString("%1").arg(i));
        }
   //Vẽ lại mũi tên
    if(mode2 == 1)
    {

        //int m=toadocanh1.size();
        int barb =  15;
        int r=20;
        double phi = 3.141592653589793238462643383279502884/6;
        for(int i=1;i<=n;i++)
           for(int j=1;j<=n;j++ )
               if(dothi[i][j]!=0)
       {
                   if(checkdinh2(i,j))
                   {
                      QPen pen(Qt::red,1,Qt::SolidLine);
                      painter.setPen(pen);
                      double theta = atan2(toadodinh.value(j-1).y()-toadodinh.value(i-1).y(),toadodinh.value(j-1).x()-toadodinh.value(i-1).x());
                      double  xx = toadodinh.value(j-1).x() - r *  cos(theta),yy = toadodinh.value(j-1).y() - r * sin(theta);
                      double x = xx - barb * cos(theta + phi);
                      double y = yy - barb * sin(theta + phi);
                      painter.drawLine(xx,yy,x,y);
                      x = xx - barb * cos(theta - phi);
                      y = yy - barb * sin(theta - phi);
                      painter.drawLine(xx,yy,x,y);
                   }
                   else
                   {

                       QPen pen(Qt::black,1,Qt::SolidLine);
                       painter.setPen(pen);
                       double theta = atan2(toadodinh.value(j-1).y()-toadodinh.value(i-1).y(),toadodinh.value(j-1).x()-toadodinh.value(i-1).x());
                       double  xx = toadodinh.value(j-1).x() - r *  cos(theta),yy = toadodinh.value(j-1).y() - r * sin(theta);
                       double x = xx - barb * cos(theta + phi);
                       double y = yy - barb * sin(theta + phi);
                       painter.drawLine(xx,yy,x,y);
                       x = xx - barb * cos(theta - phi);
                       y = yy - barb * sin(theta - phi);
                       painter.drawLine(xx,yy,x,y);
                   }
        }
    }

}


bool sovle::checkdinh(int x) //Kiểm tra đỉnh có trong đường đi hay không(1)
{
    int check=0,s2=s;
    while(s2!=t)
    {
        if(s2 == x)
            check = 1;
        s2=next[s2][t];
    }
    if(check == 1 || x==t)
        return true;
    else return false;
}

bool sovle::checkdinh2(int u, int v)//Kiểm tra đỉnh có trong đường đi hay không (2)
{
    int check1=-1,check2=-1;
    for(int i=0;i<duongdi.size();i++ )
    {
        if(u==duongdi[i])
            check1=i;
        if(v==duongdi[i])
            check2=i;
    }
    if(check1!=-1 && check2!=-1)
    {
        if(check1-check2 == -1)
            return true;
        return false;
    }
    else
    return false;
}

bool sovle::checkdinh3(int u, int v)//Kiểm tra đỉnh có trong đường đi hay không (2)
{
    int check1=-1,check2=-1;
    for(int i=0;i<duongdi.size();i++ )
    {
        if(u==duongdi[i])
            check1=i;
        if(v==duongdi[i])
            check2=i;
    }
    if(check1!=-1 && check2!=-1)
    {
        if(abs(check1-check2) == 1)
            return true;
        return false;
    }
    else
    return false;
}
int sovle::timdinh(QPoint a)
{
    for(int i=0;i<toadodinh.size();i++)
    {
        if(a == toadodinh.value(i))
            return i+1;
    }
}

void sovle::vedothi(QPainter &painter) //Vẽ đồ thị
{
    vecanh(painter);
    if(mode2 ==1 )
        vemuiten(painter);
    vedinh(painter);
}


