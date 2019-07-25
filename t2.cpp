#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int T=0;
const int NN=1e5+10;
const int TT=NN;
long long sum[NN*26];
long long ad[NN*26];
int L[TT*26],R[TT*26];
long long a[NN];
int troot[TT];
int n,m;
void up(int cur,int l,int r){
	sum[cur]=sum[L[cur]]+sum[R[cur]]+ad[cur]*(r-l+1);
}
int cnt=0;
void build(int &cur,int l,int r){
	cur=++cnt;
	if(l==r){sum[cur]=a[l];return;}
	int mid=(l+r)>>1;
	build(L[cur],l,mid);
	build(R[cur],mid+1,r);
	up(cur,l,r);
}
void add(int &cur,int l,int r,int x,int y,long long val,int pre){
	cur=++cnt;
	ad[cur]=ad[pre];
	sum[cur]=sum[pre];
	L[cur]=L[pre];
	R[cur]=R[pre];
	if((x<=l&&r<=y)||(l==r)){
		ad[cur]+=val;
		sum[cur]+=val*(r-l+1);
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)add(L[cur],l,mid,x,y,val,L[pre]);
	if(y>mid)add(R[cur],mid+1,r,x,y,val,R[pre]);
	up(cur,l,r);
}
long long ask(int cur,int l,int r,int x,int y,long long lei){
	//printf("%d %d %lld %lld\n",l,r,sum[cur],lei);
	if((x<=l&&r<=y)||(l==r)){
		return sum[cur]+lei*(r-l+1);
	}
	int mid=(l+r)>>1;
	long long ans=0;
	if(x<=mid)ans+=ask(L[cur],l,mid,x,y,lei+ad[cur]);
	if(y>mid)ans+=ask(R[cur],mid+1,r,x,y,lei+ad[cur]);
	return ans;
}
int main(){
	
	while(scanf("%d%d",&n,&m)==2){
		T=0;
		memset(sum,0,sizeof(sum));
		memset(ad,0,sizeof(ad));
		cnt=0;
		for(int i=1;i<=n;i++){
			scanf("%lld",a+i);
		}
		build(troot[0],1,n);
		for(int i=1;i<=m;i++){
			char op[10];
			scanf("%s",op);
			if(op[0]=='C'){
				int l,r,d;
				T++;
				scanf("%d%d%d",&l,&r,&d);
				add(troot[T],1,n,l,r,d,troot[T-1]);
			}
			else if(op[0]=='Q'){
				int l,r;
				scanf("%d%d",&l,&r);
				long long ans=ask(troot[T],1,n,l,r,0);
				printf("%lld\n",ans);
			}
			else if(op[0]=='H'){
				int l,r,t;
				scanf("%d%d%d",&l,&r,&t);
				if(t>T)return 0;
				long long ans=ask(troot[t],1,n,l,r,0);
				printf("%lld\n",ans);
			}
			else{
				int t;scanf("%d",&t);
				T=t;
				cnt=troot[T+1]-1;
			}
		}
		//printf("\n");
	}
	return 0;
}