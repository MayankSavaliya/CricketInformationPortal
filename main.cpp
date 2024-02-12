#include<bits/stdc++.h>
#include "match.cpp"
using namespace std;

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    vector<Match> match;
    while(1){
        int x;
        cout<<"------------------------------------------------------------\n";
        cout<<"Choose An Option : \n";
        cout<<"1 : Add Match Information \n"<<"2 : Display specific Match Information\n"
            <<"3 : Display top 10 run scorer \n"<<"4 : Display top 10 bowler \n"<<
              "5 : For display Player Wise 3 Maximum Score \n"<<
              "6:  Display Player Wise 3 Best Bowler \n"<<
              "7 : Display Specific Player Batting Information \n"<<
              "8 : Display Specific Player Bowling Information \n"<<
              "9 : Exit \n";
        cin>>x;
        if(x==1){
            Match m;
            match.push_back(m);
        }
        else if(x==2){
            string dt,team1,team2;
            cout<<"Enter the date of the match\n";
            cin>>dt;
            lower(dt);
            cout<<"Enter the Name of the team1: \t";
            cin>>team1;
            cout<<"\n";
            cout<<"Enter the Name of the team2: \t";
            cin>>team2;
            cout<<'\n';
            lower(team1);
            lower(team2);
            vector<int> date=getdetails(dt);
            bool f=0;
            for(int i=0;i<match.size();i++){
                if(match[i].dt==date[0] && match[i].mn==date[1] && match[i].yr==date[2]){
                    if(team1==match[i].Name1 && team2==match[i].Name2){
                        DisplayMatch(match[i]); f=1;
                        break;
                    }
                    if(team2==match[i].Name1 && team1==match[i].Name2){
                        DisplayMatch(match[i]); f=1;
                        break;
                    }
                }
            }
            if(f==0) cout<<"Match Not Found \n";
        }
        else if(x==3){
            Displaytopbat(10);
        }
        else if(x==4){
            Displaytopbowl(10);
        }
        else if(x==5){
            for(auto it:bestbat){
                int count=0;
                cout<<"-------------------------------------------\n";
                cout<<"Player Name : - "<<it.second<<endl;
                cout<<"-------------------------------------------\n";
                cout<<"| Match Date          | Run Score         |\n";
                mergesort(bestbatting[it.second],0,bestbatting[it.second].size()-1);
                auto obj=bestbatting[it.second];
                for(auto it2:obj){
                    string dt=it2.second;
                    string run=to_string(it2.first.first);
                    while(dt.size()<=19){
                        dt.push_back(' ');
                    }
                    while(run.size()<=17){
                        run.push_back(' ');
                    }
                    run.push_back('|');
                    cout<<"| ";
                    cout<<dt<<"| "<<run<<endl;
                    if(count>=2) break;
                    count++;
                }   
            }
        }
        else if(x==6){
            for(auto it:bestbowl){
                int count=0;
                cout<<"-------------------------------------------\n";
                cout<<"Player Name : - "<<it.second<<endl;
                cout<<"-------------------------------------------\n";
                cout<<"| Match Date          | Wicket Taken      |\n";
                auto obj=bestbowling[it.second];
                for(auto it2:obj){
                    string dt=it2.second;
                    string wicket=to_string(it2.first.first);
                    while(dt.size()<=19){
                        dt.push_back(' ');
                    }
                    while(wicket.size()<=17){
                        wicket.push_back(' ');
                    }
                    wicket.push_back('|');
                    cout<<"| ";
                    cout<<dt<<"| "<<wicket<<endl;
                    if(count==2) break;
                    count++;
                }
                
            }
        }
        else if(x==7){
            string s;
            char x=getchar();
            getline(cin,s);
            displayInfobatsman(bestbatting[s],s);

        }
        else if(x==8){
            string s;
            char x=getchar();
            getline(cin,s);
            displayInfobowler(bestbowling[s],s);
        }
        else if(x==9){
            cout<<"Program Exit Successfully \n";
            break;
        }
        else{
            cout<<"Wrong Input\n"<<"Please Enter Input Again\n";
            break;
        }
    }

    return 0;
}