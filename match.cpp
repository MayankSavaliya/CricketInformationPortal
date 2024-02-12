#include<bits/stdc++.h>
#include "stats.cpp"

using namespace std;
void lower(string &s){
    for(int i=0;i<s.size();i++){
        if(s[i]>='A' && s[i]<='Z'){
            s[i]='a'+(s[i]-'A');
        }
    }
}
vector<int> getdetails(string &s){
    string temp="0";
    vector<int> ans;
    for(int i=0;i<s.size();i++){
        if(s[i]=='/'){
            ans.push_back(stoi(temp));
            temp="0";
        }
        else{
            temp.push_back(s[i]);
        }
    }
    ans.push_back(stoi(temp));
    return ans;
}
class Match{
    public:
    string date,Name1,Name2,TossWinnig,Toss,venue;
    int dt,mn,yr;
    map<string,vector<string>> PlayerNames;
    map<string,pair<int,int>> runs,wickets;
    queue<string> q;
    vector<string> tt;
    Match(){
        // cout<<"Enter the date of the match:"<<endl;
        cin>>date;
        // cout<<"Enter the Name of the First Team:"<<endl;
        cin>>Name1;
        // cout<<"Enter the Name of the Second Team:"<<endl;
        cin>>Name2;
        // cout<<"Enter the venue of the Match : ";
        cin>>venue;
        // cout<<'\n';
        // cout<<"Enter the Name of the Toss winning Team:"<<endl;
        cin>>TossWinnig;
        // cout<<"Enter What the team has chosen:"<<endl;
        cin>>Toss;
        lower(Name1);
        lower(Name2);
        lower(venue);
        lower(TossWinnig);
        lower(Toss);

        //For getting date,month and year
        vector<int> temp=getdetails(date);
        dt=temp[0];
        mn=temp[1];
        yr=temp[2];

        //First team batting
        char x=getchar();
        //Input for the playing 11 of Team1
        // cout<<"Enter the Playing 11 for the team "<<Name1<<endl;
        for(int i=0;i<=10;i++){
            string Name;
            getline(cin,Name);
            lower(Name);
            q.push(Name);
            PlayerNames[Name1].push_back(Name);
            TeamName[Name]=Name1;
        }
        while(q.size()){
            string ele=q.front();
            tt.push_back(ele);
            q.pop();
        }
        //Input for the playing 11 of Team2
        // cout<<"Enter the Playing 11 for the team "<<Name2<<endl;
        for(int i=0;i<=10;i++){
            string Name;
            getline(cin,Name);
            lower(Name);
            q.push(Name);
            PlayerNames[Name2].push_back(Name);
            TeamName[Name]=Name2;
        }
        while(q.size()){
            string ele=q.front();
            tt.push_back(ele);
            q.pop();
        }
        // x=getchar();
        if((TossWinnig==Name1 && Toss=="bowl") || (TossWinnig==Name2 && Toss=="bat")){
            swap(Name1,Name2);
        }


        //Details for the first Inning
        // cout<<"---------------------Details for the First Inning---------------------\n";
        // cout<<"Enter the batting details of the team "<<Name1<<endl;
        for(int i=0;i<11;i++){
            string temp;
            // cout<<"Enter the run scored by the player "<<PlayerNames[Name1][i]<<endl; 
            cin>>temp;
            pair<int,int> obj=runbowl(temp);
            runs[PlayerNames[Name1][i]].first=obj.first;
            runs[PlayerNames[Name1][i]].second=obj.second;
        }
        // cout<<"Enter the bowling details for the team "<<Name2<<endl;
        for(int i=0;i<11;i++){
            string temp;
            // cout<<"Enter the runs and wickets taken by the player "<<PlayerNames[Name2][i]<<endl;
            cin>>temp;
            pair<int,int> obj=runbowl(temp);
            wickets[PlayerNames[Name2][i]].first=obj.first;
            wickets[PlayerNames[Name2][i]].second=obj.second;
        }    


        //Details for the second Inning
        // cout<<"---------------------Details for the Second Inning---------------------\n";
        // cout<<"Enter the batting details of the team "<<Name2<<endl;
        for(int i=0;i<11;i++){
            string temp;
            // cout<<"Enter the run scored by the player "<<PlayerNames[Name2][i]<<endl;                
            cin>>temp;
            pair<int,int> obj=runbowl(temp);
            runs[PlayerNames[Name2][i]].first=obj.first;
            runs[PlayerNames[Name2][i]].second=obj.second;
        }
        // cout<<"Enter the bowling details for the team "<<Name2<<endl;
        for(int i=0;i<11;i++){
            string temp;
            // cout<<"Enter the runs and wickets taken by the player "<<PlayerNames[Name1][i]<<endl;
            cin>>temp;
            pair<int,int> obj=runbowl(temp);
            wickets[PlayerNames[Name1][i]].first=obj.first;
            wickets[PlayerNames[Name1][i]].second=obj.second;
        }    

        setdata(Name1,Name2,PlayerNames,runs,wickets,date);
        setdata(Name2,Name1,PlayerNames,runs,wickets,date);
    }
    void print(){
        cout<<"Playing 11 for Team "<<Name1<<endl;
        for(auto it:PlayerNames[Name1]){
            cout<<it<<endl;
        }
        cout<<endl;
        cout<<"Playing 11 for Team "<<Name2<<endl;
        for(auto it:PlayerNames[Name2]){
            cout<<it<<endl;
        }
    }
    void printruns(){
        for(auto it:PlayerNames[Name1]){
            cout<<runs[it].first<<" "<<runs[it].second<<endl;
        }
    }
    void printwickets(){
        for(auto it:PlayerNames[Name2]){
            cout<<wickets[it].first<<" "<<wickets[it].second<<endl;
        }
    }
    private:
    pair<int,int> runbowl(string &s){
        string temp1="0",temp2="0";
        int i=0;
        while(i<s.size() && s[i]!='('){
            temp1.push_back(s[i]);
            i++;
        }
        i++;
        while(s[i]!=')'){
            temp2.push_back(s[i]);
            i++;
        }
        int run=stoi(temp1);
        int bowl=stoi(temp2);
        return {run,bowl};
    }

};

