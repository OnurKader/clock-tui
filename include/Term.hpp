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

	static void handle_interrupt(int) { m_interrupted = true; }

	static void handle_resize(int)
	{
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
	static inline bool m_interrupted {false};

	std::uint16_t m_width {80};
	std::uint16_t m_height {40};

	std::pair<std::uint8_t, std::uint8_t> m_hour {0, 0};
	std::pair<std::uint8_t, std::uint8_t> m_minute {0, 0};
	std::pair<std::uint8_t, std::uint8_t> m_second {0, 0};
};
