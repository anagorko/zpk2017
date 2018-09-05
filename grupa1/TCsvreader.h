#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <boost/algorithm/string.hpp>

using namespace std;

class TCsvreader
{
public:
	TCsvreader(string v_folder, string v_delimeter);
	vector<vector<string> > getdata(string v_filename);
private:
	string folder;
	string delimeter;
};

