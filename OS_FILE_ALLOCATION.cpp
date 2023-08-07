#include <iostream>
#include <cstdlib>
#include<math.h>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <set>
using namespace std;
//--------------------------------------- FILE ALLOCATION -----------------------------------//
bool check(vector<string>memory,int blocks){
    bool flag=0;
    for(int i=0;i<blocks;i++){
        if(memory[i]!="0")return false;
    }
    return true;
}
// ---------------------Contigous Allocation---------------------- // (3)
void contigous(int blocks){
    map<string,int>m;
    //unordered_map<int,int>r_file;
    vector<string>memory(blocks,"0");
    while(true){
        string file_name;cout<<"Enter file name : ";
        cin>>file_name;
        int s_point;cout<<"Starting pointer of "<<file_name<<" is : ";
        cin>>s_point;
        int file_size;cout<<"File size of "<<file_name<<" is : ";
        cin>>file_size;

        if(s_point < 0 || s_point + file_size - 1 >= blocks){
            cout<<"Segmentation Fault "<<endl;
        }
        else{
            int f=0;
            for(auto it : m){
                if(s_point <= it.second && s_point + file_size - 1 >= it.second){
                    cout<<"Not available Space for "<<file_name<<endl;
                    f=1;break;
                }   
            }
            if(f==0)m[file_name]=s_point;
            for(int i = s_point;i < file_size + s_point && f==0; i++){
                memory[i]=file_name;
            }
        }
        cout<<"Do you want to allocate more files (y/n): ";
        char flag;cin>>flag;
        if(flag=='n')break;
        for(int i=0;i < blocks;i++){
            cout<<memory[i]<<"   ";
        }cout<<endl;   
    }

    //Memory record//
    cout<<"Final contigous memory is : ";
    for(int i=0;i < blocks;i++){
        cout<<memory[i]<<"   ";
    }
    
    //Deallocation of Memory//
    while(true){
        char f;
        cout<<"Deallocation of file : ";cin>>f;
        if(f=='n')break;
        else if(check(memory,blocks)==true){
            cout<<"Currently Empty Memory Space"<<endl;
            break;
        }
        string name;cout<<"File name you want to delete : ";cin>>name;
        int tt=0;
        for(int i=0;i<blocks;i++){
            if(memory[i]==name){
                memory[i]="0";tt=1;
            }
        }
        if(tt==1)m.erase(name);
        else cout<<"No such File Exist"<<endl;
        cout<<"Final contigous memory is : ";
        for(int i=0;i < blocks;i++){
            cout<<memory[i]<<"   ";
        }
    }
}

// --------------------Linked Allocation-------------------- //     (2)
void linked(int blocks){
    vector<string>memory(blocks,"0");
    unordered_map<string,vector<int>>map;
    int size=blocks;
    while(true){
        string file_name;cout<<"Enter file name : ";
        cin>>file_name;
        int start_point;cout<<"Enter start pointer : ";
        cin>>start_point;
        int file_size;cout<<"File size of "<<file_name<<" is : ";
        cin>>file_size;

        if(file_size > size)cout<<" Not available Size for "<<file_name<<endl;
        else{
            int s=file_size;
            size-=file_size;
            int i=start_point;
            while(s>0){
                int j = i % (blocks);
                if(memory[j]!="0"){
                    i++;
                    continue;
                }
                else{
                    memory[j]=file_name;
                    map[file_name].push_back(j);   
                    s--;
                }
                i++;
            }
        }
        cout<<"Do you want to allocate more files (y/n): ";
        char flag;cin>>flag;
        if(flag=='n')break;
        for(int i=0;i < blocks;i++){
            cout<<memory[i]<<"   ";
        }cout<<endl; 
    }
    cout<<"Final linked memory is : ";
    for(int i=0;i < blocks;i++){
        cout<<memory[i]<<"   ";
    }
    cout<<endl;

    //Accessing the File//
    while(true){
        char temp;
        cout<<"Wanna access file : ";cin>>temp;
        if(temp=='n')break;
        string name;cout<<"Which File : ";cin>>name;cout<<endl;
        vector<int>v=map[name];
        for(int i=0;i<v.size();i++)cout<<"-->"<<v[i];cout<<endl;
    }

    //Deallocation of Memory//
    while(true){
        char f;
        cout<<"Deallocation of file : ";cin>>f;
        if(f=='n')break;
        else if(check(memory,blocks)==true){
            cout<<"Currently Empty Memory Space"<<endl;
            break;
        }
        string name;cout<<"File name you want to delete : ";cin>>name;
        int tt=0;
        for(int i=0;i<blocks;i++){
            if(memory[i]==name)memory[i]="0",tt=1;
        }
        if(tt==1)map.erase(name);
        else cout<<"No suck File exist"<<endl;
        for(int i=0;i < blocks;i++){
            cout<<memory[i]<<"   ";
        }
        cout<<endl;
    }
}

