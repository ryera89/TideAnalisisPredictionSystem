#ifndef HORACOTIDIANADIURNA_H
#define HORACOTIDIANADIURNA_H

#include <QString>

class HarmonicConstant;

class HoraCotidianaDiurna
{
public:
    HoraCotidianaDiurna(const HarmonicConstant &K1, const HarmonicConstant &O1, const double &longitud);

    int hours() const {return m_hours;}
    int minutes() const {return m_minutes;}
private:

    static const QString m_name = "Hora Cotidiana de la Marea Diurna";

    HarmonicConstant m_K1;
    HarmonicConstant m_O1;
    double m_longitud;

    int m_hours;
    int m_minutes;

    void calculate();
};

#endif // HORACOTIDIANADIURNA_H
