#include<stdio.h>
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
using namespace std ;
#define int long long 
int k,m,n; 




int fn( map<string,set<string>>batches,  int total,  int a, int b, int c,vector<vector<vector<pair<string,string>>>>& cls )
{

    set<string> s ;

    if(b-1>=0 && c-1>=0 && !cls[a][b-1][c-1].first.empty())
    {
       s.insert(cls[a][b-1][c-1].first);
    }

    if(b+1<m  && c+1<n && !cls[a][b+1][c+1].first.empty())
    {  
       s.insert(cls[a][b+1][c+1].first);
    }

    if(b-1>=0 && !cls[a][b-1][c].first.empty()) 
    {      
       s.insert(cls[a][b-1][c].first);
    }
    if(b+1<m  && !cls[a][b+1][c].first.empty()) 
    {            
       s.insert(cls[a][b+1][c].first);
    }

    if(c-1>=0 && !cls[a][b][c-1].first.empty())
    {            
        s.insert(cls[a][b][c-1].first);
    }

    if(c+1<n  && !cls[a][b][c+1].first.empty())
    {             
        s.insert(cls[a][b][c+1].first);
    }

    if(b-1>=0 && c+1<n && !cls[a][b-1][c+1].first.empty())
    {
        s.insert(cls[a][b-1][c+1].first);
    }

    if(b+1<m  && c-1>=0 && !cls[a][b+1][c-1].first.empty())
    {
       s.insert(cls[a][b+1][c-1].first);
    }
 
    for(auto it=s.begin();it!=s.end();it++)
    {
        total=total-batches[*it].size();
    }  



    return total ; 


 

}


bool issafe(vector<vector<pair<string,string>>> cls ,int a,int b,string batch)
{

    if(a+1<m && b+1<n)
    {
        if(!cls [a+1][b+1].first.empty() && cls[a+1][b+1].first==batch) {
            return false;
        }
    }

    
    if(a-1>=0 && b-1>=0)
    {
        if(!cls[a-1][b-1].first.empty() && cls[a-1][b-1].first==batch) {
            return false;
        }
    }

    if(a-1>=0 )
    {
        if(!cls[a-1][b].first.empty() && cls[a-1][b].first==batch) {
            return false;
        }
    }

    
    if(a-1>=0 && b+1<n)
    {
        if(!cls[a-1][b+1].first.empty() && cls[a-1][b+1].first==batch) 
        {
            return false;
        }
    }

    if(b+1<n)
    {
        if(!cls[a][b+1].first.empty() && cls[a][b+1].first==batch) 
        {
            return false;
        }
    } 


    if(a+1<m && b-1>=0)
    {
        if(!cls[a+1][b-1].first.empty() && cls[a+1][b-1].first==batch) 
        {
            return false;
        }
    }
   
    if(b-1>=0)
    {
        if(!cls[a][b-1].first.empty() && cls[a][b-1].first==batch)  
        {
            return false;
        }
    }

    if(a+1<m)
    {
        if(!cls[a+1][b].first.empty() && cls[a+1][b].first==batch) 
        { 
            return false;
        }
    }


   
    return true;


}







vector<int> find_mini_remaining_value( vector<vector<vector<pair<string,string>>>>& cls, map<string,set<string>>batches, set<pair<string,string>>&notAssigned, vector<vector<vector<int > > >& visited )
{

    vector<int> v ;

    int mini=INT_MAX;
    int cc, xx, yy; 
    int flag=0 ;  

    int total=notAssigned.size();

    for(int a=0;a<k;a++)
    {
        for(int b=0;b<m;b++)
        {
            for(int c=0;c<n;c++)
            {
                if(cls[a][b][c].first.empty() && visited[a][b][c]==-1)
                {

                    int count= fn(batches, total,  a,b,c,cls); 
                    if(count<mini)
                    {
                        flag=1; 
                        mini=count;
                        cc=a; 
                        xx=b; 
                        yy=c; 
                    }
                }
            }
        }
    }


    if(flag==0)
    {
        return v; 
    }
    else
    {
        v.push_back(cc); 
        v.push_back(xx); 
        v.push_back(yy) ; 
    }


    return v;
    
 
}

 
 
