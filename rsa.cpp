#include<iostream>
#include<math.h>
#include <cstdlib>
#define ll long long
using namespace std;

ll fme(ll a, ll b, ll c) {                       
	 if(b == 0) 
       return 1;                                
	 if(b % 2 == 1) 
       return a * fme(a*a % c, b/2, c) % c; 
	 else 
       return fme(a*a % c, b/2, c) % c;
}  

bool Miller_Rabin(ll n)
{
	ll r = 0;
   ll d = n-1;
   int s = 0;
   if(n%2==0)return false;
   while((d/2)%2==0){
        d/=2;
        s++;
    }

   srand(time(NULL));
	ll a = rand() % (n - 2) + 2;
   
   ll y = fme(a,d,n);
   if(y == 1)
        return true;
   for(r=0;r<s;r++){
        ll z = pow(2,r)*d;
        if(fme(a,z,n) == n-1)
            return true;
    }
        return false;
}

ll gcd(ll a, ll b) {
   ll t;
   while(1) {
      t= a%b;
      if(t==0)
      return b;
      a = b;
      b = t;
   }
}
ll eea_d(ll a, ll b){
    ll x_0 = 1,x_1 = 0,r ,q = 0, N = 1,temp, x;
    while(a!=0){
        r = a;
        x = x_1*q + x_0;
        q = b/r;
        temp = a;
        a = b%r;
        b = temp;
        x_0 = x_1;
        x_1 = x;
        N++;
    }
    if(N%2 == 0)  
       return x;
    else 
       return -x;
}

ll eea_x(ll a, ll b){
    ll x_0 = 1,x_1 = 0,r ,q = 0, N = 1,temp, x;
    while(a!=0){
        r = a;
        x = x_1*q + x_0;
        q = b/r;
        temp = a;
        a = b%r;
        b = temp;
        x_0 = x_1;
        x_1 = x;
        N++;
    }
    if(N%2 == 0)  
       return x;
    else 
       return -x;
}

ll eea_y(ll a, ll b){
    ll y_0 = 0,y_1 = 1,r ,q = 0, N = 1,temp, y;
    while(a!=0){
        r = a;
        y = y_1*q + y_0;
        q = b/r;
        temp = a;
        a = b%r;
        b = temp;
        y_0 = y_1;
        y_1 = y;
        N++;
    }
    if(N%2 == 1)  
       return y;
    else 
       return -y;
}

int main() {
   ll m;
   cout<<"Input the message you want to encrypt:"<<endl;
   srand(time(NULL));
	ll p = rand() % (5000) + 3;
   ll q = rand() % (5000) + 3;
   //MR test for p
   for(int i = 0;i<3;){
      if(Miller_Rabin(p))i++;
      else {
         p = rand() % (5000) + 3;
         i = 0;
      }
   }
   //MR test for q
   for(int i = 0;i<3;){
      if(Miller_Rabin(q)&&p!=q)
         i++;
      else {
         q = rand() % (5000) + 3;
         i=0;
      }
   }
   ll n = p*q;
   ll t;
   ll phi = (p-1)*(q-1);
   ll e = 3;

   while(e<phi) {
      t = gcd(e,phi);
      if(t==1)
         break;
      else
         e++;
   }
   ll d = eea_d(e,phi);
   if(d < 0)
      d += phi;
      
   ll v,c,u;
   cin>>m;
   cout<<"Original Message = "<<m;

   c=fme(m,e,n);
   m=fme(c,d,n);
   cout<<"\n"<<"p = "<<p;
   cout<<"\n"<<"q = "<<q;
   cout<<"\n"<<"n = "<<n;
   cout<<"\n"<<"phi = "<<phi;
   cout<<"\n"<<"e = "<<e;
   cout<<"\n"<<"d = "<<d;
   cout<<"\n"<<"x = "<<eea_x(e,phi);
   cout<<"\n"<<"y = "<<eea_y(e,phi);
   cout<<"\n"<<"r = "<<t;
   cout<<"\n"<<"Encrypted message = "<<c;
   cout<<"\n"<<"Decrypted message = "<<m<<endl;
   return 0;
}