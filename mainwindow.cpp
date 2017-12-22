#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QMessageBox>
#include <QDialog>
#include <QInputDialog>
#include <QTableView>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QLineEdit>
#include <QTime>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setMouseTracking(true);
    this->setWindowTitle("Ứng dụng mô phỏng giải thuật FLoyd-Warshall");
  // window()->setFont(QFont("",12));
  //  window()->setCursor(Qt::PointingHandCursor);
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

    //if(event->x()<= this->size().width()-width()/3-30 && event->y()<=this->size().height()-height()/7)
    //if(event->x() >50 && event->y() > 40)
 //   ui->lbmouse_current_pos->setText(QString("Mouse move X = %1,Y = %2").arg(event->x()).arg(event->y()));
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int n=ui->khungve->toadodinh.size();
    if(event->x()<= this->size().width()-423 && event->y()<=this->size().height()-410)
    if(event->x() >20 && event->y() > 20)
    {
                                                       // luu toa do dinh************************************************
        if(event->button() == Qt::LeftButton && ui->khungve->mode == 1)
        {
           int x,y,xx,yy;
           x=event->x()-10;
           y=event->y()-20;
           int check=0;
           if(n>0)
           {
            for(int j=0;j<n;j++)
            {
                xx=ui->khungve->toadodinh.value(j).x()-x;
                yy=ui->khungve->toadodinh.value(j).y()-y;
                xx=xx*xx;
                yy=yy*yy;
                if( sqrt(xx+yy) < 40)
                    check=1;
            }
            if(check != 1)
            {
                ui->khungve->toadodinh<<QPoint(x,y);
            }
           }
           else if(n==0)
               ui->khungve->toadodinh<<QPoint(x,y);
           luudothi();
           ui->khungve->repaint();
        }
        else
            if(event->button() == Qt::LeftButton && ui->khungve->mode == 2 && n>=2) // lưu tọa độ của đỉnh 1 của cạnh************************
        {
            int x,y,xx,yy; x=event->x()-10; y=event->y()-20;
             for(int j=0;j<n;j++)
             {
                 xx=ui->khungve->toadodinh.value(j).x()-x;
                 yy=ui->khungve->toadodinh.value(j).y()-y;
                 xx=xx*xx;
                 yy=yy*yy;
                 if( sqrt(xx+yy) <= 22)
                 {
                    ui->khungve->toadocanh1<<ui->khungve->toadodinh.value(j);
                    break;
                 }
             }
        }
     }
}

                                       //lưu  tọa độ đỉnh 2 của cạnh************************************************
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    int n=ui->khungve->toadodinh.size();
    int m=ui->khungve->toadocanh1.size();
    if(event->x()<= this->size().width()-423 && event->y()<=this->size().height()-410)
    if(event->x() >20 && event->y() > 20)
    {
        if(ui->khungve->mode == 2  && n>=2 && m>=1)
        {
            int x,y,xx,yy;
            x=event->x()-10;
            y=event->y()-20;
            int check=0;

             for(int j=0;j<n;j++)
             {
                 xx=ui->khungve->toadodinh.value(j).x()-x;
                 yy=ui->khungve->toadodinh.value(j).y()-y;
                 xx=xx*xx;
                 yy=yy*yy;
                 if( sqrt(xx+yy) <= 22 )
                 {
                   ui->khungve->toadocanh2<<ui->khungve->toadodinh.value(j);
                   check = 1;
                   break;
                 }

             }
             if(check == 0)
                 ui->khungve->toadocanh1.pop_back();
             else
             {
                 int check2=0;                       // kiem tra trung cung*************************************
                 for(int j=0;j<ui->khungve->toadocanh1.size()-1;j++)
                 {
                     if(ui->khungve->toadocanh1.value(j)== ui->khungve->toadocanh1.value(ui->khungve->toadocanh1.size()-1))
                     {
                         if(ui->khungve->toadocanh2.value(j) == ui->khungve->toadocanh2.value(ui->khungve->toadocanh2.size()-1))
                         {
                             ui->khungve->toadocanh1.pop_back();
                             ui->khungve->toadocanh2.pop_back();
                             check2 = 1;
                         }
                     }
                 }
                 if(check2==0)                       // Tao wd nhập trọng số**********************************
                 {
                    bool ok = false;
                    QString TS = QInputDialog::getText(this, " ", "Hãy nhập trọng số!", QLineEdit::Normal, QString(), &ok);
                    if (ok && !TS.isEmpty())
                       {
                            ui->khungve->mang[ui->khungve->toadocanh1.size()-1]= TS.toInt();
                       }
                    luudothi();
                    ui->khungve->repaint();
                 }
             }

        }

    }
}

