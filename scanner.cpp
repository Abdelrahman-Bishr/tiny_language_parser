#include "scanner.h"

Scanner::Scanner(QString path)
{

    input=new QTextEdit("ENTER CODE HERE",this);
    comms=new QTextEdit("COMMENTS",this);
    output=new QTextEdit("OUTPUT DISPLAYED HERE",this);
    output->setReadOnly(true);
    comms->setReadOnly(true);
    startBttn= new QPushButton("Parse",this);
    scanProcess=new QProcess();
    verLayout=new QVBoxLayout() ;
    horLayout=new QHBoxLayout ();
    this->setLayout(verLayout);
    verLayout->addWidget(input);
    horLayout->addWidget(output,Qt::AlignTrailing);
    output->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    horLayout->addWidget(comms,Qt::AlignRight);
    verLayout->addLayout(horLayout);
    verLayout->addWidget(startBttn,0,Qt::AlignRight);
    QString p=QDir::currentPath()+"/scanner.py";
    scanProcess->setProgram("python3 "+p);

    this->path=path;



    connect(startBttn,SIGNAL(clicked()),this,SLOT(scan()));
}

void Scanner::scan()
{
    QString inputString=this->input->toPlainText();
    qDebug()<<"=============================================";
    qDebug()<<inputString;
    qDebug()<<"=============================================";

    {
        fstream cout(path.toStdString().c_str());
        QStringList in=inputString.split('\n');
        for(int i=0;i<in.size();i++)
            cout<<in[i].toStdString()<<endl;
    }

    emit start();
}
