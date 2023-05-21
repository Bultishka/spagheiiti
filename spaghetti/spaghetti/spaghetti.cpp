#include <stdlib.h>
#include <stdio.h>
#include "cl_application.h"

int main()
{
	cl_application ob(nullptr); // создание корневого объекта
	ob.build_tree_objects();    // конструирование системы, построение дерева объектов
	return ob.exec_app();       // запуск системы
}
