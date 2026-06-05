using ll = long long;
class Solution {
private:
ll memo1[16][2][2];
ll memo2[16][2][2][3][10][10];
public:
    long long totalWaviness(long long num1, long long num2) {
       string val1 = to_string(num1);
       string val2 = to_string(num2);
       int len_diff = val2.length()-val1.length();
       string zero="";
       for(int k=1;k<=len_diff;k++) zero+='0';
       val1=zero+val1;
       memset(memo1,-1,sizeof memo1);
       memset(memo2,-1,sizeof memo2);
       return rec2(0,1,1,0,0,0,val1,val2);

    }
    ll rec2(int i,int tlo,int thi,int len_sofar,int prev,int prev_prev,string &num1,string &num2){
        if(i==num2.length()){
            return 0;
        }
        if(memo2[i][tlo][thi][len_sofar][prev][prev_prev]!=-1){
            return memo2[i][tlo][thi][len_sofar][prev][prev_prev];
        }
        int start = (tlo==1?num1[i]-'0':0);
        int end = (thi==1?num2[i]-'0':9);
        ll count=0;
        ll contri=0;
        for(int d=start;d<=end;d++){
            int ntlo=0;
            int nthi=0;
            int nlen_sofar=len_sofar;
            if(tlo==1 && d==start){
                ntlo=1;
            }
            if(thi==1 && d==end){
                nthi=1;
            }
            if(len_sofar==0 && d!=0){
                nlen_sofar=1;
            }
            if(len_sofar==1){
                nlen_sofar=2;
            }
            if(len_sofar==2 && ((prev>prev_prev && prev>d) || (prev<prev_prev && prev<d))){
                // cout<<"index: "<<i<<", ntlo: "<<ntlo<<", nthi: "<<nthi<<", possible number count: "<<rec1(i+1,ntlo,nthi,num1,num2)<<'\n';
                contri+=rec1(i+1,ntlo,nthi,num1,num2);
            }
            count+=rec2(i+1,ntlo,nthi,nlen_sofar,d,prev,num1,num2);
        }
        count+=contri;
        return memo2[i][tlo][thi][len_sofar][prev][prev_prev]=count;
    }
    //Find how many numbers are possible starting from this ith index
    //onwards with the given tlo & thi  
    ll rec1(int i,int tlo, int thi,string &num1,string &num2 ){
        if(i==num1.length()){
            return 1;
        }
        if(memo1[i][tlo][thi]!=-1){
            return memo1[i][tlo][thi];
        }
        int start = (tlo==1?num1[i]-'0':0);
        int end = (thi==1?num2[i]-'0':9);
        ll count=0;
        for(int d=start;d<=end;d++){
            int ntlo=0;
            int nthi=0;
            if(tlo==1 && d==start){
                ntlo=1;
            }
            if(thi==1 && d==end){
                nthi=1;
            }
            count+=rec1(i+1,ntlo,nthi,num1,num2);
        }
        return memo1[i][tlo][thi]=count;
    }
};