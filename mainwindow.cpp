#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    parser=new Parser(QDir::currentPath()+"/../parsertest.txt");
    scanner=new Scanner(QDir::currentPath()+"/../parsertest.txt");

    connect(scanner,SIGNAL(start()),this,SLOT(startParser()));
    connect(parser,SIGNAL(newRoot(ParseTree*)),this,SLOT(setRoot(ParseTree*)));
    this->setCentralWidget(scanner);
    root=nullptr;
    view= new QGraphicsView();
    createScene();
    view->show();
    view->setGeometry(50,50,640,480);
    for(int i=0;i<100;i+=2)
        maxX[i]=-100000;
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
    if(temp->vec.size()!=0){
        cout<<"\n";
        for(vector<ParseTree*>::iterator i = temp->vec.begin();i != temp->vec.end();i++){
        }
        level++;
        for(vector<ParseTree*>::iterator i = temp->vec.begin();i != temp->vec.end();i++){
            traverse((*i),level+3);
        }
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

int MainWindow::drawChildren(ParseTree *parent, int level,int x,int y)
{
    int childCount=parent->vec.size();
    float id=(float)(childCount/2);
    int newX;
    int chosenX=0;
    vector <int> childrenX;
    newX=((x)+(400*(0.5+(id)-childCount)));
    int temp;
    //for non terminals , draw their children first
    for(vector<ParseTree*>::iterator i = parent->vec.begin();i != parent->vec.end();i++){
        newX=((x)+(400*(0.5+(id)-childCount)));
        temp=drawChildren((*i),level+2,newX,y);
        chosenX+=temp;
        childrenX.push_back(temp);
        id++;
    }
    id=(float)(childCount/2);
    if(childCount>0)
        x=chosenX/childCount;

    //for non terminals only , draw lines connecting them to their children
    for(vector<int>::iterator i = childrenX.begin();i != childrenX.end();i++){
        drawLine(x,y+level*80+40,(*i),y+(level+2)*80);
    }
    if(x-400<maxX[level]){
        qDebug()<<"level exceeded";
        x=maxX[level]+400;
    }
    maxX[level]=x;

    //draw node itself
    QPointF p1(x-80, y +    level  * 80);
    QPointF p2(x+80, y + (1+level) * 80);
    QRectF rect(p1,p2);
    if(parent==nullptr)
        qDebug()<<"null parent";
    drawEllipse(rect,/*QString::fromStdString((parent)->type)+"\n"+*/QString::fromStdString((parent)->value));
    return x;
}


void MainWindow::createScene()
{
    scene=new QGraphicsScene(this);
    QBrush br(Qt::green);
    scene->setBackgroundBrush(br);
    view->setScene(scene);

}

void MainWindow::inits()
{
    for(int i=0;i<100;i+=2)
        maxX[i]=-100000;
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
    createScene();
    inits();
    parser->parse();
    for(int i=0;i<100;i+=2){
        if(maxX[i]!=-100000)
            qDebug()<<maxX[i];
    }
}
