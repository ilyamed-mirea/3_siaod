#include <stdlib.h>
#include <stdio.h>
#include "application.h"

int main() {
    application go(nullptr);
    go.build_tree_objects(); // построение дерева объектов
    return go.exec_app(); // запуск системы
}