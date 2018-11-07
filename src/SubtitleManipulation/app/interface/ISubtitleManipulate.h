#ifndef APP_INTERFACE_ISUBTITLEMANIPULATE_H_
#define APP_INTERFACE_ISUBTITLEMANIPULATE_H_

#include <string>
#include <vector>

struct SubtitleLine {
    int index;
    long fromTheTime;
    long to_Time;
    std::string content;
};

class ISubtitleManipulate
{
public:
    virtual ~ISubtitleManipulate() {}
    virtual int load_FromFile(const char* sz_File, std::vector<SubtitleLine>& v_out) = 0;
    virtual int groupingSentences(std::vector<SubtitleLine> v_sub_title, std::vector<SubtitleLine>& v_out) = 0;
    virtual int groupingSentences_ByBlockTime(int block_ByMilliSecs,std::vector<SubtitleLine> v_sub_title, std::vector<SubtitleLine>& v_out) = 0;
    virtual int writeToFile(const char* sz_File_Out, std::vector<SubtitleLine> v_sub) = 0;
};

#endif // !APP_INTERFACE_ISUBTITLEMANIPULATE_H_