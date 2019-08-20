#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int NN=20010;
const int oo=1e9+10;
int s[NN];
int y[NN],x[NN],c[NN],sa[NN],rk[NN],height[NN];
int n,m;
void get_SA()
{
    memset(c,0,sizeof(c));
    memset(sa,0,sizeof(sa));
    memset(x,0,sizeof(x));
    memset(y,0,sizeof(y));
    for(int i=1;i<=n;++i) ++c[x[i]=s[i]];
    for(int i=2;i<=m;++i) c[i]+=c[i-1];
    for(int i=n;i>=1;--i) sa[c[x[i]]--]=i;
    for(int k=1;k<=n;k<<=1)
	{
        int num=0;
        for(int i=n-k+1;i<=n;++i) y[++num]=i;
        for(int i=1;i<=n;++i) if(sa[i]>k) y[++num]=sa[i]-k;
        for(int i=1;i<=m;++i) c[i]=0;
        for(int i=1;i<=n;++i) ++c[x[i]];
        for(int i=2;i<=m;++i) c[i]+=c[i-1];
        for(int i=n;i>=1;--i) sa[c[x[y[i]]]--]=y[i],y[i]=0;
        swap(x,y);
        x[sa[1]]=1;
        num=1;
        for(int i=2;i<=n;++i)
            x[sa[i]]=(y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k]) ? num:++num;
        if(num==n) break;
        m=num;
    }
}
void get_height()
{
    int k=0;
    for(int i=1;i<=n;++i) rk[sa[i]]=i;
    for(int i=1;i<=n;++i)
	{
        if(rk[i]==1) continue;
        if(k) --k;
        int j=sa[rk[i]-1];
        while(j+k<=n&&i+k<=n&&s[i+k]==s[j+k]) ++k;
        height[rk[i]]=k;
    }
}
int ss[NN];
int main(){

    while(1){
        scanf("%d",&n);  if(n==0)break;
        for(int i=1;i<=n;i++){
            scanf("%d",ss+i);
        }
        memset(s,0,sizeof(s));
        for(int i=1;i<n;i++)s[i]=ss[i+1]-ss[i]+88;
        n--;m=200;
        get_SA();
        memset(height,0,sizeof(height));
        get_height();
        //for(int i=1;i<=n;i++)printf("%d ",sa[i]);printf("\n");
        int l=4;int r=n-1;
        int ans=0;
        while(l<=r){
            int mid=(l+r)/2;
            int beg=1;
            int can=0;
            //printf("%d:\n",mid);
            for(int i=2;i<=n+1;i++){
                if(height[i]<mid||i==n+1){
                    int minn=oo,maxn=0;
                    //printf("%d %d\n",beg,i);
                    for(int j=beg;j<i;j++){
                        minn=min(minn,sa[j]);maxn=max(maxn,sa[j]);
                    }
                    if(maxn-minn>mid){
                        can=1;break;
                    }
                    beg=i;
                }
            }
            if(can==0){
                r=mid-1;
            }
            else{
                ans=max(ans,mid);
                l=mid+1;
            }
        }
        if(ans<4)printf("0\n");
        else printf("%d\n",ans+1);
    }
    return 0;
}
