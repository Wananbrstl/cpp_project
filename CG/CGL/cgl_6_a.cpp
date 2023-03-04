#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;
typedef pair<P,int> P2;
struct RSQ{
  int n=(1<<17),data[(1<<18)];
  RSQ(){
    memset(data,0,sizeof(data));
  }
  // 0 index
  void add(int i,int v){
    i++;
    while(i<=n){
      data[i]+=v;
      i+=i&-i;
    }
  }
  int sum(int i){
    int res=0;
    while(i>0){
      res+=data[i];
      i-=i&-i;
    }
    return res;
  }
  //[a,b) 
  int sum(int x,int y){
    return sum(y)-sum(x);
  }
};

struct Sweap{
    int n;
    vector<int>ye,ys,xs,xe;
    vector<P2>vx,vy;
    Sweap(vector<int>X1,vector<int>X2,vector<int>Y1,vector<int>Y2,int sz,int flag_zaatsu){
        n=sz;xs=X1;xe=X2;ys=Y1;ye=Y2;
        if(flag_zaatsu!=0)zaatsu();
        for(int i=0;i<n;i++){
            if(ys[i]>ye[i])swap(ys[i],ye[i]);
            if(xs[i]>xe[i])swap(xs[i],xe[i]);
            if(xs[i]==xe[i]){
                vx.push_back(P2(P(xs[i], 2), i));
                vy.push_back(P2(P(ys[i], 1), i));
                vy.push_back(P2(P(ye[i], 3), i));
            }
            else{
                vx.push_back(P2(P(xs[i], 1), i));
                vx.push_back(P2(P(xe[i], 3), i));
                vy.push_back(P2(P(ys[i], 2), i));
            }
        }
        sort(vx.begin(),vx.end());
        sort(vy.begin(),vy.end());
    }
    void zaatsu(){
        map<int,int>Mx,My;
        vector<int>tvx,tvy;
        for(int i=0;i<n;i++){
            tvx.push_back(xs[i]);
            tvx.push_back(xe[i]);
            tvy.push_back(ys[i]);
            tvy.push_back(ye[i]);
        }
        sort(tvx.begin(),tvx.end());
        sort(tvy.begin(),tvy.end());
        tvx.erase(unique(tvx.begin(),tvx.end()),tvx.end());
        tvy.erase(unique(tvy.begin(),tvy.end()),tvy.end());
        for(int i=0;i<tvx.size();i++)Mx[tvx[i]]=i;
        for(int i=0;i<tvy.size();i++)My[tvy[i]]=i;
        for(int i=0;i<n;i++){
            xs[i]=Mx[xs[i]];
            xe[i]=Mx[xe[i]];
            ys[i]=My[ys[i]];
            ye[i]=My[ye[i]];
        }
    }
    int build(){
        RSQ rsq;
        int sum=0;
        for(int i=0;i<vx.size();i++){
            int id=vx[i].second;
            int seed=vx[i].first.second;
            if(seed==1){
                rsq.add(ys[id],1);
            }
            else if(seed==3){
                rsq.add(ye[id],-1);
            }
            else{
                sum+=rsq.sum(ys[id],ye[id]+1);
            }
        }
        return sum;
    }
};
 
 
int main(){
    int n;
    scanf(" %d", &n);
    vector<int>X1(n),X2(n),Y1(n),Y2(n);
    for(int i = 0; i < n; i++)scanf("%d%d%d%d",&X1[i],&Y1[i],&X2[i],&Y2[i]);
    Sweap s(X1,X2,Y1,Y2,n,1);
    cout<<s.build()<<endl;
}

