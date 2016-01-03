
#ifndef _TEXTQUERY_H_
#define _TEXTQUERY_H_

#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>

class TextQuery
{
public:
    typedef std::string::size_type str_size;
    typedef std::vector<std::string>::size_type line_no;

    void read_file(std::ifstream& is)
    {
        store_file(is);
        build_map();
    }
    std::set<line_no> run_query(const std::string&) const;
    std::string text_line(line_no) const;
    str_size size() const
    {
        return lines_of_text.size();
    }
    void display_map();
private:
    void store_file(std::ifstream&);
    void build_map();
    static std::string cleanup_str(const std::string&);

    std::vector<std::string> lines_of_text;
    std::map<std::string, std::set<line_no> > word_map;
};
#endif // _TEXTQUERY_H_
