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


std::vector<std::string> split(std::string str,char pattern)
{
    vector<string> res;
    str += pattern;
    int len = str.length();
    string tmp = "";
    for (int i = 0; i < len; i ++)
    {
       if(str[i] == pattern)
       {
           res.push_back(tmp);
           tmp = " ";
           continue;
       }
       tmp += str[i];
    }
    return res;
}
