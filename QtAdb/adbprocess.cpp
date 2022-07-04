#include "adbprocess.h"

adbProcess::adbProcess()
{
    explainer = new textExplainer;
    connect(this , SIGNAL(readyReadStandardError()) , this , SLOT(on_readerror()));
}

QString adbProcess::run(QString command)                   //Adb 命令解析 - 单条命令
{
    QStringList args_0;
    QStringList args_1;

    args_0 = command.split(" ");
    args_0.append("*");

    QString shell_command;
    for(int i = 0, tag = 1; args_0[i] != "*" ; i++)
    {
        if(args_0[i] != "'" && tag == 1)
        {
            args_1.append(args_0[i]);
            //qDebug() << "append0" << shell_command;
        }
        /*
        if(tag == 0)
        {
            //qDebug() << "No." << i << ":" << "args_0[" << i << "] is:" << args_0[i] << "\n" << "tag = " << tag << "\n";
            shell_command = shell_command + args_0[i] + " ";
            //q.enqueue(args_0[i]);
            //qDebug() << shell_command;
        }*/

        if(args_0[i] == "'" && tag == 0)
        {
            //qDebug() << "No." << i << ":" << "args_0[" << i << "] is:" << args_0[i] << "\n" << "tag = " << tag << "\n";
            shell_command.remove(QRegularExpression("\\s* +$"));
            args_1.append(shell_command);
            tag = 1;
            shell_command.clear();
        }
        if(args_0[i] == "'" && tag == 0)
        {
            //qDebug() << "No." << i << ":" << "args_0[" << i << "] is:" << args_0[i] << "\n" << "tag = " << tag << "\n";
            args_1.append(shell_command);
            tag = 1;
        }

        if(args_0[i] == "'" && tag == 1)
        {
            //qDebug() << "No." << i << ":" << "args_0[" << i << "] is:" << args_0[i] << "\n" << "tag = " << tag << "\n";
            tag = 0;
            shell_command = shell_command + args_0[i] + " ";
            //qDebug() << q << "\n";
        }

    }
    args_1.removeAt(0);
    qDebug()  << "'run' running with arguments" << args_1 ;
    this->start("adb", args_1);

    //qDebug() << readAllStandardOutput();
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    waitForReadyRead();
    waitForFinished();

    QString output;
    output = readAllStandardOutput();
    standardOutput.append(output);
    explainer->explainOutput(output);
    return output;
}

QString adbProcess::run(QString command, device dev)                   //Adb 命令解析 - 对指定设备发送单条命令
{
    QStringList args_0;
    QStringList args_1;

    args_1.append("-s");
    args_1.append(dev.addr);

    //qDebug()  << "'run' running with arguments" << args_1 ;

    args_0 = command.split(" ");
    args_0.append("*");

    QString shell_command;
    for(int i = 0, tag = 1; args_0[i] != "*" ; i++)
    {
        if(args_0[i] != "'" && tag == 1)
        {
            args_1.append(args_0[i]);
            //qDebug() << "append0" << shell_command;
        }
        /*
        if(tag == 0)
        {
            //qDebug() << "No." << i << ":" << "args_0[" << i << "] is:" << args_0[i] << "\n" << "tag = " << tag << "\n";
            shell_command = shell_command + args_0[i] + " ";
            //q.enqueue(args_0[i]);
            //qDebug() << shell_command;
        }*/
        if(args_0[i] == "'" && tag == 0)
        {
            //qDebug() << "No." << i << ":" << "args_0[" << i << "] is:" << args_0[i] << "\n" << "tag = " << tag << "\n";
            shell_command.remove(QRegularExpression("\\s* +$"));
            args_1.append(shell_command);
            tag = 1;
            shell_command.clear();
        }
        if(args_0[i] == "'" && tag == 0)
        {
            //qDebug() << "No." << i << ":" << "args_0[" << i << "] is:" << args_0[i] << "\n" << "tag = " << tag << "\n";
            args_1.append(shell_command);
            tag = 1;
        }

        if(args_0[i] == "'" && tag == 1)
        {
            //qDebug() << "No." << i << ":" << "args_0[" << i << "] is:" << args_0[i] << "\n" << "tag = " << tag << "\n";
            tag = 0;
            shell_command = shell_command + args_0[i] + " ";
            //qDebug() << q << "\n";
        }
    }

    args_1.removeAt(2);

    qDebug()  << "'run' running with arguments" << args_1 ;
    //qDebug()  << "calling this->start('adb', args_1);";
    this->start("adb", args_1);
    //qDebug()  << "this->start('adb', args_1); ended";
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    waitForReadyRead();
    waitForFinished();

    QString output;
    output = readAllStandardOutput();
    //qDebug() << "run output:" << output << "\n";
    explainer->explainOutput(output);
    return output;
}