void MainWindow::delay()                            // delay ************************************************
{
    QTime dieTime= QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::on_vd_released()
{
      QString s;
      s = ui->vd->text();
      if ( s == "Vẽ đỉnh")
      {
         ui->khungve->mode =1;
         ui->vd->setText("Ngưng vẽ");
         ui->vc->setText("Vẽ cạnh");
      }
      else
      {
          ui->khungve->mode = 0;
          ui->vd->setText("Vẽ đỉnh");
      }

}

void MainWindow::on_pushButton_clicked()
{

    ui->khungve->mode = 0;
}

void MainWindow::on_vc_clicked()
{
    QString s;
    s = ui->vc->text();
    if ( s == "Vẽ cạnh")
    {
       ui->khungve->mode =2;
       ui->vc->setText("Ngưng vẽ");
       ui->vd->setText("Vẽ đỉnh");
    }
    else
    {
        ui->khungve->mode = 0;
        ui->vc->setText("Vẽ cạnh");
    }
   // ui->khungve->mode = 2;
}


void MainWindow::on_xoa_clicked()                      //xoa************************************************
{
    ui->khungve->mode2 = 2;
    ui->khungve->repaint();
   // ui->khungve->mode2=0;
 //   ui->khungve->mode= 0;
}

int MainWindow::timdinh(QPoint a)
{
    for(int i=0;i<ui->khungve->toadodinh.size();i++)
    {
        if(a == ui->khungve->toadodinh.value(i))
            return i+1;
    }
}

void MainWindow::luudothi()                            //luu đồ thị************************************************
{
    int n= ui->khungve->toadodinh.size();
    for(int i =0 ;i<=n;i++)
        for(int j=0;j<=n;j++)
            ui->khungve->dothi[i][j]=0;
    for(int i=0;i<ui->khungve->toadocanh1.size();i++)
    {
      ui->khungve->dothi[timdinh(ui->khungve->toadocanh1.value(i))][timdinh(ui->khungve->toadocanh2.value(i))] = ui->khungve->mang[i];
      if(ui->khungve->mode2 == 0)
         ui->khungve->dothi[timdinh(ui->khungve->toadocanh2.value(i))][timdinh(ui->khungve->toadocanh1.value(i))] = ui->khungve->mang[i];
    }
}

void MainWindow::floyd()                             // FLoyd************************************************
{
    int inf=9999999;
    int u,v,n=ui->khungve->toadodinh.size(),k;
    for(u=1;u<=n;u++)
        for(v=1;v<=n;v++)
        {
            ui->khungve->pi[u][v]=inf;
            ui->khungve->next[u][v]=-1;
        }

    for(u=1;u<=n;u++)
        ui->khungve->pi[u][u]=0;

    for(u=1;u<=n;u++)
            for(v=1;v<=n;v++)
        {
            if(ui->khungve->dothi[u][v] != 0)
            {
              ui->khungve->pi[u][v] = ui->khungve->dothi[u][v];
                ui->khungve->next[u][v]=v;
            }
        }

    for(k=1;k<=n;k++)
            for(u=1;u<=n;u++)
                for(v=1;v<=n;v++)
                    if(ui->khungve->pi[u][k]+ui->khungve->pi[k][v] < ui->khungve->pi[u][v])
                    {
                        ui->khungve->pi[u][v]=ui->khungve->pi[u][k]+ui->khungve->pi[k][v];
                        ui->khungve->next[u][v]=ui->khungve->next[u][k];
                    }
}

void MainWindow::floyd2()                         //Floy Run step************************************************
{
        int inf=9999999;
        int u,v,n=ui->khungve->toadodinh.size(),k;
        for(u=1;u<=n;u++)
            for(v=1;v<=n;v++)
            {
                ui->khungve->pi[u][v]=inf;
                ui->khungve->next[u][v]=-1;
            }

        for(u=1;u<=n;u++)
            ui->khungve->pi[u][u]=0;

        for(u=1;u<=n;u++)
                for(v=1;v<=n;v++)
            {
                if(ui->khungve->dothi[u][v] != 0)
                {
                  ui->khungve->pi[u][v] = ui->khungve->dothi[u][v];
                    ui->khungve->next[u][v]=v;
                }
            }

            for(k=1;k<=n;k++)
                    for(u=1;u<=n;u++)
                        for(v=1;v<=n;v++)
                        {
                            inmtkhoancach(u-1,v-1,k-1);
                            inmtduongdi();
                            ui->kuv->setText(QString("K = %1 U = %2  V= %3 ").arg(k).arg(u).arg(v));
                            int x=ui->khungve->pi[u][k],y=ui->khungve->pi[k][v],z=ui->khungve->pi[u][v];
                            if(ui->khungve->pi[u][k]+ui->khungve->pi[k][v] < ui->khungve->pi[u][v])
                            {

                                if(x!=inf && y!=inf && z!=inf)
                                {
                                     ui->dk->setText(QString(" %1 + %2 <  %3 ").arg(ui->khungve->pi[u][k]).arg(ui->khungve->pi[k][v]).arg(ui->khungve->pi[u][v]));
                                }
                                else if(x!=inf && y!=inf && z==inf)
                                {
                                    ui->dk->setText(QString(" %1 + %2 <  oo ").arg(ui->khungve->pi[u][k]).arg(ui->khungve->pi[k][v]));
                                }

                                ui->khungve->pi[u][v]=ui->khungve->pi[u][k]+ui->khungve->pi[k][v];
                                ui->khungve->next[u][v]=ui->khungve->next[u][k];
                            }
                            else
                            {
                                if(x!=inf && y!=inf && z!=inf)
                                {
                                     ui->dk->setText(QString("!( %1 + %2 <  %3 )").arg(ui->khungve->pi[u][k]).arg(ui->khungve->pi[k][v]).arg(ui->khungve->pi[u][v]));
                                }
                                else if(x==inf && y==inf && z==inf)
                                {
                                    ui->dk->setText(QString("!( oo + oo < oo )"));
                                }
                                else if(x!=inf && y==inf && z==inf)
                                {
                                    ui->dk->setText(QString("!( %1 + oo <  oo )").arg(ui->khungve->pi[u][k]));
                                }
                                else if(x!=inf && y==inf && z!=inf)
                                {
                                    ui->dk->setText(QString("!( %1 + oo <  %2 )").arg(ui->khungve->pi[u][k]).arg(ui->khungve->pi[u][v]));
                                }
                                else if(x==inf && y!=inf && z==inf)
                                {
                                    ui->dk->setText(QString("!( oo + %1 <  oo )").arg(ui->khungve->pi[k][v]));
                                }
                                else if(x==inf && y!=inf && z!=inf)
                                {
                                    ui->dk->setText(QString("!( oo + %2 <  %3 )").arg(ui->khungve->pi[k][v]).arg(ui->khungve->pi[u][v]));
                                }
                            }
                             delay();
                        }
            ui->kuv->setText("K =  U =  V =  ");
            ui->dk->setText("Điều kiện");
}

void MainWindow::on_matran_clicked()                  // In ma tran trong so ******************************
{
    luudothi();
    int n= ui->khungve->toadodinh.size();
    ui->inmatran->setRowCount(n);
    ui->inmatran->setColumnCount(n);

    for(int i=0;i<ui->inmatran->rowCount();i++)
    {
        for(int j=0;j<ui->inmatran->columnCount();j++)
        {
             ui->inmatran->setColumnWidth(j,30);
             ui->inmatran->setRowHeight(i,30);
             QTableWidgetItem *itm = new QTableWidgetItem(tr("%1").arg(ui->khungve->dothi[i+1][j+1]));
             ui->inmatran->setItem(i,j,itm);
        }
    }
}

void MainWindow::nhapst()
{
    ui->khungve->s = ui->nhaps->text().toInt();
    ui->khungve->t = ui->nhapt->text().toInt();
}

void MainWindow::induongdi()                        // In đường đi********************************************
{
    QString ss;
    int inf=9999999;
    nhapst();
    int s = ui->khungve->s,t= ui->khungve->t;
    if(ui->khungve->pi[s][t]==inf)
    {
        ui->induongdi->setText(QString("Không có đường đi %1 đến %2").arg(s).arg(t));
        ss="";
        ui->induongdi2->setText(ss);
    }
    else
    {
        ui->khungve->mode  = 3;
        ui->induongdi->setText(QString("Khoản cách từ %1 đến %2 = %3").arg(s).arg(t).arg(ui->khungve->pi[s][t]));
        ss+=QString("%1").arg(s);
        ui->khungve->duongdi.push_back(s);
        while(s!=t)
        {
            ui->khungve->duongdi.push_back(ui->khungve->next[s][t]);
            ss+=QString("->%1").arg(ui->khungve->next[s][t]);
            s=ui->khungve->next[s][t];
        }
       ui->induongdi2->setText(ss);
       ui->khungve->repaint();
    }
}



void MainWindow::on_runall_clicked()
{
    ui->vd->setText("Vẽ đỉnh");
    ui->vc->setText("Vẽ cạnh");
    luudothi();
    floyd();
    ms=0;
    int inf=9999999;
                                               //in mt khoan cach runall ****************************************
    int n= ui->khungve->toadodinh.size();
    ui->mttrongso->setRowCount(n);
    ui->mttrongso->setColumnCount(n);

    for(int i=0;i<ui->mttrongso->rowCount();i++)
    {
        for(int j=0;j<ui->mttrongso->columnCount();j++)
        {
             ui->mttrongso->setColumnWidth(j,30);
             ui->mttrongso->setRowHeight(i,30);
             if(ui->khungve->pi[i+1][j+1]==inf)
             {
                  QTableWidgetItem *itm = new QTableWidgetItem(tr("oo"));
                  ui->mttrongso->setItem(i,j,itm);
             }
             else
             {
              QTableWidgetItem *itm = new QTableWidgetItem(tr("%1").arg(ui->khungve->pi[i+1][j+1]));
              ui->mttrongso->setItem(i,j,itm);
             }
        }
    }
    inmtduongdi();
    induongdi();

}

void MainWindow::on_runstep_clicked()                        //Run Step************************************************
{
    ui->vd->setText("Vẽ đỉnh");
    ui->vc->setText("Vẽ cạnh");
    QString ss;
    ui->khungve->mode =4;
    ui->khungve->repaint();
    ui->induongdi->setText(QString("PATH:"));
    ss="";
    ui->induongdi2->setText(ss);

    luudothi();
    floyd2();
    induongdi();
}

void MainWindow::inmtkhoancach(int u, int v, int k)             //in ma tran khoản cách runstep******************************
{
    int inf=9999999;
    int n= ui->khungve->toadodinh.size();
    ui->mttrongso->setRowCount(n);
    ui->mttrongso->setColumnCount(n);

    for(int i=0;i<ui->mttrongso->rowCount();i++)
    {
        for(int j=0;j<ui->mttrongso->columnCount();j++)
        {

             ui->mttrongso->setColumnWidth(j,30);
             ui->mttrongso->setRowHeight(i,30);
            if(ui->khungve->pi[i+1][j+1]==inf)
            {
                 QTableWidgetItem *itm = new QTableWidgetItem(tr("oo"));
                 ui->mttrongso->setItem(i,j,itm);
                 ui->mttrongso->item(u,k)->setBackground(Qt::red);
                 ui->mttrongso->item(k,v)->setBackground(Qt::red);
                 ui->mttrongso->item(u,v)->setBackground(Qt::red);
            }
            else
            {
             QTableWidgetItem *itm = new QTableWidgetItem(tr("%1").arg(ui->khungve->pi[i+1][j+1]));
             ui->mttrongso->setItem(i,j,itm);
             ui->mttrongso->item(u,k)->setBackground(Qt::red);
             ui->mttrongso->item(k,v)->setBackground(Qt::red);
             ui->mttrongso->item(u,v)->setBackground(Qt::red);
                }
        }
    }
}

void MainWindow::inmtduongdi()                          //In ma trận đường đi ******************************************
{
    int n= ui->khungve->toadodinh.size();
    ui->mtduongdi->setRowCount(n);
    ui->mtduongdi->setColumnCount(n);

    for(int i=0;i<ui->mtduongdi->rowCount();i++)
    {
        for(int j=0;j<ui->mtduongdi->columnCount();j++)
        {
             ui->mtduongdi->setColumnWidth(j,30);
             ui->mtduongdi->setRowHeight(i,30);
             QTableWidgetItem *itm = new QTableWidgetItem(tr("%1").arg(ui->khungve->next[i+1][j+1]));
             ui->mtduongdi->setItem(i,j,itm);
        }
    }
}

void MainWindow::on_horizontalSlider_valueChanged(int value)// Tóc độ
{
    ms = 2001-value;
}


void MainWindow::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
        ui->khungve->mode2 = 1;
        ui->khungve->mode =2;
        ui->vd->setText("Vẽ đỉnh");
        ui->vc->setText("Vẽ cạnh");
        ui->khungve->repaint();
        ui->khungve->mode = 0;
    }
    else
    {
        ui->khungve->mode2 = 0;
        ui->khungve->mode = 2;
        ui->vd->setText("Vẽ đỉnh");
        ui->vc->setText("Vẽ cạnh");
        ui->khungve->repaint();
        ui->khungve->mode = 0;
    }
}
