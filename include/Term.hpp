#pragma once

#include <fmt/core.hpp>
#include <termio.h>

class Term
{
public:
	Term(std::uint8_t color);
	Term(const Term&) = delete;
	Term(Term&&) = delete;
	~Term();

	void flush();
	void echo(bool enable);
	void icanon(bool enable);

	static void alt_screen(bool enable) { fmt::print("\033[?1049{}", enable ? 'h' : 'l'); }
	static void show_cursor(bool enable) { fmt::print("\033[?25{}", enable ? 'h' : 'l'); }

	void update_size();

	static void handle_interrupt(int) { m_interrupted = true; }

	static void handle_resize(int)
	{
		m_resized = true;
		cls();
	}

	static void cls() { fmt::print("\033[H\033[2J\033[3J"); }

	static void move_up(std::size_t count = 1) { fmt::print("\033[{}A", count); }
	static void move_down(std::size_t count = 1) { fmt::print("\033[{}B", count); }
	static void move_right(std::size_t count = 1) { fmt::print("\033[{}C", count); }
	static void move_left(std::size_t count = 1) { fmt::print("\033[{}D", count); }

	static void goto_xy(std::size_t x, std::size_t y) { fmt::print("\033[{1};{0}H", x, y); }
	static void goto_rc(std::size_t r, std::size_t c) { fmt::print("\033[{};{}H", r, c); }

	void update();
	void draw();

	using time_unit = std::pair<std::uint8_t, std::uint8_t>;

private:
	void print_row(std::string_view row);
	void print_digit_on_its_own(std::uint8_t id);
	void print_unit_of_time(Term::time_unit unit);
	void draw_colon();

private:
	struct termios m_original_attrs;
	struct termios m_current_attrs;

	static inline bool m_resized {false};
	static inline bool m_interrupted {false};

	std::uint16_t m_width {80};
	std::uint16_t m_height {40};

	time_unit m_hour {0, 0};
	time_unit m_minute {0, 0};
	time_unit m_second {0, 0};

	std::uint8_t m_color {45};
};
