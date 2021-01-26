#include "racer.h"
#include <iostream>

using namespace std;

racer::racer()
{

}

racer::racer(QString name, unsigned speed) : m_name(name), m_speed(speed), m_percentage(0.0)
{}

QString racer::toString() {
    cout << "m_percentage " << m_percentage << endl;

    int percentage = static_cast<int>(m_percentage) / 10;
    cout << "Percentage: " << percentage << endl;
    QString track;

    for(auto i = 0; i < percentage; ++i) {
        track += "#";
    }

    return m_name +": " + track + "\n";
}


void racer::fromVariant(QVariant variant) {
    QVariantMap map = variant.toMap();

    m_name = map.value("name").toString();
    m_speed = map.value("speed").toUInt();
    m_percentage = map.value("percent").toDouble();
}
