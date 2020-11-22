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
