#include"util.cpp"



string get_binary_frac(double z, int precision)
{
    string s = "";
    while(precision){
        z *= 2;
        if (z-1 > 0){
            s.append("1");
            z--;
        }
        else s.append("0");
        precision--;
    }

    return s;
}

double get_mCDF(pair<double,double> p)
{
    return p.second;
}

int get_length(double p)
{
    return ceil((log((1/p))/log(2)))+1;
}

string get_code(double z, int l)
{
    string c = get_binary_frac(z,l);
    return c;
}


map<char,string> SFE_encode(map<char,pair<double,double>> pmap)
{
    double p;   // p(x) of src symbol
    double z;   // modified CDF
    string c;   // encoded string
    int l;      // length of string
    map<char,string> sfe_map;
    for (auto i:pmap){
        p = i.second.first;
        z = get_mCDF(i.second);
        l = get_length(p);
        c = get_code(z, l);       
        sfe_map[i.first] = c;
    }

    return sfe_map;
}


int main(void)
{
    string src = "source.txt";
    map<char,int> fmap = build_freq(src);
    map<char,pair<double,double>> pmap = build_prob(fmap);
    map<char,string> cmap = SFE_encode(pmap);
    double ave =  average_len(cmap,pmap);
    double entropy = get_entropy(pmap);
    write_output(cmap,"source.txt","SFE",ave,entropy);
    //return 0;
}