#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPainter>
#include <QMainWindow>
#include <bits/stdc++.h>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsEllipseItem>
#include <QVBoxLayout>
#include <QDebug>
#include "scanner.h"

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
    void setRoot(ParseTree * rootNode);
private:
    ParseTree * root;

    QWidget *cw;
    QGraphicsScene *scene;
    QGraphicsView * view;
    QGraphicsLineItem * line;
    QGraphicsRectItem * rect;
    QGraphicsEllipseItem * ell;

    int x=0,y=0,level=0;
    void traverse(ParseTree *root,int level);
    void drawEllipse(QRectF rect,QString text);
    void drawRect(QRectF rect,QString text);
    void drawLine(QRectF parent,QRectF Child);
    void drawLine(int x1,int y1,int x2,int y2);
    void drawChildren(ParseTree * parent,int level,int x,int y);
    Scanner * scanner;
};
#endif // MAINWINDOW_H
