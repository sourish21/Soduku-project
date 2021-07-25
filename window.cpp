#include "window.h"
#include<math.h>

#include <QPainter>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>
#include <QString>

#include <map>
#include <vector>

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Window::Window(QWidget *parent) : QWidget(parent)
{
   // set form size
   setFixedSize(450,450);
   setStyleSheet("background-color: white;");

}


void Window::paintEvent(QPaintEvent * e)
{
    QPainter painter(this);
    QPen pen;
    QFont font;
    painter.setFont(font);





    //set grid lines
    int hor = 0;
    for(hor=0; hor<=450; hor++) {
        if((hor%50)==0 && hor!=0 && hor!=450 && (hor%150)!=0){
        painter.setPen(QPen(Qt::red,2));
        painter.drawLine(hor,0,hor,450);

        }

        else if((hor%150)==0){
            painter.setPen(QPen(Qt::black,6));
            painter.drawLine(hor,0,hor,450);
        }

    }



    int vert = 0;
    for(vert=0; vert<450; vert++) {
        if((vert%50)==0 && vert!=0 && vert!=450 && (vert%150)!=0){
        painter.setPen(QPen(Qt::red,2));
        painter.drawLine(0,vert,450,vert);

        }

        else if((vert%150)==0){
            painter.setPen(QPen(Qt::black,5));
            painter.drawLine(0,vert,450,vert);
        }


    }




    ifstream myfile;
    myfile.open("C:/Users/souri/Downloads/programming y1/gui/soduku.txt");

    for(int i=0; i<N; i++) {
        for(int j=0; j < N; j++) {
            myfile >> inputarr[i][j];
            //qDebug()<<inputarr[i][j];

        }
    }
    myfile.close();

    int a=0,b=0;
    QFont f;
    f.setBold(true);
    f.setPointSize(15);
    painter.setFont(f);
    painter.setPen((QPen(Qt::blue,8)));

    for(int i=20; i<=450; i+=50) {
        for(int j=30; j<=450; j+=50) {
            if(inputarr[a][b] == 'X') {

                painter.drawText(j,i,tr(" "));

            }
            else {
            painter.drawText(i,j,QString(inputarr[a][b]));
            }

            a++;
            if(a==N){
                a=0;
                b++;
                break;
            }



        }
        if(b==N)
            break;

    }



    //mouse click
    if(mPoint.isNull()==false){

        if(gridx == (nPoint.x()/50) && gridy == (nPoint.y()/50)){
             p++;
             if(p==N)
                 p=0;

        }
        else{
            p=0;

        }



        if(gridx != (nPoint.x()/50) || gridy != (nPoint.y()/50)){
                myval.push_back(myarr[p]);
        }
        else{
            myval.last()= myarr[p];
        }




        for(int i=0;i<mousepos.size();i++){
            painter.drawText(mousepos.at(i),QString(myval.at(i)));
        }

    }

    //solver
            for(int i =0;i<N;i++){
                for(int j=0; j<N;j++){


                    if(inputarr[j][i] == 'X'){
                        while(d<myval.size()){
                        //qDebug()<<myval.size();
                            if(gridx==j && gridy==i){
                                duplicate[j][i] = myval[d];
                                 d++;
                            }
                            else{
                                duplicate[j][i] = '0';
                                d=0;
                            }

                        }
                    }

                    else{
                        duplicate[j][i] = inputarr[j][i];
                        //qDebug()<<duplicate[j][i];
                    }
                }
            }



           ifstream solvedfile;
            solvedfile.open("C:/Users/souri/Downloads/programming y1/gui/soduku_solved.txt");

            for(int i=0; i<N; i++) {
                for(int j=0; j < N; j++) {
                    solvedfile >> solvedarr[i][j];
                    qDebug()<<solvedarr[i][j]<< " "<<duplicate[i][j];

                }
            }
            qDebug()<<"\n";
            solvedfile.close();


            for(int i=0;i<N;i++){
                for(int j=0;j<N;j++){


                    if(duplicate[i][j]==solvedarr[i][j])
                        counter++;


                }
            }

            if(counter==81){
                qDebug()<<"Solved!";
                exit(1);

            }

            else{
                qDebug()<<"Not solved!";
                //qDebug()<<"New counter"<<(counter-23);
                counter =0;
            }








}

void Window::mouseReleaseEvent(QMouseEvent * event)
{



    // get click position
  qDebug() << "Mouse x " << event->x() << " Mouse y " << event->y();
  qDebug() << "Grid x" << (event->x() / 50) << "Grid y" << (event->y() / 50);
    nPoint = mPoint;

if(event){
     gridx = (event->x() / 50);
     gridy = (event->y() / 50);
       // qDebug()<<gridx<<gridy;
        //qDebug()<<nPoint;


        mPoint = event->pos();

        if(gridx != (nPoint.x()/50) || gridy != (nPoint.y()/50)){
            tPoint.setX((gridx *50) +23);
            tPoint.setY((gridy *50) +28);


            mousepos.push_back(tPoint);

        }
        //qDebug()<<mPoint<<nPoint;
        update();
    }
}








