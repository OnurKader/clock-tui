#include "Term.hpp"

#include <csignal>
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

void Term::update()
{
	if(m_resized)
	{
		update_size();
		m_resized = false;
	}

	// TODO: Update time
}

void Term::draw()
{
	// TODO: Draw the time
}
