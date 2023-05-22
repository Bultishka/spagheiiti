#ifndef __CL_FIELD__H
#define __CL_FIELD__H
#include "cl_base.h"

class cl_field : public cl_base
{
	int lines, columns;
	vector <string> field;
public:
	cl_field(cl_base* p_head_object, string s_name);
	void set_columns(int columns);
	vector<string> get_field();
	void winners_signal(string& command);
	void ball_signal_begin(string& command);
	void ball_signal_move(string& command);
	void signal_output(string& command);
	void handler_panel(string& command);
	void handler_ball(string& command);
	void handler_application(string& command);
};

#endif
