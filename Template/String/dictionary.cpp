/*
先输入一大堆字典，然后再输入一大堆查询，问是否在字典里面，或者增加、删除或替换一个字符后是否在字典里面。
其中有几个比较坑的地方，比如输出是要按照输入的顺序的，输入的单词可能有前几个是重复的等等。
*/


#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>


using namespace std;


struct node{
    char c;
    bool ed;
    vector<node*> son;
    node (){
        ed = false;
    }
    node (char d){
        c = d;
        ed = false;
    }
};
map <string,int> order;<//这个是存字符串顺序的
bool cmp(string a,string b){//对答案进行排序
    return order[a]<order[b];
}
int number;
node top;
node *now;
string tem;


vector<string> ans;
bool found(string a){//在答案集里找重复
    for(int i = 0;i<ans.size();i++)
    {
        if(ans[i]==a)
            return true;
    }
    return false;
}
void buildtree(node *p,string s,int pos){//建立字典树
    if(pos >= s.length()){
        p->ed = true;
        return;
    }
    bool yes = false;
    for(int i = 0 ; i < p->son.size() ; i++){
        node *ww  = p->son[i];
        if(ww->c == s[pos]){
            buildtree(ww,s,pos+1);
            yes = true;
            break;
        }
    }
    if(!yes)
    {
        node* ww = new node;
        ww -> c = s[pos];
        p->son.push_back(ww);
        buildtree(p->son.back(),s,pos+1);
    }
}


bool exis(node *p,string s,int pos){//单词是否在树中
   // cout<<s<<endl;
    if(pos >= s.length() && p->ed)
        return true;
    for(int i = 0 ; i < p->son.size() ; i++){
        node *ww  = p->son[i];
        //cout<<tem->c<<endl;
        if(ww->c == s[pos])
        {
            return exis(ww,s,pos+1);
        }
    }
    return false;
}
void rep(node *p,string s,int pos){//替换
    if(pos >= s.length())
        return ;
    int len = p->son.size();
    for(int i = 0 ; i < len ; i++){
        node *ttt  = p->son[i];
        string a = s.substr(0,pos)+ttt->c+s.substr(pos+1);
        //printf("a[%d] has be %c\n",pos,ttt->c);
        if(exis(now,a,0) && !found(a)){
            tem+=" "+a;
            ans.push_back(a);
        }
    }
    for(int i = 0 ; i < len ; i++){
        node *ttt  = p->son[i];
        if(ttt -> c == s[pos])
        {
            rep(ttt,s,pos+1);
            break;
        }
    }
}
void inc(node *p,string s,int pos){//增加
    if(pos>=s.length())
        return ;
    int len = s.length()-pos;
        for(int i = 0 ; i < p->son.size() ; i++){
            node *rrr  = p->son[i];
            if(rrr -> c == s[pos])
            {
                inc(rrr,s,pos+1);//___________
                break;
            }
        }
    for(int i = 0 ; i < p->son.size() ; i++){
        node *ttt  = p->son[i];
        string a = s.substr(0,pos) + ttt->c + s.substr(pos);
       // printf("now a = ");
        //cout<<a<<endl;
        if(exis(now,a,0) && !found(a))
        {
            ans.push_back(a);
            tem+=" "+a;
        }
    }
}
void add(node *p,string s,int pos){//末尾增加
    int len = p->son.size();
    if(pos >= s.length()){
        for(int i = 0 ;i<len;i++){
            node * ttt = p->son[i];
            string a = s + ttt->c;
            if(exis(now,a,0)&& !found(a)){
                tem+=" " + a;
                ans.push_back(a);
            }
        }
    }
    for(int i=0;i<len;i++){
        node *ttt = p->son[i];
        if(ttt->c==s[pos])
        {
            add(ttt,s,pos+1);
            return;
        }
    }
}
void dic(string s,int pos){//减少一个
    int length = s.length();
    string a = s.substr(1,length-1);
    if( exis(now,a,0)&&!found(a))
    {
        ans.push_back(a);
        tem += " " +a;
    }
    a=s.substr(0,length-1);
    if(exis(now,a,0) &&!found(a))
    {
        tem += " " +a;
        ans.push_back(a);
    }
    for(int i = 1; i < s.length()-1;i++){
        string k = s.substr(0,i)+s.substr(i+1,length-i-1);


        if(exis(now,k,0)&&!found(k))
        {
            ans.push_back(k);
            tem += " " + k;
        }
    }
}


