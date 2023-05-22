#ifndef __CL_BALL__H
#define __CL_BALL__H
#include "cl_base.h"

class cl_ball : public cl_base
{
	/*string i_line = "-1";
	string checker = "P";*/
	queue<char> column;
	int num;
public:
	cl_ball(cl_base* p_head_object, string s_name);
	void signal_field(string& command);
	void signal_panel(string& command);
	void handler(string& command);
	void handler_fill(string& command);

};


#endif
