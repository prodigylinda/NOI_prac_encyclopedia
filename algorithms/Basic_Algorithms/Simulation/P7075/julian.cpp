#include<bits/stdc++.h>
using namespace std;
int main(){
    freopen("julian.in","r",stdin);
    freopen("julian.out","w",stdout);
    long long q;
    cin>>q;
    long long fourn = 3*365+366;
    long long a = 1178*fourn+366;
    long long b = 1581*365+395+365-61-27;
    long long qian=a+b;
    long long sinian[4]={366,365,365,365};
    long long yueburun[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    long long yuerun[12]={31,29,31,30,31,30,31,31,30,31,30,31};
    long long sibai=97*366+303*365;
    long long rsibai=100*366+300*365;
    while(q--){
        long long d;
        cin>>d;
        if(d<qian){
            string x="BC";
            if(d<a){
                long long tmp =d;
                long long nian=4713;
                long long si = 0;
                long long yue = 1;
                long long shier = 0;
                long long da = tmp/rsibai;
                nian-=da*400;
                tmp-=da*rsibai;
                while(tmp>=sinian[(si%4)]){
                    nian-=1;
                    tmp-=sinian[(si%4)];
                    si++;
                }
                if((4713-nian)%4==0){
                    while(tmp>=yuerun[shier%12]+yuerun[(shier+1)%12]+yuerun[(shier+2)%12]){
                        tmp-=yuerun[shier%12]+yuerun[(shier+1)%12]+yuerun[(shier+2)%12];
                        yue+=3;
                        shier+=3;
                    }
                    while(tmp>=yuerun[shier%12]){
                        tmp-=yuerun[shier%12];
                        yue++;
                        shier++;
                    }
                }else{
                    while(tmp>=yueburun[shier%12]+yueburun[(shier+1)%12]+yueburun[(shier+2)%12]){
                        tmp-=yueburun[shier%12]+yueburun[(shier+1)%12]+yueburun[(shier+2)%12];
                        yue+=3;
                        shier+=3;
                    }
                    while(tmp>=yueburun[shier%12]){
                        tmp-=yueburun[shier%12];
                        yue++;
                        shier++;
                    }
                }
                int ri = tmp+1;
                cout<<ri<<" "<<yue<<" "<<nian<<" "<<x<<endl;
            }else{
                long long tmp2=d-a;
                long long nian =1;
                long long si=1;
                long long yue=1;
                long long shier = 0;
                long long da = tmp2/rsibai;
                nian+=da*400;
                tmp2-=da*rsibai;
                while(tmp2>=sinian[si%4]){
                    nian+=1;
                    tmp2-=sinian[si%4];
                    si++;
                }
                if(nian%4==0){
                    while(tmp2>=yuerun[shier%12]){
                        tmp2-=yuerun[shier%12];
                        yue+=1;
                        shier++;
                    }
                }else{
                    while(tmp2>=yueburun[shier%12]){
                        tmp2-=yueburun[shier%12];
                        yue+=1;
                        shier++;
                    }
                }
                int ri = tmp2+1;
                cout<<ri<<" "<<yue<<" "<<nian<<" "<<endl;
            }
        }else{
            long long nian = 1582;
            long long tmp3 = d-qian;
            long long yue =10;
            long long yueji=9;
            long long ri = 15;
            if(tmp3>77){
                tmp3-=78;
                nian+=1;
                yue=1;
                yueji=0;
                ri=1;
                int da = tmp3/sibai;
                nian+=da*400;
                tmp3-=da*sibai;
                while(tmp3>=((nian%4==0&&nian%100!=0 || nian%400==0)?366:365)){
                    if(nian%4==0&&nian%100!=0 || nian%400==0){
                        tmp3-=366;
                        nian+=1;
                    }else{
                        tmp3-=365;
                        nian+=1;
                    }
                }
                while(tmp3>=((nian%4==0&&nian%100!=0 || nian%400==0)?yuerun[yueji%12]:yueburun[yueji%12])){
                    if(nian%4==0&&nian%100!=0 || nian%400==0){
                        tmp3-=yuerun[yueji%12];
                        yue+=1;
                        yueji+=1;
                        //cout<<yue<<1<<endl;
                    }else{
                        tmp3-=yueburun[yueji%12];
                        yue+=1;
                        yueji+=1;
                        //cout<<yue<<endl;
                    }
                }
                ri += tmp3;
                cout<<ri<<" "<<yue<<" "<<nian<<" "<<endl;
            }else{
                if(tmp3>16){
                    tmp3-=17;
                    yue++;
                    yueji++;
                    ri=1;
                    while(tmp3>=((nian%4==0&&nian%100!=0 || nian%400==0)?yuerun[yueji%12]:yueburun[yueji%12])){
                    if(nian%4==0&&nian%100!=0 || nian%400==0){
                        tmp3-=yuerun[yueji%12];
                        yue+=1;
                        yueji+=1;
                        //cout<<yue<<1<<endl;
                    }else{
                        tmp3-=yueburun[yueji%12];
                        yue+=1;
                        yueji+=1;
                        //cout<<yue<<endl;
                    }
                    }
                }
                ri += tmp3;
                cout<<ri<<" "<<yue<<" "<<nian<<" "<<endl;
            } 
        }
    }
    return 0;
}
