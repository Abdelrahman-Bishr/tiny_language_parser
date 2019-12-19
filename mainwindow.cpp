#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scanner=new Scanner();
    this->setCentralWidget(scanner);
    root=nullptr;
//    this->hide();
    scene=new QGraphicsScene(this);
    view= new QGraphicsView(scene);
    view->show();
    QBrush br(Qt::green);
    scene->setBackgroundBrush(br);
    QPointF p1(0,0);
    QPointF p2(100,100);
    QRectF rec(p1,p2);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setRoot(ParseTree *rootNode)
{
    root=rootNode;
    cout<<"root is "<<root->value;
    drawChildren(root,0,500,500);

}
void MainWindow::traverse(ParseTree * root, int level)
{
    ParseTree * temp=root;
//    drawChildren(root,0,500,500);
    if(temp->vec.size()!=0){
        cout<<"\n";
        for(vector<ParseTree*>::iterator i = temp->vec.begin();i != temp->vec.end();i++){
//            print((*i));

//            QPointF p1(80*x++,80*(y+level));
//            QPointF p2(80*(x++),80*(y+1+level));
//            x+=2;
//            QRectF rect(p1,p2);
//            drawEllipse(rect,QString::fromStdString((*i)->value));
        }
//        cout<<"\n";
        level++;
        for(vector<ParseTree*>::iterator i = temp->vec.begin();i != temp->vec.end();i++){
            traverse((*i),level+3);
        }
    }
    else{
//        print(temp);
//        cout<<(temp->type)<<" :: "<<(temp->value);
//        cout<<"\t";
    }
}

void MainWindow::drawEllipse(QRectF rect, QString text)
{

    QGraphicsTextItem *textitem=new QGraphicsTextItem(text);
    scene->addItem(textitem);
    scene->addEllipse(rect);
    textitem->setPos(rect.center());
    textitem->setPos(textitem->x()-35,textitem->y()-15);
}

void MainWindow::drawRect(QRectF rect, QString text)
{

    QGraphicsTextItem textitem(text);
    textitem.setTextWidth(50);
    scene->addItem(&textitem);
    scene->addRect(rect);
    textitem.setPos(rect.center());
    textitem.adjustSize();
}

void MainWindow::drawLine(QRectF parent, QRectF Child)
{
    QLineF l(parent.center(),Child.center());
    scene->addLine(l);
}

void MainWindow::drawLine(int x1, int y1, int x2, int y2)
{
    scene->addLine(x1,y1+40,x2,y2);
}

void MainWindow::drawChildren(ParseTree *parent, int level,int x,int y)
{
    QPointF p1(x-80, y +    level  * 80);
    QPointF p2(x+80, y + (1+level) * 80);
    QRectF rect(p1,p2);
    cout<<"(parent)->value is "<<(parent)->value<<endl;
    drawEllipse(rect,/*QString::fromStdString((parent)->type)+"\n"+*/QString::fromStdString((parent)->value));
    int childCount=parent->vec.size();
    float id=(float)(childCount/2);
    for(vector<ParseTree*>::iterator i = parent->vec.begin();i != parent->vec.end();i++){
        QPointF p3((x+(400*(0.5+(id)-childCount)))-80,y+level*80);
        QPointF p4((x+(400*(0.5+(id+1)-childCount)))+80,y+80*(1+level));
        QRectF rect2(p3,p4);
//        rect2.setTopRight(p3);
//        drawLine(rect,rect2);
        drawLine(x,y+level*80+40,(x+(400*(0.5+(id)-childCount))),y+(level+2)*80);
        drawChildren((*i),level+2,(x+(400*(0.5+(id++)-childCount))),y);
    }
}
