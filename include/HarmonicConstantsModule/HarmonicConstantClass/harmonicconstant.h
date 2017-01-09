#ifndef HARMONICCONSTANT_H
#define HARMONICCONSTANT_H

#include <QString>

class HarmonicConstant
{
public:
    HarmonicConstant();
    HarmonicConstant(const QString &name, const double &frequency, const QString &description);
    HarmonicConstant(const QString &name, const double &frequency, const QString &description, const double &C, const double &S);

    void setDescription(const QString &description){m_description = description;}
    void setName(const QString &name){m_name = name;}
    void setFrequency(const double &frequency){m_frequency = frequency;}
    void setComponentValues(const double &C,const double &S);
    void setAmplitud(const double &amp){m_amplitud = amp;}
    void setPhase(const double &fase){m_phase = fase;}

    QString description()const {return m_description;}
    QString name()const {return m_name;}
    double frequency() const {return m_frequency;}
    double cosComponent()const{return m_C;}
    double senComponent()const{return m_S;}
    double amplitud()const{return m_amplitud;}
    double phase()const {return m_phase;}

private:
    QString m_name;
    double m_frequency;
    QString m_description;

    double m_C;   //componente que se multiplica con los cosenos
    double m_S;   //componente que se multiplica con los senos
    double m_amplitud;
    double m_phase;

};

#endif // HARMONICCONSTANT_H
