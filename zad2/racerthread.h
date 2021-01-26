#ifndef RACERTHREAD_H
#define RACERTHREAD_H

#include <QThread>
#include <QObject>

class RacerThread : public QThread
{
    Q_OBJECT
public:
    RacerThread(QObject* parent, int idx);
    void run();

signals:
    void racerUpdated();
    void racerFinished(int idx);

private:
    int m_idx;
};

#endif // RACERTHREAD_H
