#include "TCsvreader.h"

using namespace std;

TCsvreader::TCsvreader(string v_folder, string v_delimiter)
{
	folder = v_folder;
	delimeter = v_delimiter;

}
vector<vector<string> > TCsvreader::getdata(string v_filename)
{
	string filename = folder + "/" + v_filename;
	ifstream file(filename);

	vector<vector<string> > dataflow;
	vector< vector<string> > transpose;
	vector<string> temp;

	string line = "";
	vector<string> vec;
	bool if_header = true;
	int rows = 0;
	// Iterate through each line and split the content using delimeter
	while (getline(file, line))
	{
		boost::algorithm::split(vec, line, boost::is_any_of(delimeter));
		if (if_header == true) if_header = false;
		else { dataflow.push_back(vec); temp.push_back("");}
	}
	// Close the File
	file.close();

	for (int i = 0; i < dataflow[0].size(); i++) {
		transpose.push_back(temp);
	}

	for (int i = 0; i < dataflow.size(); i++) {
		for (int j = 0; j < dataflow[i].size(); j++) {
			transpose[j][i] = dataflow[i][j];
		}
	}

	return transpose;

}
