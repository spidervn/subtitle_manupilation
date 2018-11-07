#include "CSubtitleManipulate.h"

CSubtitleManipulate::~CSubtitleManipulate()
{
}

int CSubtitleManipulate::load_FromFile(const char* sz_File, std::vector<SubtitleLine>& v_out)
{
    /* A state machine for reading the Subtitle file */
    return 0;
}

int  CSubtitleManipulate::groupingSentences(std::vector<SubtitleLine> v_sub_title, std::vector<SubtitleLine>& v_out)
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