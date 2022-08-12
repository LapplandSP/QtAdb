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
    bool explainOutput(QString op, bool thread);

    QMessageBox *msgBox;
    bool thread = false;

    QStringList explainPermissionGroups(QString s);

private:
    QString setState(QString state);

signals:
    void textExplained(QString);
    void permissionGroupsExplained(QStringList);

public slots:
    void slot_get_words_after(QString s, QString k);
    void slot_explain_cpu_output(QString s);
};

#endif // TEXTEXPLAINER_H
