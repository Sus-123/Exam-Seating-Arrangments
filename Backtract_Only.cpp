#include<bits/stdc++.h>
using namespace std ; 
int m , n; 


 
bool issafe(string batch, int k , int x,int y,vector<vector<vector<string>>>& cls )
{
    if((x-1 >=0) and cls[k][x-1][y]==batch) //up
    {
        return false ;  
 
    }   
     
 
    if((y-1 >=0) and cls[k][x][y-1]==batch) //left 
    {
        return false ; 
    }
 
    if((y+1 <n ) and cls[k][x][y+1]==batch) //right
    {   
        return false ;  
 
    }
 
    if(x+1 <m and cls[k][x+1][y]==batch) //beyond 
    {    
        return false ; 
    }
 
 
    if(x-1>=0 and y-1 >=0 and cls[k][x-1][y-1]==batch) // diagonal left up
    {
        // if(x==3 and y==0 and k==0)
        // cout<<" "<<"5st ";
        return false ; 
 
    }
 
    if(x-1>=0 and y+1 < n and cls[k][x-1][y+1]==batch) //diagonal right up
    {
        // if(x==3 and y==0 and k==0)
        // cout<<" "<<"6st ";
        return false ; 
 
    }
 
    if(x+1< m and y-1 >=0 and cls[k][x+1][y-1]==batch) //diagonal left btm
    {
        // if(x==3 and y==0 and k==0)
        // cout<<" "<<"7st ";
        return false ; 
 
    }
 
    if(x+1< m  and y+1 < n  and cls[k][x+1][y+1]==batch) //diagonal right btm
    {
        // if(x==3 and y==0 and k==0)
        // cout<<" "<<"8st ";
        return false ; 
 
    }
 
 
    return true ; 
    
}
 
 
 
bool fn(map<string,int >& mp , int total_no_classes , int c, int x, int y, int total_student, vector<vector<vector<string>>>& cls )
{
 
    if(total_student == 0)
    {
        return true ;  
    } 
 
 
    if(y==n)
    {
        y=0; 
        x=x+1;  
 
    }
 
 
    if( x == m )
    {
       x=0 ; 
       c=c+1;   
    }
    
 
    if(c==total_no_classes)
    {
        return false ; 
    }

 

    for(auto i : mp)  
    {  
        string batch= i.first ; 
        int kitna_bacha= i.second ; 
        if(kitna_bacha != 0) 
        {
            if(issafe(batch, c, x, y, cls))
            {
                cls[c][x][y]=batch ;  
                mp[batch]--  ; 

                bool kyaaagesafemila = fn(mp, total_no_classes , c, x, y+1 ,total_student-1,  cls) ; 
                if(kyaaagesafemila)
                {
                    return true  ; 
                }  
 
                cls[c][x][y]= "NIL" ;   
                mp[batch]++;     
            }
           
        }
    }
 
    return fn(mp, total_no_classes , c, x, y+1 ,total_student,  cls) ;
   
}
 
 
 
 
int main()
{
    int t; 
    cin>>t; 
    while(t--)
    {
        // get_roll.clear() ; 
        // get_roll_real.clear() ;
        // classes.clear() ; 
        // rolls.clear(); 
        // mp_print.clear() ; 
        // mapped_class.clear(); 

        map<string, bool> visited ;    
        map<string, vector<string>> get_roll_real ;
        map<string, vector<string>> get_roll ;


        map<string , int > mp ;     

 
 
        //take inputs :
       
        int total_no_classes; 
        int total_student ; 
        cin>>total_no_classes>>m>>n ;  
        cin>>total_student ; 

       
        for (int i = 0; i < total_student; ++i)
        {
            string batch, roll ; 
            cin>>batch>>roll ; 
    
            mp[batch]++ ; 
            get_roll[batch].push_back(roll);  
           
            visited[roll]=false ; 
 
        }
 

        // int cnt=0 ; 
 
        // // for(auto i : mp)
        // // {
        // //     classes.push_back(i.first) ; 
        // //     mapped_class[i.first]= cnt++ ; 
        // // } 
 
 
        // map<int, int> class_no;
        // map<int , string> mp_print; 
 
        // for(auto i : mp)
        // {
        //     string btc= i.first ; 
        //     int cnt= i.second ; 
        //     int int_val= mapped_class[btc]; 
 
        //     // class_no[int_val]= cnt ;  
        //     mp_print[int_val]=btc ; 
 
        // } 
 
 
 
 
        vector<vector<vector<string>>> cls ; 
        // int cls[10][10][10] ;  
        for(int a= 0 ; a< total_no_classes ; a++)
        {
            vector<vector<string>> v2; 
            for(int b= 0 ; b< m ; b++)
            { 
                std::vector<string> v1;
                for(int c=0 ; c<  n ; c++)
                {
                    v1.push_back("NIL") ; 
                }
                v2.push_back(v1); 
 
            }
 
            cls.push_back(v2) ; 
        }
 
      
        // // sort(classes.begin(), classes.end()) ; 
        // sort(rolls.begin() , rolls.end()) ;   
 
 
 
 
        for(auto rr : get_roll)
        {
            vector<string> v= rr.second; 
            sort(v.begin(), v.end()) ; 
            get_roll_real[rr.first]= v;   
 
        } 
 
       bool res= fn(mp ,total_no_classes, 0, 0, 0,total_student, cls) ;
       if(!res)
       {
           cout<<"-1"<<endl ; 
       } 
       else
       {
            for (int a = 0; a <cls.size()  ; a++)
            {
                for(int b= 0 ; b< cls[a].size() ; b++)
                { 
                    for(int p=0 ; p<cls[a][b].size() ; p++)
                    {
                        string batch = cls[a][b][p];
                        if(batch=="NIL")
                        {
                            cout<<"NIL "<<"NIL " ; 
                        }
                        else
                        {
                            vector<string> v= get_roll_real[batch];  
                            for(auto Rr : v)
                            {
                                if(!visited[Rr])
                                {
                                    visited[Rr]=true ; 
                                    cout<<batch<<" "<<Rr<<" " ; 
                                    break ;  
                                }
                            }
                        }
                        
                    }
                    cout<<endl ;
                }
            }  
        }
    }


}