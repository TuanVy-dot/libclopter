/*
 * A liblogger(by myself, github - TuanVy-dot/liblogger) library supporting API
 * Define LOGGER *CLOPTER in your source and use debug version(with -DLOG)
 * See my repo for more info
 * with your own config (must compile using make libdb, not lib, store in bin_db)
*/

#ifndef LOG_API_H
#define LOG_API_H


#include "logger.h"
extern LOGGER *CLOPTER; // declare anyway to avoid warning
                        // since it's not used it will not affect
                        // the product
#undef logger_logf
#undef logger_tracef
#undef logger_debugf
#undef logger_infof
#undef logger_warningf
#undef logger_errorf
#undef logger_fatalf
#undef logger_log
#undef logger_trace
#undef logger_debug
#undef logger_info
#undef logger_warning
#undef logger_error
#undef logger_fatal

#ifdef LOG

/* redefine logging macro to not need to specify logger everytimes */

#define logger_logf(level, msg, ...) \
__logger_msg__(__FILE__, __LINE__, CLOPTER, level, msg, __VA_ARGS__)

#define logger_tracef(msg, ...) \
__logger_msg__(__FILE__, __LINE__, CLOPTER, TRACE, msg, __VA_ARGS__)
#define logger_debugf(msg, ...) \
__logger_msg__(__FILE__, __LINE__, CLOPTER, DEBUG, msg, __VA_ARGS__)
#define logger_infof(msg, ...) \
__logger_msg__(__FILE__, __LINE__, CLOPTER, INFO, msg, __VA_ARGS__)
#define logger_warningf(msg, ...) \
__logger_msg__(__FILE__, __LINE__, CLOPTER, WARNING, msg, __VA_ARGS__)
#define logger_errorf(msg, ...) \
__logger_msg__(__FILE__, __LINE__, CLOPTER, ERROR, msg, __VA_ARGS__)
#define logger_fatalf(msg, ...) \
__logger_msg__(__FILE__, __LINE__, CLOPTER, FATAL, msg, __VA_ARGS__)

#define logger_log(level, msg) \
__logger_msg__(__FILE__, __LINE__, CLOPTER, level, msg)

#define logger_trace(msg) \
__logger_msg__(__FILE__, __LINE__, CLOPTER, TRACE, msg)
#define logger_debug(msg) \
__logger_msg__(__FILE__, __LINE__, CLOPTER, DEBUG, msg)
#define logger_info(msg) \
__logger_msg__(__FILE__, __LINE__, CLOPTER, INFO, msg)
#define logger_warning(msg) \
__logger_msg__(__FILE__, __LINE__, CLOPTER, WARNING, msg)
#define logger_error(msg) \
__logger_msg__(__FILE__, __LINE__, CLOPTER, ERROR, msg)
#define logger_fatal(msg) \
__logger_msg__(__FILE__, __LINE__, CLOPTER, FATAL, msg)

#else

/* redefine macros with nothing to remove by the preprocessor */
#define logger_log(level, msg) (void *)0
#define logger_trace(msg) (void *)0
#define logger_debug(msg) (void *)0
#define logger_info(msg) (void *)0
#define logger_warning(msg) (void *)0
#define logger_error(msg) (void *)0
#define logger_fatal(msg) (void *)0
#define logger_logf(level, msg, ...) (void *)0
#define logger_tracef(msg, ...) (void *)0
#define logger_debugf(msg, ...) (void *)0
#define logger_infof(msg, ...) (void *)0
#define logger_warningf(msg, ...) (void *)0
#define logger_errorf(msg, ...) (void *)0

#endif

#endif
