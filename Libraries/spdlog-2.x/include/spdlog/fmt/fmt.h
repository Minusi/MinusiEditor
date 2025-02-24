//
// Copyright(c) 2016-2018 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//

#pragma once

//
// Include a bundled header-only copy of fmtlib or an external one.
// By default, spdlog include its own copy.
//

#if defined(SPDLOG_USE_STD_FORMAT)  // SPDLOG_USE_STD_FORMAT is defined - use std::format
    #include <format>
#elif !defined(SPDLOG_FMT_EXTERNAL)
    #include "bundled/core.h"
    #include "bundled/format.h"
#else  // SPDLOG_FMT_EXTERNAL is defined - use external fmtlib
    #include <fmt/core.h>
    #include <fmt/format.h>
#endif
