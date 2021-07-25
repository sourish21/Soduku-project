#ifndef WINDOW_H
#define WINDOW_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <QMouseEvent>
#include <vector>
#include <QList>
#include <map>
#define N 9
#define sq (int)sqrt(N)

using namespace std;



class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);




    int counter=0;
    int d=0;
    int p=0;
    int gridx;
    int gridy;
    int select;
    char inputarr[N][N];
    char myarr[N]={'1','2','3','4','5','6','7','8','9'};
    char duplicate[N][N];
    char solvedarr[N][N];
    QList<QPoint>mousepos;
    QList<char>myval;


private:
    QPoint mPoint;
    QPoint nPoint;
    QPoint tPoint;

};

#endif
