#include "cl_panel.h"

cl_panel::cl_panel(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name)
{
}


void cl_panel::signal_field(string& command)
{
}


void cl_panel::signal_application(string& command)
{
}


void cl_panel::signal_output(string& command)
{
}



void cl_panel::handler_application(string& command)
{
	command = "";
	if (winners.empty())
	{
		emit_signal(SIGNAL_D(cl_panel::signal_field), command);
	}
	else if (!winners.empty())
	{
		command = winners;
		emit_signal(SIGNAL_D(cl_panel::signal_output), command);
		emit_signal(SIGNAL_D(cl_panel::signal_application), command);
	}
}


void cl_panel::handler_w_ball(string& command)
{
	if (winners.empty())
		winners = command;
	else winners += " : " + command;
}