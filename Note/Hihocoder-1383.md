#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

const int MAXN = 107;
typedef struct Trie{
    string s;
    Trie* next[MAXN];
    int num;
    bool flag;
    Trie(string s = ""):s(s), flag(false)
    {
        num = 0;
        for (int i = 0; i < MAXN; i ++)
        {
            next[i] = nullptr;
        }
    }
}Trie;
Trie* root = new Trie();

std::vector<std::string> split(std::string str,std::string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str += pattern;
    int size=str.size();

    for(int i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<(unsigned int)size)
        {
            std::string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
    return result;
}
void Delete(Trie* cur)
{
    for (int i = 0; i < MAXN; i ++)
    {
        if(cur->next[i] != nullptr)
            Delete(cur->next[i]);
    }
    delete cur;
}
bool Cmp(const Trie* a, const Trie* b)
{
    return a->s < b->s;
}
void Print(Trie* cur, int num)
{
    vector<Trie*> f1, f2;
    for (int i = 0; i < cur->num; i ++)
    {
        if(cur->next[i]->flag == true && cur->next[i]->num == 0)
            f2.push_back(cur->next[i]);
        else
            f1.push_back(cur->next[i]);
    }
    sort(f1.begin(), f1.end(), Cmp);
    sort(f2.begin(), f2.end(), Cmp);
    for (int i = 0; i < f1.size(); i ++)
    {
        for (int j = 0; j < num*4; ++j)printf(" ");
        printf("%s\n", (f1[i]->s).c_str());
        Print(f1[i], num + 1);
    }
    for (int i = 0; i < f2.size(); i ++)
    {
        for (int j = 0; j < num*4; ++j)printf(" ");
        printf("%s\n", (f2[i]->s).c_str());
        Print(f2[i], num + 1);
    }
}
vector<string> tmp;
int main()
{
    //freopen("22.in", "r", stdin);
    string text;
    int cas_ = 0;
    while(getline(cin, text))
    {
        if(text == "0")
        {
            printf("Case %d:\n", ++ cas_);
            Print(root, 0);
            Delete(root);
            root = new Trie();
            continue;
        }
        tmp = split(text, "/");
        Trie* ptr = root;
        for (unsigned int i = 0; i < tmp.size(); i ++)
        {
            string cur = tmp[i];
            if(i == tmp.size() - 1)
            {
                bool find_file = false;
                for (int j = 0; j < ptr->num; j ++)
                {
                    if(ptr->next[j]->s == cur && ptr->next[j]->flag == true)
                    {
                        find_file = true;
                        ptr = ptr->next[j];
                        break;
                    }
                }
                if(!find_file)
                {
                    ptr->next[ptr->num ++] = new Trie(cur);
                    ptr = ptr->next[ptr->num - 1];
                    ptr->flag = true;
                }
            }else{
                bool find_catalog = false;
                for (int j = 0; j < ptr->num; j ++)
                {
                    if(ptr->next[j]->s == cur && ptr->next[j]->flag == false)
                    {
                        find_catalog = true;
                        ptr = ptr->next[j];
                        break;
                    }
                }
                if(!find_catalog)
                {
                    ptr->next[ptr->num ++] = new Trie(cur);
                    ptr = ptr->next[ptr->num - 1];
                }
            }
        }
    }
    return 0;
}

















