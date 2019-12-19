#ifndef SCANNER_H
#define SCANNER_H
#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QProcess>
#include <QDir>

class Scanner:public QWidget
{
    Q_OBJECT
public:
    Scanner();
private:
    QTextEdit * input,* comms,*output;
    QPushButton * startBttn;
    QProcess * scan;
    QVBoxLayout * verLayout;
    QHBoxLayout * horLayout;

    void parse();
};

#endif // SCANNER_H
