#include "mainwindow.h"

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QFileDialog>
#include <QMessageBox>
#include <QKeyEvent>
#include <QMouseEvent>
//이미지 선, 사각형, 원 그리기
//도형의 선택 및 이동
//이미지 로드하기
//확대, 축소, 이동
//이미지 회전, 대칭이동


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);   //Scene 변수 명
    scene->setBackgroundBrush(QBrush(QColor(Qt::cyan))); //Scene의 배경
    scene->setSceneRect(-300, -300, 600, 600); //(-300, -300) 좌표 부터 (600, 600) 크기 까지 배경 지정

    QPen mPen; //펜의 변수 선언
    mPen.setWidth(5); //펜의 굵기 5
    mPen.setColor(Qt::red); //펜의 색상 붉은색

    /* 선 만들기 */
    lineItem = new QGraphicsLineItem(); //QLineItem 변수 지정(선 만들기)
    lineItem->setLine(0, 0, 200, 200);        //선 의 좌표 설정
    lineItem->setFlag(QGraphicsItem::ItemIsFocusable);  //focus 설정, 고정
    //lineItem->setFlag(QGraphicsItem::ItemIsMovable);    //고정해제
    //lineItem->setFlag(QGraphicsItem::ItemIsSelectable); //선택 레이어 표출
    lineItem->setFocus();       //포커싱
    lineItem->setPen(mPen); //선언된 펜 변수를 lineItem에 적용


    /* 사각형 만들기 */
    rectItem = new QGraphicsRectItem();  //QRectItem 변수지정
    rectItem->setRect(-100, -100, 100, 100);    //사각형 좌표 및 크기 설정
    //rectItem->setFlag(QGraphicsItem::ItemIsFocusable);
    rectItem->setFlag(QGraphicsItem::ItemIsMovable);    //고정해제
    rectItem->setFlag(QGraphicsItem::ItemIsSelectable); //선택 레이어 표출
    //rectItem->setFocus();
    rectItem->setPen(mPen);             //설정된 펜 세팅
    //rectItem->setBrush(QBrush(Qt::green));  //사각형 채우기

    /* 원 만들기 */
    ellipseItem = new QGraphicsEllipseItem(); //QEllipseItem 변수 지정
    ellipseItem->setRect(-150, 0, 150, 150);          //원의 좌표 및 크기 설정
    ellipseItem->setFlag(QGraphicsItem::ItemIsMovable);
    ellipseItem->setFlag(QGraphicsItem::ItemIsSelectable);
    ellipseItem->setPen(mPen);
    ellipseItem->setBrush(QBrush(Qt::green));

    scene->addItem(lineItem);   //lineItem 추가
    scene->addItem(rectItem);   //rectItem 추가
    scene->addItem(ellipseItem);//ellipseItem 추가
    scene->addLine(-250, 0, 250, 0, mPen); // x 좌표 선 추가
    scene->addLine(0, -250, 0, 250); // y 좌표 선 추가

    //ui->loadButton = new QPushButton(this);          /*이미지 버튼 생성*/
    connect(ui->loadButton, &QPushButton::clicked,                 /*람다 함수로 이미지 버튼 클릭시 이벤트 발생*/
            [=]{
        /*현재 이미지르 받은 슬옷은 파일 경로를 받고 클라이언트 채팅창에 이미지로 출력하는 기능을 구현*/
        QString filename = QFileDialog::getOpenFileName(this, "file select",
       /*현 경로는 개발자의 디바이스에서만 연결 가능하오니 다른 디바이스를 사용하는 경우에는 경로를 필히 바꿔주기 바람*/
            "C:\\QtHardWork\\samQtProject-master\\build-Miniproject-Desktop_Qt_6_3_1_MSVC2019_64bit-Debug",
            "image file(*.png *.jpg)");                         /*jpg, png를 부르는 경로 작성*/
        QImage Img;                        /*이미지 변수 생성*/
        QPixmap buffer;                    /*픽스맵 변수 생성*/


        qDebug() << filename;

        if(Img.load(filename)){                             /*해당경로로 포함된 이미지 파일 호출이 가능하면*/
            buffer = QPixmap::fromImage(Img);             /*픽스맵에 Img변수에 이미지 할당*/
            //*buffer = buffer->scaled(200, 200, Qt::KeepAspectRatio);  /*사이즈의 크기를 200 by 200으로 채움*/
        }else{
            QMessageBox::about(0, QString("Image load Error"),      /*만일 이미지를 못 찾을시 메세지박스 호출*/
                               QString("Image load Error"));
        }

        //buffer.scaled(100, 100);
        scene->addPixmap(buffer);
        //ui->graphicsView->setScene(scene);

    });   /*버튼을 클릭시 이미지를 찾는 버튼을 클릭한 시그널*/

    /*이미지의 확대, 축소를 커넥트로 연결*/
    ui->sceneScaleCombo->setCurrentIndex(2); //콤보박스의 위치가 100%에 위치할 수 있도록 지정
    connect(ui->sceneScaleCombo, &QComboBox::currentTextChanged,    //콤보박스의 데이터가 바뀔 때마다
            this, &MainWindow::sceneScaleChanged);  //사용자 지정 슬롯의 값을 변환(sceneScaleChanged

    /*버튼 클릭시 사각형 크기 조절*/
    connect(ui->createButton, &QPushButton::clicked,
            this, &::MainWindow::recreateRect); //버튼을 클릭시 현재 위치한 사각형의 크기 및 위치를 재조정

    ui->graphicsView->setScene(scene); //scene에 add한 속성들 전부 set
}

