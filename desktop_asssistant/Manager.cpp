// Manager.cpp
#include "Manager.h"

Manager::~Manager() {
    for (auto rec : records) {
        delete rec;
    }
    records.clear();
}