QString adbProcess::run_contains_empty(QString command, device dev)                   //Adb 命令解析 - 对指定设备发送单条命令（可能包含空格）
{
    QStringList args_0;
    QStringList args_1;

    args_1.append("-s");
    args_1.append(dev.addr);

    //qDebug()  << "'run' running with arguments" << args_1 ;

    args_0 = command.split(" ");
    args_0.append("*");

    QString shell_command;
    for(int i = 0, tag = 1; args_0[i] != "*" ; i++)
    {
        if(args_0[i] != "~" && tag == 1)
        {
            args_1.append(args_0[i]);
            //qDebug() << "常规添加" << shell_command << "\n";
        }

        if(args_0[i] != "~" &&tag == 0)
        {
            //qDebug() << "No." << i << ":" << "args_0[" << i << "] is:" << args_0[i] << "\n" << "tag = " << tag << "\n";
            shell_command = shell_command + args_0[i] + " ";
            //qDebug() << "里面添加" << shell_command << "\n";
            //q.enqueue(args_0[i]);
            //qDebug() << shell_command;
        }

        if(args_0[i] == "~" && tag == 0)
        {
            //qDebug() << "No." << i << ":" << "args_0[" << i << "] is:" << args_0[i] << "\n" << "tag = " << tag << "\n";
            shell_command.remove(QRegularExpression("\\s* +$"));
            args_1.append(shell_command);
            tag = 1;
            shell_command.clear();
        }

        if(args_0[i] == "~" && tag == 1)
        {
            //qDebug() << "No." << i << ":" << "args_0[" << i << "] is:" << args_0[i] << "\n" << "tag = " << tag << "\n";
            tag = 0;
            //shell_command = shell_command + args_0[i] + " ";
            //qDebug() << q << "\n";
        }
    }

    args_1.removeAt(2);

    qDebug()  << "'run' running with arguments" << args_1 ;
    this->start("adb", args_1);
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    waitForReadyRead();
    waitForFinished();

    QString output;
    output = readAllStandardOutput();
    //qDebug() << "run output:" << output << "\n";
    explainer->explainOutput(output);
    return output;
}

