#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    parser=new Parser();
    scanner=new Scanner();
    dummy=new QTimer(this);
    dummy->setSingleShot(true);
    dummy->setInterval(200);
    connect(dummy,SIGNAL(timeout()),parser,SLOT(parse()));
    connect(scanner,SIGNAL(start()),this,SLOT(startParser()));
    connect(parser,SIGNAL(newRoot(ParseTree*)),this,SLOT(setRoot(ParseTree*)));
    this->setCentralWidget(scanner);
    root=nullptr;
//    this->hide();
    view= new QGraphicsView();
    createScene();
    view->show();
    view->setGeometry(50,50,640,480);
    maxX.push_back(500);
    minX.push_back(0);
//    parser->parse();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setRoot(ParseTree *rootNode)
{
    root=rootNode;
    cout<<"root is "<<root->value;
    drawChildren(root,0,500,500);
//    drawChildren(root,0,500);

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
    textitem->setParent(scene);
    scene->addEllipse(rect);
    textitem->setPos(rect.center());
    textitem->setPos(textitem->x()-35,textitem->y()-15);
}

void MainWindow::drawRect(QRectF rect, QString text)
{

    QGraphicsTextItem *textitem=new QGraphicsTextItem(text);
    scene->addItem(textitem);
    textitem->setParent(scene);
    scene->addRect(rect);
    textitem->setPos(rect.center());
    textitem->setPos(textitem->x()-35,textitem->y()-15);
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

//void MainWindow::drawChildren(ParseTree *parent, int level,int x,int y)
//{
//    int childCount=parent->vec.size();
//    QPointF p1(x-80, y +    level  * 80);
//    QPointF p2(x+80, y + (1+level) * 80);
//    QRectF rect(p1,p2);
//    if(parent==nullptr)
//        qDebug()<<"null parent";
//    drawEllipse(rect,/*QString::fromStdString((parent)->type)+"\n"+*/QString::fromStdString((parent)->value));
//    float id=(float)(childCount/2);
//    int newX;
//    for(vector<ParseTree*>::iterator i = parent->vec.begin();i != parent->vec.end();i++){
//        newX=(x+(400*(0.5+(id)-childCount)));
//        drawLine(x,y+level*80+40,newX,y+(level+2)*80);
//        drawChildren((*i),level+2,newX,y);
//        id++;
//    }
//}

int MainWindow::drawChildren(ParseTree *parent, int level,int x,int y)
{
    int childCount=parent->vec.size();
    float id=(float)(childCount/2);
    int newX;
    int val=x;
    int shift=0;
    for(vector<ParseTree*>::iterator i = parent->vec.begin();i != parent->vec.end();i++){
        newX=(x+(400*(0.5+(id)-childCount)));
        if(newX-400<maxX[level+2]){
            shift=400+(maxX[level+2]-newX);
            newX+=shift;
            x+=shift;
            maxX[level]=x-399;
        }
        maxX[level+2]=newX;
        drawLine(x,y+level*80+40,newX,y+(level+2)*80);
        val=drawChildren((*i),level+2,newX,y);
        id++;
    }


    QPointF p1(x-80, y +    level  * 80);
    QPointF p2(x+80, y + (1+level) * 80);
    QRectF rect(p1,p2);
    if(parent==nullptr)
        qDebug()<<"null parent";
    drawEllipse(rect,/*QString::fromStdString((parent)->type)+"\n"+*/QString::fromStdString((parent)->value));
    return shift;
}




//int MainWindow::drawChildren(ParseTree *parent, int level, int x)
//{
//    int childCount=parent->vec.size();
//    x+=400*childCount;
//    QPointF p1(x-80, y +    level  * 80);
//    QPointF p2(x+80, y + (1+level) * 80);
//    QRectF rect(p1,p2);

//}

void MainWindow::createScene()
{
    scene=new QGraphicsScene(this);
    QBrush br(Qt::green);
    scene->setBackgroundBrush(br);
    view->setScene(scene);

}

void MainWindow::startParser()
{
    scene->clear();
    while(scene->items().size()>0){
        scene->removeItem(*(scene->items().begin()));
        delete *(scene->items().begin());
    }
    delete scene;
    view->viewport()->update();
//    dummy->start();
    createScene();
    parser->parse();
}
