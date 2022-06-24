//
// Created by 王波 on 2022/6/24.
//

#ifndef PLAYOPENGL_CAT_HEADER_PROVIDER_H
#define PLAYOPENGL_CAT_HEADER_PROVIDER_H
#include "../drawer/texture_drawer.h"

class CatHeaderRender : public DataProvider {
public:
    CatHeaderRender(): DataProvider(){}
    ~CatHeaderRender() = default;

protected:
    void provideData(list<Vec8> *targetVertexes, list<Vec3> *targetIndicates)  override{
        float xCenter = -0.32f;
        float yCenter = 0.28f;
        VertexUtils::createCircleVertex(targetVertexes, targetIndicates, xCenter, yCenter, 0.2f,32, 0.8f,0.8f,0.0f);
    }

public:
    char *provideImage() override {
        return "resources/imgs/header.png";
    }
};

#endif //PLAYOPENGL_CAT_HEADER_PROVIDER_H
