#include "parser.h"

Parser::Parser()
{

}

void Parser::parse()
{
//    while(output.size()!=0)
//        delete *output.begin();

    output.clear();
    input.clear();
    errors=0;
    string s,h;
    QString path= QDir::currentPath()+"/../parser_gui/parsertest.txt";
    qDebug()<<path;
    {
//        freopen(path.toStdString().c_str(),"r",stdin);
        fstream cin(path.toStdString().c_str());
        while(getline(cin,s)){

            auto temp=split(s,',');

            input.push_back({split(temp[0],' ')[0],split(temp[1],' ')[0]});
//            cout<<"input : "<<split(temp[0],' ')[0]<<"\t\t"<<split(temp[1],' ')[0]<<endl;

        }

        cout<<"=========================================================\n";
        while(inputcnt<input.size()&& !errors){
            qDebug()<<"path";
            auto tree_node=statment();
//            print_tree(tree_node);
            if(errors!=0)
                qDebug()<<"ERRORRROROROR";

            if(tree_node==nullptr)
                return;

//            cout<<"output : "<<(tree_node->type)<<" :: "<<(tree_node->value);
            emit newRoot(tree_node);
            //        w.setRoot(tree_node);

            output.push_back(tree_node);

        }
        cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
        if(errors)qDebug()<<"ERROR OCCURED";

        qDebug()<<"leaving parse";
        cout<<endl;
    }
    inputcnt=0;
//    stdin = fdopen(1, "w"); //reopen: 1 is file descriptor of std output
}

void Parser::print(Parser::ParseTree *node){
    if(node== NULL)return;
    if(node->vec.size()){
        print((node->vec[0]));
        cout<<node->value<<" ";
        print((node->vec[1]));
    }
    else  cout<<node->value<<" ";
}

Parser::ParseTree *Parser::term() {

    ParseTree* temp= factor();
    // inputcnt++;
    while(inputcnt+1 <input.size() && (input[inputcnt+1].first == "*" || input[inputcnt].first == "/")){
        ParseTree* newtemp=new ParseTree("OP",input[++inputcnt].first );
        inputcnt++;
        newtemp->vec.push_back(temp);
        newtemp->vec.push_back(factor());
        temp=newtemp;
    }

    return temp;

}

Parser::ParseTree *Parser::exp(){
    ParseTree* temp= term();
    // inputcnt++;
    while(inputcnt+1 <input.size() && (input[inputcnt+1].first == "+" || input[inputcnt+1].first == "-")){

        ParseTree* newtemp=new ParseTree("OP",input[++inputcnt].first );
        inputcnt++;
        newtemp->vec.push_back(temp);
        newtemp->vec.push_back(term());
        temp=newtemp;

    }
    return temp;

}

Parser::ParseTree *Parser::factor(){

    ParseTree* temp=NULL  ;
    if(input[inputcnt].first == "("){
        inputcnt++;
        temp=exp();
        inputcnt++;
        if(input[inputcnt].first != ")")
            errors++;
    }
    else if(input[inputcnt].second == "NUMBER" || input[inputcnt].second == "IDENTIFIER")
        temp=new ParseTree(input[inputcnt].second,input[inputcnt].first);
    else errors++;

    if(errors)
        qDebug()<<"factor";
    return temp;
}

Parser::ParseTree *Parser::IFcon(){
    ParseTree* res=new ParseTree("IF","if");
    // inputcnt++;
    // if(inputcnt >=input.size() && (input[inputcnt].first !="(")){
    //     errors++;
    //     return NULL;
    // }
    inputcnt++;
    ParseTree* temp= exp();
    if(inputcnt+1 <input.size() && (input[inputcnt+1].first == "<" || input[inputcnt+1].first == ">"
                                    || input[inputcnt+1].first == "=")){
        ParseTree* temp2=new ParseTree("OP",input[++inputcnt].first );
        temp2->vec.push_back(temp);
        // res->vec.push_back(temp2);
        inputcnt++;
        temp2->vec.push_back(exp());
        res->vec.push_back(temp2);
    }
    // inputcnt++;
    // if(inputcnt >=input.size() && (input[inputcnt].first !=")")){
    //     errors++;
    //     return NULL;
    // }
    inputcnt++;
    if(inputcnt>= input.size() || input[inputcnt].first!="then")
        errors++;

    inputcnt++;
    while(inputcnt< input.size() && input[inputcnt].first!="else" && input[inputcnt].first!="end" )
        res->vec.push_back(statment());

    // inputcnt++;

    if(inputcnt>= input.size() ){
        errors++;
        return NULL;
    }

    if(input[inputcnt].first=="else"){
        ParseTree* temp2=new ParseTree("ELSE",input[inputcnt++].first );

        while(inputcnt< input.size()  && input[inputcnt].first!="end" )
            temp2->vec.push_back(statment());

        res->vec.push_back(temp2);
    }

    if (inputcnt>= input.size()  && input[inputcnt].first!="end" )
        errors++;

    inputcnt++;

    if(errors)
        qDebug()<<"IFCON";
    return res;

}

