#pragma once

#include <array>
#include <string_view>

struct Font
{
	static constexpr std::string_view colon = "        "
											  "        "
											  "   **   "
											  "        "
											  "   **   "
											  "        "
											  "        ";

	static constexpr std::size_t font_width = 8;
	static constexpr std::size_t font_height = 7;
	static constexpr std::size_t font_size = font_width * font_height;
	static constexpr std::size_t seperator_width = 4;

	// 12:34:56
	static constexpr std::size_t total_width = 8 * font_width + 3 * seperator_width;

	static constexpr std::array digits = std::to_array<std::string_view>({"********"
																		  "**    **"
																		  "**    **"
																		  "**    **"
																		  "**    **"
																		  "**    **"
																		  "********",

																		  "      **"
																		  "      **"
																		  "      **"
																		  "      **"
																		  "      **"
																		  "      **"
																		  "      **",

																		  "********"
																		  "      **"
																		  "      **"
																		  "********"
																		  "**      "
																		  "**      "
																		  "********",

																		  "********"
																		  "      **"
																		  "      **"
																		  "  ******"
																		  "      **"
																		  "      **"
																		  "********",

																		  "**    **"
																		  "**    **"
																		  "**    **"
																		  "********"
																		  "      **"
																		  "      **"
																		  "      **",

																		  "********"
																		  "**      "
																		  "**      "
																		  "********"
																		  "      **"
																		  "      **"
																		  "********",

																		  "********"
																		  "**      "
																		  "**      "
																		  "********"
																		  "**    **"
																		  "**    **"
																		  "********",

																		  "********"
																		  "      **"
																		  "      **"
																		  "      **"
																		  "      **"
																		  "      **"
																		  "      **",

																		  "********"
																		  "**    **"
																		  "**    **"
																		  "********"
																		  "**    **"
																		  "**    **"
																		  "********",

																		  "********"
																		  "**    **"
																		  "**    **"
																		  "********"
																		  "      **"
																		  "      **"
																		  "      **"

	});
};

/*
▀▄
▄▄▄▄
▄▄▄█
█▄▄▄
*/
