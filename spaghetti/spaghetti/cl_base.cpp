#include "cl_base.h"

cl_base::cl_base(cl_base* p_head_object, string s_name) //конструктор объекта базового класса
{
	this->p_head_object = p_head_object;
	this->s_name = s_name;

	if (p_head_object != nullptr) //добавление в вектор указателей на подчинённые объекты, при возможности
	{
		p_head_object->p_sub_objects.push_back(this);
	}
}


cl_base :: ~cl_base()
{
	for (int i = 0; i < p_sub_objects.size(); i++) //освобождение памяти, выделенной под подчинённые объекты
	{
		delete p_sub_objects[i];
	}
}


void cl_base::set_line(string line)
{
	this->line = line;
}


bool cl_base::set_name(string s_new_name) //сеттер имени объекта
{
	if (get_head() != nullptr) //проверка на наличие головного объекта
		for (int i = 0; i < get_head()->p_sub_objects.size(); i++)
			if (get_head()->p_sub_objects[i]->get_name() == s_new_name) //проверка на уникальность имени среди подчинённых объектов
				return false;
	this->s_name = s_new_name; //установка имени объекта
	return true;
}


void cl_base::set_r(int enable) //установка состояния объекта
{
	if (enable == 0) //выключение подчинённых объектов
	{
		for (int i = 0; i < p_sub_objects.size(); i++)
			p_sub_objects[i]->set_r(0);
		is_ready = enable; //выключение самого объекта
	}
	else
	{
		bool checker = true; //возможность состояния включения
		cl_base* object = this->get_head();
		while (object != nullptr) //проверка включённости объектов более высокого уровня, вплоть до корневого
		{
			if (object->is_ready == 0) //проверка выключенности головного объекта
			{
				checker = false;
				break;
			}
			object = object->get_head(); //переход на более высокий уровень в дереве
		}
		if (checker == true) //объект можно включать
		{
			is_ready = enable;
		}

	}
}


string cl_base::get_name() //геттер имени объекта
{
	return s_name;
}


string cl_base::get_line()
{
	return line;
}


cl_base* cl_base::get_head() //геттер указателя на головной объект
{
	return p_head_object;
}


cl_base* cl_base::get_root() //геттер корневого объекта
{
	if (p_head_object != nullptr) return p_head_object->get_root(); //рекурсивный переход вплоть до корневого объекта
	return this;
}


cl_base* cl_base::get_sub_object(string s_name) //геттер указателя на подчинный объект по имени
{
	for (int i = 0; i < p_sub_objects.size(); i++)
	{
		if (p_sub_objects[i]->get_name() == s_name)
			return p_sub_objects[i]; //возврат указателя на искомый объект
	}
	return nullptr; //такого объекта нет
}