/*실선의 대칭이동 및 사각형 회전*/
void MainWindow::keyPressEvent(QKeyEvent *e)            //이벤트 핸들러
{
    //키 이벤트를 Qt함수의 key()로 선언
    switch(e->key()){
    case Qt::Key_A:              //키보드 A버튼을 누를 시
        lineItem->moveBy(-move, 0); //x축 -10 만큼 이동
        break;
    case Qt::Key_D:             //키보드 D버튼을 누를 시
        lineItem->moveBy(move, 0);  //x축 10 만큼 이동
        break;
    case Qt::Key_W:              //키보드 W버튼을 누를 시
        lineItem->moveBy(0, -move); //y축 -10 만큼 이동
        break;
    case Qt::Key_S:              //키보드 S버튼을 누를 시
        lineItem->moveBy(0, move);  //y축 10 만큼 이동
        break;
    case Qt::Key_E:             //키보드 R버튼을 누를 시
        rectItem->setRotation(rotate += 10);  //시계방향으로 10도 만큼 이동
        break;
    case Qt::Key_Q:             //키보드 Q버튼을 누를 시
        rectItem->setRotation(rotate -= 10);  //반시게방향으로 10도 만큼 이동
        break;
    }
}

/*이미지 확대, 축소 슬롯*/
void MainWindow::sceneScaleChanged(const QString &scale)
{
    //left : 문자열의 가장 왼쪽에 있는 n개의 문자를 포함하는 하위 문자열을 반환합니다.
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0; //'%'이후의 double형 인자 값과 100.0으로 나누어진 변수 설정
    //QTransform 클래스는 좌표계의 2D 변환을 지정합니다.
    QTransform oldMatrix = ui->graphicsView->transform(); //그래픽스 뷰를 변환(transform) 변수로 지정
    ui->graphicsView->resetTransform(); //보기 변환을 항등 행렬로 재설정합니다.
    //크기가 n x n이고, 대각 성분이 모두 1인 대각행렬을 항등행렬 혹은 단위행렬이라 한다.
    ui->graphicsView->translate(oldMatrix.dx(), oldMatrix.dy());//현재 보기 변환을 그래픽스뷰(dx, dy)로 변환합니다.
    ui->graphicsView->scale(newScale, newScale);    //이미지 비율을 sx, sy로 변환한다.
}

/*사각형의 위치와 크기를 재조정하는 함수*/
void MainWindow::recreateRect()
{
    rectItem->setRect(ui->x1Edit->text().toInt(),
                      ui->y1Edit->text().toInt(),
                      ui->x2Edit->text().toInt(),
                      ui->y2Edit->text().toInt());  //에디트의 값의변화에 따라 위치/크기 조절
    rectItem->setFlag(QGraphicsItem::ItemIsMovable);    //고정해제
    rectItem->setFlag(QGraphicsItem::ItemIsSelectable); //선택 레이어 표출
    //scene->addItem(rectItem);   //rectItem 추가
}


MainWindow::~MainWindow()
{
    delete ui;
    /*동적할당 해제*/
    delete lineItem;
    delete rectItem;
    delete ellipseItem;
    delete scene;
}

