#include "cl_output.h"

cl_output::cl_output(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name)
{
}


void cl_output::handler_field(string& command)
{
	cout << command << "\n";
}


void cl_output::handler_panel(string& command)
{
	cout << command;
}
