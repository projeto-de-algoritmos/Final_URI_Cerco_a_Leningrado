#include<bits/stdc++.h>

using namespace std;
using ii = pair<int, int>;
using pp = pair<int, ii>;

const int MAX { 100010 }, oo { 1000010 };
int dist[MAX];
int w[MAX];
vector<int> adj[MAX];
bitset<MAX> processed;
/*
	Foi utlizado o dijkstra onde foram priorizadas as estradas(arestas) que levam o atirador a gastar menos balas(k). 
	Por fim, a probabilidade foi calculada a partir da quantidade de inimigos existentes no caminho que leva o soldado 
	a gastar o menor número de balas(k) possível.
*/
int dijkstra(int s,int dest ,int k,int N){
 	for (int i = 1; i <= N; ++i)
 		dist[i] = oo;

 	dist[s] = 0;
 	processed.reset();
	priority_queue<pp, vector<pp>, greater<pp>> pq;
    pq.push(pp(0,ii(s, k - w[s])));

 	while (not pq.empty()){
 		auto qq = pq.top();
        auto u = qq.second.first;
        auto b = qq.second.second;
        auto d = qq.first;
 		pq.pop();

 		if (processed[u]) continue;

 		processed[u] = true;
        for(auto v : adj[u]){
 			if ((dist[v] > d + w[v])&&(b - w[v] >= 0)) {
 				dist[v] = d + w[v];
                pq.push(pp(dist[v],ii(v,b-w[v])));
 			}
 		}
 	}

 	if(dist[dest] == oo) return -1;
 	else return (dist[dest] + w[s]);
}

int main(){
    int n,m,k,a,b,s,pos,o,d;
    double p;

    while(cin >> n >> m >> k >> p){
        for(int i = 0;i < m;i++){
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        memset(w,0,sizeof(w));
        cin >>  s;
        while(s--){
            cin >> pos;
            w[pos]++;
        }

        cin >> o >> d;
        int ret = dijkstra(o,d,k,n);
        if(ret == -1) cout << "0.000" << endl;
        else{
            double r = pow(p,ret);
            cout << fixed;
            cout.precision(3);
            cout << r << endl;
        }
        for(int i = 1;i <= n;i++) adj[i].clear();
    }

    return 0;
}