void DisplayMatch(Match m){
    //Match stats
    cout<<"-----------------------Match Stats-----------------------\n";
    cout<<"--------------------"<<m.Name1<<" VS "<<m.Name2<<"--------------------\n";
    cout<<"Date : "<<m.date<<'\n';
    cout<<"---------------------------------------------"<<endl;

    //First Inning 
    cout<<"First Innings: Bating "<<m.Name1<<"\n";
    cout<<"Player Name \t\t Run \t\t Ball \n";
    for(auto it:m.PlayerNames[m.Name1]){
        string temp=it;
        string temp2=to_string(m.runs[it].first);
        while(temp2.size()<=9){
            temp2.push_back(' ');
        }
        temp2.push_back('|');
        while(temp.size()<=19){
            temp.push_back(' ');
        }
        temp.push_back('|');
        cout<<temp<<" "<<temp2<<" "<<m.runs[it].second<<endl;
    }
    cout<<"---------------------------------------------"<<endl;
    cout<<"First Innings: Bowling "<<m.Name2<<"\n";
    cout<<"Player Name \t\t wicket \t\t over \n";
    for(auto it:m.PlayerNames[m.Name2]){
        string temp=it;
        string temp2=to_string(m.wickets[it].first);
        while(temp2.size()<=12){
            temp2.push_back(' ');
        }
        temp2.push_back('|');
        while(temp.size()<=19){
            temp.push_back(' ');
        }
        temp.push_back('|');
        cout<<temp<<" "<<temp2<<" "<<m.wickets[it].second<<endl;
    }
    

    //Second Inning
    cout<<"---------------------------------------------"<<endl;
    cout<<"Second Innings: Bating "<<m.Name2<<"\n";
    cout<<"Player Name \t\t Run \t\t Ball \n";
    for(auto it:m.PlayerNames[m.Name2]){
        string temp=it;
        string temp2=to_string(m.runs[it].first);
        while(temp2.size()<=9){
            temp2.push_back(' ');
        }
        while(temp.size()<=19){
            temp.push_back(' ');
        }
        temp2.push_back('|');
        temp.push_back('|');
        cout<<temp<<" "<<temp2<<" "<<m.runs[it].second<<endl;
    }
    cout<<"---------------------------------------------"<<endl;
    cout<<"First Innings: Bowling "<<m.Name1<<"\n";
    cout<<"Player Name \t\t wicket \t\t over \n";
    for(auto it:m.PlayerNames[m.Name1]){
        string temp=it;
        string temp2=to_string(m.wickets[it].first);
        while(temp2.size()<=12){
            temp2.push_back(' ');
        }
        while(temp.size()<=19){
            temp.push_back(' ');
        }
        temp2.push_back('|');
        temp.push_back('|');
        cout<<temp<<" "<<temp2<<" "<<m.wickets[it].second<<endl;
    }
}

