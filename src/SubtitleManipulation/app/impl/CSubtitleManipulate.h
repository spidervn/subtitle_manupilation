#ifndef APP_IMPL_CSUBTITLEMANIPULATE_H_
#define APP_IMPL_CSUBTITLEMANIPULATE_H_

#include "app/interface/ISubtitleManipulate.h"
#include <string>
#include <vector>

class CSubtitleManipulate : public ISubtitleManipulate
{
public:
    virtual ~CSubtitleManipulate();
    int load_FromFile(const char* sz_File, std::vector<SubtitleLine>& v_out);
    int groupingSentences(std::vector<SubtitleLine> v_sub_title, std::vector<SubtitleLine>& v_out);
    int groupingSentences_ByBlockTime(int blockByMinute,std::vector<SubtitleLine> v_sub_title, std::vector<SubtitleLine>& v_out);
    int writeToFile(const char* sz_File_Out, std::vector<SubtitleLine> v_sub);
};

#endif // !APP_IMPL_CSUBTITLEMANIPULATE_H_
