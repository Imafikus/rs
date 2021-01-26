#include "racerthread.h"
#include "mainwindow.h"
#include <QMutexLocker>

RacerThread::RacerThread(QObject* parent, int idx) : QThread(parent), m_idx(idx)
{

}

void RacerThread::run() {

    while(true) {
        sleep(1);
        auto window = qobject_cast<MainWindow*>(parent());
        auto& racers = window->m_racers;
        auto& mutex = window->m_mutex;


        QMutexLocker lock(&mutex);
        racers.at(m_idx).m_percentage += racers.at(m_idx).m_speed;
        emit racerUpdated();

        if(racers.at(m_idx).m_percentage > 100) {
            break;
        }
    }
    emit racerFinished(m_idx);
}


