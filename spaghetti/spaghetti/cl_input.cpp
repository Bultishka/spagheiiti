#include "cl_input.h"

cl_input::cl_input(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name)
{
}


void cl_input::handler_application(string& command)
{
	emit_signal(SIGNAL_D(cl_input::signal_application), command);
}


void cl_input::signal_application(string& command)
{
	if (command == "1")
		getline(cin, command);
	else cin >> command;
}