void Displaytopbat(int x){
    int count=0;
    cout<<"\n";
    cout<<"---------------------------------------------"<<endl;
    cout<<"|              Top "<<x<<" Batsman               |"<<endl;
    cout<<"---------------------------------------------\n"<<endl;

    cout<<"Player Name \t\t Run \t\t Strike Rate \n";
    for(auto it:bestbat){
        string temp=it.second;
        string temp2=to_string(max(0,-1*(it.first.first-(int)1e8)));
        while(temp2.size()<=9){
            temp2.push_back(' ');
        }
        temp2.push_back('|');
        while(temp.size()<=19){
            temp.push_back(' ');
        }
        temp.push_back('|');
        cout<<temp<<" "<<temp2<<" "<<max(0.0f,-100*(it.first.second-1000))<<endl;
        if(count==x){
            break;
        }
        count++;
    }
    cout<<"\n";
}
void Displaytopbowl(int x){
    int count=0;
    cout<<"\n";
    cout<<"---------------------------------------------"<<endl;
    cout<<"|                Top "<<x<<" Bowler              |"<<endl;
    cout<<"---------------------------------------------\n"<<endl;

    cout<<"Player Name \t\t Wickets \t Overs \n";
    for(auto it:bestbowl){
        string temp=it.second;
        string temp2=to_string(max(0,-1*(it.first.first-10000)));
        while(temp2.size()<=9){
            temp2.push_back(' ');
        }
        temp2.push_back('|');
        while(temp.size()<=19){
            temp.push_back(' ');
        }
        temp.push_back('|');
        cout<<temp<<" "<<temp2<<" "<<it.first.second<<endl;
        if(count==x){
            break;
        }
        count++;
    }
    cout<<"\n";
}

void displayInfobatsman(vector<pair<pair<int,int>,string>> v,string name){
    int Inning=v.size(),truns=0,tballs=0;
    for(auto it:v){
        if(it.first.first==0 && it.first.second==0) Inning--;
        truns+=it.first.first;
        tballs+=it.first.second;
    }
    cout<<"---------------------------------------------"<<endl;
    cout<<"           ----------------------            "<<endl;
    cout<<"           |                    |            "<<endl;         
    cout<<"           |                    |            "<<endl;         
    cout<<"           |                    |            "<<endl;         
    cout<<"           |    "<<name<<"     |            "<<endl;         
    cout<<"           |                    |            "<<endl;         
    cout<<"           |                    |            "<<endl;         
    cout<<"           |                    |            "<<endl;         
    cout<<"           ----------------------            "<<endl;
    cout<<"           Team    : -  "<<TeamName[name]<<"\n";
    cout<<"           Matches : -  "<<v.size()<<"\n";
    cout<<"           Innings : -  "<<Inning<<"\n";
    cout<<"           Runs    : -  "<<truns<<"\n";
    cout<<"           Balls   : -  "<<tballs<<"\n";
    cout<<"---------------------------------------------"<<endl;
}
void displayInfobowler(vector<pair<pair<int,int>,string>> v,string name){
    int Inning=v.size(),twickets=0,tovers=0;
    for(auto it:v){
        if(it.first.first==0 && it.first.second==0) Inning--;
        twickets+=it.first.first;
        tovers+=it.first.second;
    }
    cout<<"---------------------------------------------"<<endl;
    cout<<"           ----------------------            "<<endl;
    cout<<"           |                    |            "<<endl;         
    cout<<"           |                    |            "<<endl;         
    cout<<"           |                    |            "<<endl;         
    cout<<"           |    "<<name<<"     |            "<<endl;         
    cout<<"           |                    |            "<<endl;         
    cout<<"           |                    |            "<<endl;         
    cout<<"           |                    |            "<<endl;         
    cout<<"           ----------------------            "<<endl;
    cout<<"           Team    : -  "<<TeamName[name]<<"\n";
    cout<<"           Matches : -  "<<v.size()<<"\n";
    cout<<"           Innings : -  "<<Inning<<"\n";
    cout<<"           Wickets : -  "<<twickets<<"\n";
    cout<<"           Ovres   : -  "<<tovers<<"\n";
    cout<<"---------------------------------------------"<<endl;
}