QString adbProcess::run(QString command, QString write_command)                   //Adb 命令解析 - 发送单条命令并向控制台输入内容
{
    QStringList args_0;
    QStringList args_1;

    args_0 = command.split(" ");
    args_0.append("*");

    QString shell_command;
    for(int i = 0, tag = 1; args_0[i] != "*" ; i++)
    {
        if(args_0[i] != "'" && tag == 1)
        {
            args_1.append(args_0[i]);
            //qDebug() << "append0" << shell_command;
        }
        /*
        if(tag == 0)
        {
            //qDebug() << "No." << i << ":" << "args_0[" << i << "] is:" << args_0[i] << "\n" << "tag = " << tag << "\n";
            shell_command = shell_command + args_0[i] + " ";
            //q.enqueue(args_0[i]);
            //qDebug() << shell_command;
        }*/
        if(args_0[i] == "'" && tag == 0)
        {
            //qDebug() << "No." << i << ":" << "args_0[" << i << "] is:" << args_0[i] << "\n" << "tag = " << tag << "\n";
            shell_command.remove(QRegularExpression("\\s* +$"));
            args_1.append(shell_command);
            tag = 1;
            shell_command.clear();
        }

        if(args_0[i] == "'" && tag == 0)
        {
            //qDebug() << "No." << i << ":" << "args_0[" << i << "] is:" << args_0[i] << "\n" << "tag = " << tag << "\n";
            args_1.append(shell_command);
            tag = 1;
        }

        if(args_0[i] == "'" && tag == 1)
        {
            //qDebug() << "No." << i << ":" << "args_0[" << i << "] is:" << args_0[i] << "\n" << "tag = " << tag << "\n";
            tag = 0;
            shell_command = shell_command + args_0[i] + " ";
            //qDebug() << q << "\n";
        }

    }
    args_1.removeAt(0);
    qDebug()  << "'run' running with arguments" << args_1 ;
    this->start("adb", args_1);

    //qDebug() << "write 0";
    //qDebug() << "write 1";
    this->write(write_command.toLocal8Bit());
    //qDebug() << "write 2";
    waitForReadyRead();
    //qDebug() << "write 3";
    waitForFinished();
    //qDebug() << "write 4";

    QString output;
    output = readAllStandardOutput();
    standardOutput.append(output);

    //qDebug() << "output:" << output;

    explainer->explainOutput(output);
    return output;
}

QString adbProcess::run(QString command, device dev, QString write_command)                   //Adb 命令解析 - 对指定设备发送单条命令并向控制台输入内容
{
    QStringList args_0;
    QStringList args_1;

    args_1.append("-s");
    args_1.append(dev.addr);

    //qDebug()  << "'run' running with arguments" << args_1 ;

    args_0 = command.split(" ");
    args_0.append("*");

    QString shell_command;
    for(int i = 0, tag = 1; args_0[i] != "*" ; i++)
    {
        if(args_0[i] != "'" && tag == 1)
        {
            args_1.append(args_0[i]);
            //qDebug() << "append0" << shell_command;
        }

        /*
        if(tag == 0)
        {
            qDebug() << "No." << i << ":" << "args_0[" << i << "] is:" << args_0[i] << "\n" << "tag = " << tag << "\n";
            shell_command = shell_command + args_0[i] + " ";
            //q.enqueue(args_0[i]);
            qDebug() << shell_command;
        }*/

        if(args_0[i] == "'" && tag == 0)
        {
            //qDebug() << "No." << i << ":" << "args_0[" << i << "] is:" << args_0[i] << "\n" << "tag = " << tag << "\n";
            shell_command.remove(QRegularExpression("\\s* +$"));
            args_1.append(shell_command);
            tag = 1;
            shell_command.clear();
        }

        if(args_0[i] == "'" && tag == 0)
        {
            //qDebug() << "！！！！！！！！！！！！！！！！！！！！！No." << i << ":" << "args_0[" << i << "] is:" << args_0[i] << "\n" << "tag = " << tag << "\n";
            args_1.append(shell_command);
            tag = 1;
        }

        if(args_0[i] == "'" && tag == 1)
        {
            //qDebug() << "No." << i << ":" << "args_0[" << i << "] is:" << args_0[i] << "\n" << "tag = " << tag << "\n";
            tag = 0;
            shell_command = shell_command + args_0[i] + " ";
        }
    }

    args_1.removeAt(2);

    qDebug()  << "'run' running with arguments" << args_1 ;
    this->start("adb", args_1);
    this->write(write_command.toLocal8Bit());
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    waitForReadyRead();
    waitForFinished();

    QString output;
    output = readAllStandardOutput();
    //qDebug() << "run output:" << output << "\n";

    explainer->explainOutput(output);
    return output;
}

adbProcess::~adbProcess()
{
    run("adb kill-server");
    terminate();
    waitForFinished();
}

void adbProcess::on_readerror()
{
    QString text = this->readAllStandardError().data();
    explainer->explainError(text);
    //if(text.contains(""))
    //QMessageBox::information(0, "Error", this->readAllStandardError().data());
}
