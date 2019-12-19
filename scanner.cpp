#include "scanner.h"

Scanner::Scanner()
{

    input=new QTextEdit("ENTER CODE HERE",this);
    comms=new QTextEdit("COMMENTS",this);
    output=new QTextEdit("OUTPUT DISPLAYED HERE",this);
    output->setEnabled(false);
    comms->setEnabled(false);
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
//    scan->setProgram("python3 ")
}

void Scanner::parse()
{

}
