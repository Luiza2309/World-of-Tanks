#pragma once

#include "components/simple_scene.h"
#include "components/transform.h"
#include "lab_m1/Tema2/camera.h"
#include "lab_m1/Tema2/Projectile.h"
#include "lab_m1/Tema2/Tank.h"
#include "lab_m1/Tema2/Building.h"
#include "lab_m1/Tema2/Movement.h"
#include "components/text_renderer.h"
#include <vector>
#include <chrono>


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        Tema2();
        ~Tema2();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color = glm::vec3(1), const int hp = 3);
        void RenderProjectiles(float deltaTimeSeconds);
        void RandomEnemySpawning();
        void RenderTanks(float deltaTime);
        void ShowTank(Tank* e, float deltaTime);
        void ProjectileTankCollision(float deltaTime);
        void RandomBuildingSpawning();
        void RenderBuildings();
        void TankTankCollision(float deltaTime);
        void ProjectileBuildingCollision(float deltaTime);
        void TankBuildingCollision(float deltaTime);
        bool SpawningInTheBuilding(glm::vec3 possiblePosition);
        void MoveEnemies(float deltaTime);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        glm::vec3 lightPosition;
        glm::vec3 lightDirection;
        unsigned int materialShininess;
        float materialKd;
        float materialKs;

        implemented::Cameraa* camera;

        // tank
        std::vector<Tank*> allTanks;
        Tank* myTank;
        float distanceToTarget;
        float radius;

        // projectiles
        std::vector<Projectile*> projectiles;

        // enemies
        int numberEnemies;
        float planeX;
        float planeZ;
        int spawningEnemyTime;
        std::vector<Tank*> enemies;
        std::vector<Projectile*> allProjectiles;

        // buildings
        std::vector<Building*> buildings;

        gfxc::TextRenderer* textRenderer;
        int score;
    };
}   // namespace m1
