#pragma once

class Tracker
{
public:
    Tracker(const char *name);
    ~Tracker();

private:
    const char *name_;
};

void createStatic();
void createAutomatic();
void createHeap();
void createTemporary();
