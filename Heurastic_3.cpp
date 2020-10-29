#include<bits/stdc++.h>
using namespace std;
int k,m,n;
 struct cordinate
{
    int kk,mm,nn;
    int mrv;
    int mcv;
};

bool findit(cordinate & x, cordinate & y)
{
    return (x.mrv > y.mrv) || ((x.mrv == y.mrv) && (x.mcv < y.mcv)) || ((x.mcv == y.mcv) && (x.mrv == y.mrv) && (x.kk > y.kk)) || ((x.mcv == y.mcv) &&(x.mrv == y.mrv)&&(x.kk == y.kk)&&(x.mm > y.mm)) || ((x.mcv == y.mcv) && (x.mrv == y.mrv)&&(x.kk == y.kk)&&(x.mm == y.mm)&&(x.nn > y.nn));
}
struct combi
{
    string batch;
    string roll;
};
bool issafe(vector<vector<vector<combi>>>&cls , int c, int x, int y, string batch)
{
    int i=c; 
    int j=x; 
    int h=y ; 


    if(j+1<m and cls[i][j+1][h].batch == batch)
        return false ; 
    
    if(h-1>=0  and cls[i][j][h-1].batch == batch)
        return false ; 
    

    if(h+1<n and  cls[i][j][h+1].batch == batch)
       return false ; 
    
    if(j+1<m && h+1<n and cls[i][j+1][h+1].batch == batch )
        return false ; 


    if(j-1>=0  and cls[i][j-1][h].batch == batch)
        return false ; 


    
    if(j+1<m && h-1>=0 and cls[i][j+1][h-1].batch == batch )
        return false ; 


    
    if(j-1>=0 && h-1>=0 and cls[i][j-1][h-1].batch == batch )
        return false ; 


    if(j-1>=0 && h+1<n  and cls[i][j-1][h+1].batch == batch )
        return false ; 


    return true;


}
 
struct lestvalued
{
	string batch;
    string roll;
	int lcv; 
};

int calculate_mcv( vector<vector<vector<combi>>>& cls,  int c , int x, int y )
{
    int i= c; 
    int j= x; 
    int h= y; 

    int cnt =0;


    if(j+1<m and  h+1<n and cls[i][j+1][h+1].batch == "NIL")
    {
       cnt++ ; 
    }


    if(h+1<n and cls[i][j][h+1].batch == "NIL" )
    {
        cnt++ ; 
    }
   
    if(j+1<m  and cls[i][j+1][h].batch == "NIL")
    {
        cnt++ ; 
    }


    if(j-1>=0 && h-1>=0 and cls[i][j-1][h-1].batch == "NIL")
    {
        cnt++ ; 
    }


    if(j+1<m and  h-1>=0 and cls[i][j+1][h-1].batch == "NIL" )
    {
        cnt++ ; 
    }

    if(j-1>=0 and  h+1<n and cls[i][j-1][h+1].batch == "NIL")
    {
        cnt++ ; 
    }


    if(h-1>=0 and cls[i][j][h-1].batch == "NIL")
    {
       cnt ++; 
    }
   
    if(j-1>=0 and cls[i][j-1][h].batch == "NIL")
    {
        cnt ++; 
    }

    return cnt ;


}

 

struct SortLeastValue
{
	bool operator()
    (lestvalued a,lestvalued b)
    {
		return a.lcv < b.lcv;
	}
};
 



int dummy(vector<vector<vector<combi>>>&cls,  int i, int j , int kh ,   map< string, priority_queue<string,vector<string>,greater<>>> &students )
{

    int cnt =0;
    for(auto Xx: students)
    {
        if(issafe(cls,i,j,kh,Xx.first)) 
        {
            cnt=cnt+Xx.second.size(); 
        }
    }

    return cnt ; 

}

