#ifndef __CL_BASE__H
#define __CL_BASE__H
#define SIGNAL_D(signal_f) (TYPE_SIGNAL) (&signal_f)
#define HANDLER_D(handler_f) (TYPE_HANDLER) (&handler_f)

#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct link;
class cl_base;

typedef void (cl_base ::* TYPE_SIGNAL) (string&);
typedef void (cl_base ::* TYPE_HANDLER) (string&);

struct o_sh // Структура задания одной связи
{
	TYPE_SIGNAL p_signal; //указатель на метод сигнала
	cl_base* p_cl_base; //указатель на целевой объект
	TYPE_HANDLER p_handler; //указатель на метод обработчика
};

class cl_base
{
private:
	string s_name;
	cl_base* p_head_object;
	vector <cl_base*> p_sub_objects;
	vector <o_sh> connects;
	int is_ready = 0;
	int o_class;
public:
	cl_base(cl_base* p_head_object, string s_name = "Base object");
	~cl_base();

	bool set_name(string s_new_name);
	void set_r(int enable = 1);
	void set_class(int o_class);

	string get_line();
	string get_name();
	cl_base* get_head();
	cl_base* get_root();
	cl_base* get_sub_object(string s_name);
	cl_base* get_object_by_coordinate(string coord);
	vector <cl_base*> get_sub_objects();
	int get_class();
	string get_path();

	int count(string name);

	cl_base* search_object(string s_name);
	cl_base* find_object_from_current(string s_name);
	cl_base* find_object_from_root(string s_name);

	bool move_object(cl_base* head_object);
	void delete_object(string name);

	void print_tree(int level = 0);
	void print_branch(int level);
	void print_tree_readiness(int level = 0);

	void set_connect(TYPE_SIGNAL p_signal, cl_base* p_obj, TYPE_HANDLER p_handler); //Установка связи
	void delete_connect(TYPE_SIGNAL p_signal, cl_base* p_obj, TYPE_HANDLER p_handler); //Удаление связи
	void emit_signal(TYPE_SIGNAL p_signal, string& s_command); //Посылка сигнала обработчику с передачей данных


};


#endif