#include <bits/stdc++.h>
using namespace std;
ifstream in("date.in");
ofstream out("date.out");
class FST ///Mealy Machine
{
    static const int NR_STARI = 250;
    struct Muchie
    {
        int to;
        char ip, op;
    };
    vector<Muchie> g[NR_STARI];
    set<int> finale;
    int start;
public:
    void baga_final(int fin)
    {
        finale.insert(fin);
    }
    void baga_muchie(int from, int to, char ip, char op)
    {
        Muchie mu = {to, ip, op};
        g[from].push_back(mu);
    }
    void set_start(int st)
    {
        this -> start = st;
    }
    int get_start()
    {
        return start;
    }
    pair<bool, string> eval(int nod, int idx, string& inp, string& outp )
    {
        if ( idx == inp.size() )
        {
            if ( finale.find(nod) != finale.end() )
            {
                return make_pair(true, outp);
            }
            return make_pair(false, outp);
        }
        for ( Muchie mu : g[nod] )
        {
            if ( mu.ip == inp[idx] )
            {
                outp += mu.op;
                return eval(mu.to, idx+1, inp, outp);
            }
        }
        return make_pair(false, outp);
    }
    bool computeaza(string s)
    {
        string idk = "";
        pair<bool, string> aux = eval(start, 0, s, idk);
        bool ans = false;
        if ( aux.first == true )
        {
            cout<<"A fost acceptat\n";
            ans = true;
        }
        cout<<"OUTPUT: "<<aux.second;
        return ans;
    }
};
FST automata;
string cuvant;
void citire()
{
    int n;
    in>>n;
    map<int, int> maparea;
    for ( int i = 1 ; i <= n ; i++ )
    {
        int x;
        in>>x;
        maparea[x] = i;
    }
    int m;
    in>>m;
    for( int i = 1 ; i <= m ; i++ )
    {
        int from, to;
        char ip, op;
        in>>from>>to;
        in.get();
        in.get(ip);
        in.get();
        in.get(op);
        automata.baga_muchie(from, to, ip, op);
    }
    int start;
    in>>start;
    automata.set_start(start);
    int nrfin;
    in>>nrfin;
    for ( int i = 1 ; i <= nrfin ; i++ )
    {
        int x;
        in>>x;
        automata.baga_final(x);
    }
    in>>cuvant;
}
void rez()
{
    automata.computeaza(cuvant);
}
int main()
{
    citire();
    rez();
    return 0;
}