//-----------------Indexing based Allocation----------//   (1)
void indexing(int blocks){
    vector<string>memory(blocks,"0");
    map<string,int>m;
    unordered_map<int,vector<int>>map;
    int size=blocks;
    while(true){
        string file_name;cout<<"Enter file name : ";
        cin>>file_name;
        int start_point;cout<<"Enter start pointer : ";
        cin>>start_point;
        int file_size;cout<<"File size of "<<file_name<<" is : ";
        cin>>file_size;

        if(file_size + 1 > size)cout<<"Not available Size for "<<file_name<<endl;
        else{
            int s=file_size;
            size-=file_size + 1;
            int idx;
            int i=start_point;
            while(true){
                int j=i % blocks;
                if(memory[j]=="0"){
                    m[file_name]=j;
                    idx=j;memory[j]="Ind_"+file_name;
                    break;
                }
                i++;
            }
            i=0;
            while(s>0){
                int j = i % (blocks);
                if(memory[j]!="0"){
                    i++;
                    continue;
                }
                else{
                    memory[j]=file_name;
                    map[idx].push_back(j);   
                    s--;
                }
                i++;
            }
        }
        cout<<"Do you want to allocate more files (y/n): ";
        char flag;cin>>flag;
        if(flag=='n')break;
        for(int i=0;i < blocks;i++){
            cout<<memory[i]<<"   ";
        } cout<<endl;
    }

    cout<<"Final Indexing memory is : ";
    for(int i=0;i < blocks;i++){
        cout<<memory[i]<<"   ";
    }cout<<endl;

     //Accessing the File//
    while(true){
        char temp;
        cout<<"Wanna access file : ";cin>>temp;
        if(temp=='n')break;
        string name;cout<<"Which File : ";cin>>name;cout<<endl;
        int i=m[name];
        vector<int>v=map[i];
        cout<<i<<" : ";
        for(int i=0;i<v.size();i++)cout<<v[i]<<"  ";cout<<endl;
    }

    //Deallocation of Memory//
    while(true){
        char f;
        cout<<"Deallocation of file : ";cin>>f;
        if(f=='n')break;
        else if(check(memory,blocks)==true){
            cout<<"Currently Empty Memory Space"<<endl;
            break;
        }
        string name;cout<<"File name you want to delete : ";cin>>name;
        string temp="Ind_"+name;cout<<endl;
        int tt=0;
        for(int i=0;i<blocks;i++){
            if(memory[i]==name || memory[i]==temp)memory[i]="0",tt=1;
        }
        int tem=m[name];
        if(tt==0)cout<<"No such File exist"<<endl;
        else m.erase(name),map.erase(tem);
        cout<<endl<<"Final Indexing memory is : ";
        for(int i=0;i < blocks;i++){
            cout<<memory[i]<<"   ";
        }cout<<endl;
    }
}
// ----------------------Main function----------------------//
int main(){
    int blocks;
    cout<<" Number of blocks you want to allocate : ";cin>>blocks;cout<<endl;
    int allocation_type;
    cout<<"Which type of allocation do you want to attempt : ";
    cin>>allocation_type;
    if(allocation_type==1)cout<<endl,indexing(blocks);
    else if(allocation_type==2)cout<<endl,linked(blocks);
    else if(allocation_type==3)cout<<endl,contigous(blocks);
    else cout<<"---------------------Invalid Type-------------------------";
}