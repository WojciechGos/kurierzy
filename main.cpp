#include <iostream>
#include <cmath>
#include <map>
#include <vector>


using namespace std;

const int TREE_SIZE = 1e6 + 1e5;
const int MAX = 5e5+2;

int n, m, a, b, k, r, R, range;
int p[MAX];
int s[MAX];
pair<int,int> tree[TREE_SIZE];
map<int,vector<int>> pos;
vector<int>::iterator it;

int normal_search(const int& f, const int& value, bool is_lower_q){
    int previous = 0;
    for(auto& it: pos[value]){
        
        if(it > f && is_lower_q == true){
            cout << "prev: " <<  previous << endl;
            return s[previous];
        }
        previous = it;
    }
}

int binary_search(const int& f, const int& value, bool is_lower_q){

    int start = 0, end = pos[value].size(), mid, tmp;

    while(start <= end){
        mid = (start + end) / 2;
        tmp = pos[value][mid];


        if(tmp == f){                
            break;
        }else if(tmp > f){
            end = mid - 1;
        }else if(tmp < f){
            start = mid + 1;
        }
    }
    if(pos[value].size() <= mid){
        mid = pos[value].size() - 1;
    }
    if(pos[value][mid] < f && is_lower_q == true){
         cout << value << " a " << f << " index: "<< pos[value][mid] << " am " << s[pos[value][mid]] + 1 <<  endl;
        return s[pos[value][mid]] + 1;
    }
    cout << value << " a " << f << " index: "<< pos[value][mid] << " am " << s[pos[value][mid]] <<  endl;
    return s[pos[value][mid]];
}

pair<int,int> assaign_candidate(const pair<int,int>& a, const pair<int,int>& b){
    if(a.first == b.first){
        return {a.first, a.second + b.second};
    }else if(a.second > b.second){
        return {a.first, a.second - b.second};
    }else{
        return {b.first, b.second - a.second};
    }
}

void create_chain_of_count(const int& value, const int& index){
    pos[value].push_back(index);

    if(pos[value].size() != 1){
        it = pos[value].end();
        it -= 2;
        s[index] = s[*it] + 1;
    }else{
        s[index]++;
    }  
}

vector<int> q;
void query(int source, int start_range, int end_range, int l, int r){
    if(l <= start_range && r >= end_range){
        q.push_back(source);
        return;
    }
    if(l > end_range || r < start_range){
        return;
    }
    int mid = (start_range + end_range) / 2;
    query(source*2, start_range, mid, l, r);
    query(source*2+1, mid+1, end_range, l, r);
}

void create_tree(){
    for(int i=1; i<=n; ++i){
        tree[i+r] = {p[i], 1};
    }
    for(int i=r; i>=1; --i){
        tree[i] = assaign_candidate(tree[2*i], tree[2*i+1]);
    }
}

void solve(){
    cin >> n >> m;
    k = ceil(log2(n));
    r = pow(2,k) - 1;
    R = pow(2, ceil(log(n)/log(2)));
    for(int i=1; i<=n; ++i){
        cin >> p[i];
        create_chain_of_count(p[i], i);  
    }

    create_tree();
    // for(int i=n+r; i>=1; --i){
    //     cout << "p: " << i << "   | " << tree[i].first << " " << tree[i].second << endl;
    // }
    bool is_contain_leader = false;
    for(int i=1; i<=m; ++i){
        cin >> a >> b;
        range = b - (a-1);
        query(1, 1, R, a, b);
        is_contain_leader = false;
        // cout << "A " << a << " | B " << b << endl; 
        for(auto& it: q){
            // cout << it << endl;
            if(tree[it].second > 0){
                // cout << "v " << tree[it].first << " B:  "  << b << "  r : ";
                // cout << tree[it].first << " bs " << binary_search(a, tree[it].first) << endl;
                // (binary_search(a,tree[it].first, true)
                if( range/2  < binary_search(b, tree[it].first, false) - (normal_search(a, tree[it].first, true))){
                    cout << tree[it].first << endl;
                    is_contain_leader = true;
                    break;
                }
                
            }
        }
        if(is_contain_leader == false){
            cout << 0 << endl;
        }
        q.clear();
        // cout << endl;

    }

}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
