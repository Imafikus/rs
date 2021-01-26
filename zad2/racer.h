#ifndef RACER_H
#define RACER_H

#include <QString>
#include <QVariant>

class racer
{
public:
    racer();
    racer(QString name, unsigned speed);
    QString m_name;
    unsigned m_speed;
    double m_percentage;
    void fromVariant(QVariant variant);

    QString toString();

};

#endif // RACER_H
