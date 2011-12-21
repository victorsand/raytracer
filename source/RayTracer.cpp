#include "Scene.h"

int main() {
    Scene* scene = new Scene("../scenes/PinkBalls.txt");
    scene->parse();
    scene->render();
    scene->writeToFile();
    return 0;
}