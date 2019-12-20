#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsEllipseItem>
#include <QVBoxLayout>
#include <QDebug>
#include "scanner.h"
#include "parser.h"
#include <QTimer>

using namespace std;

typedef struct ParseTree{
    string type;
    string value;
    vector<  ParseTree* >vec;
    ParseTree(string typeValue="",string val=""){
        type=typeValue;
        value=val;
    };


}ParseTree;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void setRoot(ParseTree * rootNode);
    void startParser();
private:

    Scanner * scanner;
    Parser * parser;
    ParseTree * root;

    QWidget *cw;
    QGraphicsScene *scene;
    QGraphicsView * view;
    QGraphicsLineItem * line;
    QGraphicsRectItem * rect;
    QGraphicsEllipseItem * ell;

    int level=0;
    map <int,int> maxX;        // <level , coordinate>
    void traverse(ParseTree *root,int level);
    void drawEllipse(QRectF rect,QString text);
    void drawRect(QRectF rect,QString text);
    void drawLine(QRectF parent,QRectF Child);
    void drawLine(int x1,int y1,int x2,int y2);
    int drawChildren(ParseTree * parent,int level,int x,int y);
    void createScene();
    void inits();

};
#endif // MAINWINDOW_H
