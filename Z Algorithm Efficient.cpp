#include <bits/stdc++.h>
using namespace std;
#define mx 10000
string s;
int z[mx];
void Zfunction()
{
    int l, r;
    z[0]= l = r =0;
    int len = s.size();
    for(int i=1; i<len; i++){
        if(i <= r){
            z[i] = min(z[i-l], z[r - i +1]);
        }
        while(i + z[i] < len && s[i + z[i]] == s[z[i]]){
            z[i]++;
        }
        if(i + z[i] -1 > r){
            l = i;
            r = i + z[i] -1;
        }
    }
}
int main()
{
   cin>>s;
   string t;
   cin>>t;
   s= "$"+s;
   s = t+s;
   Zfunction();
   int ans = INT_MIN;
   int len = s.size();
   for(int i=0; i<len; i++){
       ans= max(ans, z[i]);
   }
   cout<<ans<<endl;

}