cl_base* cl_base::get_object_by_coordinate(string coord) //расшифровка координат
{
	if (coord == "")
		return nullptr;

	if (coord == "/") //координата корневого объекта
		return get_root();

	if (coord.substr(0, 2) == "//") //поиск объекта по уникальному имени от корневого
	{
		string object_name = coord.substr(2, coord.size() - 2); //отделение "//" от имени объекта
		return find_object_from_root(object_name); //поиск объекта
	}

	if (coord == ".") //запрашивается текущий объект
		return this;

	if (coord[0] == '.') //поиск объекта по уникальному имени от текущего
	{
		string object_name = coord.substr(1, coord.size() - 1); //отделение "." от имени объекта
		return find_object_from_current(object_name);
	}

	stringstream sin(coord);
	string object_name;
	cl_base* p_object = this;

	//расшифровывание "более сложных координат"
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


vector<cl_base*> cl_base::get_sub_objects() //геттер вектора указателей на подчинённые объекты
{
	return p_sub_objects;
}


int cl_base::count(string s_name) // Подсчёт количества вхождений объектов с данным именем
{
	int counter = 0; // Количество найденных объектов с данным именем
	if (get_name() == s_name) // Проверка текущего объекта
	{
		counter++;
	}
	for (auto p_sub_object : p_sub_objects) // Проход по подчиненным объектам
	{
		counter += p_sub_object->count(s_name); // рекурсивный вызов
	}
	return counter;
}


cl_base* cl_base::search_object(string s_name) // Поиска объекта по имени от текущего объекта
{
	cl_base* p_found = nullptr;
	if (get_name() == s_name) // Проверка имени текущего объекта
	{
		return this;
	}
	for (auto p_sub_object : p_sub_objects) // Проход по подчиненным объектам
	{
		p_found = p_sub_object->search_object(s_name); // Рекурсивный вызов метода для каждого подчинённого объекта
		if (p_found != nullptr) // Указатель на найденный объект ненулевой?
		{
			return p_found; // Возврат указателя на найденный объект
		}
	}
	return p_found;

}


cl_base* cl_base::find_object_from_current(string s_name) // Поиск объекта по имени в дереве иерархии от текущего объекта с проверкой на уникальность имени текущего объекта
{
	if (count(s_name) != 1) // Проверка объекта на уникальность
	{
		return nullptr;
	}
	return search_object(s_name); // Возврат метода поиска от имени текущего объекта, если объект уникален
}


cl_base* cl_base::find_object_from_root(string s_name) //нахождение объекта по его имени в дереве иерархии от корневого
{
	return get_root()->find_object_from_current(s_name); //поиск объекта
}


void cl_base::print_tree(int level)
{
	get_root()->print_branch(0); //вызов метода вывода ветви для корневого объекта

}


void cl_base::print_branch(int level) //вывод иерархии объектов (дерева или ветки) от текущего объекта
{
	cout << "\n";
	cout.width(4 * level + get_name().size());
	cout << get_name();
	for (int i = 0; i < p_sub_objects.size(); i++)
	{
		p_sub_objects[i]->print_branch(level + 1); //рекурсивный вывод элементов дерева

	}
}


void cl_base::print_tree_readiness(int level) //вывод дерева иерархии и готовности его элементов
{
	cout << "\n";
	cout.width(4 * level + get_name().size());
	cout << get_name();
	if (is_ready) cout << " is ready";
	else cout << " is not ready";
	for (int i = 0; i < p_sub_objects.size(); i++)
		p_sub_objects[i]->print_tree_readiness(level + 1); //рекурсивный вывод дерева иерархии и готовности его элементов
}


void cl_base::set_connect(TYPE_SIGNAL    p_signal,      //метод установки связи между объектами
	cl_base* p_object,
	TYPE_HANDLER   p_ob_handler)
{
	//Проверка попытки повторной установки установленных связей
	for (unsigned int i = 0; i < connects.size(); i++)
	{
		if (connects[i].p_signal == p_signal &&
			connects[i].p_cl_base == p_object &&
			connects[i].p_handler == p_ob_handler)
		{
			return;
		}
	}

	o_sh   p_value;                 // создание объекта структуры для хранения информации о новой связи

	p_value.p_signal = p_signal;
	p_value.p_cl_base = p_object;
	p_value.p_handler = p_ob_handler;

	connects.push_back(p_value);          // добавление новой связи
}


void cl_base::delete_connect(TYPE_SIGNAL    p_signal,      //метод удаления связи между подчинёнными объектами
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


void cl_base::emit_signal(TYPE_SIGNAL p_signal, string& s_command) //метод излучения сигнала
{
	if (!is_ready)
	{
		return;
	}

	TYPE_HANDLER   p_handler;
	cl_base* p_object;

	(this->*p_signal) (s_command);  // вызов метода сигнала

	for (unsigned int i = 0; i < connects.size(); i++) // цикл по всем обработчикам
	{
		if (connects[i].p_signal == p_signal)      // определение допустимого обработчика
		{
			p_handler = connects[i].p_handler;
			p_object = connects[i].p_cl_base;

			if (p_object->is_ready != 0)
				(p_object->*p_handler) (s_command);      // вызов метода обработчика
		}
	}
}


void cl_base::set_class(int o_class) //метод установки значения класса объекта
{
	this->o_class = o_class;
}


int cl_base::get_class() //геттер значения класса объекта
{
	return this->o_class;
}


string cl_base::get_path() //удаление объекта
{
	if (this->p_head_object == nullptr)
		return "/";
	string path = '/' + this->get_name();
	cl_base* temp = p_head_object;
	while (temp->p_head_object != nullptr) //воссоздание полного пути до объекта
	{
		path = "/" + temp->s_name + path;
		temp = temp->p_head_object;
	}
	return path;
}