//
// Created by 王波 on 2022/6/18.
//

#ifndef PLAYOPENGL_CAT_BODY_PROVIDER_H
#define PLAYOPENGL_CAT_BODY_PROVIDER_H
#include "../drawer/texture_drawer.h"


class CatBodyProvider : public DataProvider {
public:
    CatBodyProvider(): DataProvider(){}
    ~CatBodyProvider() = default;

protected:
    void provideData(list<Vec8> *targetVertexes, list<Vec3> *targetIndicates)  override{
        VertexUtils::createRectangle(targetVertexes, targetIndicates, 0.25f, 0.0f, 0.4f, 0.8f,0.8f,0.5f,0.2f);
    }
};


#endif //PLAYOPENGL_CAT_BODY_PROVIDER_H
