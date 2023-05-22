#include "cl_application.h"

cl_application::cl_application(cl_base* p_head_object) : cl_base(p_head_object) //конструктор головного объекта
{
}


void cl_application::build_tree_objects() //метод построения дерева иерархии
{

	this->set_name("system"); //установка имени корневого объекта

	cl_input* input = new cl_input(this, "input");
	cl_panel* panel = new cl_panel(this, "panel");
	cl_field* field = new cl_field(this, "field");
	cl_output* output = new cl_output(this, "output");

	this->set_connect(SIGNAL_D(cl_application::signal_input), input, HANDLER_D(cl_input::handler_application));
	this->set_connect(SIGNAL_D(cl_application::signal_panel), panel, HANDLER_D(cl_panel::handler_application));
	this->set_connect(SIGNAL_D(cl_application::signal_field), field, HANDLER_D(cl_field::handler_application));

	input->set_connect(SIGNAL_D(cl_input::signal_application), this, HANDLER_D(cl_application::handler_input));

	panel->set_connect(SIGNAL_D(cl_panel::signal_field), field, HANDLER_D(cl_field::handler_panel));
	panel->set_connect(SIGNAL_D(cl_panel::signal_output), this, HANDLER_D(cl_application::handler_panel));
	panel->set_connect(SIGNAL_D(cl_panel::signal_output), output, HANDLER_D(cl_output::handler_panel));

	field->set_connect(SIGNAL_D(cl_field::signal_output), output, HANDLER_D(cl_output::handler_field));

	string command = "1";
	
	emit_signal(SIGNAL_D(cl_application::signal_input), command);
	stringstream sin(data);
	int columns, lines;
	sin >> columns >> lines;
	field->setSize(lines, columns);

	lever(this);
	for (int i = 0; i < columns; i++)
	{
		string name = to_string(i + 1);
		cl_ball* ball = new cl_ball(field, name);
		field->set_connect(SIGNAL_D(cl_field::ball_signal_begin), ball, HANDLER_D(cl_ball::handler));
		field->set_connect(SIGNAL_D(cl_field::ball_signal_move), ball, HANDLER_D(cl_ball::handler_move));
		ball->set_connect(SIGNAL_D(cl_ball::signal_panel), panel, HANDLER_D(cl_panel::handler_w_ball));
		ball->set_connect(SIGNAL_D(cl_ball::signal_field), field, HANDLER_D(cl_field::handler_ball));
	}
	lever(this);

	for (int i = 1; i < lines; i++)
	{
		emit_signal(SIGNAL_D(cl_application::signal_input), command);
		emit_signal(SIGNAL_D(cl_application::signal_field), command);
	}
}


void cl_application::lever(cl_base* step) //включение всех объектов дерева
{
	step->set_r(1); //включение объекта по переданному в параметрах указателю

	for (int i = 0; i < step->get_sub_objects().size(); i++) //рекурсивное включение подчинённых объектов
	{
		lever(step->get_sub_objects()[i]);
	}
}


int cl_application::exec_app() //метод выполнения основного алгоритма
{
	lever(this);	//включение дерева, т.к. текущий объект - корневой

	int takt = 1;
	string command = to_string(takt);
	while (true)
	{
		if (command.find(":") != -1) break;
		else emit_signal(SIGNAL_D(cl_application::signal_panel), command);
		takt++;
	}
	return 0;
}


void cl_application::signal_input(string& command)
{
}


void cl_application::signal_panel(string& command)
{

}


void cl_application::signal_field(string& command)
{
}


void cl_application::handler_input(string& command)
{
	data = command;
}


void cl_application::handler_panel(string& command)
{
	data = command;
}