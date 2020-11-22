#include "Term.hpp"

#include <ctime>
#include <fmt/core.h>
#include <unistd.h>

int main()
{
	Term term;

	while(true)
	{
		term.update();
		term.draw();
		usleep(1'000'000);
	}

	return 0;
}
