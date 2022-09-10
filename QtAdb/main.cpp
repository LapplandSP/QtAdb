#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QCoreApplication>
#include <QStringList>
#include <QFontDatabase>
#include <QFont>
#include <QSplashScreen>
#include <QThread>
#include <Windows.h>

int main(int argc, char *argv[])
{
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));

    QApplication a(argc, argv);

    QFont font;
    int index = QFontDatabase::addApplicationFont(":/fonts/fonts/MiSans-Normal.ttf");
    if (index != -1)
    {
        QStringList fontList(QFontDatabase::applicationFontFamilies(index));
        if (fontList.count() > 0)
        {
            font.setFamily(fontList.at(0));
            font.setBold(false);
        }
    }
    a.setFont(font);
    a.setStyleSheet("QToolTip{border:1px solid #BDBDBD; background-color: #ffffff; color:rgba(117, 117, 117, 0.9);font-family: MiSans Medium; font-size:12px;border-radius:4px;}");

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "QtAdb_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    QPixmap pix(":/ico/image/ico/logo.svg");
    QSplashScreen splash(pix);
    splash.setBaseSize(100,100);
    splash.setMaximumSize(100,100);
    splash.show();
    //Sleep(5000);
    a.processEvents();


    MainWindow w;
    w.show();

    splash.finish(&w);

    return a.exec();
}
