#include "mappings.h"
#include "automapper.h"

c_mappings* mappings = new c_mappings;

bool c_mappings::init() {
    class_ave = automapper->map("ave");
}