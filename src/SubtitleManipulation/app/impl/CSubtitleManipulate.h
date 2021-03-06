#ifndef APP_IMPL_CSUBTITLEMANIPULATE_H_
#define APP_IMPL_CSUBTITLEMANIPULATE_H_

#include "app/interface/ISubtitleManipulate.h"
#include <string>
#include <vector>

class CSubtitleManipulate : public ISubtitleManipulate
{
public:
    virtual ~CSubtitleManipulate();
    int load_FromFile(const char* sz_File, std::vector<SubtitleLine>& v_out, SuccessResult& ret);
    int groupingSentences(std::vector<SubtitleLine> v_sub_title, std::vector<SubtitleLine>& v_out);
    int groupingSentences_ByBlockTime(int blockByMinute,std::vector<SubtitleLine> v_sub_title, std::vector<SubtitleLine>& v_out);
    int writeToFile(const char* sz_File_Out, std::vector<SubtitleLine> v_sub);

private:
    bool is_MarkType(const char* szLine, int n_mark_Type);
    int next_candidateMarkTypes(int currentType, int arr_outCandidates[2], int& n_count);
    int parse_Subtitle_Time(const char* szLine, std::string& str_from_Time, std::string& str_To_Time, long& fromTimeVal, long& to_Time_Val);
};

#endif // !APP_IMPL_CSUBTITLEMANIPULATE_H_