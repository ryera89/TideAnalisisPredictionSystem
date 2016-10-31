#ifndef FREQEDITOR_H
#define FREQEDITOR_H

/*Este Widget es para editar las fecuencias angulares de los
componentes de la marea*/


#include <QDialog>
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class EditionTable;
class HarmonicConstantFrequencyTableModel;


class FreqEditor : public QDialog
{
    Q_OBJECT

private:

    enum {MagicNumber = 19891804};  //Numero magico para reconocer si el archivo leido es correcto

    QString m_filePath; //Direccion del archivo donde se guardan las freq de las constantes armonicas

    QPushButton *m_okButton;
    QPushButton *m_cancelButton;

    QPushButton *m_addButton;
    QPushButton *m_removeButton;

    EditionTable *m_frequencyTable;
    HarmonicConstantFrequencyTableModel *m_frequencyModel;

    void createButtons();


public slots:
    //void saveFile();

    bool readFile(const QString &filePath);     //Carga un archivo
    //bool writeFile(const QString &filePath);   //Copia la info de la tabla para el archivo especificado en m_filePath

    void setfilePath(const QString &filePath);

private slots:
    bool insertRow();

signals:
    void filePathChanged(const QString &filePath);
    void acceptButtonClicked();


public:
    FreqEditor(const QString &filePath, QWidget *parent = 0);

    QString filePath() const {return m_filePath;}
    HarmonicConstantFrequencyTableModel* harmonicConstantsModel() const {return m_frequencyModel;}
};

#endif // FREQEDITOR_H
