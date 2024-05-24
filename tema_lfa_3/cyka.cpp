#include<bits/stdc++.h>
using namespace std;
ifstream in("date.in");
ofstream out("date.out");
struct Chestie
{
    char nume[3];
    bool terminal;
    friend ostream& operator<< (ostream& out, const Chestie& c);
    bool operator<(const Chestie& c) const
    {
        return strcmp(this -> nume, c.nume) < 0;
    }
    bool operator>(const Chestie& c) const
    {
        return strcmp(this -> nume, c.nume) > 0;
    }
    bool operator==(const Chestie& c) const
    {
        return strcmp(this -> nume, c.nume) == 0;
    }
};
ostream& operator<< (ostream& out, const Chestie& c)
{
    out<<c.nume;
}
string cuvant;
Chestie start;
map<Chestie, set<Chestie> > reguli_citite;
map<Chestie, set<Chestie> > invers_reguli;
void citire()
{
    int n;
    in>>n;
    in.get();
    for ( int i = 1 ; i <= n ; i++ )
    {
        string linie;
        getline(in, linie);
        char *parsez = new char[linie.size()];
        strcpy(parsez, linie.c_str());
        char* p = strtok(parsez, " ");
        char variabila = p[0];
        Chestie from = {{p[0], NULL}, false};
        if ( reguli_citite.find(from) == reguli_citite.end() ){
            set<Chestie> aux;
            reguli_citite.insert(make_pair(from, aux));
        }
        p = strtok(NULL, " ");
        while ( p != NULL )
        {
            Chestie to;
            to.nume[0] = p[0];
            to.terminal = (to.nume[0] >= 'a' && to.nume[0] <= 'z' ? true : false);
            int last = 1;
            if ( p[1] != NULL )
            {
                to.nume[last++] = p[1];
            }
            to.nume[last] = NULL;
            reguli_citite[from].insert(to);
            if ( invers_reguli.find(to) == invers_reguli.end() )
            {
                set<Chestie> aux;
                invers_reguli.insert(make_pair(to, aux));
            }
            invers_reguli[to].insert(from);
            p = strtok(NULL, " ");
        }
    }
    in>>cuvant;
    start.nume[0] = cuvant[0];
    start.nume[1] = NULL;
    in>>cuvant;
}
void afmap(map<Chestie, set<Chestie> > mp, string mesaj1, string mesaj2 )
{
    for ( pair<Chestie, set<Chestie> > p : mp )
    {
        cout<<mesaj1<<p.first<<mesaj2;
        for ( Chestie c : p.second )
        {
            cout<<c<<" ";
        }
        cout<<'\n';
    }
}
bool check_final(set<Chestie>& s)
{
    if ( s.find(start) == s.end() )
        return false;
    return true;
}
void rez()
{
    set<Chestie> ans[cuvant.size()+1][cuvant.size()+1];
    ///initiem prima linie
    for ( int i = 0 ; i < cuvant.size() ; i++ )
    {
        Chestie aux = {{cuvant[i], NULL}, true};
        for ( Chestie c : invers_reguli[aux] )
        {
            ans[1][i+1].insert(c);
        }
    }
    for ( int l = 2 ; l <= cuvant.size() ; l++ )
    {
        for ( int i = 1 ; i <= cuvant.size() ; i++ )
        {
            int ceva = cuvant.size();
            int j = min(ceva, i + l - 1);
            if ( ans[l][i].size() != 0 )
                continue;
            for ( int k = i ; k < j ; k++ )
            {
                ///nu pot face functie ca am local ans
                for ( Chestie c1 : ans[k-i+1][i] )
                {
                    for ( Chestie c2 : ans[j-k][k+1] )
                    {
                        Chestie aux = {{c1.nume[0], c2.nume[0], NULL}, false};
                        if ( invers_reguli.find(aux) != invers_reguli.end() )
                        {
                            for ( Chestie c3 : invers_reguli[aux] )
                            {
                                ans[j-i+1][i].insert(c3);
                            }
                        }
                    }
                }
            }
        }
    }
    bool ebun = check_final(ans[cuvant.size()][1]);
    if ( ebun )
    {
        cout<<"DA";
    }
    else
    {
        cout<<"NU";
    }
}
int main()
{
    citire();
    rez();
    return 0;
}
