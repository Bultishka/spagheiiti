#include "cl_field.h"

cl_field::cl_field(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name)
{
	vector<string> field;
}


void cl_field::ball_signal_begin(string& command)
{
}


void cl_field::ball_signal_move(string& command)
{
}


void cl_field::signal_output(string& command)
{
	command = get_sub_objects()[0]->get_line() + " : ";
	for (int i = 1; i < get_sub_objects().size() - 1; i++)
	{
		command += get_sub_objects()[i]->get_line() + " : ";
	}
	if (get_sub_objects().size() > 1)
		command += get_sub_objects()[get_sub_objects().size() - 1]->get_line();
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
	i_line -= 1;
	i_column -= 1;
	command = "";
	if (field.size() == 1)
	{
		command = to_string(i_line+1) + " V";
		emit_signal(SIGNAL_D(cl_field::ball_signal_move), command);
	}
	else if (field[i_line + 1][i_column] == '0')
	{
		command = to_string(i_line + 2);
		if (i_line + 1 == field.size())
			command += " V";
		else command += " P";
		emit_signal(SIGNAL_D(cl_field::ball_signal_move), command);
	}
	else if (field[i_line + 1][i_column] == '1')
	{
		field[i_line + 1][i_column] = '0';
	}
	cout << i_line + 1 << " " << i_column+1 << "\n";
}


void cl_field::handler_application(string& command)
{
	if ((int)command.find(" ") == -1)
	{
		field.push_back(command);
	}
}