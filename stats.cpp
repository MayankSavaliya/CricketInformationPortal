#include<bits/stdc++.h>
using namespace std;
void merge(vector<pair<pair<int,int>,string>> &v,int l,int r,int mid){
    vector<pair<pair<int,int>,string>> temp1;
    int i=l,j=mid+1;
    while(i<=mid && j<=r){
        if(v[i].first.first>v[j].first.first){
            temp1.push_back(v[i]);
            i++;
        }
        else if(v[i].first.first==v[j].first.first){
            if(v[i].first.second<v[j].first.second){
                temp1.push_back(v[i]);
                i++;
            }
            else{
                temp1.push_back(v[j]);
                j++;
            }
        }
        else{
            temp1.push_back(v[j]);
            j++;
        }
    }
    while(i<=mid){
      temp1.push_back(v[i]);
      i++;
    }
    while(j<=r){
      temp1.push_back(v[j]);
      j++;
    }
    for(int i=0;i<temp1.size();i++){
        v[i+l]=temp1[i];
    }
}
void mergesort(vector<pair<pair<int,int>,string>> &v,int l,int r){
    if(l>=r) return ;
    int mid=(l+r)/2;
    mergesort(v,l,mid);
    mergesort(v,mid+1,r);
    merge(v,l,r,mid);
}
map<string,pair<int,int>> batsman,bowler;
set<pair<pair<int,float>,string>> bestbat,bestbowl;
map<string,vector<pair<pair<int,int>,string>>> bestbatting,bestbowling;
map<string,string> TeamName;
void setdata(string team1,string team2,map<string,vector<string>> &PlayerNames,map<string,pair<int,int>> &runs,map<string,pair<int,int>> &wickets,string &date){
    for(auto it:PlayerNames[team1]){
        int x=(int)1e8-batsman[it].first;
        int y=batsman[it].second;
        float z=100*batsman[it].first/max(1.0f,(float)batsman[it].second);
        for(auto it2:bestbat){
            if(it2.second==it){
                bestbat.erase(it2);
                break;
            }
        }
        bestbatting[it].push_back({{runs[it].first,runs[it].second},date});
        batsman[it].first+=runs[it].first;
        batsman[it].second+=runs[it].second;
        z=1000-batsman[it].first/max(1.0f,(float)batsman[it].second);
        auto ob=make_pair(make_pair((int)1e8-batsman[it].first,z),it);
        bestbat.insert(ob);
    }
    for(auto it:PlayerNames[team2]){
       int x=10000-bowler[it].first;
        int  y=bowler[it].second;
        for(auto it2:bestbowl){
            if(it2.second==it){
                bestbowl.erase(it2);
                break;
            }
        }
        bestbowling[it].push_back({{wickets[it].first,wickets[it].second},date});
        bowler[it].first+=wickets[it].first;
        bowler[it].second+=wickets[it].second;
        auto ob=make_pair(make_pair(10000-bowler[it].first,max(0,bowler[it].second)),it);
        bestbowl.insert(ob);
    }
}
