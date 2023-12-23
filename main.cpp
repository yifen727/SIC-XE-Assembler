#include <bits/stdc++.h>
#include <fcntl.h>
using namespace std;
// #include "my_functions.h" // 引入你的函數庫標頭文件
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
string type2[] = {"CLEAR", "COMPR", "TIXR"};
string type3[23][23] = {
    {"STL", "14"}, {"LDB", "68"}, {"RSUB", "4C"}, {"LDA", "00"}, {"COMP", "28"}, {"JEQ", "30"}, {"J", "3C"}, {"STA", "0C"}, {"CLEAR", "B4"}, {"LDCH", "50"}, {"LDT", "74"}, {"TD", "E0"}, {"JEQ", "30"}, {"RD", "D8"}, {"COMPR", "A0"}, {"STCH", "54"}, {"TIXR", "B8"}, {"JLT", "38"}, {"STX", "10"}, {"WD", "DC"}, {"JSUB", "48"}};
string bintab[10] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "100"};
string hextab[18][18] = {{"0000", "0"}, {"0001", "1"}, {"0010", "2"}, {"0011", "3"}, {"0100", "4"}, {"0101", "5"}, {"0110", "6"}, {"0111", "7"}, {"1000", "8"}, {"1001", "9"}, {"1010", "A"}, {"1011", "B"}, {"1100", "C"}, {"1101", "D"}, {"1110", "E"}, {"1111", "F"}};
string registertab[9][9] = {{"A", "0"}, {"X", "1"}, {"L", "2"}, {"B", "3"}, {"S", "4"}, {"T", "5"}, {"F", "6"}, {"PC", "8"}, {"SW", "9"}};
int total_line = 0;

