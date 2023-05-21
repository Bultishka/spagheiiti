#include "cl_base.h"

cl_base::cl_base(cl_base* p_head_object, string s_name) //����������� ������� �������� ������
{
	this->p_head_object = p_head_object;
	this->s_name = s_name;

	if (p_head_object != nullptr) //���������� � ������ ���������� �� ���������� �������, ��� �����������
	{
		p_head_object->p_sub_objects.push_back(this);
	}
}


cl_base :: ~cl_base()
{
	for (int i = 0; i < p_sub_objects.size(); i++) //������������ ������, ���������� ��� ���������� �������
	{
		delete p_sub_objects[i];
	}
}


void cl_base::set_line(string line)
{
	this->line = line;
}


bool cl_base::set_name(string s_new_name) //������ ����� �������
{
	if (get_head() != nullptr) //�������� �� ������� ��������� �������
		for (int i = 0; i < get_head()->p_sub_objects.size(); i++)
			if (get_head()->p_sub_objects[i]->get_name() == s_new_name) //�������� �� ������������ ����� ����� ���������� ��������
				return false;
	this->s_name = s_new_name; //��������� ����� �������
	return true;
}


void cl_base::set_r(int enable) //��������� ��������� �������
{
	if (enable == 0) //���������� ���������� ��������
	{
		for (int i = 0; i < p_sub_objects.size(); i++)
			p_sub_objects[i]->set_r(0);
		is_ready = enable; //���������� ������ �������
	}
	else
	{
		bool checker = true; //����������� ��������� ���������
		cl_base* object = this->get_head();
		while (object != nullptr) //�������� ������������ �������� ����� �������� ������, ������ �� ���������
		{
			if (object->is_ready == 0) //�������� ������������� ��������� �������
			{
				checker = false;
				break;
			}
			object = object->get_head(); //������� �� ����� ������� ������� � ������
		}
		if (checker == true) //������ ����� ��������
		{
			is_ready = enable;
		}

	}
}


string cl_base::get_name() //������ ����� �������
{
	return s_name;
}


string cl_base::get_line()
{
	return line;
}


cl_base* cl_base::get_head() //������ ��������� �� �������� ������
{
	return p_head_object;
}


cl_base* cl_base::get_root() //������ ��������� �������
{
	if (p_head_object != nullptr) return p_head_object->get_root(); //����������� ������� ������ �� ��������� �������
	return this;
}


cl_base* cl_base::get_sub_object(string s_name) //������ ��������� �� ��������� ������ �� �����
{
	for (int i = 0; i < p_sub_objects.size(); i++)
	{
		if (p_sub_objects[i]->get_name() == s_name)
			return p_sub_objects[i]; //������� ��������� �� ������� ������
	}
	return nullptr; //������ ������� ���
}


cl_base* cl_base::get_object_by_coordinate(string coord) //����������� ���������
{
	if (coord == "")
		return nullptr;

	if (coord == "/") //���������� ��������� �������
		return get_root();

	if (coord.substr(0, 2) == "//") //����� ������� �� ����������� ����� �� ���������
	{
		string object_name = coord.substr(2, coord.size() - 2); //��������� "//" �� ����� �������
		return find_object_from_root(object_name); //����� �������
	}

	if (coord == ".") //������������� ������� ������
		return this;

	if (coord[0] == '.') //����� ������� �� ����������� ����� �� ��������
	{
		string object_name = coord.substr(1, coord.size() - 1); //��������� "." �� ����� �������
		return find_object_from_current(object_name);
	}

	stringstream sin(coord);
	string object_name;
	cl_base* p_object = this;

	//��������������� "����� ������� ���������"
	if (coord[0] == '/')
	{
		p_object = get_root();
		getline(sin, object_name, '/');
	}

	while (getline(sin, object_name, '/'))
	{
		p_object = p_object->get_sub_object(object_name);
		if (p_object == nullptr)
			break;
	}
	return p_object;
}


vector<cl_base*> cl_base::get_sub_objects() //������ ������� ���������� �� ���������� �������
{
	return p_sub_objects;
}


int cl_base::count(string s_name) // ������� ���������� ��������� �������� � ������ ������
{
	int counter = 0; // ���������� ��������� �������� � ������ ������
	if (get_name() == s_name) // �������� �������� �������
	{
		counter++;
	}
	for (auto p_sub_object : p_sub_objects) // ������ �� ����������� ��������
	{
		counter += p_sub_object->count(s_name); // ����������� �����
	}
	return counter;
}


