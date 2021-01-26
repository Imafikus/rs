#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "racer.h"
#include <vector>
#include <QMutex>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    vector<racer> m_racers;
    QMutex m_mutex;
    int m_numOfActiveRacers;


private slots:
    void onRacerFinished(int idx);
    void onRacerUpdated();
private:
    Ui::MainWindow *ui;
    void onStartButtonClicked();
    void onRegisterButtonClicked();


};
#endif // MAINWINDOW_H
