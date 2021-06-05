#include <iostream>
#include "Directory.h"

int main() {
    Directory* root = Directory::getRoot();
    auto alfa = root->addDirectory("alfa");
    root->addDirectory("beta")->addDirectory("beta1");
    root->getDir("beta")->addDirectory("beta2");
    alfa->getDir("..")->ls(4);
    root->remove("beta");
    root->ls(4);

    return 0;
}
