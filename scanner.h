#ifndef SCANNER_H
#define SCANNER_H
#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QProcess>
#include <QDir>
#include <QDebug>
#include <bits/stdc++.h>

using namespace std;

class Scanner:public QWidget
{
    Q_OBJECT

signals:
    void start();
public:
    Scanner(QString path);
private:
    QTextEdit * input,* comms,*output;
    QPushButton * startBttn;
    QProcess * scanProcess;
    QVBoxLayout * verLayout;
    QHBoxLayout * horLayout;
    QString path;
private slots:
    void scan();
};

#endif // SCANNER_H
