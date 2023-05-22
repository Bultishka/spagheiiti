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
	
	if (column.front() == '0')
	{
		column.pop();
	}
	else
	{
		column.front() = '0';
	}
	command = to_string(column.size()) + " " + to_string(num);
	emit_signal(SIGNAL_D(cl_ball::signal_field), command);
	if (column.empty())
		emit_signal(SIGNAL_D(cl_ball::signal_panel), command);
	/*set_line(i_line);
	command = i_line + ' ' + get_name();
	emit_signal(SIGNAL_D(cl_ball::signal_field), command);
	set_line(i_line);
	cout << get_line() << " " << get_name() << "\n";
	if (checker == "V")
	{
		command = get_name();
		emit_signal(SIGNAL_D(cl_ball::signal_panel), command);
	}*/
}


void cl_ball::handler_fill(string& command)
{
	/*stringstream sin(command);
	sin >> i_line >> checker;*/
	column.push(command[num - 1]);
}