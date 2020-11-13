#include "Term.hpp"

#include <chrono>
#include <csignal>
#include <fmt/core.h>
#include <sys/time.h>
#include <unistd.h>

void alarm_timer_stuff(int) { fmt::print("1 Second has passed\n"); }

int main()
{
	signal(SIGPROF, alarm_timer_stuff);

	Term term;
	fmt::print("TIME!\n");

	const struct itimerval interval
	{
		{1, 0}, {}
	};

	auto a = setitimer(ITIMER_PROF, &interval, nullptr);
	fmt::print("a: {}\n", a);

	for(int _ = 0; _ < 5; ++_)
		sleep(1);

	return 0;
}
