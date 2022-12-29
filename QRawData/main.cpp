#include "widget.h"

#include <QApplication>
#include <QWidget>
#include <QLineEdit>            //해상도 입력을 위해
#include <QLabel>               //이미지 표시
#include <QPushButton>          //이미지 로드 동작 수행
#include <QBoxLayout>           //위젯들을 배치
#include <QFileDialog>          //이미지 파일 선택
#include <QDir>                 //홈디렉터리
#include <QFile>                //이미지 파일 읽기
#include <QFileInfo>            //이미지 파일 정보 읽기

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);     //QApplication 객체 생성
    Widget w;                       //메인 위젯

    QLineEdit* widthLineEdit = new QLineEdit("256", &w);        //X 해상도 입력
    QLineEdit* heightLineEdit = new QLineEdit("256", &w);       //Y 해상도 입력
    QPushButton* button = new QPushButton("Load", &w);          //버튼 생성
    QLabel* imageLabel = new QLabel(&w);                //이미지 표시를 위한 위젯

    QHBoxLayout* layout = new QHBoxLayout();            //위젯을 배치
    layout->addWidget(widthLineEdit);
    layout->addWidget(heightLineEdit);
    layout->addStretch(1);
    layout->addWidget(button);

    QVBoxLayout* mainLayout = new QVBoxLayout(&w);
    mainLayout->addLayout(layout);
    mainLayout->addWidget(imageLabel);

    QObject::connect(button, &QPushButton::clicked, [&](){          //버튼 클릭시 동작
        QString fileName = QFileDialog::getOpenFileName(0,          //파일명 입력
                            "Open a file", QDir::homePath(),
                            "Image file(*.raw *.pgm *.ppm *.pbm *.bmp *.jpg *.png)");
        if(!fileName.length())return;       //만약 이미지를 불러오지 못하면 리턴



        QFile file(fileName);               //파일 불러오기
        file.open(QFile::ReadOnly);         //파일 열기
        QByteArray byteArray = file.readAll();  //파일 읽어서 QByteArray에 저장
        file.close();                       //다 쓴 파일 닫기

        int width = widthLineEdit->text().toInt();  //문자열을 정수로 변환
        int height = heightLineEdit->text().toInt();

        uchar* data = (uchar*)(byteArray.data());   //QByteArray를 uchar로 변환

        //uchar를 QImage객체로 변환
        QImage image = QImage(data, width, height,
                              QImage::Format_Grayscale8); //해당 이미지를 그레이스케일로 전환
        QFileInfo fileInfo(fileName);

        if(fileInfo.suffix() == "raw")  //raw데이터 파일을 받을 때만
            imageLabel->setPixmap(QPixmap::fromImage(image, Qt::AutoColor)); //raw데이터에 맞는 이미지 형식을 출력
        else
            imageLabel->setPixmap(QPixmap(fileName).scaled(width, height)); //높이와 너비에 맞게 이미지를 출력
        w.setWindowTitle(fileName);
    });

    w.show();
    return a.exec();
}
