#ifndef __CL_APPLICATION__H
#define __CL_APPLICATION__H
#include "cl_base.h"
#include "cl_input.h"
#include "cl_panel.h"
#include "cl_field.h"
#include "cl_ball.h"
#include "cl_output.h"

class cl_application : public cl_base
{
	string data;
	bool checker = false;
public:
	cl_application(cl_base* p_head_object);
	void build_tree_objects();
	int exec_app();
	void lever(cl_base* step);

	void signal_input(string& command);
	void signal_panel(string& command);
	void signal_field(string& command);
	void handler_input(string& command);
	void handler_panel(string& command);
};

#endif
