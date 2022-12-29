#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "ui_mainwindow.h"

//QGraphicsView 안에 QGraphicsScene를 넣는 개념이라고 생각하면 된다.
class QGraphicsView;            //QGraphicsView는 Layout으로 넣을 수 있지만
class QGraphicsScene;           //QGraphicsScene은 Layout에 넣을 수 없다.

class QGraphicsLineItem;        //Qt에서 제공하는 Line 클래스
class QGraphicsRectItem;        //Qt에서 제공하는 Rect 클래스
class QGraphicsEllipseItem;     //Qt에서 제공하는 Ellipse 클래스

class QFileDialog;              //파일을 로드 할 수 있는 다이얼로그 클래스
class QMessageBox;              //시스템의 상태를 출력할 메세지박스 클래스

class QMouseEvent;              //마우스 핸들러를 갖기 위한 클래스
class QKeyEvent;                //키보드 핸들러를 갖기 위한 클래스


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *);    //키보드 키 이벤트 핸들러 함수



private slots:
    void sceneScaleChanged(const QString &scale);   //이미지 스케일 변환 슬롯
    void recreateRect();            //사각형의 위치와 크기를 재조절하는 슬롯


private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsLineItem *lineItem;
    QGraphicsRectItem *rectItem;
    QGraphicsEllipseItem *ellipseItem;

    qreal move = 10.0;     //x, y방향으로 10만큼 이동시킬 수 있는 변수
    int rotate = 0;            //시계방향으로 회전하는 각도 변수
};
#endif // MAINWINDOW_H
