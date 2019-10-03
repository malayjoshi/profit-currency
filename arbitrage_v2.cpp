#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cout<<"Enter the number of currencies"<<endl;
    cin>>n;
    cout<<"Enter currency notations(must be 3 char long)"<<endl;
    char curr[n][3];
    for(int i=0;i<n;i++)
        cin>>curr[i];

    float curr_rate[n][n]={0};
    float log_rate[n][n]={0};
    //taking rates as input
    for(int i=0;i<n;i++)
        {cout<<"Enter rates for "<<curr[i][0]<<curr[i][1]<<curr[i][2]<<endl;
         for(int j=0;j<n;j++)
           {cin>>curr_rate[i][j];
            log_rate[i][j]=-log(curr_rate[i][j]);
            }
        }
        cout<<endl;

        //for 1 source
        float d[n]={100000};
        d[0]=0;
        int p[n]={-1};

        int flag=0;//to tell about detection of negative cycle
        for(int k=0;k<n;k++)
          {for(int i=0;i<n;i++)  //i=from j=to
            { for(int j=0;j<n;j++)
              {
               if(i!=j)
               {
                  if(d[j]>(d[i]+log_rate[i][j])) //relax edge
                  {
                      d[j]=d[i]+log_rate[i][j];
                      if(k<(n-1))
                        p[j]=i;
                      if(k==n-1)
                        {
                          flag=1;

                          int temp_p[n]={-1};
                          for(int u=0;u<n;u++)
                            temp_p[u]=p[u];

                          temp_p[j]=i;

                          int path[20];
                          int visited[n];
                          int cyc;
                          for(int u=0;u<n;u++)
                          {
                           cyc=0;
                          for(int v=0;v<20;v++)
                           path[v]=-1;
                          for(int v=0;v<n;v++)
                          visited[v]=0;
                          //when current node is already visited and not equal to path[0] break from while
                          //when current node == path[0] break from while and for loop
                          int next=u;
                          int c=0;
                          while(1)
                          {
                            if((visited[next]==1)&&(next!=path[0]))
                              break;
                            if(next==path[0])
                            {c=1;
                             path[cyc]=next;
                             break;}
                             path[cyc]=next;//adding
                             cyc+=1;
                             visited[next]=1;
                             next=temp_p[next];
                             }
                             if(c)
                              break;
                             }

                            //starting with 1000
                           float prf=1000;
                           int rev_path[20]={-1};
                           for(int v=0;v<=cyc;v++)
                           rev_path[v]=path[cyc-v];
                           for(int v=0;v<cyc;v++)
                            {
                             cout<<prf<<" "<<curr[rev_path[v]][0]<<curr[rev_path[v]][1]<<curr[rev_path[v]][2]<<" to "<<curr[rev_path[v+1]][0]<<curr[rev_path[v+1]][1]<<curr[rev_path[v+1]][2]<<" at rate "<<curr_rate[rev_path[v]][rev_path[v+1]]<<" = "<<prf*curr_rate[rev_path[v]][rev_path[v+1]]<<endl;
                             prf=prf*curr_rate[rev_path[v]][rev_path[v+1]];
                             }
                            cout<<endl;


                         }
                  }
               }
               }

            }
          }

         if(!flag)
         {
           cout<<"No arbitrage opportunity detected\n"<<endl;

         }





    return 0;
}
