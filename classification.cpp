#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
vector<string>attribute,classification;
string str1[100],str2[100];
int cnt = 0,c = 0;
struct css
{
    string name1,name2;
    int numb=0;
    double p;
} lkld[10];
struct pkn
{
    string clss;
    int nmb = 0;
    double pr;
} prkn[10];
void likelyhood()
{
    for(int j=0; j<classification.size(); j++)
    {
        for(int k=0; k<attribute.size(); k++)
        {
            lkld[c].name1 = attribute[k];
            lkld[c].name2 = classification[j];
            c++;

        }
    }
    cout<<c<<endl;
    int trck = 0;
    for(int j=0; j<classification.size(); j++)
    {
        for(int k=0; k<attribute.size(); k++)
        {
            for(int i=0; i<cnt; i++)
            {
                if(str2[i]==classification[j] && str1[i]==attribute[k])
                {
                    lkld[trck].numb++;
                }
            }
            trck++;
        }
    }
    for(int i=0; i<c; i++)
    {
        if(i%2==1)
        {
            lkld[i].p = lkld[i].numb/(lkld[i].numb+lkld[i-1].numb+0.00);
        }
        else
        {
            lkld[i].p = lkld[i].numb/(lkld[i].numb+lkld[i+1].numb+0.00);
        }
    }
    for(int i=0; i<c; i++)
    {
        cout<<lkld[i].name1<<" | "<<lkld[i].name2<<" = "<<lkld[i].numb<<" Probability "<<lkld[i].p<<endl;
    }
    cout<<endl;
    int oj=c-1;
    ofstream outobj("result.txt", ios::out | ios::trunc);
    while(oj>=0)
    {
        outobj<<lkld[oj].name1<<" ";
        outobj<<lkld[oj].name2<<" ";
        outobj<<lkld[oj].p<<"\n";
        oj--;
    }
}
void calpriorkn()
{
    for(int i=0; i<classification.size(); i++)
    {
        for(int j=0; j<cnt; j++)
        {
//            cout<<classification[i]<<endl;
            if(str2[j]==classification[i])
            {
                prkn[i].nmb++;
            }
        }
        prkn[i].clss = classification[i];
        prkn[i].pr = prkn[i].nmb/(cnt+0.00);
    }
    int itmp = 0;
    ofstream obja("priorknowledge.txt");
    while(itmp<classification.size())
    {
        obja<<prkn[itmp].clss<<" "<<prkn[itmp].pr<<endl;
        itmp++;
    }
    for(int i=0; i<classification.size(); i++)
    {
        cout<<prkn[i].clss<<" ";
        cout<<prkn[i].pr<<"\n";
    }
    cout<<endl;
}
void train()
{
    bool flag = false;
    ifstream inp("data.txt");
    while(inp>>str1[cnt])
    {
        inp>>str2[cnt];
        cout<<str1[cnt]<<" "<<str2[cnt]<<endl;
        flag = false;
        for(int i=0; i<attribute.size(); i++)
        {
            if(str1[cnt]==attribute[i])
            {
                flag = true;
            }
        }
        if(!flag)
        {
            attribute.push_back(str1[cnt]);
        }
        flag = false;
        for(int i=0; i<classification.size(); i++)
        {
            if(str2[cnt]==classification[i])
            {
                flag = true;
            }
        }
        if(!flag)
        {
            classification.push_back(str2[cnt]);
        }
        cnt++;
    }
    cout<<attribute.size()<<endl;
    cout<<classification.size()<<endl;
    likelyhood();
    calpriorkn();
}
void predict()
{
    string a1[10],a2[10],a3[10],udata,expclass;
    double pr1[10],pr2[10],ulkld=-1;
    double gg[10];
    int v1 = 0,v2 = 0;
    cout<<"small or big ear?\n";
    cin>>udata;
    ifstream inpobj("result.txt");
    while(inpobj>>a1[v1])
    {
        inpobj>>a2[v1];
        inpobj>>pr1[v1];
        cout<<a1[v1]<<" | "<<a2[v1]<<" "<<pr1[v1]<<"\n";
        v1++;
    }
    cout<<endl;
    ifstream inpobjb("priorknowledge.txt");
    while(inpobjb>>a3[v2])
    {
        inpobjb>>pr2[v2];
        cout<<a3[v2]<<" "<<pr2[v2]<<"\n";
        v2++;
    }
    cout<<endl;
    for(int i=0; i<v1; i++)
    {
        for(int j=0; j<v2; j++)
        {
            if(a1[i]==udata && a3[j]==a2[i] && ulkld<pr1[i]*pr2[j])
            {
                expclass = a2[i];
                ulkld = pr1[i]*pr2[j];
            }
        }
    }



    if(ulkld!=-1)
        cout<<"\n-----> The class is "<<expclass<<" <-----\n"<<endl;
    else
        cout<<"\n-----> The class wasn't found on the dataset. :( "<<" <-----\n"<<endl;

    cout<<"Likelyhood X Prior Knowledge "<<ulkld<<endl<<endl;


}
int main()
{

    char option;
    for(;;)
    {
        cout<<"1. To train.\n2. To predict.\nAny key to break\n";
        cin>>option;
        if(option=='1')
        {
            train();
        }
        else if(option=='2')
        {
            predict();
        }
        else
        {
            break;
        }
    }
}
