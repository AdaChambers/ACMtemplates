#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int NN=100010;
int n,m,v0;
long long cov[4*NN],add[4*NN],sum[4*NN];
void down(int cur,int l,int r){
	int mid=(l+r)>>1;
	int ls=cur<<1,rs=cur<<1|1;
	if(cov[cur]!=1000000){
		cov[ls]=cov[cur];
		cov[rs]=cov[cur];
		add[ls]=add[cur];
		add[rs]=add[cur];
		sum[ls]=(cov[ls]+add[ls])*(mid-l+1);
		sum[rs]=(cov[rs]+add[rs])*(r-mid);
	}
	else{
		add[ls]+=add[cur];
		add[rs]+=add[cur];
		sum[ls]+=add[cur]*(mid-l+1);
		sum[rs]+=add[cur]*(r-mid);
	}
	cov[cur]=1000000;
	add[cur]=0;
}
void update(int cur){
	sum[cur]=sum[cur<<1]+sum[cur<<1|1];
}
void co(int l,int r,int x,int y,int val,int cur){
	if(x<=l&&r<=y){
		add[cur]=0;
		cov[cur]=val;
		sum[cur]=val*(r-l+1);
		return;
	}
	down(cur,l,r);
	int mid=(l+r)>>1;
	if(x<=mid)co(l,mid,x,y,val,cur<<1);
	if(y>mid)co(mid+1,r,x,y,val,cur<<1|1);
	update(cur);
}
void ad(int l,int r,int x,int y,int val,int cur){
	if(x<=l&&r<=y){
		add[cur]+=val;
		sum[cur]+=val*(r-l+1);
		return;
	}
	down(cur,l,r);
	int mid=(l+r)>>1;
	if(x<=mid)ad(l,mid,x,y,val,cur<<1);
	if(y>mid)ad(mid+1,r,x,y,val,cur<<1|1);
	update(cur);
}
long long ask(int l,int r,int x,int y,int cur){
	if(x<=l&&r<=y){
		return sum[cur];
	}
	down(cur,l,r);
	int mid=(l+r)>>1;
	long long ans=0;
	if(x<=mid)ans+=ask(l,mid,x,y,cur<<1);
	if(y>mid)ans+=ask(mid+1,r,x,y,cur<<1|1);
	update(cur);
	return ans;
}
void build(int l,int r,int cur){
	if(l==r){
		sum[cur]=v0;
		cov[cur]=1000000;
		add[cur]=0;
		return;
	}
	add[cur]=0;cov[cur]=1000000;
	int mid=(l+r)>>1;
	build(l,mid,cur<<1);
	build(mid+1,r,cur<<1|1);
	update(cur);
}
int main(){
	while(scanf("%d %d %d",&n,&m,&v0)==3){
		build(1,n,1);
		for(int i=1;i<=m;i++){
			int op;
			scanf("%d",&op);
			if(op==0){
				int x,y,z;
				scanf("%d%d%d",&x,&y,&z);
				ad(1,n,x,y,z,1);
			}
			else if(op==1){
				int x,y,z;
				scanf("%d%d%d",&x,&y,&z);
				co(1,n,x,y,z,1);
			}
			else{
				int x,y;
				scanf("%d%d",&x,&y);
				long long ans=ask(1,n,x,y,1);
				printf("%lld\n",ans );
			}
		}
	}
	return 0;
}