#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QComboBox>
#include <QMainWindow>
#include <QNetworkReply>
#include <QListView>
#include <QStandardItemModel>

class QWebEngineView;
class QProgressBar;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void openRssFeed();
    void replyFinished(QNetworkReply*);

    //더블클릭 시 진행되는 함수
    void listViewDoubleClicked(const QModelIndex & index);

    void downloadProgress(qint64 bytes, qint64 bytesTotal);

private:
    QComboBox* combo;
    QNetworkAccessManager* manager;
    QNetworkReply* reply;

    QListView* tv;
    QStandardItemModel* model;

    QWebEngineView* wv;
    QProgressBar* progress;
};

class ListView : public QListView{
    Q_OBJECT

protected:
    void keyPressEvent(QKeyEvent* event);
};

#endif // MAINWINDOW_H
