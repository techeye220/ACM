#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

const int MAXN = 26;

typedef struct Trie
{
    bool flag;    //从根到此是否为一个单词 || 是否是叶节点
    Trie *next[MAXN];
    Trie()
    {
        flag = false;
        for (int i = 0; i < MAXN; i ++)
        {
            next[i] = nullptr;
        }
    }
}Trie;
Trie *root = new Trie();

void Trie_insert(char *word)
{
    Trie *tmp = root;
    while(*word != '\0')
    {
        if(tmp->next[*word - 'a'] == nullptr)
        {
            Trie *cur = new Trie();
            tmp->next[*word - 'a'] = cur;
        }
        tmp = tmp->next[*word - 'a'];
        word ++;
    }
    tmp->flag = true;
}

bool Trie_search(char *word)
{
    Trie *tmp = root;
    for (int i = 0; word[i] != '\0'; i ++)
    {
        if(tmp == nullptr || tmp->next[word[i] - 'a'] == nullptr)
            return false;
        tmp = tmp->next[word[i] - 'a'];
    }
    return tmp->flag;
}

void Trie_delete(Trie *cur)
{
    for (int i = 0; i < MAXN; i ++)
    {
        if(cur->next[i] != nullptr)
            Trie_delete(cur->next[i]);
    }
    delete cur;
}
int main()
{
    freopen("22.in", "r", stdin);
    char tmp[50];
    cout << "请输入初始化字典树的字符串(字符0结束）：" << endl;
    while(cin >> tmp)
    {
//        cout << tmp << endl;
        if(tmp[0] == '0' && tmp[1] =='\0') break;
        Trie_insert(tmp);
    }
    cout << "请输入要查找的字符串：" << endl;
    while(cin >> tmp)
    {
//        cout << tmp << endl;
        if(tmp[0] == '0' && tmp[1] =='\0') break;
        if(Trie_search(tmp))
            cout << "查找成功！再次输入查找，字符0结束查找：" << endl;
        else
            cout << "查找失败！再次输入查找，字符0结束查找：" << endl;
    }
    Trie_delete(root);
    return 0;
}















