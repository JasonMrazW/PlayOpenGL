//
// Created by 王波 on 2022/6/19.
//

#ifndef PLAYOPENGL_VERTEXUTILS_H
#define PLAYOPENGL_VERTEXUTILS_H
#include<list>
#include <cmath>

using namespace std;
class Vec6 {
public:
    Vec6(float x, float y, float z, float r, float g, float b) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->r = r;
        this->g = g;
        this->b = b;
    }

    float x,y,z,r,g,b = 0.0f;
};

class Vec3 {
public:
    Vec3(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    float x,y,z;
};
class VertexUtils {
public:
    static void createTriangle(list<Vec6> *targetVertexes, list<Vec3> *targetIndicates, float leftX, float leftY, float upX, float upY, float r, float g, float b) {
        int start = targetVertexes->size();
        //left
        targetVertexes->push_back(Vec6(leftX, leftY, 0.0f, r, g, b));
        //top
        targetVertexes->push_back(Vec6(upX, upY, 0.0f,r, g, b));
        //right
        targetVertexes->push_back(Vec6(2 * upX - leftX, leftY, 0.0f,r, g, b));


        targetIndicates->push_back(Vec3(start, start + 1, start + 2));
    }

    static void createRectangle(list<Vec6> *targetVertexes, list<Vec3> *targetIndicates, float centerX, float centerY,
                                float height, float width,float r, float g, float b) {
        int start = targetVertexes->size();
        float leftX = centerX - width/2;
        float leftY_Top = centerY + height/2;
        float leftY_Bottom = centerY - height/2;
        float rightX = centerX + width/2;
        float rightY_Top = leftY_Top;
        float rightY_Bottom = leftY_Bottom;

        //left-top
        targetVertexes->push_back(Vec6(leftX, leftY_Top, 0.0f,r, g, b));
        //left-bottom
        targetVertexes->push_back(Vec6(leftX, leftY_Bottom, 0.0f,r, g, b));
        //right-bottom
        targetVertexes->push_back(Vec6(rightX, rightY_Bottom, 0.0f,r, g, b));
        //right-top
        targetVertexes->push_back(Vec6(rightX, rightY_Top, 0.0f,r, g, b));


        targetIndicates->push_back(Vec3(start, start + 1, start + 2));

        targetIndicates->push_back(Vec3(start, start + 2, start + 3));
    }

    static void createCircleVertex(list<Vec6> *targetVertexes, list<Vec3> *targetIndicates, float centerX,
                                   float centerY, double radius, int sides,float r, float g, float b) {
        int inputVertexSize = targetVertexes->size();
        //圆心顶点
        targetVertexes->emplace_back(Vec6(centerX, centerY, 0.0f, r,g,b));

        //弧度
        double radUnit = 3.1415926535897932384626433832795 / 180;
        //角度
        double rad = 0;
        int size = 0;
        for (int angle = 0; angle < 360; angle += 360 / sides)
        {
            rad = angle * radUnit;
            float x = cos(rad)* radius + centerX;
            float y = sin(rad)* radius + centerY;
            targetVertexes->emplace_back(Vec6(x, y, 0.0f,r, g, b));
            size++;
        }

        //求 indicates
        //顶点个数
        for (int i = 1; i < size; i++) {
            targetIndicates->emplace_back(Vec3(inputVertexSize, inputVertexSize + i, inputVertexSize + i + 1));
        }

        //原点
        targetIndicates->emplace_back(Vec3(inputVertexSize, inputVertexSize + size, inputVertexSize + 1));
    }

    static void createStar(list<Vec6> *targetVertexes, list<Vec3> *targetIndicates, float centerX, float centerY, double radius,float r, float g, float b) {
        int sides = 10;
        int inputVertexSize = targetVertexes->size();
        //圆心顶点
        targetVertexes->emplace_back(Vec6(centerX, centerY, 0.0f,r, g, b));
        //弧度
        double radUnit = 3.1415926535897932384626433832795 / 180;

        double solidRad = 36*radUnit;
        double longRadius = 2*radius*cos(solidRad);

        //角度
        double rad = 0;
        int size = 0;
        double tmp = longRadius;
        for (int angle = 0; angle < 360; angle += 360 / sides)
        {
            if (size % 2 == 0) {
                tmp = longRadius;
            } else {
                tmp = radius;
            }
            rad = angle * radUnit;
            float x = cos(rad)* tmp + centerX;
            float y = sin(rad)* tmp + centerY;
            targetVertexes->emplace_back(Vec6(x, y, 0.0f,r, g, b));
            size++;
        }

        //求 indicates
        //顶点个数
        for (int i = 1; i < size; i++) {
            targetIndicates->emplace_back(Vec3(inputVertexSize, inputVertexSize + i, inputVertexSize + i + 1));
        }

        //原点
        targetIndicates->emplace_back(Vec3(inputVertexSize, inputVertexSize + size, inputVertexSize + 1));
    }

    static float* convertListToArray(list<Vec6> *inputs, float catVertices[]) {
        uint32_t i = 0;
        while (!inputs->empty()) {
            Vec6 tmp = inputs->front();
            inputs->pop_front();
            catVertices[i++] = tmp.x;
            catVertices[i++] = tmp.y;
            catVertices[i++] = tmp.z;
            catVertices[i++] = tmp.r;
            catVertices[i++] = tmp.g;
            catVertices[i++] = tmp.b;
        }
    }

    static float* convertListToArray(list<Vec3> *inputs, int catIndicates[]) {
        uint32_t i = 0;
        while (!inputs->empty()) {
            Vec3 tmp = inputs->front();
            inputs->pop_front();
            catIndicates[i++] = tmp.x;
            catIndicates[i++] = tmp.y;
            catIndicates[i++] = tmp.z;
        }
    }
};
#endif //PLAYOPENGL_VERTEXUTILS_H
