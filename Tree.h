#pragma once
#include <iostream>
#include <vector>
using namespace std;

struct Nodes {
    string name;
    string data;
    vector<string> paramnames;
    vector<string> params;
    vector<Nodes*> childs;
    Nodes(string mname, string mdata, vector<string> mparamnames, vector<string> mparams)
    {
        name = mname;
        data = mdata;
        paramnames = mparamnames;
        params = mparams;
    }
};


