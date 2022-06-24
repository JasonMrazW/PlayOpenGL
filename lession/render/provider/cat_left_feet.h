//
// Created by 王波 on 2022/6/24.
//

#ifndef PLAYOPENGL_CAT_LEFT_FEET_H
#define PLAYOPENGL_CAT_LEFT_FEET_H
#include "../drawer/texture_drawer.h"

class CatLeftFeet : public DataProvider {
public:
    CatLeftFeet(): DataProvider(){}
    ~CatLeftFeet() = default;

protected:
    void provideData(list<Vec8> *targetVertexes, list<Vec3> *targetIndicates)  override{
        VertexUtils::createRectangle(targetVertexes, targetIndicates, 0.1f, -0.3f, 0.2f, 0.2f,0.2f,0.8f,0.5f);
    }

public:
    char *provideImage() override {
        return "resources/imgs/left_feet.png";
    }
};
#endif //PLAYOPENGL_CAT_LEFT_FEET_H
