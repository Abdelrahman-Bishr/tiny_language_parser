#include "mainwindow.h"
#include <QApplication>


#define all(v)     (v.begin()),(v.end())
typedef long long int ll;

#define lp(i,n)      for(int i=0;i<n;i++)
#define lpi(i,j,n)   for(int i=j;i<n;i++)
#define lpd(i,j,n)   for(int i=j;i>=n;i--)
#define f first
#define s second

vector<string> split(string target,unsigned char c ){
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


int inputcnt;
vector<pair<string,string> >input;

void print_tree(ParseTree * root);

vector< ParseTree* >output;
int errors;


ParseTree* exp() ;
ParseTree* term() ;
ParseTree* factor();

ParseTree* IFcon();

ParseTree* statment();




void print(ParseTree* node){
    if(node== NULL)return;
    if(node->vec.size()){
        print((node->vec[0]));
        cout<<node->value<<" ";
        print((node->vec[1]));
    }
    else  cout<<node->value<<" ";
}


ParseTree* term() {

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

ParseTree* exp(){
    ParseTree* temp= term();
    // inputcnt++;
    while(inputcnt+1 <input.size() && (input[inputcnt+1].first == "+" || input[inputcnt].first == "-")){

        ParseTree* newtemp=new ParseTree("OP",input[++inputcnt].first );
        inputcnt++;
        newtemp->vec.push_back(temp);
        newtemp->vec.push_back(term());
        temp=newtemp;

    }
    return temp;

}
ParseTree* factor(){

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

    return temp;
}
ParseTree* IFcon(){
    ParseTree* res=new ParseTree("IF","if");
    // inputcnt++;
    // if(inputcnt >=input.size() && (input[inputcnt].first !="(")){
    //     errors++;
    //     return NULL;
    // }
    inputcnt++;
    ParseTree* temp= exp();
    if(inputcnt+1 <input.size() && (input[inputcnt+1].first == "<" || input[inputcnt].first == ">"
    || input[inputcnt].first == "=")){
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
    while(inputcnt< input.size() && input[inputcnt].first!="else" && input[inputcnt].first=="end" )
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

    return res;

}
// zz IDENTIFIER
// := ASSIGN
// 9 NUMBER
// * MULT
// 10 NUMBER
ParseTree* statment(){
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

        return res;

    }

    if(input[inputcnt].first=="read"){

        inputcnt++;
        if(inputcnt>=input.size() || input[inputcnt].second!="IDENTIFIER"){
            errors++;
            return NULL;
        }

        ParseTree* res= new ParseTree("READ",input[inputcnt].second);

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
        if(inputcnt+1 <input.size() && (input[inputcnt+1].first == "<" || input[inputcnt].first == ">"
         || input[inputcnt].first == "=")){
                ParseTree* temp2=new ParseTree("OP",input[++inputcnt].first );
                temp2->vec.push_back(temp);
                // res->vec.push_back(temp2);
                inputcnt++;
                temp2->vec.push_back(exp());
                inputcnt++;
                res->vec.push_back(temp2);

            if(inputcnt>=input.size() || input[inputcnt].first!=";")
               errors++;
            else
                inputcnt++;

            return res;
         }

    }
}


void print_tree(ParseTree * root){
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


int main(int argc, char *argv[]){

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    string s,h;

    freopen("parsertest.txt","r",stdin);

    while(getline(cin,s)){

        auto temp=split(s,',');

        input.push_back({split(temp[0],' ')[0],split(temp[1],' ')[0]});
//        cout<<split(temp[0],' ')[0]<<"\t\t"<<split(temp[1],' ')[0]<<endl;

    }

    cout<<"=========================================================\n";
    while(inputcnt<input.size()&& !errors){
        auto tree_node=statment();
        print_tree(tree_node);
//        w.setRoot(tree_node);
//        cout<<(tree_node->type)<<" :: "<<(tree_node->value);

        output.push_back(tree_node);

    }
    if(errors)cout<<"ERROR OCCURED";


    cout<<endl;
    return a.exec();

}
