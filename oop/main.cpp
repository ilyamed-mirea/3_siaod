#include <stdlib.h>
#include <stdio.h>
#include "System.h"
#include "base.h"
#include "classes.h"
int main() {
    System go;
    go.build_tree_objects(); // построение дерева объектов
    return go.exec_app(); // запуск системы
}