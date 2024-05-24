#include<bits/stdc++.h>
using namespace std;
ifstream in("date.in");
class PDA
{
    const char LAMBDA = '#';
    static const int NR_STARI = 1e3;
    struct Tranzitie
    {
        char verif, popuiesc, pushuiesc;
    };
    struct Muchie
    {
        int to;
        Tranzitie tranzitie;
    };
    vector<Muchie> graf[NR_STARI];
    set<int> finale;
    int start;
    stack<char> stiva;
    bool verif_lambda(char verificatul, char daca_nu)
    {
        if ( verificatul == LAMBDA )
            return true;
        return verificatul == daca_nu;
    }
public:
    void set_start(int start)
    {
        this -> start = start;
    }
    void adauga_final(int fin)
    {
        finale.insert(fin);
    }
    void baga_muchie(int from, Muchie to)
    {
        graf[from].push_back(to);
    }
    int get_start()
    {
        return start;
    }
    set<int>& get_finale()
    {
        return finale;
    }
    vector< vector<int> > viz;
    bool evalueaza(string& s)
    {
        viz.resize(NR_STARI);
        for ( int i = 0 ; i < NR_STARI ; i++ )
        {
            viz[i].resize(s.size());
            fill(viz[i].begin(), viz[i].end(), 0);
        }
        return dfs(start, s, 0);
    }
    bool dfs(int nod, string& s, int idx)
    {
        viz[nod][idx]++;
        if ( viz[nod][idx] > 1 )
            return false;
        for ( Muchie mu : graf[nod] )
        {
            if ( mu.tranzitie.verif != LAMBDA )
            {
                if ( mu.tranzitie.verif == s[idx] && verif_lambda(mu.tranzitie.popuiesc, stiva.top()) )
                {
                    if ( mu.tranzitie.popuiesc != LAMBDA )
                        stiva.pop();
                    if ( mu.tranzitie.pushuiesc != LAMBDA )
                        stiva.push(mu.tranzitie.pushuiesc);
                    bool ans = dfs(mu.to, s, idx+1);
                    if ( ans == true )
                        return true;
                    if ( mu.tranzitie.pushuiesc != LAMBDA )
                        stiva.pop();
                    if ( mu.tranzitie.popuiesc != LAMBDA )
                        stiva.push(mu.tranzitie.popuiesc);
                }
            }
            else
            {
                if ( stiva.size() == 0 || verif_lambda(mu.tranzitie.popuiesc, stiva.top()) )
                {
                    if ( mu.tranzitie.popuiesc != LAMBDA )
                        stiva.pop();
                    if ( mu.tranzitie.pushuiesc != LAMBDA )
                        stiva.push(mu.tranzitie.pushuiesc);
                    bool ans = dfs(mu.to, s, idx);
                    if ( ans == true )
                        return true;
                    if ( mu.tranzitie.pushuiesc != LAMBDA )
                        stiva.pop();
                    if ( mu.tranzitie.popuiesc != LAMBDA )
                        stiva.push(mu.tranzitie.popuiesc);
                }
            }
        }
        if ( idx == s.size() )
        {
            if ( stiva.size() == 0 && finale.find(nod) != finale.end() ) ///posibil sa nu fie nevoie de prima conditie
            {
                return true;
            }
            return false;
        }
    }

};
int main()
{
    PDA automata;
    int n;
    in>>n;
    for ( int i = 1 ; i <= n ; i++ )
    {
        int x;
        in>>x;
    }
    int m;
    in>>m;
    for ( int i = 1 ; i <= m ; i++ )
    {
        int from, to;
        char ve, po, pu;
        in>>from>>to;
        in.get();
        in.get(ve);
        in.get();
        in.get(po);
        in.get();
        in.get(pu);
        automata.baga_muchie(from, {to, ve, po, pu});
    }
    int startul, fin, cate_fin;
    in>>startul>>cate_fin;
    automata.set_start(startul);
    for ( int i = 1 ; i <= cate_fin ; i++ )
    {
        in>>fin;
        automata.adauga_final(fin);
    }
    in.get();

    string s;
    getline(in, s);
    cout<<automata.evalueaza(s);
}
