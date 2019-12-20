#ifndef PARSER_H
#define PARSER_H

#include <QDebug>
#include <bits/stdc++.h>
#include <QObject>
#include <QDir>
using namespace std;

#define all(v)     (v.begin()),(v.end())
typedef long long int ll;

#define lp(i,n)      for(int i=0;i<n;i++)
#define lpi(i,j,n)   for(int i=j;i<n;i++)
#define lpd(i,j,n)   for(int i=j;i>=n;i--)
#define f first
#define s second










class Parser : public QObject
{
    Q_OBJECT

public:
    typedef struct ParseTree{
        string type;
        string value;
        vector<  ParseTree* >vec;
        ParseTree(string typeValue="",string val="");


    }ParseTree;


    Parser();
public slots:
    void parse();
signals:
    void newRoot(ParseTree * root);
private:
    void print(ParseTree* node);
    void print_tree(ParseTree * root);

    ParseTree* term();
    ParseTree* exp();
    ParseTree* factor();
    ParseTree * IFcon();
    ParseTree* statment();



    vector< ParseTree* >output;
    int errors;
    vector<string> split(string target,unsigned char c );

    int inputcnt=0;
    vector<pair<string,string> >input;
};

#endif // PARSER_H
