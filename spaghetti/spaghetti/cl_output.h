#ifndef __CL_OUTPUT__H
#define __CL_OUTPUT__H
#include "cl_base.h"

class cl_output : public cl_base
{
public:
	cl_output(cl_base* p_head_object, string s_name);
	void handler_panel(string& command);
	void handler_field(string& command);
};

#endif
