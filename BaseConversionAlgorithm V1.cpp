#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<ctime>

using namespace std;

char ch[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
char ch1[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

const long int size1=1000000;//4094 IS FIX FOR CHAR
char instring[size1*2];
unsigned int process[3][size1]={0};
//100000 digits of decimal to hex 397 seconds
//168 FFF->output from randomDECIMAL->INPUT
//168
void dis(long int n,long int f=0,long int k1=0,long int num=0)
{
    long int k;
    if(k1!=0 && num != 0)
     cout<<k1<<"-"<<n+1<<"-|";
        for(k=n;k>=0;k--)
         cout<<ch1[process[0][k]];
         if(!(f == 0 && process[2][0] ==0))
         {cout<<".";
         for(k=0;k<=f;k++)
         cout<<ch1[process[2][k]];
         }
         cout<<endl;
}

int main()
{
    fstream input,output;
    clock_t start;
    double duration;
    long int rows=size1,trows;//int n=sizeof(process[0])/2;
    long int j,i,k,m=0,m1=0,l,p,o,dec;
    long int base1,base2,nbase2,ilen=0,flen=0,pos,f1,flimit=100;
    int choice=0,temp,numtemp,i2,save,value=0,j1;
    long int dd=0,tr=0,allzero=0;
    base1=10;
    base2=16;
    trows=rows;
    save=0;
    begining:
        //cout<<"size"<<size<<endl;
        rows=trows;
         {  for(p=0;p<rows;p++){instring[p]=process[0][p]=process[1][p]=process[2][p]=0;}}


             cout<<"________________________________________________________________________________________________________________"<<endl;
            cout<<"                 DATA REPRESENTATION"<<endl;
            cout<<"1.CONVERT A (BASE1="<<base1<<") TO (BASE2="<<base2<<") \n ( FRACTION LIMIT ="<<flimit<<"   SAVE OUTPUT=";
                if(save==1)
                {
                  cout<<"YES"<<endl;
                }
                else
                    cout<<"NO"<<endl;
            cout<<"2.CHANGE THE BASE , FRACTION LIMIT & SAVING OUTPUT?"<<endl;

           cout<<"3.CLEAR SCREEN "<<endl;
           cout<<"4.HELP "<<endl;
           cout<<"5.EXIT "<<endl;
           cout<<"ENTER YOUR CHOICE =";
           cin>>choice;
            if(choice==1)
            {
                goto case1_start;
            }
            else if (choice==2)
            {
                cout<<"BASE1 = ";
                cin>>base1;
                cout<<"BASE2 = ";
                cin>>base2;
                cout<<"FRACTION LIMIT = ";
                cin>>flimit;
                cout<<"1.SAVE OUTPUT IN FILE (YES =1  IF NO = 0 )) = ";
                cin>>save;
                goto begining;
            }
            else if (choice==3)
            { system("cls");
              goto begining;
            }
           else if(choice ==4)
           { cout<<"  *.OUTPUT AUTOMATICALLY SAVED IN FILE \"output.txt\" IF YOU SET THE OPTION   (NOTE: NO NEED TO CREATE FILE)"<<endl;
             cout<<"  *.BEFORE CHOOOSING OPTION(1.2.INPUT THROUGH FILE) INPUT SHOULD BE SAVED IN FILE \"input.txt\"  "<<endl;
             goto begining;
           }
           else if(choice ==5)
           {
             exit(0);
           }
            else if(choice> 6 || choice <=0)
            {
                cout<<"INVALID CHOICE "<<endl;
                goto begining;
            }
case1_start:


     cout<<"      1.1.INPUT THROUGH CONSOLE   1.2.INPUT THROUGH FILE"<<endl;

     cout<<"      ENTER YOUR CHOICE = ";
     cin>>choice;
     if(choice==1)
     {  cout<<"ENTER THE  NUMBER (base)"<<base1<<endl;
         cin>>instring;}
     else if(choice==2)
     {
        input.open("input.txt",ios::in);
        input>>instring;
        cout<<instring<<endl;
        input.close();
     }
     else
        {cout<<"INVALID CHOICE RE-ENTER"<<endl;
        goto case1_start;
        }
        //strrev(instring);
        ilen=strlen(instring);
        cout<<"LENGTH ="<<ilen<<endl;
     if(ilen > sizeof(instring))
     {
         cout<<" STRING SIZE LIMIT IS = "<<sizeof(instring)<<endl;
         goto case1_start;
     }
for(p=0;p<ilen;p++)
 {
     if(instring[p]=='.')
      break;
 }
 for(i=0;i<ilen;i++)
  {
      if(instring[i]>57)
        instring[i]=instring[i]-7;
        instring[i]=instring[i]-48;
  }
  k=0;
  for(i=ilen-1;i>p;i--)
  {
      process[1][k]=instring[i];
      k++;
  }
dec=1;
cout<<"please wait(processiong ......) "<<endl;
start = std::clock();
flen=ilen-p;
ilen=p;
dd=0;
f1=-1;
nbase2=base2-1;
for(k=0;k<ilen;k++)
{                 for(p=0;(process[0][p]*=base1),p<dec;p++);
                  process[0][0]+=instring[k];
                  for(i=0;dec>i;i++)
                       {     i2=i;
                                  while(process[0][i2] > nbase2)
                                  {
                                   if(dd<i2){dd=i2;}
                                    process[0][i2+1]+=process[0][i2]/base2;
                                   process[0][i2]%=base2;
                                  i2++;
                                 }
                       }
                       dec=dd+2;
//dis(dec-1);
}
do
{                allzero=0;
                  for(p=0;(process[1][p]*=base2),p<flen;p++);
                  for(i=0;flen-1>i;i++)
                       {
                                    process[1][i+1]+=process[1][i]/base1;
                                   process[1][i]%=base1;
                       }
                process[2][++f1]=process[1][flen-1];
                //dis(dec-1,f1);
                process[1][flen-1]=0;
               for(p=0;p<flen;p++){ if(process[1][p]!=0 && f1 < flimit-1){ allzero=1; break; } }
}while(allzero==1);
duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        pos=0;
         for(p=0;p<rows;p++)
         {
                 if(process[0][p]>0)
                  pos=p;
         }
    cout<<endl<<"EQUIVALENT TO (base)"<<base2<<endl;
    dis(pos,f1);
    if(save==1)
    {      for(i=0;i<ilen;i++)
               {
               instring[i]=0;
               }
            p=0;
         for(i=pos;i>=0;i--)
         {instring[p]=ch[process[0][i]];p++;}
          if(!(f1 == 0 && process[2][0] ==0))
         { instring[p]='.';
          for(k=0;k<=f1;k++)
          { p++;
             instring[p]=ch[process[2][k]];
          }
       }
        output.open("output.txt",ios::out);
        output<<instring;
        output.close();
    }
    std::cout<<"TIME TAKEN FOR CONVERTION "<< duration <<endl;
    goto begining;
    return 0;
}
