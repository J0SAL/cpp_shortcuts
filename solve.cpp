#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll MOD = 1000000007;

ll expo(ll a, ll b, ll mod) {
	ll res = 1; while (b > 0) 
	{
		if (b & 1) res = (res * a) % mod; 
		a = (a * a) % mod; 
		b = b >> 1;
	} 
	return res;
}


ll mminvprime(ll a, ll b) {
	return expo(a, b - 2, b);
}


ll mod_add(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a + b) % m) + m) % m;}
ll mod_mul(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a * b) % m) + m) % m;}
ll mod_sub(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a - b) % m) + m) % m;}
ll mod_div(ll a, ll b, ll m) {a = a % m; b = b % m; return (mod_mul(a, mminvprime(b, m), m) + m) % m;} 

struct Hashing{
    string s;
    int n;
    int primes;
    vector<ll> hashPrimes = {1000000009, 100000007};
    const ll base = 31;
    vector<vector<ll>> hashValues;
    vector<vector<ll>> powersOfBase;
    vector<vector<ll>> inversePowersOfBase;
    Hashing(string a){
        primes = hashPrimes.size();
        hashValues.resize(primes);
        powersOfBase.resize(primes);
        inversePowersOfBase.resize(primes);
        s = a;
        n = s.length(); 
        for(int i = 0; i < hashPrimes.size(); i++) {
            powersOfBase[i].resize(n + 1);
            inversePowersOfBase[i].resize(n + 1);
            powersOfBase[i][0] = 1;
            for(int j = 1; j <= n; j++){
                powersOfBase[i][j] = (base * powersOfBase[i][j - 1]) % hashPrimes[i];
            }
            inversePowersOfBase[i][n] = mminvprime(powersOfBase[i][n], hashPrimes[i]);
            for(int j = n - 1; j >= 0; j--){
                inversePowersOfBase[i][j] = mod_mul(inversePowersOfBase[i][j + 1], base, hashPrimes[i]);
            } 
        }
        for(int i = 0; i < hashPrimes.size(); i++) {
            hashValues[i].resize(n);
            for(int j = 0; j < n; j++){
                hashValues[i][j] = ((s[j] - 'a' + 1LL) * powersOfBase[i][j]) % hashPrimes[i];
                hashValues[i][j] = (hashValues[i][j] + (j > 0 ? hashValues[i][j - 1] : 0LL)) % hashPrimes[i];
            }
        }
    }
    vector<ll> substringHash(int l, int r){
        vector<ll> hash(primes);
        for(int i = 0; i < primes; i++){
            ll val1 = hashValues[i][r];
            ll val2 = l > 0 ? hashValues[i][l - 1] : 0LL;
            hash[i] = mod_mul(mod_sub(val1, val2, hashPrimes[i]), inversePowersOfBase[i][l], hashPrimes[i]);
        }
        return hash;
    }
};
void solve() {
    string s;
    cin >> s;
    set<vector<ll>> unique_subs;
    
    int n = s.length();
    Hashing hs = Hashing(s);
    
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            vector<ll> hash = hs.substringHash(i, j);
            unique_subs.insert(hash);
        }
    }
    
    cout << unique_subs.size() << endl;

}

int main(){
	#ifndef ONLINE_JUDGE
       freopen("input.txt","r",stdin);
       freopen("output.txt","w",stdout);
  	#endif
	int t=1; //cin>>t;
	while(t--){
		solve();
		cout<<"\n";
	}
	return 0;
}