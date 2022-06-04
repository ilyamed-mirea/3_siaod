#include <stdlib.h>
#include <stdio.h>
#include "System.h"

int main() {
    System app(nullptr);
    app.build_tree_objects(); // построение дерева объектов
    return app.exec_app(); // запуск системы
}