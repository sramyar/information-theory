#include<iostream>
#include<fstream>
#include<map>
#include<string>
#include<vector>
#include<bits/stdc++.h> 
#include<math.h>
using namespace std;






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

double get_sum(map<char,int> fmap)
{
    int sum = 0;
    for(auto i: fmap){
        sum += i.second;
    }
    return static_cast<double>(sum);
}

map<char,pair<double,double>> build_prob(map<char,int> fmap)
{
    double sum = get_sum(fmap);
    double temp_sum = 0;
    double zSum;
    map<char,pair<double,double>> prob_map;
    for (auto i: fmap){
        temp_sum += static_cast<double>(i.second);
        zSum = temp_sum - static_cast<double>(i.second)/2;
        prob_map[i.first] = make_pair(i.second/sum,zSum/sum);
    }

    return prob_map;
}

void print_prob(map<char,pair<double,double>> m)
{
    for(auto i: m){
        cout << i.first << "\t" << i.second.first << "\t" << i.second.second<<endl;
    }
}

void print_list(pair<int,vector<pair<char,string>>> x){
    cout << x.first << endl;
    for(int i=0; i< x.second.size(); i++){
        pair<char,string> temp = x.second[i];
        cout << temp.first << ": " << temp.second << endl;
    }
}

void print_map(map<char,string> cmap)
{
    // prints the map of encoded symbols
    for(auto i:cmap)
    {
        cout << i.first << "\t" << i.second << endl;
    }
}

double average_len(map<char,string> cmap, map<char,pair<double,double>> pmap)
{
    double ave = 0;
    char c;
    for (auto i: cmap){
        c = i.first;
        ave += cmap[c].size()*(pmap[c].first);
    }

    return ave;
}

double get_entropy(map<char,pair<double,double>> pmap)
{
    double h = 0;
    double p;
    for(auto i:pmap){
        p = pmap[i.first].first;
        h += (-p)*(log(p)/log(2));
    }

    return h;
}

void write_output(map<char,string> cmap, string src_file, string encode_type,
                    double ave, double entropy)
{

    ofstream fout;
    string fname = encode_type;
    fname.append(".txt");
    fout.open(fname, ofstream::out | ofstream::trunc);
    fstream fin("source.txt", fstream::in);
    fout << "using " << encode_type<< " coding average lengthof is: " << ave << "\n";
    fout << "Entropy is: " << entropy << "\n";
    fout << "Coded source using " << encode_type << " coding:\n";
    char c;
    while(fin >> noskipws >> c){
        if(cmap.find(c) != cmap.end()) fout << cmap[c];
    }
    fout.close();

}
