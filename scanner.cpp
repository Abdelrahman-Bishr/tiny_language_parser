#include "scanner.h"

Scanner::Scanner()
{

    input=new QTextEdit("ENTER CODE HERE",this);
    comms=new QTextEdit("COMMENTS",this);
    output=new QTextEdit("OUTPUT DISPLAYED HERE",this);
    output->setReadOnly(true);
    comms->setReadOnly(true);
    startBttn= new QPushButton("Parse",this);
    scan=new QProcess();
    verLayout=new QVBoxLayout() ;
    horLayout=new QHBoxLayout ();
    this->setLayout(verLayout);
    verLayout->addWidget(input);
    horLayout->addWidget(output,Qt::AlignTrailing);
    output->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    horLayout->addWidget(comms,Qt::AlignRight);
    verLayout->addLayout(horLayout);
    verLayout->addWidget(startBttn,0,Qt::AlignRight);
    QString path=QDir::currentPath()+"/scanner.py";
//    scan->setProgram("python3 "+path);



    connect(startBttn,SIGNAL(clicked()),this,SIGNAL(start()));
}

void Scanner::parse()
{

}
