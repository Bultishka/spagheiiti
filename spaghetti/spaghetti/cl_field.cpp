#include "cl_field.h"

cl_field::cl_field(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name)
{
	vector<string> field;
}


void cl_field::set_columns(int columns)
{
	this->columns = columns;
}


void cl_field::ball_signal_begin(string& command)
{
}


void cl_field::ball_signal_move(string& command)
{
}


void cl_field::signal_output(string& command)
{
}

void cl_field::handler_panel(string& command)
{
	emit_signal(SIGNAL_D(cl_field::ball_signal_begin), command);
}


void cl_field::handler_ball(string& command)
{
	int i_line, i_column;
	stringstream sin(command);
	sin >> i_line >> i_column;
	i_column -= 1;
	if (field[i_line - 1][i_column] == '0')
	{
		if (i_column + 1 != columns)
			command = to_string(i_line + 1) + " : ";
		else
			command = to_string(i_line + 1) + "\n";

		emit_signal(SIGNAL_D(cl_field::signal_output), command);
		command = to_string(i_column + 1) + " " + to_string(i_line + 1);
		if (i_line == field.size())
			command += " V";
		else command += " P";
		emit_signal(SIGNAL_D(cl_field::ball_signal_move), command);
	}
	else if (field[i_line - 1][i_column] == '1')
	{
		if (i_column + 1 != columns)
			command = to_string(i_line) + " : ";
		else
			command = to_string(i_line) + "\n";

		emit_signal(SIGNAL_D(cl_field::signal_output), command);
		field[i_line - 1][i_column] = '0';
	}
}


void cl_field::handler_application(string& command)
{
	if ((int)command.find(" ") == -1)
	{
		field.push_back(command);
	}
}