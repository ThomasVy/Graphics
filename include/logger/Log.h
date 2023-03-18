#pragma once
#include "fmt/core.h"
#include "fmt/xchar.h"
#include "fmt/color.h"

namespace logger {
	template <typename S1, typename S3, typename... Args>
	void _log(S1&& prefix, fmt::color color, S3&& format_str, Args&&... args) {
		fmt::print(
			"[{}]: {}\n",
			fmt::styled(std::forward<S1>(prefix), fmt::fg(color)),
			fmt::format(fmt::runtime(std::forward<S3>(format_str)), std::forward<Args>(args)...)
		);
		std::fflush(stdout);
	}

	template <typename S, typename... Args>
	void Debug(S &&format_str, Args&&... args) {
		_log("DEBUG", fmt::color::green , std::forward<S>(format_str), std::forward<Args>(args)...);
	}

	template <typename S, typename... Args>
	void Info(S &&format_str, Args&&... args) {
		_log("INFO", fmt::color::white, std::forward<S>(format_str), std::forward<Args>(args)...);
	}

	template <typename S, typename... Args>
	void Warn(S &&format_str, Args&&... args) {
		_log("WARN", fmt::color::yellow, std::forward<S>(format_str), std::forward<Args>(args)...);
	}

	template <typename S, typename... Args>
	void Error(S &&format_str, Args&&... args) {
		_log("ERROR", fmt::color::red, std::forward<S>(format_str), std::forward<Args>(args)...);
	}
}