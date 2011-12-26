#include "Scene.h"

int main() {
    Scene* scene = new Scene("../scenes/CornellBoxPath.txt");
    scene->parse();
    scene->render();
    scene->writeToFile();
    scene->cleanUp();
    return 0;
}