int string_to_int(string s) // for decimal
{
    int d = 1, ans = 0;
    for (int i = s.length() - 1; i >= 0; i--)
    {
        ans += d * (s[i] - '0');
        d *= 10;
    }
    return ans;
}
int search_type2(string s)
{
    for (int i = 0; i < sizeof(type2) / sizeof(type2[0]); i++)
    {
        if (s == type2[i])
            return 1;
    }
    return 0;
}
int hex_to_dec(string s)
{
    int len = s.length();
    int base = 1;

    int dec = 0;
    for (int i = len - 1; i >= 0; i--)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            dec += (int(s[i]) - 48) * base;

            // incrementing base by power
            base = base * 16;
        }
        else if (s[i] >= 'A' && s[i] <= 'F')
        {
            dec += (int(s[i]) - 55) * base;

            // incrementing base by power
            base = base * 16;
        }
    }
    return dec;
}
string dec_to_hex(int n)
{
    stringstream stream;
    stream << hex << n;
    string result(stream.str());
    char ans[10];
    strcpy(ans, result.c_str());
    for (int i = 0; i < strlen(ans); i++)
    {
        ans[i] = toupper(ans[i]);
    }
    return ans;
}
string byte_c(string st) // turn string to hex
{
    stringstream stream;
    for (int i = 0; i < st.length(); i++)
    {
        stream << hex << int(st[i]);
    }
    string ans = stream.str();
    for (int i = 0; i < ans.length(); i++)
    {
        ans[i] = toupper(ans[i]);
    }
    // cout << ans << endl;
    return ans;
}
string search_opcode(string s)
{
    string ans;
    // cout << "optable size= " << sizeof(type3) / sizeof(type3[0][0]) << endl;
    for (int i = 0; i < sizeof(type3) / sizeof(type3[0][0]); i++)
    {
        if (s == type3[i][0])
        {
            ans = type3[i][1];
            break;
        }
    }
    return ans;
}
string hex_to_binary(string s)
{
    string ans;
    // cout << "s=" << s << endl;
    for (int i = 0; i < s.size(); i++)
    {
        // cout << s[i] << endl;
        if (s[i] == 'A')
            ans += "1010";
        else if (s[i] == 'B')
            ans += "1011";
        else if (s[i] == 'C')
            ans += "1100";
        else if (s[i] == 'D')
            ans += "1101";
        else if (s[i] == 'E')
            ans += "1110";
        else if (s[i] == 'F')
            ans += "1111";
        else
            ans += bintab[s[i] - '0'];
    }
    // cout << "hex to bin " << ans << endl;
    return ans;
}
string binary_to_hex(string s)
{
    string ans;
    while (s.length() % 4 != 0)
    {
        s += '0';
    }
    for (int i = 0; i < s.length(); i += 4)
    {
        string temp = s.substr(i, 4);
        // cout << "sizeof(hextab)= " << sizeof(hextab) / sizeof(hextab[0]) << endl;
        for (int j = 0; j < sizeof(hextab) / sizeof(hextab[0]); j++)
        {
            if (hextab[j][0] == temp)
            {
                // cout << temp << endl;
                // cout << hextab[j][1] << endl;
                ans += hextab[j][1];
            }
        }
    }
    // cout << "bin to hex " << ans << endl;
    return ans;
}
string search_register_op(string s)
{
    string temp;
    for (int i = 0; i < sizeof(registertab) / sizeof(registertab[0]); i++)
    {
        if (s == registertab[i][0])
        {
            temp = registertab[i][1];
            break;
        }
    }
    return temp;
}
string search_location(string s, int total_line)
{
    // cout << "total line= " << total_line << endl;
    string ans;
    for (int i = 0; i < total_line; i++)
    {
        if (assem[i].symbol == s)
        {
            ans = assem[i].loc;
        }
    }
    return ans;
}
int is_number(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (isdigit(s[i]) == 0)
        {
            return 0;
        }
    }
    return 1;
}
int index_based(string s)
{
    // cout << "indexed_base function ";
    // cout << s << " " << s.length() - 2 << " " << s.length() << endl;
    if (s.substr(s.length() - 2, s.length()) == ",x")
        return 1;
    if (s.substr(s.length() - 2, s.length()) == ",X")
        return 1;
    return 0;
}
int is_pc_relative(int x)
{
    if (x >= -2048 && x <= 2047)
        return 1;
    else
        return 0;
}
int search_base(int total_line)
{
    // cout << "total line= " << total_line << endl;
    int ans;
    string loc;
    for (int i = 0; i < total_line; i++)
    {
        // cout << assem[i].inst << endl;
        if (assem[i].inst == "BASE")
        {
            // cout << "search base function " << assem[i].ref << endl;
            loc = search_location(assem[i].ref, total_line);
            break;
        }
    }
    ans = hex_to_dec(loc);
    return ans;
}
void show()
{
    for (int i = 0; i < total_line; i++)
    {
        cout << assem[i].symbol << "   " << assem[i].inst << " " << assem[i].ref << endl;
    }
}
int main()
{
    ofstream ofs;
    string input_file_name;
    cout << "Please enter the inputfile name:";
    cin >> input_file_name;
    ofs.open("output.txt");
    if (!ofs.is_open())
    {
        cout << "Failed to open file.\n";
        return 1; // EXIT_FAILURE
    }
    //
    // ifstream input_file;
    // input_file.open(input_file_name);
    // input_file.open("assembly_code.txt"); // for my test
    // string line;
    // string symbol_str, inst_str, ref_str;
    // int i = 0;
    // while (getline(input_file, line))
    // {
    //     stringstream str(line);
    //     getline(str, symbol_str, '\t');
    //     getline(str, inst_str, '\t');
    //     getline(str, ref_str, '\t');
    //     // cout << symbol_str << " " << inst_str << " " << ref_str << endl;
    //     assem[i].symbol = symbol_str;
    //     assem[i].inst = inst_str;
    //     assem[i].ref = ref_str;
    //     assem[i].format = 3;
    //     i++;
    // }
    //================================================
    ifstream input_file;
    // string input_file_name;
    input_file.open(input_file_name);
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
        // cout << "wordcount " << wordCount << endl;
        // 再次分解並輸出內容
        assem[i].w_count = wordCount;
        i++;
    }
    input_file.close();
    input_file.open(input_file_name);
    if (!input_file.is_open())
    {
        cout << "cannot open" << endl;
    }

    string symbol_str, inst_str, ref_str;
    i = 0;
    while (getline(input_file, line))
    {
        // cout << "i=" << i << endl;
        stringstream str(line);
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
            // cout << "3" << endl;
            // getline(str, symbol_str, '\t');
            // getline(str, inst_str, '\t');
            // getline(str, ref_str, '\t');
            // cout << symbol_str << endl;
            // cout << inst_str << endl;
            // cout << symbol_str << " " << inst_str << " " << ref_str << endl;
            // assem[i].inst = inst_str;
            // assem[i].ref = ref_str;
            // assem[i].symbol = symbol_str;
            // cout << "i=" << i << endl;
            istringstream iss(line);
            while (iss >> word)
            {
                if (j == 1)
                    assem[i].symbol = word;
                else if (j == 2)
                    assem[i].inst = word;
                else if (j == 3)
                {
                    assem[i].ref = word;
                }
                j++;
            }
        }
        // ofs << assem[i].symbol << " " << assem[i].inst << " " << assem[i].ref << endl;
        // assem[i].format = 3;
        // cout << "assem[0].inst=" << assem[0].inst << endl;
        i++;
    }
    //===============================================

    input_file.close();
    // for (int j = 0; j < i; j++)
    // {
    //     ofs << "j= " << j << " " << assem[j].symbol << " " << assem[j].inst << " " << assem[j].ref << endl;
    // }
    total_line = i;
    // show();
    // cout << "i=" << i << endl;

    // 決定起始位置
    if ((assem[0].ref).length() == 1)
    {
        assem[0].loc = assem[1].loc = "000" + assem[0].ref;
    }
    else if ((assem[0].ref).length() == 2)
    {
        assem[0].loc = assem[1].loc = "00" + assem[0].ref;
    }
    else if ((assem[0].ref).length() == 3)
    {
        assem[0].loc = assem[1].loc = '0' + assem[0].ref;
    }
    // cout << "total_line " << total_line << endl;
    for (int i = 1; i < total_line; i++)
    {
        // cout << assem[i].inst << endl;
        int done = 0;
        if (assem[i + 1].symbol == "" && assem[i + 1].inst == "" && assem[i + 1].ref == "")
        {
            break;
        }
        if (assem[i].inst == "")
            break;
        int add;

        if (assem[i].inst[0] == '+')
        {
            // cout << assem[i].inst << endl;
            add = 4;
        }

        else if (assem[i + 1].inst == "BASE")
        {
            assem[i + 1].loc = "";
            add = 0;
            done = 1;
            // add = 3;
            // continue;
        }
        else if (search_type2(assem[i].inst) == 1)
        {
            // ofs << "2   ";
            add = 2;
        }
        else if (assem[i].inst == "BYTE")
        {
            if (assem[i].ref[0] == 'X' || assem[i].ref[0] == 'x')
            {
                int rl = (assem[i].ref).length();
                // cout << "x " << rl << endl;
                add = (rl - 3) / 2;
            }
            if (assem[i].ref[0] == 'C' || assem[i].ref[i] == 'c')
            {
                int rl = (assem[i].ref).length();
                add = rl - 3;
            }
        }
        else if (assem[i].inst == "RESW")
        {
            // int r = stoi(assem[i].ref);
            // cout << "RESW" << endl;
            add = hex_to_dec(assem[i].ref) * 3;
        }
        else if (assem[i].inst == "RESB")
        {
            // cout << "RESB" << assem[i].ref << endl;
            string tempstr = dec_to_hex(string_to_int(assem[i].ref));
            int temp = hex_to_dec(tempstr);
            temp += hex_to_dec(assem[i].loc);
            assem[i + 1].loc = dec_to_hex(temp);
            done = 1;
        }
        else
        {
            add = 3;
        }
        //
        // 將LOC轉成10進位
        int temp = hex_to_dec(assem[i].loc);
        if (assem[i].loc == "")
            temp = hex_to_dec(assem[i - 1].loc);

        if (done == 0)
        {
            temp += add;
            string nextobj = dec_to_hex(temp);
            // cout << nextobj << endl;
            assem[i + 1].loc = nextobj;

            if ((assem[i + 1].loc).length() == 1)
            {
                assem[i + 1].loc = "000" + assem[i + 1].loc;
            }
            else if ((assem[i + 1].loc).length() == 2)
            {
                assem[i + 1].loc = "00" + assem[i + 1].loc;
            }
            else if ((assem[i + 1].loc).length() == 3)
            {
                assem[i + 1].loc = "0" + assem[i + 1].loc;
            }
        }
        // ofs << " loc i=" << i << " " << assem[i].loc << " " << assem[i].symbol << " " << assem[i].inst << " " << assem[i].ref << endl;
    }
    // ofs << "----------------------" << endl;
    // do obj
    for (int i = 1; i < total_line; i++)
    {
        if (assem[i].inst == "START" || assem[i].inst == "BASE" || assem[i].inst == "RESB" || assem[i].inst == "RESW" || assem[i].inst == "END")
        {
            assem[i].obj = "";
        }
        else if (assem[i].inst == "BYTE")
        {
            if (assem[i].ref[0] == 'C' || assem[i].ref[0] == 'c')
            {
                string temp;
                for (int j = 2; j < (assem[i].ref).length() - 1; j++)
                {
                    temp += assem[i].ref[j];
                }
                // cout << "C " << temp << endl;
                assem[i].obj = byte_c(temp);
                // cout << assem[i].obj << endl;
            }
            if (assem[i].ref[0] == 'X' || assem[i].ref[0] == 'x')
            {
                string temp;
                for (int j = 2; j < (assem[i].ref).length() - 1; j++)
                {
                    temp += assem[i].ref[j];
                }
                // cout << "X= " << temp << endl;
                assem[i].obj = temp;
            }
        }
        // else if (assem[i].inst[0] == '+')
        // {
        //     assem[i].format = 4;
        // }
        else if (assem[i].inst == "RSUB")
        {
            string id = search_opcode(assem[i].inst);
            string temp;
            temp = hex_to_binary(id).substr(0, 6);
            temp = temp + "1" + "1";
            // cout << "newtemp= " << temp << endl;
            temp = binary_to_hex(temp);
            assem[i].obj = temp + "0000";
        }
        else if (search_type2(assem[i].inst) == 1)
        {
            string temp = search_opcode(assem[i].inst);
            if ((assem[i].ref).length() == 3)
            {
                temp += search_register_op(assem[i].ref.substr(0, 1));
                temp += search_register_op(assem[i].ref.substr(2, (assem[i].ref.length() - 1)));
                // cout << temp << endl;
            }
            else if ((assem[i].ref).length() == 1)
            {
                temp += search_register_op(assem[i].ref);
            }
            //
            if (temp.length() == 3)
                temp += '0';
            assem[i].obj = temp;
        }
        else if (assem[i].inst[0] == '+')
        {
            // cout << "assem.inst " << assem[i].inst << endl;
            // cout << assem[i].inst.substr(1, assem[i].inst.length()) << endl;
            string opformat4 = search_opcode(assem[i].inst.substr(1, assem[i].inst.length()));
            // cout << opformat4 << endl;
            // cout << hex_to_binary(opformat4) << endl;
            string f6 = hex_to_binary(opformat4).substr(0, 6);
            // cout << "f6 " << f6 << endl;
            string n4, i4, e4, x4, b4, p4;
            n4 = i4 = e4 = "1";
            x4 = b4 = p4 = "0";
            string symbol_loc;
            symbol_loc = search_location(assem[i].ref, total_line);

            if (assem[i].ref[0] == '#')
            {
                n4 = "0";
                if (is_number(assem[i].ref.substr(1, assem[i].ref.length())) == 1)
                {
                    int temp;
                    temp = string_to_int(assem[i].ref.substr(1, assem[i].ref.length()));
                    symbol_loc = dec_to_hex(temp);
                }
                else
                    symbol_loc = search_location(assem[i].ref.substr(1, assem[i].ref.length()), total_line);
            }
            if (assem[i].ref[0] == '@')
            {
                i4 = "0";
                symbol_loc = search_location(assem[i].ref.substr(1, assem[i].ref.length()), total_line);
            }
            if (index_based(assem[i].ref) == 1)
            {
                x4 = "1";
                symbol_loc = search_location((assem[i].ref).substr(0, ((assem[i].ref).length()) - 2), total_line);
            }
            string temp = n4 + i4 + x4 + b4 + p4 + e4;
            opformat4 = f6 + temp;
            symbol_loc = "0" + symbol_loc;
            assem[i].obj = binary_to_hex(opformat4) + symbol_loc;
            // cout << "symbol loc: " << symbol_loc << endl;
        }
        else if (assem[i].ref[0] != '+' && search_type2(assem[i].inst) != 1 && assem[i].inst != "")
        {
            // ofs << "format3===== " << assem[i].inst << " i=" << i << endl;
            string opformat3 = search_opcode(assem[i].inst);
            // ofs << "opformat3 " << opformat3 << endl;
            string f6 = hex_to_binary(opformat3).substr(0, 6);
            // ofs << "f6 " << f6 << endl;
            string n3, i3, x3, b3, p3, e3;
            n3 = i3 = p3 = "1";
            x3 = b3 = e3 = "0";
            string tar_add = "";
            string disp;
            tar_add = search_location(assem[i].ref, total_line);
            int done = 0;
            if (assem[i].ref[0] == '#' && done == 0)
            {
                n3 = "0";
                if (is_number(assem[i].ref.substr(1, assem[i].ref.length())))
                {
                    // ofs << string_to_int((assem[i].ref).substr(1, (assem[i].ref).length())) << endl;
                    tar_add = dec_to_hex(string_to_int((assem[i].ref).substr(1, (assem[i].ref).length())));
                    disp = tar_add;
                    p3 = "0";
                    done = 1;
                    // ofs << "# " << tar_add << endl;
                }
                else
                    tar_add = search_location(assem[i].ref.substr(1, (assem[i].ref).length()), total_line);
            }

            if (assem[i].ref[0] == '@' && done == 0)
            {
                i3 = "0";
                tar_add = search_location(assem[i].ref.substr(1, (assem[i].ref).length()), total_line);
            }

            if (index_based(assem[i].ref) == 1)
            {
                x3 = "1";
                tar_add = search_location(assem[i].ref.substr(0, (assem[i].ref).length() - 2), total_line);
            }

            if (index_based(assem[i].ref) == 1 && assem[i].ref[0] == '@' && done == 0)
            {
                i3 = "0";
                x3 = "1";
                tar_add = search_location(assem[i].ref.substr(1, assem[i].ref.length() - 3), total_line);
            }
            if (index_based(assem[i].ref) == 1 && assem[i].ref[0] == '#' && done == 0)
            {
                n3 = "0";
                x3 = "1";
                tar_add = search_location(assem[i].ref.substr(1, assem[i].ref.length() - 3), total_line);
            }
            //---------------

            int pc, base;
            // ofs << "assem[i+1].loc " << assem[i + 1].loc << endl;
            if (assem[i + 1].loc == "")
                pc = hex_to_dec(assem[i + 2].loc);
            else
                pc = hex_to_dec(assem[i + 1].loc);
            // cout << "i=" << i << " pc=" << pc << endl;
            // ofs << assem[i].inst << " pc " << pc << " tar_add " << tar_add << endl;
            // ofs << "x=======" << hex_to_dec(tar_add) - pc << endl;
            // ofs << is_pc_relative(hex_to_dec(tar_add) - pc) << endl;
            // ofs << "done=" << done << endl;
            if (is_pc_relative(hex_to_dec(tar_add) - pc) == 0 && done == 0)
            {
                p3 = "0";
                b3 = "1";
                base = search_base(total_line);
                // ofs << "base= " << base << endl;
                disp = dec_to_hex(hex_to_dec(tar_add) - base);
                // ofs << "disp " << disp << endl;
            }
            else if (is_pc_relative(hex_to_dec(tar_add) - pc) == 1 && done == 0)
            {
                disp = dec_to_hex(hex_to_dec(tar_add) - pc);
                // ofs << "disp in dec " << hex_to_dec(tar_add) - pc << endl;
            }

            string temp = n3 + i3 + x3 + b3 + p3 + e3;
            opformat3 = f6 + temp;
            // ofs << "opformat3= " << opformat3 << endl;
            // ofs << "disp=" << disp << endl;
            if (disp.length() == 1)
                disp = "00" + disp;
            else if (disp.length() == 2)
                disp = "0" + disp;
            // if (opformat3.substr(0, 4) == "0000")
            // {
            //     opformat3 = "0" + binary_to_hex(opformat3);
            //     assem[i].obj = opformat3 + disp;
            // }
            // else
            //     assem[i].obj = binary_to_hex(opformat3) + disp;
            assem[i].obj = binary_to_hex(opformat3) + disp;
            // i don't understand part
            // ofs << "assem[i].obj.length " << assem[i].obj.length() << endl;
            // ofs << "assem[i].obj " << assem[i].obj << endl;
            if (assem[i].obj.length() > 8)
            {
                // ofs << assem[i].obj.substr(0, 3) << endl;
                assem[i].obj = assem[i].obj.substr(0, 3) + (assem[i].obj).substr(assem[i].obj.length() - 3, assem[i].obj.length());
            }
        }
    }
    for (int i = 0; i < total_line; i++)
    {
        // ofs << "i=" << i << " " << assem[i].loc << " " << assem[i].symbol << " " << assem[i].inst << " " << assem[i].ref << " -----" << assem[i].obj << endl;
        ofs << setw(4) << assem[i].loc << " ";
        ofs << setw(5) << setfill(' ') << assem[i].symbol << "  ";
        ofs << setw(5) << setfill(' ') << assem[i].inst << "    ";
        ofs << setw(8) << setfill(' ') << assem[i].ref << "     ";
        ofs << setw(10) << setfill(' ') << assem[i].obj << endl;
    }
    //============================object program===========================================
    ofstream ofs1;
    // cout << "Please enter the inputfile name:";
    // cin >> input_file_name;
    ofs1.open("object_program.txt");
    if (!ofs1.is_open())
    {
        cout << "Failed to open file1.\n";
        return 1; // EXIT_FAILURE
    }
    //
    string head_r = assem[0].symbol;
    if (head_r.length() == 4)
        head_r = head_r + "  ";
    else if (head_r.length() == 5)
        head_r = head_r + " ";
    string start_add = assem[0].loc;
    if (start_add.length() == 4)
    {
        start_add = "00" + start_add;
    }
    else if (start_add.length() == 5)
    {
        start_add = "0" + start_add;
    }
    string program_length;
    string end_add = assem[total_line - 1].loc;
    program_length = dec_to_hex(hex_to_dec(end_add) - hex_to_dec(start_add));
    if (program_length.length() == 4)
        program_length = "00" + program_length;
    else if (program_length.length() == 5)
        program_length = "0" + program_length;
    // cout << program_length << endl;
    // cout << head_r << endl;
    head_r = "H^" + head_r + "^" + start_add + "^" + program_length;
    ofs1 << head_r << endl;
    string end_r = "E^" + start_add;
    vector<string> t_r;
    vector<string> temp;
    int t_r_length = 0;
    int flag = 0, first = 0, cnt = 0;
    string last_add = "";

    for (int i = 0, j = 0; i < total_line; i++, j++)
    {
        if (flag == 0)
        {
            if (first == 0)
            {
                t_r.push_back("T^" + start_add + "^");
                first = 1;
            }
            if (t_r_length + assem[i].obj.length() / 2 <= 30)
            {
                t_r_length += (assem[i].obj.length()) / 2;
                temp.push_back(assem[i].obj);
            }
            if (t_r_length + assem[i].obj.length() / 2 >= 30)
            {
                // cout << "t_r_length " << t_r_length << "   assem[i].obj.length() " << assem[i].obj.length() << endl;
                t_r_length = 0;
                flag = 1;
                last_add = assem[i + 1].loc;
                t_r.push_back(dec_to_hex(hex_to_dec(assem[i + 1].loc) - hex_to_dec(start_add)) + "^");
                t_r.insert(t_r.end(), temp.begin(), temp.end());
                t_r.push_back("\n");
                temp.clear();
            }
        }
        else if (flag == 1)
        {
            // cout << "i= " << i << endl;
            if (first == 1)
            {
                if (last_add.length() == 4)
                    last_add = "00" + last_add;
                else if (last_add.length() == 5)
                    last_add = "0" + last_add;
                t_r.push_back("T^" + last_add + "^");
                first = 0;
            }
            if (t_r_length + assem[i].obj.length() / 2 <= 30)
            {
                t_r_length += assem[j].obj.length() / 2;
                temp.push_back(assem[j].obj);
            }
            if (t_r_length + assem[i].obj.length() / 2 >= 30 || assem[i].inst == "RESW" || assem[i].inst == "RESB" || assem[i].inst == "END")
            {
                t_r_length = 0;
                string temp_length = dec_to_hex(hex_to_dec(assem[i].loc) - hex_to_dec(last_add));
                if (temp_length.length() == 1)
                {
                    temp_length = "0" + temp_length;
                }
                t_r.push_back(temp_length + "^");
                t_r.insert(t_r.end(), temp.begin(), temp.end());
                t_r.push_back("\n");
                temp.clear();
                while (assem[i].inst == "RESW" || assem[i].inst == "REWB")
                {
                    i++;
                }
                j = i - 1;
                last_add = assem[i].loc;
                first = 1;
                if (assem[i].inst == "END")
                    break;
            }
        }
    }
    //-----------------m_record----------------------
    vector<string> m_r;
    for (int i = 0; i < total_line; i++)
    {
        if (assem[i].obj.length() == 8)
        {
            string temp = assem[i].loc;
            temp = dec_to_hex(hex_to_dec(temp) + 1);
            if (temp.length() == 5)
                temp = "0" + temp;
            else if (temp.length() == 4)
                temp = "00" + temp;
            else if (temp.length() == 3)
                temp = "000" + temp;
            else if (temp.length() == 2)
                temp = "0000" + temp;
            else if (temp.length() == 1)
                temp = "00000" + temp;
            if (assem[i].ref[0] == '#')
            {
                if (is_number(assem[i].ref.substr(1, assem[i].ref.length())) == 0)
                {
                    m_r.push_back("M^" + temp + "^05\n");
                }
            }
            else
                m_r.push_back("M^" + temp + "^05\n");
        }
    }
    for (int i = 0; i < t_r.size(); i++)
    {
        ofs1 << t_r[i];
    }
    for (int i = 0; i < m_r.size(); i++)
    {
        ofs1 << m_r[i];
    }
    ofs1 << end_r << endl;
    cout << "finished!" << endl;

    return 0;
}