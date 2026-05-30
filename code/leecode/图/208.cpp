#include <bits/stdc++.h>
using namespace std;
class Trie
{
public:
    Trie *liuhao[27];
    int end;
    Trie()
    {
        for (int i = 0; i < 26; i++)
        {
            liuhao[i] = nullptr;
        }
        end=0;
    }

    void insert(string word)
    {
        Trie *node = this;
        for (auto a : word)
        {
            int hao = a - 'a';
            if (node->liuhao[hao] == nullptr)
                node->liuhao[hao] = new Trie();
            node = node->liuhao[hao];
        }
        node->end = 1;
    }

    bool search(string word)
    {
        Trie *node = this;
        for (auto a : word)
        {
            int hao = a - 'a';
            if (node->liuhao[hao] == nullptr)
                return false;
            node = node->liuhao[hao];
        }
        return node->end;
    }

    bool startsWith(string prefix)
    {
        Trie *node = this;
        for (auto a : prefix)
        {
            int hao = a - 'a';
            if (node->liuhao[hao] == nullptr)
                return false;
            node = node->liuhao[hao];
        }
        return 1;
    }
}; // Trie 类结束
int main()
{
}

class Trie
{                       // 定义 Trie 前缀树类
public:                 // LeetCode 会调用 public 里面的函数
    Trie *children[26]; // 每个节点最多有 26 个孩子，对应 a 到 z

    bool isEnd; // 标记当前节点是不是某个完整单词的结尾

    Trie()
    { // 构造函数：创建一个 Trie 节点
        for (int i = 0; i < 26; i++)
        {                          // 遍历 26 个字母位置
            children[i] = nullptr; // 一开始每个孩子都不存在
        } // for 结束

        isEnd = false; // 一开始当前节点不是任何单词的结尾
    } // 构造函数结束

    void insert(string word)
    {                      // 插入一个单词 word
        Trie *node = this; // 从当前 Trie 的根节点开始

        for (char c : word)
        {                        // 遍历 word 中的每个字符
            int index = c - 'a'; // 把字符转换成 0 到 25 的下标

            if (node->children[index] == nullptr)
            {                                       // 如果这个字母对应的节点还不存在
                node->children[index] = new Trie(); // 就新建一个 Trie 节点
            } // if 结束

            node = node->children[index]; // 移动到这个字母对应的节点
        } // for 结束

        node->isEnd = true; // 单词走完后，把最后一个节点标记为单词结尾
    } // insert 函数结束

    bool search(string word)
    {                      // 查询完整单词 word 是否存在
        Trie *node = this; // 从根节点开始

        for (char c : word)
        {                        // 遍历 word 中的每个字符
            int index = c - 'a'; // 把字符转换成 0 到 25 的下标

            if (node->children[index] == nullptr)
            {                 // 如果当前字母路径不存在
                return false; // 说明这个单词不存在
            } // if 结束

            node = node->children[index]; // 移动到当前字母对应的节点
        } // for 结束

        return node->isEnd; // 只有最后节点是单词结尾，才说明完整单词存在
    } // search 函数结束

    bool startsWith(string prefix)
    {                      // 判断是否存在某个单词以 prefix 为前缀
        Trie *node = this; // 从根节点开始

        for (char c : prefix)
        {                        // 遍历 prefix 中的每个字符
            int index = c - 'a'; // 把字符转换成 0 到 25 的下标

            if (node->children[index] == nullptr)
            {                 // 如果当前字母路径不存在
                return false; // 说明没有单词以这个 prefix 开头
            } // if 结束

            node = node->children[index]; // 移动到当前字母对应的节点
        } // for 结束

        return true; // prefix 全部能走完，说明这个前缀存在
    } // startsWith 函数结束
}; // Trie 类结束