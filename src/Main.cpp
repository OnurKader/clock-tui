#include "Term.hpp"

#include <unistd.h>

int main(int argc, char** argv)
{
	std::uint8_t color = 45;
	if(argc > 2)
	{
		if(!std::strncmp(argv[1], "-c", 2))
		{
			const auto color_arg = (std::uint8_t)std::atoi(argv[2]);
			if(color_arg > 7 || color_arg == 0)
			{
				fmt::print(stderr, "Invalid color input!\nUsage: clock [-c (1..7)]\n");
				return 1;
			}

			color = 40 + color_arg;
		}
	}

	Term term {color};

	while(true)
	{
		term.update();
		term.draw();
		usleep(1'000'000);
	}

	return 0;
}