int calculate2(vector<vector<vector<combi>>>&cls, int i, int j, int kh,   map< string, priority_queue<string,vector<string>,greater<>>> &students    )
{

	int ans=0;

    if(j+1<m and cls[i][j+1][kh].batch == "NIL")
    {
        int z= dummy(cls,i, j+1, kh,  students); 
        ans= ans+z ;
        
    } 

    if(kh+1<n and cls[i][j][kh+1].batch == "NIL")
    {
       int z= dummy(cls,i, j, kh+1,  students); 
       ans= ans+z ;
    }

    if( kh+1<n and j+1<m  and cls[i][j+1][kh+1].batch == "NIL" )
    {
        int z= dummy(cls,i, j+1, kh+1,  students); 
        ans= ans+z ;
    }

    

    if( kh-1>=0 and j+1<m  and cls[i][j+1][kh-1].batch == "NIL")
    {
        int z= dummy(cls,i, j+1, kh-1,  students); 
        ans= ans+z ;
    }

    if(kh-1>=0 and cls[i][j][kh-1].batch == "NIL")
    {
        int z= dummy(cls,i, j, kh-1,  students); 
        ans= ans+z ;
    }

    if(kh+1<n and j-1>=0  and cls[i][j-1][kh+1].batch == "NIL")
    {
        int z= dummy(cls,i, j-1, kh+1,  students); 
        ans= ans+z ;
    }
    return ans;

    if( kh-1>=0 and j-1>=0  and cls[i][j-1][kh-1].batch == "NIL")
    {
        int z= dummy(cls,i, j-1, kh-1,  students); 
        ans= ans+z ;
    }

    if(j-1>=0 and cls[i][j-1][kh].batch == "NIL")
    {
        int z= dummy(cls,i, j-1, kh,  students); 
        ans= ans+z ;
    }

}

struct sortitagain 
{
    bool operator()
    (cordinate x,cordinate y)
    {
        return findit(x,y); 
    }

};




void fn1(map< string,priority_queue<string,vector<string>,greater<> > >& stds,vector<vector<vector<combi>>>& cls, cordinate p, priority_queue<lestvalued,vector<lestvalued>,SortLeastValue>& TempStudents)
{

    for(auto it : stds)
    {
        if(stds[it.first].empty())
        {
            continue;
        }
        if(cls[p.kk][p.mm][p.nn].batch == "NIL")
        {
            if(issafe(cls,p.kk,p.mm,p.nn,it.first))
            {
                string roll = stds[it.first].top(); 
                stds[it.first].pop();  
                cls[p.kk][p.mm][p.nn].batch = it.first;
                cls[p.kk][p.mm][p.nn].roll = roll;
                int z=calculate2(cls, p.kk,p.mm,p.nn, stds) ; 

                lestvalued stt;
                stt.batch=it.first ; 
                stt.roll=roll; 
                stt.lcv=z; 
                TempStudents.push(stt);

                cls[p.kk][p.mm][p.nn].roll = "NIL";
                cls[p.kk][p.mm][p.nn].batch = "NIL";
                stds[it.first].push(roll);

            }
        }
    }


}


lestvalued fn33(vector<cordinate>& temp_v, priority_queue<cordinate,vector<cordinate>,sortitagain>& temp,  int& total_students,   priority_queue<lestvalued,vector<lestvalued>,SortLeastValue>& TempStudents, map< string,priority_queue<string,vector<string>,greater<> > >& stds, cordinate p ,  vector<vector<vector<combi>>>& cls, vector<cordinate>& vec )
{

    lestvalued studenttempp = TempStudents.top();
    TempStudents.pop();

    stds[studenttempp.batch].pop();
    cls[p.kk][p.mm][p.nn].batch = studenttempp.batch;
    cls[p.kk][p.mm][p.nn].roll = studenttempp.roll;

    for(cordinate iterator : vec)
    {
        if(iterator.kk == p.kk)
        {
            if( iterator.mm == p.mm)
                if(iterator.nn == p.nn)
                    continue;
        }

        int upv =0;
        for(auto iterator2 : stds)
        {
            if(issafe(cls,iterator.kk,iterator.mm,iterator.nn,iterator2.first))
            {
                upv= upv+(iterator2.second).size();
            }
        }

        cordinate iite = iterator;
        iite.mrv = upv;
        iite.mcv = calculate_mcv( cls,  iterator.kk,iterator.mm,iterator.nn);
        temp_v.push_back(iite);
        temp.push(iite);
        

    }

    return studenttempp ; 


} 

bool checkvalidity2(vector<vector<pair<string,string>>> cls ,int a,int b,string batch)
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


