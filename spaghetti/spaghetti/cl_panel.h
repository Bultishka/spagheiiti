#ifndef __CL_PANEL__H
#define __CL_PANEL__H
#include "cl_base.h"
class cl_panel : public cl_base
{
	string winners;
public:
	cl_panel(cl_base* p_head_object, string s_name);
	void signal_field(string& command);
	void signal_output(string& command);
	void signal_application(string& command);
	void handler_application(string& command);
	void handler_w_ball(string& command);
};


#endif
