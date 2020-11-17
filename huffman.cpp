#include"util.cpp"

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

map<char,string> huffman(vector<pair<int,vector<pair<char,string>>>> v)
{
    map<char,string> cmap;
    if(v.size()==1){
        for(auto i:v[0].second){
            cmap[i.first] = i.second;
        }
    }

    return cmap;
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
    //print_list(ls[0]);
    map<char,pair<double,double>> pmap = build_prob(fmap);
    map<char,string> cmap = huffman(ls);
    double ave =  average_len(cmap,pmap);
    double entropy = get_entropy(pmap);
    write_output(cmap,"source.txt","Huffman",ave,entropy);
    return 0;
}