bool solvefn(map< string,priority_queue<string,vector<string>,greater<> > > stds, vector<vector<vector<combi>>>& cls,  priority_queue<cordinate,vector<cordinate>,sortitagain> pos, vector<cordinate>vec,  int total_students)
{
    if(total_students==0)
    {
        return true;
    }
    if(vec.size() < total_students)
    {
        return false;
    }

    while(!pos.empty())
    {
        vector<cordinate>Myvec ;
        cordinate p = pos.top();    
        priority_queue<lestvalued,vector<lestvalued>,SortLeastValue> TempStudents ; 
        fn1(stds, cls, p, TempStudents ); 
        while(!TempStudents.empty())
        {
            vector<cordinate>temp_v;
            priority_queue<cordinate,vector<cordinate>,sortitagain> temp ; 

            lestvalued temp_stt= fn33(temp_v, temp,   total_students, TempStudents, stds, p, cls,vec );
            if(solvefn(stds, cls,temp,temp_v,total_students-1))
            {
				return true;
			}
            else
            {
				cls[p.kk][p.mm][p.nn].batch = "NIL";
				cls[p.kk][p.mm][p.nn].roll = "NIL";
				stds[temp_stt.batch].push(temp_stt.roll);
			}

        } 


        if(cls[p.kk][p.mm][p.nn].batch == "NIL")
        {
            cls[p.kk][p.mm][p.nn].roll = "$";
            cls[p.kk][p.mm][p.nn].batch = "$";
            priority_queue<cordinate,vector<cordinate>,sortitagain>  temp ;

            vector<cordinate>temp_v;

            for(cordinate iterator : vec)
            {
                if(iterator.kk == p.kk)
                {
                    if(iterator.mm == p.mm) 
                    {
                        if(iterator.nn == p.nn)
                            continue ; 
                    }
                }
                cordinate posire = iterator;
                posire.mcv = calculate_mcv( cls, iterator.kk,iterator.mm,iterator.nn);
                temp.push(posire);
                temp_v.push_back(posire);
                
            }


            if(solvefn(stds, cls,temp,temp_v,total_students))
            {
                return true;
            }
            else
            {
                cls[p.kk][p.mm][p.nn].batch = "NIL";
                cls[p.kk][p.mm][p.nn].roll = "NIL";
            }


        }
        for(cordinate iterator : Myvec)
        {
            if(iterator.kk == p.kk)
            {
                if(iterator.mm == p.mm)
                {
                    if(iterator.nn == p.nn)
                        continue ; 
                }
            }
            Myvec.push_back(iterator);
        }

        Myvec.clear();
        vec.clear();
        pos.pop();
        vec.assign(Myvec.begin(),Myvec.end()); 
        
    }

    return false;
}



int main()
{

    int T;
    cin>>T;
    for(int xy=0 ; xy< T ; xy++)
    {

        vector<vector<vector<combi>>> cls ;
        map< string,  priority_queue<string,vector<string>,greater<> > >  students ;
        vector<cordinate>v;

        cin>>k; 
        cin>>m; 
        cin>>n;
        int total_students;
        cin>>total_students;
        

        
        if(total_students>m*n*k)
        {
            cout<<-1<<endl;
            continue;
        } 

        vector<vector<combi>> v1;
        vector<combi>v2;

        for(int i=0; i<k; i++)
        {
            v1.clear(); 
            for(int j=0;j<m;j++)
            {
                v2.clear(); 
                for(int h=0; h<n; h++)
                {
                    combi pt; 
                    pt.batch="NIL"; 
                    pt.roll="NIL" ; 
                    v2.push_back(pt);
                }

                v1.push_back(v2);
            }

            cls.push_back(v1);
        } 
 

        for(int j=0;j<total_students;j++)
        {
            string roll ; 
            string batch ;
            cin>>batch>>roll;
            students[batch].push(roll);
        }

        priority_queue<cordinate,vector<cordinate>,sortitagain> positions ; 

        for(int ii=0;ii<k;ii++)
        {
            for(int jj=0;jj<m;jj++)
            {
                for(int hh=0; hh<n; hh++)
                {
                    int z = calculate_mcv( cls , ii, jj, hh) ;  
                    cordinate pp ; 
                    pp.kk=ii ; 
                    pp.mm=jj; 
                    pp.nn=hh ; 
                    pp.mrv= total_students ; 
                    pp.mcv= z; 

                    v.push_back(pp);
                    positions.push(pp);
                    
                }
            }
        }


        bool kyasolmila= solvefn(students, cls,positions ,v ,total_students); 

        if(kyasolmila)
        {
            for(int i=0;i<k;i++)
            {
                for(int j=0;j<m;j++)
                {
                    for(int h=0;h<n;h++)
                    {
                        if(cls[i][j][h].batch == "$")
                        {
                            cout<<"NIL NIL ";
                        }
                        else
                        {
                            cout<<cls[i][j][h].batch<<" "<<cls[i][j][h].roll<<" ";
                        }
                    }
                    cout<<endl;
                }
            }

        }
        else
        {
            cout<<-1<<endl;
        }
        

    } 


}