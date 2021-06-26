//logger-call.h
#define LOG(logentry, loglevel) logger.log(__FILE__, __func__, __LINE__, logentry, loglevel)

