#include <fmt/core.hpp>
#include <termio.h>

class Term
{
public:
	Term();
	~Term();

	void flush();
	void echo(bool enable);
	void icanon(bool enable);

	static void alt_screen(bool enable) { fmt::print("\033[?1049{}", enable ? 'h' : 'l'); }
	static void show_cursor(bool enable) { fmt::print("\033[?25{}", enable ? 'h' : 'l'); }

	void update_size();

	static void handle_interrupt(int)
	{
		alt_screen(false);
		show_cursor(true);
	}

	static void handle_resize(int)
	{
		// update_size();
		m_resized = true;
		cls();
	}

	static void cls() { fmt::print("\033[H\033[2J\033[3J"); }

	void update();
	void draw();

private:
	struct termios m_original_attrs;
	struct termios m_current_attrs;

	static inline bool m_resized {false};

	std::uint16_t m_width {80};
	std::uint16_t m_height {40};
};
