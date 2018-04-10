#include <bits/stdc++.h>
#include <sstream>
using namespace std;
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);
#define clr(a,v) memset(a, v, sizeof(a))
#define trace(x) cerr << #x << ": " << x << '\n'
#define trace2(x,y) cerr << #x << ": " << x << " | " << #y << ": " << y << '\n';
#define trace3(x,y,z) cerr << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": " << z << '\n';
#define all(v) (v).begin(),(v).end()
#define pb push_back
#define sz(v) ((int)v.size())
#define REP(i,x,y) for(long long (i)=(x);(i)<(y);(i)++)
#define RREP(i,x,y) for(long long (i)=(x);(i)>=(y);(i)--)
#define mp make_pair
#define mt(x,y,z) mp((x),mp((y),(z)))
#define fst first
#define snd second
#define ones(x) __builtin_popcountll(x)
#define gcd __gcd
#define MOD 1000000007
#define oo 1e12
#define N 1500000
#define cot 21
#define itm1 fst
#define EPS 1e-3
#define itm2 snd.fst
#define itm3 snd.snd
#define FILES 1
#define min INT_MIN
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vll;
typedef pair<ll,ii> tri;
typedef vector<tri> vt;
typedef pair<double, int> pi;

map<string,int> m;
map<ii, int> pesos;
vector<string> nombres;

void fix(string& s, int n){
	string aux = "";
	while(n){
		int dig = n%10;
		aux += (char)(dig + '0');
		n/=10;
	}
	reverse(all(aux));
	s+=aux;
}

int main(){
	freopen("autoria.txt", "r", stdin);
	int id = 1;
   	for(int n = 100; n <= 100000; n+=100){
		string s = "input";
		fix(s,n);
		s+=".txt";
		freopen(s.c_str(), "w", stdout);
	    REP(i,0,100){
	        string s1, s2;
	        getline(cin,s1); getline(cin,s2);
	        int id1, id2;
	        if(m[s1] == 0){
	            m[s1] = id++;
	            nombres.pb(s1);
	        }
	        if(m[s2] == 0){
	            m[s2] = id++;
	            nombres.pb(s2);
	        }
	        id1 = m[s1]; id2 = m[s2];
	        if(id1 > id2) swap(id1, id2);
	        pesos[mp(id1,id2)]++;    
	    }
	    cout << sz(nombres) << " " << sz(pesos) << endl;
	    REP(i,0,sz(nombres)){
	        cout << nombres[i] << endl;
	    }
	    for(auto x: pesos){
	        cout << x.fst.fst << " " << x.fst.snd << " " << x.snd << endl;
	    }
	}
    return 0;
}








