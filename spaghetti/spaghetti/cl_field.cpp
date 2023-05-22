#include "cl_field.h"

cl_field::cl_field(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name)
{
	vector<string> field;
}


void cl_field::ball_signal_begin(string& command)
{
}


void cl_field::ball_signal_fill(string& command)
{
}


void cl_field::signal_output(string& command)
{
	command = to_string(positions[0]);
	for (int i = 1; i < positions.size(); i++)
	{
		command += " : " + to_string(positions[i]);
	}
}

void cl_field::handler_panel(string& command)
{
	emit_signal(SIGNAL_D(cl_field::ball_signal_begin), command);
	emit_signal(SIGNAL_D(cl_field::signal_output), command);
}


void cl_field::handler_ball(string& command) // "9 2"
{
	int i_line, i_column;
	stringstream sin(command);
	sin >> i_line >> i_column;
	i_line = lines - i_line;
	i_column -= 1;
	command = "";
	positions[i_column] = i_line;
	/*if (field.size() == 1)
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
	cout << i_line + 1 << " " << i_column+1 << "\n";*/
	
}


void cl_field::handler_application(string& command)
{
	emit_signal(SIGNAL_D(cl_field::ball_signal_fill), command);
}