bool solvefn( vector<vector<vector<int > > >& visited,  vector<vector<vector<pair<string,string>>>>& cls, map<string,set<string>>&details,  set<pair<string,string>>&notAssigned)
{

    int z= notAssigned.size(); 

    if(z==0) 
    {
        return true;
    }


    vector<int>position  = find_mini_remaining_value(cls,details,notAssigned, visited);

    int a;
    int b;
    int c;

    if(position.size()==0) 
    {
        return false;
    }
    else
    {

        b=position[1];
        c=position[2];
        a=position[0]; 
       
        
        for(auto iterator =details.begin(); iterator!=details.end();iterator++)
        {
            if(cls[a][b][c].first.empty())
            {
                if(issafe(cls[a],b,c,iterator->first))
                {
                    if(iterator->second.size()>0)
                    {
                
                        string roll= *(iterator->second.begin());

                        cls[a][b][c]=make_pair(iterator->first,roll);

                        iterator->second.erase(iterator->second.begin());

                        notAssigned.erase(notAssigned.find(make_pair(iterator->first,roll)));
                        visited[a][b][c]=1;

                        bool kyaaagesafemila= solvefn(visited, cls,details,notAssigned); 
     
                        if(kyaaagesafemila) 
                        {
                            return true;
                        }
                        else
                        {
                            iterator->second.insert(roll);
                            cls[a][b][c].first.clear();
                            notAssigned.insert(make_pair(iterator->first,roll));
                            cls[a][b][c].second.clear();
                            
                            visited[a][b][c]=-1;
                        }
                    }
                }
            }
        }
    }

    visited[a][b][c]=1;
    if(solvefn(visited, cls,details,notAssigned)) 
    {
        return true;
    }
    else 
    {
        visited[a][b][c]=-1;
        return false;
    }


}


void printit( vector<vector<vector<pair<string,string> > > > cls)
{

    for(int a=0;a<k;a++)
    {
        for(int b=0;b<m;b++)
        {
            for(int c=0;c<n;c++)
            {
                if(cls[a][b][c].first.empty())
                {
                    cout<<"NIL NIL ";
                }
                else 
                cout<<cls[a][b][c].first<<" "<<cls[a][b][c].second<<" ";
            }

            cout<<endl ;
        }
    }
}


 
int32_t main()
{
    int t;
    cin>>t;
    while(t--)
    {

        vector<vector<vector<int > > > visited  ;


        map<string,set<string>> details ;

        cin>>k>>m>>n;

      

        int total_no_students;
        set<pair<string,string>> notAssigned;

        vector<vector<vector<pair<string,string> > > > cls (k,vector<vector<pair<string,string>>>(m,vector<pair<string,string>>(n)));


        cin>>total_no_students ;

        int kyaaagekamkarun =k*m*n;
        if(kyaaagekamkarun <total_no_students)
        {
            cout<<-1<<endl ;
            continue;
        }


        

        

        for(int i=0;i<total_no_students;i++)
        {
            string batch;
            string roll;

            cin>>batch>>roll;
            notAssigned.insert(make_pair(batch,roll));

            details[batch].insert(roll);
            

        }
 
       




        for(int a= 0 ; a< k; a++)
        {
            vector<vector<int>> v2; 
            for(int b= 0 ; b< m ; b++)
            { 
                std::vector<int> v1;
                for(int c=0 ; c<  n ; c++)
                {
                    v1.push_back(-1) ; 
                }
                v2.push_back(v1); 
 
            }
 
            visited.push_back(v2) ; 
        }


        bool kyasolnmila = solvefn(visited, cls,details,notAssigned);

        if(kyasolnmila) 
        {
            printit(cls); 
 
        }
        else 
        {
            cout<<"-1"<<endl ;
        }


    }


	return 0;
}