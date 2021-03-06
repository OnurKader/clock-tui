#include "Term.hpp"

#include "Font.hpp"

#include <csignal>
#include <ctime>
#include <stdexcept>
#include <unistd.h>

Term::Term(uint8_t color) : m_color {color}
{
	if(tcgetattr(STDIN_FILENO, &m_original_attrs) != 0)
		throw std::runtime_error {"Couldn't get the terminal attributes"};

	m_current_attrs = m_original_attrs;

	signal(SIGWINCH, handle_resize);
	signal(SIGINT, handle_interrupt);

	update_size();

	alt_screen(true);
	echo(false);
	icanon(false);
	show_cursor(false);
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

constexpr std::string_view get_nth_row_of_digit(std::uint8_t digit_id, std::size_t n)
{
	return Font::digits[digit_id].substr(n * Font::font_width, Font::font_width);
}

constexpr std::string_view get_nth_row_of_colon(std::size_t n)
{
	return Font::colon.substr(n * Font::font_width, Font::font_width);
}

void Term::print_row(std::string_view row)
{
	for(std::size_t i = 0; i < Font::font_width; ++i)
	{
		if(row[i] == '*')
			fmt::print("\033[1;{}m", m_color);

		fmt::print(" \033[m");
	}
}

void Term::draw_colon()
{
	for(std::size_t i = 0; i < Font::font_height; ++i)
	{
		const auto ith_row = get_nth_row_of_colon(i);
		print_row(ith_row);
		move_down();
		move_left(Font::font_width);
	}

	// Set position for the next digit
	move_right(Font::font_width);
	move_up(Font::font_height);
}

void Term::print_digit_on_its_own(std::uint8_t id)
{
	for(std::size_t i = 0; i < Font::font_height; ++i)
	{
		const auto ith_row = get_nth_row_of_digit(id, i);
		print_row(ith_row);
		move_down();
		move_left(Font::font_width);
	}
}

void Term::print_unit_of_time(Term::time_unit unit)
{
	print_digit_on_its_own(unit.first);
	move_right(Font::font_width + Font::seperator_width);
	move_up(Font::font_height);

	print_digit_on_its_own(unit.second);
	move_right(Font::font_width);
	move_up(Font::font_height);
}

void Term::draw()
{
	cls();

	// Center it horizontally
	move_right((m_width - Font::total_width) / 2);
	// Center it vertically
	move_down((m_height - Font::font_height) / 2);

	print_unit_of_time(m_hour);
	draw_colon();
	print_unit_of_time(m_minute);
	draw_colon();
	print_unit_of_time(m_second);

	fmt::print("\n");
}
