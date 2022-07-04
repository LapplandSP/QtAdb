#ifndef TEXTEXPLAINER_H
#define TEXTEXPLAINER_H
#include <QString>
#include <QList>
#include <QDebug>
#include <QStringList>
#include <QMessageBox>
#include <QIcon>

struct device
{
    QString addr;
    QString state;
    QString device_product;
    QString model;
    QString device_debug;
    QString transport_id;
};

class textExplainer
{
public:
    textExplainer();

    QList<device> getDevList(QString tmpStr);
    QList<device> getDevList_windows(QString tmpStr);
    QString get_words_after(QString str , QString key);
    QString explain_cpu_output(QString str);

    void showMsgBox(QString title,QString msg);

    bool explainError(QString err);
    bool explainOutput(QString op);
    QMessageBox *msgBox;

private:
    QString setState(QString state);
};

#endif // TEXTEXPLAINER_H