Parser::ParseTree *Parser::statment(){
    //    cout<<input[inputcnt].first<<endl;
    if(input[inputcnt].second=="IDENTIFIER"){
        if(input[inputcnt+1].first==":="){
            ParseTree* res= new ParseTree("OP","=");

            ParseTree* zz= new ParseTree("IDENTIFIER",input[inputcnt++].first);

            res->vec.push_back(zz);
            inputcnt++;
            res->vec.push_back(exp());
            inputcnt++;
            if(inputcnt>=input.size() || input[inputcnt].first!=";")
                errors++;
            else
                inputcnt++;

            return res;

        }
        else errors++;
        return NULL;
    }

    if(input[inputcnt].first=="write"){
        inputcnt++;
        if(inputcnt>=input.size() || input[inputcnt].second!="IDENTIFIER"){
            errors++;
            return NULL;
        }

        ParseTree* res= new ParseTree("WRITE",input[inputcnt].first);
        inputcnt++;
        if(inputcnt>=input.size() || input[inputcnt].first!=";")
            errors++;
        inputcnt++;

        if(errors)
            qDebug()<<"STATEMENT";
        return res;

    }

    if(input[inputcnt].first=="read"){

        inputcnt++;
        if(inputcnt>=input.size() || input[inputcnt].second!="IDENTIFIER"){
            errors++;
            return NULL;
        }

        ParseTree* res= new ParseTree("READ",input[inputcnt].first);

        inputcnt++;
        if(inputcnt>=input.size() || input[inputcnt].first!=";")
            errors++;
        else
            inputcnt++;

        return res;

    }
    if(input[inputcnt].first=="if"){
        return IFcon();
    }

    if(input[inputcnt].first == "repeat"){

        inputcnt++;
        ParseTree* res= new ParseTree("REPEAT","repeat");
        while(inputcnt< input.size() &&  input[inputcnt].first!="until"){
            res->vec.push_back(statment());
        }

        if(inputcnt< input.size() &&  input[inputcnt].first== "until")

            inputcnt++;
        else {
            errors++;
            // return NULL;

        }
        ParseTree* temp= exp();
        if(inputcnt+1 <input.size() && (input[inputcnt+1].first == "<" || input[inputcnt+1].first == ">"
                                        || input[inputcnt+1].first == "=")){
            ParseTree* temp2=new ParseTree("OP",input[++inputcnt].first );
            temp2->vec.push_back(temp);
            // res->vec.push_back(temp2);
            inputcnt++;
            temp2->vec.push_back(exp());
            inputcnt++;
            ParseTree* temp3=new ParseTree("UNTIL","until" );
            temp3->vec.push_back(temp2);
            res->vec.push_back(temp3);

            if(inputcnt>=input.size() || input[inputcnt].first!=";")
                errors++;
            else
                inputcnt++;

            return res;
        }

    }
}

void Parser::print_tree(Parser::ParseTree *root){
    ParseTree * temp=root;
    if(temp->vec.size()!=0){
        //        cout<<"\n";
        for(vector<ParseTree*>::iterator i = temp->vec.begin();i != temp->vec.end();i++){
            //            print((*i));
            //            cout<<"\t";
        }
        //        cout<<"\n";
        for(vector<ParseTree*>::iterator i = temp->vec.begin();i != temp->vec.end();i++){
            //            print_tree((*i));
        }
    }
    else{
        //        print(temp);
        //        cout<<(temp->type)<<" :: "<<(temp->value);
        //        cout<<"\t";
    }
}

vector<string> Parser::split(string target, unsigned char c){
    string d="";
    vector<string>arr;
    for(auto n:target)
    {
        if(n!=c)
            d+=n;
        else if(d!="")
            arr.push_back(d),d="";
    }
    if (d!="")
        arr.push_back(d),d="";
    return arr;
}

Parser::ParseTree::ParseTree(string typeValue, string val){
    type=typeValue;
    value=val;
}
