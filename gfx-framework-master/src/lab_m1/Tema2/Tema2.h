#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema2/tema_camera.h"

namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct TrianglePoints
        {
            glm::vec3 p1;
            glm::vec3 p2;
            glm::vec3 p3;
        };

        Tema2();
        ~Tema2();

        void Init() override;

    private:
        Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        //void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;
        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void RenderScene();
        void RenderScene2();
        float Tema2::dist(float x1, float y1, float x2, float y2);
        float Tema2::area(float x1, float y1, float x2, float y2, float x3, float y3);
        bool Tema2::isPointInTriangle(TrianglePoints triangle, glm::vec3 point);
        void Tema2::updateTenTr();
        bool Tema2::intersectionCubes(glm::vec3 centru1, glm::vec3 centru2);
        bool Tema2::intersectOtherCars();

    protected:
        implemented2::Camera2* camera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;

        // TODO(student): If you need any other class variables, define them here.
        float orthoUp = 0, orthoDown = 0, orthoRight = 0, orthoLeft = 0;
        bool isOrtho = false;
        float fov = 60;
        float left = -8.0f;
        float right = 8.0f;
        float down = -4.0f;
        float up = 4.0f;
        bool isPerspective = true;
        float rotateCar = 0;
        GLenum polygonMode;
        glm::vec3 cameraPos;
        ViewportArea miniViewportArea;
        ViewportArea miniViewportArea2;
        std::vector<TrianglePoints> triangles;
        int idxStartTr =-1;
        TrianglePoints startTriangle;
        std::vector<TrianglePoints> tenTriangles;
        implemented2::Camera2 *camera2;
        implemented2::Camera2 *cameraFp;
        implemented2::Camera2 *cameraBack;
        bool isFp = false;
        int cam;
        std::vector<glm::vec3> trees;
        float razaMasini;
        float miniX = 0, miniY = 0, miniWidth = 0, miniHeight = 0;
        glm::vec3 carPos[4] = { glm::vec3(0, 0, 0),glm::vec3(0, 0, 0),glm::vec3(0, 0, 0),glm::vec3(0, 0, 0) };
        glm::vec3 carPos2[4] = { glm::vec3(0, 0.12, 0),glm::vec3(0, 0.12, 0),glm::vec3(0, 0.12, 0),glm::vec3(0, 0.12, 0) };
        std::vector<glm::vec3> posObstacol;
        std::vector<glm::vec3> posObstacolInv;
        std::vector<glm::vec3> directions;
        std::vector<glm::vec3> directionsInv;
        int carIndex[4]{2,55,33,2};
        int frame = 0;
        std::vector<glm::vec3> carObst;
        glm::vec3 carObst1;
        glm::vec3 carObst2;
        glm::vec3 prev = glm::vec3(0, 0, 0);
    };
}   // namespace m1
