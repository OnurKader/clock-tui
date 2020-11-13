#include "Term.hpp"

#include <csignal>
#include <ctime>
#include <stdexcept>
#include <unistd.h>

Term::Term()
{
	if(tcgetattr(STDIN_FILENO, &m_original_attrs) != 0)
	{
		throw std::runtime_error {"Couldn't get the terminal attributes"};
	}

	m_current_attrs = m_original_attrs;

	signal(SIGWINCH, handle_resize);
	signal(SIGINT, handle_interrupt);

	update_size();

	alt_screen(true);
	echo(false);
	icanon(false);
	show_cursor(false);

	cls();
}

Term::~Term()
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &m_original_attrs);

	alt_screen(false);
	echo(true);
	icanon(true);
	show_cursor(true);
}

void Term::flush()
{
	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &m_current_attrs) != 0)
	{
		throw std::runtime_error {"Couldn't flush new terminal settings"};
	}
}

void Term::echo(bool enable)
{
	if(enable)
		m_current_attrs.c_lflag |= ECHO;
	else
		m_current_attrs.c_lflag &= (tcflag_t)~ECHO;

	flush();
}

void Term::icanon(bool enable)
{
	if(enable)
		m_current_attrs.c_lflag |= ICANON;
	else
		m_current_attrs.c_lflag &= (tcflag_t)~ICANON;

	flush();
}

void Term::update_size()
{
	struct winsize ws;
	if(ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) != 0)
	{
		// MAYBE: If this fails, read $COLUMNS and $LINES
		throw std::runtime_error {"Couldn't determine the terminal size"};
	}

	m_width = ws.ws_col;
	m_height = ws.ws_row;
}

inline std::pair<std::uint8_t, std::uint8_t> get_digits_of_time_unit(int unit)
{
	return {(unit / 10) % 10, unit % 10};
}

void Term::update()
{
	if(m_resized)
	{
		update_size();
		m_resized = false;
	}

	if(m_interrupted)
	{
		this->~Term();
		std::exit(0);
	}

	const std::time_t t = std::time(nullptr);
	const std::tm now = *std::localtime(&t);

	m_hour = get_digits_of_time_unit(now.tm_hour);
	m_minute = get_digits_of_time_unit(now.tm_min);
	m_second = get_digits_of_time_unit(now.tm_sec);
}

void Term::draw()
{
	// TODO: Draw the time
	fmt::print("\033[{};{}H", m_height / 2 + 1, m_width / 2 - 4);
	fmt::print("\033[1;32m{}\033[1;33m{}:\033[1;34m{}\033[1;35m{}:\033[1;31m{}\033[1;36m{}\033[m\n",
			   m_hour.first,
			   m_hour.second,
			   m_minute.first,
			   m_minute.second,
			   m_second.first,
			   m_second.second);
}
