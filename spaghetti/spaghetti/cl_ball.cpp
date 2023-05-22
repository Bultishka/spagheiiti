#include "cl_ball.h"

cl_ball::cl_ball(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name)
{
}


void cl_ball::signal_panel(string& command)
{
}


void cl_ball::signal_field(string& command)
{
}


void cl_ball::handler(string& command)
{
	command = "";
	command = i_line + ' ' + get_name();
	emit_signal(SIGNAL_D(cl_ball::signal_field), command);
	if (checker == "V")
	{
		command = get_name();
		emit_signal(SIGNAL_D(cl_ball::signal_panel), command);
	}
}


void cl_ball::handler_move(string& command)
{
	stringstream sin(command);
	string n;
	sin >> n;
	if (n == get_name())
		sin >> i_line >> checker;
}