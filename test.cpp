#include <bits/stdc++.h>
using namespace std;
struct NODE
{
    string symbol;
    string inst;
    string ref;
    string loc;
    string obj;
    int format;
    int w_count;
};
NODE assem[600]; // 最多讀600行

int main()
{
    ifstream input_file;
    input_file.open("assembly_code.txt");
    string line, word;

    if (!input_file.is_open())
    {
        cout << "cannot open" << endl;
    }
    int i = 0;
    while (getline(input_file, line))
    {
        istringstream iss(line);
        int wordCount = 0; // 計算單詞數量
        while (iss >> word)
        {
            ++wordCount;
        }
        cout << "wordcount " << wordCount << endl;
        // 再次分解並輸出內容
        assem[i].w_count = wordCount;
        i++;
    }
    input_file.close();

    input_file.open("assembly_code.txt");
    if (!input_file.is_open())
    {
        cout << "cannot open" << endl;
    }

    string symbol_str, inst_str, ref_str;
    i = 0;
    while (getline(input_file, line))
    {
        stringstream str(line);
        cout << "i=" << i << " " << assem[i].w_count << endl;
        int j = 1;
        if (assem[i].w_count == 2)
        {
            istringstream iss(line);
            while (iss >> word)
            {
                if (j == 1)
                    assem[i].inst = word;
                else if (j == 2)
                    assem[i].ref = word;
                j++;
            }
            assem[i].symbol = "";
        }
        else if (assem[i].w_count == 1)
        {
            istringstream iss(line);
            while (iss >> word)
            {
                assem[i].inst = word;
            }
        }
        else if (assem[i].w_count == 3)
        {
            getline(str, symbol_str, ' ');
            getline(str, inst_str, ' ');
            getline(str, ref_str, ' ');
            assem[i].symbol = symbol_str;
            assem[i].inst = inst_str;
            assem[i].ref = ref_str;
        }
        cout << assem[i].symbol << " " << assem[i].inst << " " << assem[i].ref << endl;
        cout << "================" << endl;
        // assem[i].format = 3;
        i++;
    }
    cout << "i= " << i << endl;
    ofstream ofs;
    ofs.open("test.txt");

    for (int j = 0; j < i; j++)
    {
        ofs << assem[j].symbol << " " << assem[j].inst << " " << assem[j].ref << endl;
    }
    ofs << assem[2].inst << endl;

    return 0;
}