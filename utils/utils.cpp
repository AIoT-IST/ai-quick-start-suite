#include <chrono>
#include <iomanip>
#include <regex>
#include <string>
#include <sstream>
#include <vector>
#include "gstadmeta.h"
#include "utils.h"

std::vector<std::string> split(std::string inputString)
{
    std::regex delimiter(",");
    std::vector<std::string> list(std::sregex_token_iterator(inputString.begin(), inputString.end(), delimiter, -1), std::sregex_token_iterator());
    return list;
}

GstAdBatchMeta* gst_buffer_get_ad_batch_meta(GstBuffer* buffer)
{
    gpointer state = NULL;
    GstMeta* meta;
    const GstMetaInfo* info = GST_AD_BATCH_META_INFO;
    
    while ((meta = gst_buffer_iterate_meta (buffer, &state))) 
    {
        if (meta->info->api == info->api) 
        {
            GstAdMeta *admeta = (GstAdMeta *) meta;
            if (admeta->type == AdBatchMeta)
                return (GstAdBatchMeta*)meta;
        }
    }
    return NULL;
}

std::string return_current_time_and_date()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}

std::string round2String(double d, int r)
{
    float div = 1;
    for(int i = 0 ; i < r ; ++ i)
        div *= 10;
    
    int s = d * div;
    float t = s / div;
    std::string str = std::to_string (t);
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    return str;
}