int n,m;


void dele(node *p){//释放内存
    for(int i = 0;i< p->son.size();i++){
        node *rrr  = p->son[i];
        delete(rrr);
    }
    delete p;
}


int main(){
    top.c=' ';
    n = 0;
    number=0;
    now = &top;
    string s;
    while(1){
        cin>>s;
        if(s=="#")  break;
        buildtree(now,s,0);
        order[s]=number;
        number++;
    }
    while(1){
        cin>>s;
        if(s=="#")
            break;
        tem = "";
        ans.clear();
        if(exis(now,s,0))
            cout<<s<<" "<<"is"<<" "<<"correct"<<endl;
        else{
            cout<<s<<":";
            rep(now,s,0);
            inc(now,s,0);
            add(now,s,0);
            dic(s,0);//大概这里就是超时的地方，因为必须四个操作都要试一试，所以不能减掉。无法加个if然后不去做它。
            sort(ans.begin(),ans.end(),cmp);
            for(int i =0 ;i<ans.size();i++)
                cout<<" "<<ans[i];
            cout<<" "<<endl;
        }
    }
    dele(now);
    return 0;
}

/*
下面这个代码是利用指针操作来完成上面的题目，打开了新世界的大门。
*/
/*
#include<iostream>
#include<string.h>
using namespace std;


char dict[10001][17];
char word[51][17];
int n1=0;
int n2=0;


bool Change(char* word,char* dict) 
{
	int dif=0;  //记录word与dict中在相同位置出现不同字符的个数
	
	while(*word)
	{
		if(*(word++) != *(dict++))
		{
			dif++;
			if(dif>1)
				return false;
		}
	}
	return true;
}


bool Del(char* word,char* dict)
{
	int dif=0;  //记录word与dict中在对应位置出现不同字符的个数
	while(*word)
	{
		if(*word != *dict)
		{
			word++;  //word后移一位再匹配
			dif++;
			if(dif>1)
				return false;
		}
		else
		{
			word++;
			dict++;
		}
	}
	return true;
}


bool Add(char* word,char* dict)
{	
	int dif=0;


	while(*dict)
	{
		if(*word != *dict)
		{
			dict++;
			dif++;
			if(dif>1)
				return false;
		}
		else
		{
			word++;
			dict++;
		}
	}
	return true;
}
int main(void)
{
	while(cin>>dict[n1] && dict[n1++][0]!='#');
	while(cin>>word[n2] && word[n2++][0]!='#');
	n1--;
	n2--;
	int* DictLen=new int[n1];  //记计算字典中各个单词的长度
	for(int n=0;n<n1;n++)
		DictLen[n]=strlen(dict[n]);


	for(int i=0;i<n2;i++)
	{
		int* address=new int[n1];  //记录word[i]通过变化得到的单词在dict中的下标
		int pa=0; //address指针


		bool flag=false;  //标记字典中是否含有单词word[i]
		int len=strlen(word[i]);


		for(int k=0;k<n1;k++)  //遍历字典
		{
			if(DictLen[k]==len)  //Change or Equal
			{
				if(!strcmp(word[i],dict[k]))
				{
					flag=true;
					break;
				}
				else if(Change(word[i],dict[k]))
					address[pa++]=k;
			}
			else if(len-DictLen[k]==1)  //Delete
			{
				if(Del(word[i],dict[k]))
					address[pa++]=k;
			}
			else if(DictLen[k]-len==1)  //Add
			{
				if(Add(word[i],dict[k]))
					address[pa++]=k;
			}
		}
		if(flag)
			cout<<word[i]<<" is correct"<<endl;
		else
		{
			cout<<word[i]<<": ";
			for(int j=0;j<pa;j++)
				cout<<dict[ address[j] ]<<' ';
			cout<<endl;
		}


		delete address;
	}
	return 0;
}
*/