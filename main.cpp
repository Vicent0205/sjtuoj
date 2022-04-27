#include <iostream>
#include <unordered_map>
#include <utility>
using namespace std;
//状态压缩， dp[i][j1][j2]记录到第i+1行（其中 第i行状态为j1 i+1行状态为j2）的方案数目
//转移方程  dp[i][j1][j2]=sum{dp[i-2][j3][j4]}  j3 j4 满足something
int main() {
    const int myMore=1e9+7;
    //std::cout << "Hello, World!" << std::endl;
    pair<int,int>*pairList=new pair<int,int>[2<<12];
    int pairUpper=0;
    int m,n,k;
    cin>>m>>n>>k;
    int broX,broY;
    unordered_map<int,int>map;
    for(int i=0;i<k;i++)
    {
        cin>>broX>>broY;
        if(map.count(broX-1))
            map[broX-1]=map[broX-1]|(1<<broY-1);
        else
            map[broX-1]=1<<broY-1;
    }
    int myLen=1<<n;
    int***dp=new int**[m];
    for(int i=0;i<m;i++)
    {
        dp[i]=new int*[myLen];
        for(int j=0;j<myLen;j++)
            dp[i][j]=new int[myLen];
    }
    //先预处理出两行之间所有可能的pair
    for(int i=0;i<(1<<n);i++)
    {
        for(int j=0;j<(1<<n);j++)
        {
            if(((i>>2)&j)==0 && (i<<2 &j)==0)
            {
                //cout<<"i  "<<i<<"  j  "<<j<<endl;
                pairList[pairUpper]= make_pair(i,j);
                pairUpper++;
            }
        }
    }
    //cout<<pairUpper<<endl;
    if(m==1) return (1<<n);
    //先对第0 行 第1行进行预处理
    for(int i=0;i<pairUpper;i++)
    {
        if(map.count(0) && (map[0]&pairList[i].first)!=0)
        {
            dp[0][pairList[i].first][pairList[i].second]=0;
            continue;
        }
        if(map.count(1) && (map[1] & pairList[i].second)!=0)
        {
            dp[0][pairList[i].first][pairList[i].second]=0;
            continue;
        }
        dp[0][pairList[i].first][pairList[i].second]=1;
    }
    for(int row=2;row<m;row++)
    {
        for(int i=0;i<pairUpper;i++)
        {
            if(map.count(row) && (map[row]&pairList[i].first)!=0)
            {
                dp[row][pairList[i].first][pairList[i].second]=0;
                continue;
            }
            if(map.count(row+1) && (map[row+1] & pairList[i].second)!=0)
            {
                dp[row][pairList[i].first][pairList[i].second]=0;
                continue;
            }
            //dp[row][pairList[i].first][pairList[i].second]=1;
            dp[row][pairList[i].first][pairList[i].second]=0;
            //找到上一层所有符合的
            for(int j=0;j<pairUpper;j++)
            {
                if((pairList[j].first<<1 &(pairList[i].first)) ==0 &&(pairList[j].first>>1 &(pairList[i].first))==0
                     &&(pairList[j].second<<2 &(pairList[i].first))==0 &&(pairList[j].second>>2 &(pairList[i].first))==0
                     && (pairList[j].second<<1 &(pairList[i].second))==0 &&(pairList[j].second>>1 &(pairList[i].second))==0)
                    dp[row][pairList[i].first][pairList[i].second]+=dp[row-2][pairList[j].first][pairList[j].second];
                    dp[row][pairList[i].first][pairList[i].second]=dp[row][pairList[i].first][pairList[i].second]%myMore;
            }
        }
    }
    int ans=0;
    if(m%2==0)
    {
        for(int i=0;i<pairUpper;i++)
        {
            ans+=dp[m-2][pairList[i].first][pairList[i].second];
            ans=ans%myMore;
        }
        cout<<ans<<endl;
    }
    else
    {
        for(int i=0;i<pairUpper;i++)
        {
            if(pairList[i].second==0)
            {
                ans+=dp[m-1][pairList[i].first][0];
                ans=ans%myMore;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
