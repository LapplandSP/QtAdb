#ifndef ADBPROCESS_H
#define ADBPROCESS_H
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QProcess>
#include "textexplainer.h"
#include <QHBoxLayout>
#include <QMessageBox>
#include <QThread>
#include <QRegularExpression>

#include <QTextEdit>

//#include <windows.h>

class adbProcess : public QProcess
{
    Q_OBJECT
public:
    adbProcess();
    ~adbProcess();

    QString run(QString command);
    QString run(QString command, device dev);
    QString run(QString command, device dev, QString write_command);
    QString run(QString command, QString write_command);
    QString run_contains_empty(QString command, device dev);

    QString standardOutput;
    bool thread = false;

    textExplainer *explainer;
    /*test*/
    QWidget *test;

private slots:
    //void onReadData();
    void on_readerror();

signals:
    void outputGet(QString);
};

#endif // ADBPROCESS_H
