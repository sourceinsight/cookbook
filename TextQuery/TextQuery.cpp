
#include "TextQuery.h"
#include <sstream>
#include <stdexcept>

using std::istringstream;
using std::set;
using std::string;
using std::getline;
using std::map;
using std::vector;
using std::cerr;
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ispunct;
using std::tolower;
using std::strlen;
using std::out_of_range;

string TextQuery::text_line(line_no line) const
{
    if (line < lines_of_text.size())
        return lines_of_text[line];
    throw std::out_of_range("line number out of range");
}

void TextQuery::store_file(ifstream &is)
{
    string textline;
    while (getline(is, textline))
        lines_of_text.push_back(textline);
}

void TextQuery::build_map()
{
    for (line_no line_num = 0;
                 line_num != lines_of_text.size();
                 ++line_num)
    {
        istringstream line(lines_of_text[line_num]);
        string word;
        while (line >> word)
        {
            word_map[cleanup_str(word)].insert(line_num);
        }
    }
}

set<TextQuery::line_no> TextQuery::run_query(const string& query_word) const
{
    map<string, set<line_no> >::const_iterator
                        loc = word_map.find(cleanup_str(query_word));

    if (loc == word_map.end())
    {
        return set<line_no>();
    }
    else
    {
        return loc->second;
    }
}

void TextQuery::display_map()
{
    map<string, set<line_no> >::iterator it = word_map.begin(),
                                         it_end = word_map.end();

    for (; it != it_end; ++it)
    {
        cout << "word: " << it->first << " {";

        const set<line_no>& text_locs = it->second;
        set<line_no>::const_iterator loc_it = text_locs.begin(),
                                     loc_it_end = text_locs.end();

        while (loc_it != loc_it_end)
        {
            cout << *loc_it;

            if (++loc_it != loc_it_end)
            {
                cout << ", ";
            }
        }

        cout << "}" << endl;
    }

    cout << endl;
}

// ispunct
string TextQuery::cleanup_str(const string& word)
{
    string ret;
    for (string::const_iterator it = word.begin(); it != word.end(); ++it)
    {
        if (!ispunct(*it))
        {
            ret += tolower(*it);
        }
    }
    
    return ret;
}
