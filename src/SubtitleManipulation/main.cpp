#include <stdlib.h>
#include <stdio.h>
#include "app/impl/CSubtitleManipulate.h"

int usage()
{
    // Print the usage
    printf("Subtitle manipulation.\r\n");
    printf("Usage: ./subtitle_manipulate [options] file_sub_title file_out\r\n");
    printf("Options:\r\n");
    printf("--block-min\r\n");
    printf("Example:");

    return 0;
}

int main(int argc, char const *argv[])
{    
    ISubtitleManipulate* pEng;

    if (argc < 2)
    {
        return usage();
    }
    else if (argc == 3)
    {
        std::vector<SubtitleLine> v_sub;
        std::vector<SubtitleLine> v_subSentence;
        pEng = new CSubtitleManipulate();
        
        if (pEng->load_FromFile(argv[1], v_sub) == 0)
        {
            pEng->groupingSentences(v_sub, v_subSentence);
            pEng->writeToFile(argv[2], v_subSentence);
        }        
    }

    return 0;
}
