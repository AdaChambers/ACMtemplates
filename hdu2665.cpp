#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int n,m;
int tot;
const int NN=100010;
int num[NN*20],L[NN*20],R[NN*20],a[NN],h[NN];
bool cmp(int x,int y){
	return x>y;
}
int troot[NN];
void build(int &cur,int l,int r){
	cur=++tot;
	num[cur]=0;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	build(L[cur],l,mid);
	build(R[cur],mid+1,r);

}
void add(int &cur,int pre,int l,int r,int val){
	cur=++tot;
	num[cur]=num[pre]+1;
	if(l==r)return;
	L[cur]=L[pre];
	R[cur]=R[pre];
	int mid=(l+r)>>1;
	if(val<=mid)add(L[cur],L[pre],l,mid,val);
	else add(R[cur],R[pre],mid+1,r,val);
}
int ask_kth(int x,int y,int l,int r, int k){//k is always >=1
	if(l==r){
		return h[l];
	}
	int mid=(l+r)>>1;
	int deci=num[L[x]]-num[L[y]];
	if(deci>=k)
		return ask_kth(L[x],L[y],l,mid,k);
	else{
		if(num[R[x]]-num[R[y]]<=0){
			return ask_kth(L[x],L[y],l,mid,deci);
		}
		else return ask_kth(R[x],R[y],mid+1,r,k-deci);
	}
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			scanf("%d",a+i);
			h[i]=a[i];
		}
		sort(h+1,h+n+1);
		int new_n=unique(h+1,h+n+1)-h-1;
		tot=0;
		build(troot[0],1,new_n);
		for(int i=1;i<=n;i++){
			add(troot[i],troot[i-1],1,new_n,lower_bound(h+1,h+new_n+1,a[i])-h);
		}
		for(int i=1;i<=m;i++){
			int x,y,k;
			scanf("%d%d%d",&x,&y,&k);
			if(x>y)swap(x,y);
			int ans=ask_kth(troot[y],troot[x-1],1,new_n,k);
			printf("%d\n",ans);
		}
	}
	return 0;
}