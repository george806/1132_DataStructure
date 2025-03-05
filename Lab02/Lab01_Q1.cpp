class Solution {
public:
    int findLucky(vector<int>& arr) {
        int x,result=-1;
        for(int i=0;i<=arr.size()-1;i++){
            x=0;
            for(int j=0;j<=arr.size()-1;j++){
                if(arr[i]==arr[j])
                    x++;
            }
            if(x==arr[i]&&arr[i]>result)
                result=arr[i];
        }
        return result;
    }
};
