#include "CSubtitleManipulate.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

CSubtitleManipulate::~CSubtitleManipulate()
{
}

int CSubtitleManipulate::load_FromFile(const char* sz_File, std::vector<SubtitleLine>& v_out, SuccessResult& ret)
{
    /* A state machine for reading the Subtitle file */
	ifstream file(sz_File);
	string line;

	int n_Ret = 0;
	int MARK_TYPE_INDEX = 1;
	int MARK_TYPE_TIME = 2;
	int MARK_TYPE_CONTENT = 3;
	int MARK_TYPE_BLANK = 4;

	int last_type = 0;
	int arr[1000];

	std::vector<int> v;			// Vector of mark types
	std::vector<string> v_c; 	// Vector of contents
	std::vector<string> v_t;	// Vector of time

	std::regex integer("(\\+|-)?[[:digit:]]+");

	while (std::getline(file, line))
	{
		if (!is_MarkType(line.c_str(), 4))
		{
			if (is_MarkType(line.c_str(),next_cycle_3(last_type))
			{
				// OK
				last_type = next_cycle_3(last_type);

				v.push_back(last_type);

				if (last_type == MARK_TYPE_TIME)
				{
					v_t.push_back(line);
				}
				else if (last_type == MARK_TYPE_CONTENT)
				{
					v_c.push_back(line);
				}
				else if (last_type == MARK_TYPE_INDEX)
				{
					int index = atoi(line.c_str());
					// TODO: validate the index
				}
			}
			else 
			{
				// Invalid file
				// Inform that the current file is invalid.				
				// TODO: Add more information
				n_Ret = 1;	// 
				ret.tagData = v_c.size();	// The line which contains error
			}
		}
		else 
		{
			// Ignore the blank type
		}
	}

	// Success
	if (n_Ret == 0)
	{
		v_out.clear();
		for (int i=0;i<v_t.size();i++) {
			SubtitleLine sl;
			sl.index = i;
			sl.fromTheTime = 0;
			sl.to_Time = 0;
			sl.content = v_c[i];

			v_out.push_back(sl);
		}
	}

	ret.return_Code = n_Ret;
    return n_Ret;
}

int CSubtitleManipulate::groupingSentences(std::vector<SubtitleLine> v_sub_title, std::vector<SubtitleLine>& v_out)
{
    return 0;
}

int CSubtitleManipulate::groupingSentences_ByBlockTime(int block_ByMilliSecs,std::vector<SubtitleLine> v_sub_title, std::vector<SubtitleLine>& v_out)
{
    return 0;
}

int CSubtitleManipulate::writeToFile(const char* sz_File_Out, std::vector<SubtitleLine> v_sub)
{
    return 0;
}

bool CSubtitleManipulate::is_MarkType(char* szLine, int n_mark_Type)
{

	return true;
}
