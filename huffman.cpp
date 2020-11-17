#include<iostream>
#include<fstream>
#include<map>
#include<string>
#include<vector>
#include <bits/stdc++.h> 
using namespace std;


bool compare(pair<int,vector<pair<char,string>>>& a,
                    pair<int,vector<pair<char,string>>>& b)
{
    return a.first < b.first;
}

vector<pair<int,vector<pair<char,string>>>> build_list(map<char,int>& fmap)
{
    vector<pair<int,vector<pair<char,string>>>> ls;
    for(auto& i : fmap){
        pair<char,string> code_pair = make_pair(i.first,"");
        vector<pair<char,string>> pairs;
        pairs.push_back(code_pair);
        pair<int,vector<pair<char,string>>> freq_pair = make_pair(i.second,pairs);
        ls.push_back(freq_pair);
    }

    return ls;
    
}


map<char,int> build_freq(string file)
{
    // declare the map
    map<char,int> fmap;

    char c;
    // loop through file
    fstream fin("source.txt", fstream::in);
    while(fin >> noskipws >> c){
        if(fmap.find(c) != fmap.end()) ++fmap[c];
        else fmap[c] = 1;
    }

    return fmap;
}


void print(pair<int,vector<pair<char,string>>> x){
    cout << x.first << endl;
    for(int i=0; i< x.second.size(); i++){
        pair<char,string> temp = x.second[i];
        cout << temp.first << ": " << temp.second << endl;
    }
}


pair<int,vector<pair<char,string>>> merge(pair<int,vector<pair<char,string>>> p0,
                                        pair<int,vector<pair<char,string>>> p1)
{
    vector<pair<char,string>> merged_vector = p0.second;
    merged_vector.insert(merged_vector.end(),p1.second.begin(), p1.second.end());
    int sum = p0.first+p1.first;
    pair<int,vector<pair<char,string>>> m = make_pair(sum,merged_vector);
    return m;
    
}

void update(pair<int,vector<pair<char,string>>>& p, string x)
{
    for (int i=0; i< p.second.size(); i++){
        p.second[i].second.insert(0,x);
    }
}

void encode_huffman(vector<pair<int,vector<pair<char,string>>>>& v)
{
    while (v.size() > 1){
        sort(v.begin(), v.end(), compare);
        update(v[0],"1");
        update(v[1],"0");
        pair<int,vector<pair<char,string>>> new_pair = merge(v[0],v[1]);
        v.erase(v.begin(), v.begin()+2);
        v.push_back(new_pair);
    }
}


int main(void)
{
    string file = "source.txt";
    map<char,int> fmap = build_freq(file);
    /*
    for (map<char,int>::iterator i = fmap.begin(); i!=fmap.end();i++){
        cout << i->first << ": " << i->second << endl;
    }
    */
    vector<pair<int,vector<pair<char,string>>>> ls = build_list(fmap);
    encode_huffman(ls);
    print(ls[0]);
    cout << ls[0].second.size() << endl;
    return 0;
}