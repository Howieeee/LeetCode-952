class DSU{
  public:
    DSU(int size):p(size){
        
        for(int i=0;i<size;i++)
            p[i] = i;
    }
    
    void Union(int x, int y){
        p[Find(x)] = p[Find(y)];
    }
    
    int Find(int x){
        if(p[x] != x)//若4對應到的不是4
            p[x] = Find(p[x]);//就去找4目前對應到的值 他的頭 ex p[4] = 2,  f[4] = find(2) 
        
        return p[x];//找到最後的頭
    }
    vector<int> get_p(){
        return this->p;
    }
    
 private:
    vector<int> p;//某個值 對應到的頭
    
};

class Solution {
public:
    
    int largestComponentSize(vector<int>& nums) {
        int max_n = 0;
        for(auto n:nums)
            max_n = max(max_n,n);
        
        DSU dsu(max_n+1); // vector要有n+1個位置 (從1開始)
        
        for(auto num:nums){//找每個數的factors
            int end = sqrt(num); //找到num的開根號為止
            for(int i=2;i<=end;i++){
                if(num%i==0){//是因數
                    dsu.Union(num,i);
                    dsu.Union(num,num/i);
                }
            }
        }
        unordered_map<int,int> um;
        int max_len = 0;
        for(auto num:nums){
            ++um[dsu.Find(num)];
        }
        //cout << dsu.Find(4) << " " << dsu.Find(6) << endl;
        for(auto u:um){
            // cout << u.first << " " << u.second << endl;
            // cout << dsu.Find(u.first) << endl;
            max_len = max(max_len,u.second);
        }
        // vector<int> temp = dsu.get_p();
        // for(int i=0;i<temp.size();i++){
        //     cout << "i=" << i << " " <<temp[i] << endl;
        // }
        // //cout << max_n << endl;
        
        return max_len;
    }
};


/*
    4 ,i=2  union(4,2)  p[find(4)] = p[find(2)] , p[4] = p[2] = 2,
    6, i=2  union(6,2)  p[find(6)] = p[find(2)] , p[6] = 2, 6的源頭是2, p[f6] = p[f3] , p[2] = p[3] ,=3
    


*/