cl_base* cl_base::search_object(string s_name) // ������ ������� �� ����� �� �������� �������
{
	cl_base* p_found = nullptr;
	if (get_name() == s_name) // �������� ����� �������� �������
	{
		return this;
	}
	for (auto p_sub_object : p_sub_objects) // ������ �� ����������� ��������
	{
		p_found = p_sub_object->search_object(s_name); // ����������� ����� ������ ��� ������� ����������� �������
		if (p_found != nullptr) // ��������� �� ��������� ������ ���������?
		{
			return p_found; // ������� ��������� �� ��������� ������
		}
	}
	return p_found;

}


cl_base* cl_base::find_object_from_current(string s_name) // ����� ������� �� ����� � ������ �������� �� �������� ������� � ��������� �� ������������ ����� �������� �������
{
	if (count(s_name) != 1) // �������� ������� �� ������������
	{
		return nullptr;
	}
	return search_object(s_name); // ������� ������ ������ �� ����� �������� �������, ���� ������ ��������
}


cl_base* cl_base::find_object_from_root(string s_name) //���������� ������� �� ��� ����� � ������ �������� �� ���������
{
	return get_root()->find_object_from_current(s_name); //����� �������
}


void cl_base::print_tree(int level)
{
	get_root()->print_branch(0); //����� ������ ������ ����� ��� ��������� �������

}


void cl_base::print_branch(int level) //����� �������� �������� (������ ��� �����) �� �������� �������
{
	cout << "\n";
	cout.width(4 * level + get_name().size());
	cout << get_name();
	for (int i = 0; i < p_sub_objects.size(); i++)
	{
		p_sub_objects[i]->print_branch(level + 1); //����������� ����� ��������� ������

	}
}


void cl_base::print_tree_readiness(int level) //����� ������ �������� � ���������� ��� ���������
{
	cout << "\n";
	cout.width(4 * level + get_name().size());
	cout << get_name();
	if (is_ready) cout << " is ready";
	else cout << " is not ready";
	for (int i = 0; i < p_sub_objects.size(); i++)
		p_sub_objects[i]->print_tree_readiness(level + 1); //����������� ����� ������ �������� � ���������� ��� ���������
}


void cl_base::set_connect(TYPE_SIGNAL    p_signal,      //����� ��������� ����� ����� ���������
	cl_base* p_object,
	TYPE_HANDLER   p_ob_handler)
{
	//�������� ������� ��������� ��������� ������������� ������
	for (unsigned int i = 0; i < connects.size(); i++)
	{
		if (connects[i].p_signal == p_signal &&
			connects[i].p_cl_base == p_object &&
			connects[i].p_handler == p_ob_handler)
		{
			return;
		}
	}

	o_sh   p_value;                 // �������� ������� ��������� ��� �������� ���������� � ����� �����

	p_value.p_signal = p_signal;
	p_value.p_cl_base = p_object;
	p_value.p_handler = p_ob_handler;

	connects.push_back(p_value);          // ���������� ����� �����
}


void cl_base::delete_connect(TYPE_SIGNAL    p_signal,      //����� �������� ����� ����� ����������� ���������
	cl_base* p_object,
	TYPE_HANDLER   p_ob_handler)
{
	for (unsigned int i = 0; i < connects.size(); i++)
	{
		if (connects[i].p_signal == p_signal &&
			connects[i].p_cl_base == p_object &&
			connects[i].p_handler == p_ob_handler)
		{
			connects.erase(connects.begin() + i);
			return;
		}
	}
}


void cl_base::emit_signal(TYPE_SIGNAL p_signal, string& s_command) //����� ��������� �������
{
	if (!is_ready)
	{
		return;
	}

	TYPE_HANDLER   p_handler;
	cl_base* p_object;

	(this->*p_signal) (s_command);  // ����� ������ �������

	for (unsigned int i = 0; i < connects.size(); i++) // ���� �� ���� ������������
	{
		if (connects[i].p_signal == p_signal)      // ����������� ����������� �����������
		{
			p_handler = connects[i].p_handler;
			p_object = connects[i].p_cl_base;

			if (p_object->is_ready != 0)
				(p_object->*p_handler) (s_command);      // ����� ������ �����������
		}
	}
}


void cl_base::set_class(int o_class) //����� ��������� �������� ������ �������
{
	this->o_class = o_class;
}


int cl_base::get_class() //������ �������� ������ �������
{
	return this->o_class;
}


string cl_base::get_path() //�������� �������
{
	if (this->p_head_object == nullptr)
		return "/";
	string path = '/' + this->get_name();
	cl_base* temp = p_head_object;
	while (temp->p_head_object != nullptr) //����������� ������� ���� �� �������
	{
		path = "/" + temp->s_name + path;
		temp = temp->p_head_object;
	}
	return path;
}