#include "CSubtitleManipulate.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

#define MARK_TYPE_INDEX 	1
#define MARK_TYPE_TIME 		2
#define MARK_TYPE_CONTENT 	3
#define MARK_TYPE_BLANK 	4

CSubtitleManipulate::~CSubtitleManipulate()
{
}

int CSubtitleManipulate::load_FromFile(const char* sz_File, std::vector<SubtitleLine>& v_out, SuccessResult& ret)
{
    /* A state machine for reading the Subtitle file */
	ifstream file(sz_File);
	string line;
	
	int n_Ret = 0;
	int last_type = 0;
	int loop_desired_type = 0;
	int arr[1000];

	std::vector<int> v;			// Vector of mark types
	std::vector<string> v_c; 	// Vector of contents
	std::vector<string> v_t;	// Vector of time

	while (std::getline(file, line))
	{
		printf("GetLine: %s\r\n", line.c_str());
		if (!is_MarkType(line.c_str(), 4))
		{
			loop_desired_type = next_cycle_3(last_type);
			if (is_MarkType(line.c_str(),loop_desired_type))
			{
				// OK
				last_type = loop_desired_type;
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
				ret.tag_Data_00 = v_c.size();	// The line which contains error
				ret.tag_Data_01 = loop_desired_type;


				printf("Error Here %s\r\n", line.c_str());
				printf("DesiredType = %d\r\n", loop_desired_type);
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
		for (int i=0;i<v_t.size()/3;i++) {
			SubtitleLine sl;
            string s_From_Time;
            string s_To_Time;
			long fromTimeVal;
			long to_Time_Val;

            parse_Subtitle_Time(v_c[3*i+1].c_str(), s_From_Time, s_To_Time, fromTimeVal, to_Time_Val);

			sl.index = i;
			sl.fromTheTime = s_From_Time;			
			sl.to_Time = s_To_Time;
			sl.l_From_Time = fromTimeVal;
			sl.l_ToTheTime = to_Time_Val;
			sl.content = v_c[3*i + 2];

			v_out.push_back(sl);
		}
	}

	ret.return_Code = n_Ret;	
    return n_Ret;
}

int CSubtitleManipulate::groupingSentences(std::vector<SubtitleLine> v_sub_title, std::vector<SubtitleLine>& v_out)
{
	double d_half_flag = 0;	// Flag for the Bulding state of last element 
	v_out.clear();
    
	for (int i=0;i<v_sub_title.size();++i)
	{
		if (d_half_flag == 0)		// Need new elements
		{
			SubtitleLine new_E;
			new_E = v_sub_title[i];

			v_out.push_back(new_E);
			d_half_flag = 0.5;
		}
		else if (d_half_flag == 0.5)	// The last element is building
		{
			if (i==v_sub_title.size() -1 || v_sub_title[i].content[v_sub_title[i].content.size()-1] == '.')
			{
				// Concat content to the last Element & update ToTime 
				v_out[v_out.size()-1].content += v_sub_title[i].content;
				v_out[v_out.size()-1].to_Time = v_sub_title[i].to_Time;
				v_out[v_out.size()-1].l_ToTheTime = v_sub_title[i].l_ToTheTime;

				//	Then mark that the last element finish
				d_half_flag = 0;
			}
			else 
			{
				// Concat content to the last Element & update ToTime
				v_out[v_out.size()-1].content += v_sub_title[i].content;
				v_out[v_out.size()-1].to_Time = v_sub_title[i].to_Time;
				v_out[v_out.size()-1].l_ToTheTime = v_sub_title[i].l_ToTheTime;
			}
		}
	}

    return 0;
}

int CSubtitleManipulate::groupingSentences_ByBlockTime(int block_ByMilliSecs,std::vector<SubtitleLine> v_sub_title, std::vector<SubtitleLine>& v_out)
{
	// Use "Virtual Ruler". See SOLUTION.md
	int nRulerWidth = block_ByMilliSecs;
	int anchorPoint = 0;
	int label_BeenProcessed = 0;

	v_out.clear();
	if (v_sub_title.size() > 0)
	{
		while (label_BeenProcessed < v_sub_title.size())
		{
			// Put the Ruler to the anchor Point
			SubtitleLine new_E;
			
			int begin_Ruler;
			int endingRuler;
			int i = label_BeenProcessed;

			new_E.content = "";
			new_E.l_From_Time = -1;

			anchorPoint = v_sub_title[i].l_From_Time;
			begin_Ruler = anchorPoint;
			endingRuler = anchorPoint + nRulerWidth;

			while (endingRuler > v_sub_title[i].l_From_Time && 
					v_sub_title[i].l_ToTheTime >= begin_Ruler)	// overlapped between [beginRule, endingRuler) and [v_sub_title[i].l_From_Time, v_sub_title[i].l_ToTheTime]
			{
				new_E.content += v_sub_title[i].content;
				new_E.l_ToTheTime = v_sub_title[i].l_ToTheTime;
				new_E.to_Time = v_sub_title[i].to_Time;

				if (new_E.l_ToTheTime < 0)
				{
					new_E.l_ToTheTime = v_sub_title[i].l_ToTheTime;
					new_E.to_Time = v_sub_title[i].to_Time;
				}
				i++;
			}

			if (i > label_BeenProcessed)
			{
				v_out.push_back(new_E);
			}
			else 
			{
				printf("ERRRORRRRRRRRRRRRRRRRRR\r\n");
			}

			label_BeenProcessed = i;
		}
	}

    return 0;
}

int CSubtitleManipulate::writeToFile(const char* sz_File_Out, std::vector<SubtitleLine> v_sub)
{
	int ret = 0;
	
	ofstream myfile (sz_File_Out);

  	if (myfile.is_open())
  	{
		for (int i=0;i=v_sub.size();++i)
		{
			myfile << (i+1) << endl;
			myfile << v_sub[i].fromTheTime << " --> " << v_sub[i].to_Time << endl;
			myfile << v_sub[i].content;

			myfile << endl;
		}
		myfile.close();
  	}
  	else 
	{
		// cout << "Unable to open file";
		ret = 1;
	}
    return ret;
}

int CSubtitleManipulate::next_cycle_3(int type)
{
	int ret = 1;
	if (type == 3)
	{
		ret = 1;	// Ret = 1 || 3 is OK
	}
	else if (type > 0 && type < 3)
	{
		ret = type + 1;
	}

	return ret;
}

bool CSubtitleManipulate::is_MarkType(const char* szLine, int n_mark_Type)
{
    // 00:02:17,440 --> 00:02:20,375
	std::regex regex_integer("[[:digit:]]+");
	std::regex regex_subtime("([0-9]{2}\\:[0-9]{2}\\:[0-9]{2}\\,[0-9]{3})[[:space:]]*-->[[:space:]]*([0-9]{2}\\:[0-9]{2}\\:[0-9]{2}\\,[0-9]{3})");
    
    if (n_mark_Type == MARK_TYPE_INDEX)
    {
        return std::regex_match(szLine, regex_integer);
    }
    else if (n_mark_Type == MARK_TYPE_TIME)
    {
        return std::regex_match(szLine, regex_subtime);
    }
    else if (n_mark_Type == MARK_TYPE_CONTENT)
    {
        return true;    // Always true
    }
    else if (n_mark_Type == MARK_TYPE_BLANK)
    {
        std::string s(szLine);
        return s.empty();
    }
    else 
    {
        return false;
    }
}

int CSubtitleManipulate::parse_Subtitle_Time(const char* szLine, std::string& str_from_Time, std::string& str_To_Time, long& fromTimeVal, long& to_Time_Val)
{
    int ret = 1;
    std::regex regex_subtime("([0-9]{2}\\:[0-9]{2}\\:[0-9]{2}\\,[0-9]{3})[[:space:]]*-->[[:space:]]*([0-9]{2}\\:[0-9]{2}\\:[0-9]{2}\\,[0-9]{3})");
	std::regex regex_milli("([0-9]{2})\\:([0-9]{2})\\:([0-9]{2})\\,([0-9]{3})");
    std::cmatch subtime_match;
	std::cmatch milli_match;

	long fromTimeMilli = 0;
	long toTimeMilli = 0;

    if (regex_match(szLine, subtime_match, regex_subtime) && subtime_match.size() == 3)
    {
        str_from_Time = subtime_match[1];
        str_To_Time = subtime_match[2];
        ret = 0;    // Success
    
		regex_match(str_from_Time.c_str(), milli_match, regex_milli);
		int n_startTime = (atoi(string(milli_match[1]).c_str()) * 60 * 60  + 
							atoi(string(milli_match[2]).c_str()) + 60 + 
							atoi(string(milli_match[3]).c_str()) )  * 1000 + 
							atoi(string(milli_match[4]).c_str());

		regex_match(str_To_Time.c_str(), milli_match, regex_milli);
		int n_ToTheTime = (atoi(string(milli_match[1]).c_str()) * 60 * 60  + 
							atoi(string(milli_match[2]).c_str()) + 60 + 
							atoi(string(milli_match[3]).c_str()) )  * 1000 + 
							atoi(string(milli_match[4]).c_str());

		fromTimeVal = n_startTime;
		to_Time_Val = n_ToTheTime;
	}

    return ret;
}