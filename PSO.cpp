#include<bits/stdc++.h>
using namespace std;
double pos[10]={0},vel[10]={0},pbest[10]={0};
double Gbest=0;
int c1=1,c2=1;
void init()
{
    for(int i=0;i<10;i++) pos[i]=rand()%20-10;//Random initialisation
}
double fitness_value(double x)
{
     return (-(x*x)+10*x+20);
}
int main()
{
     srand(time(0));
     init();
     int itr=0;
     while(abs(Gbest-5)>0.05)
     {
     	  //Pbest Calculations
          for(int j=0;j<10;j++)
          {
              if(pbest[j]==0) pbest[j]=pos[j];
              else if(fitness_value(pbest[j])<fitness_value(pos[j])) pbest[j]=pos[j];
          }  
          //Gbest Calculations
          for(int j=0;j<10;j++)
          {
              if(fitness_value(Gbest)<fitness_value(pbest[j])) Gbest=pbest[j];
          }
          //Updating velocities and positions
          double r1=(double)rand()/RAND_MAX,r2=(double)rand()/RAND_MAX;
          for(int j=0;j<10;j++)
          {
              vel[j]=vel[j]+c1*r1*(pbest[j]-pos[j])+c2*r2*(Gbest-pos[j]); 
              pos[j]=pos[j]+vel[j]; 
          }
          cout<<Gbest<<" "<<fitness_value(Gbest)<<"\n";
          itr++;
     }
     cout<<Gbest<<" "<<fitness_value(Gbest)<<"\n";
     cout<<"Iterations ="<<itr<<"\n";
}