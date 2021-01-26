#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QString>
#include <QFileDialog>
#include "racer.h"
#include "racerthread.h"
#include <QXmlStreamReader>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pbRegister, &QPushButton::clicked, this, &MainWindow::onRegisterButtonClicked);
    connect(ui->pbStart, &QPushButton::clicked, this, &MainWindow::onStartButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRegisterButtonClicked() {
    m_racers.clear();
    cout << "Register clicked" << endl;
    QString fname = QFileDialog::getOpenFileName(this, "Select xml file", "~", "*.xml");
    cout << fname.toStdString() << endl;

    QFile file(fname);
    if (!file.open(QFile::ReadOnly)) {
       cout << "Read failed";
       return;
    }

    QXmlStreamReader in(&file);

    in.readNextStartElement();
    while(in.readNextStartElement()) {
        QVariantMap map;
        while(in.readNextStartElement()) {
            QString xmlName = in.name().toString();
            QString xmlValue = in.readElementText();
            if(xmlName == "name") {
                map.insert(xmlName, xmlValue);
            }
            if(xmlName == "speed") {
                map.insert(xmlName, xmlValue.toUInt());
            }
            if(xmlName == "percent") {
                map.insert(xmlName, xmlValue.toDouble());
            }
        }
        racer r;
        r.fromVariant(map);
        m_racers.push_back(r);
    }
    onRacerUpdated();

}

void MainWindow::onStartButtonClicked() {
    cout << "Start clicked" << endl;

    ui->pbStart->setEnabled(false);
    ui->pbRegister->setEnabled(false);
    ui->teRacers->setEnabled(false);
    ui->leResult->setEnabled(false);


    m_numOfActiveRacers = m_racers.size() - 1;

    for(auto i = 0; i < m_racers.size(); ++i) {
        auto thread = new RacerThread(this, i);
        connect(thread, &RacerThread::racerUpdated, this, &MainWindow::onRacerUpdated);
        connect(thread, &RacerThread::racerFinished, this, &MainWindow::onRacerFinished);
        connect(thread, &RacerThread::finished, &RacerThread::deleteLater);
        thread->start();
    }

}

void MainWindow::onRacerFinished(int idx) {
    QMutexLocker lock(&m_mutex);
    if(m_numOfActiveRacers == m_racers.size() - 1) {
        ui->leResult->setText(m_racers.at(idx).m_name);
    }
    m_numOfActiveRacers--;

    if(m_numOfActiveRacers == -1) {
        ui->pbStart->setEnabled(true);
        ui->pbRegister->setEnabled(true);
        ui->teRacers->setEnabled(true);
        ui->leResult->setEnabled(true);
    }

}

void MainWindow::onRacerUpdated() {
    QString text;
    QMutexLocker lock(&m_mutex);
    for(auto r : m_racers) {
        text += r.toString();
    }
    ui->teRacers->setText(text);
}

