#include "lab_m1/Tema2/tema2.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std::chrono;
using namespace std;
using namespace m1;

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

Tema2::Tema2()
{
    myTank = new Tank(glm::vec3(0.988, 0.71, 0.675), glm::vec3(0.6, 0.435, 0.455), glm::vec3(0, 0, 0));
    allTanks.push_back(myTank);

    distanceToTarget = 9.52;
    camera = new implemented::Cameraa;
    camera->Set(glm::vec3(0, 5, -distanceToTarget), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    // movement of the tank
    radius = 3.5;

    // enemies
    numberEnemies = 0;
    planeX = -50;
    planeZ = -50;
    spawningEnemyTime = time(0) + 5;

    score = 0;
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
    RandomBuildingSpawning();

    {
        Mesh* mesh = new Mesh("turela");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "my_models"), "turela.fbx");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("ornament_turela");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "my_models"), "ornament_turela.fbx");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("corp");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "my_models"), "corp.fbx");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("tun");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "my_models"), "tun.fbx");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("ornament_tun");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "my_models"), "ornament_tun.fbx");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("senile");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "my_models"), "senile.fbx");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("roti");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "my_models"), "roti.fbx");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("funda");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "my_models"), "funda.fbx");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("funda_bila");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "my_models"), "funda_bila.fbx");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("funda_picioare");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "my_models"), "funda_picioare.fbx");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("projectile");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("plane");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("building");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader* shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    // Light & material properties
    {
        lightPosition = glm::vec3(0, 100, 0);
        lightDirection = glm::vec3(0, -1, 0);
        materialShininess = 30;
        materialKd = 0.5;
        materialKs = 0.5;
    }

    // Create the text renderer object
    glm::ivec2 resolution = window->GetResolution();
    textRenderer = new gfxc::TextRenderer(window->props.selfDir, resolution.x, resolution.y);

    textRenderer->Load(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::FONTS, "Hack-Bold.ttf"), 72);
}

void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.733, 0.906, 0.996, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

// RENDERING

void Tema2::ShowTank(Tank* e, float deltaTime) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, e->getPosition());
    modelMatrix = glm::rotate(modelMatrix, e->getAngle(), glm::vec3(0, 1, 0));
    RenderSimpleMesh(meshes["corp"], shaders["LabShader"], modelMatrix, e->getColors(), e->getLifes());
    RenderSimpleMesh(meshes["senile"], shaders["LabShader"], modelMatrix, e->getDetailColors(), e->getLifes());
    RenderSimpleMesh(meshes["roti"], shaders["LabShader"], modelMatrix, e->getColors(), e->getLifes());

    modelMatrix = glm::translate(modelMatrix, e->getTurretCenter());
    modelMatrix = glm::rotate(modelMatrix, e->getAngleTurret(), glm::vec3(0, 1, 0));
    modelMatrix = glm::translate(modelMatrix, -e->getTurretCenter());
    RenderSimpleMesh(meshes["turela"], shaders["LabShader"], modelMatrix, e->getColors(), e->getLifes());
    RenderSimpleMesh(meshes["ornament_turela"], shaders["LabShader"], modelMatrix, e->getDetailColors(), e->getLifes());
    RenderSimpleMesh(meshes["funda"], shaders["LabShader"], modelMatrix, e->getDetailColors(), e->getLifes());
    RenderSimpleMesh(meshes["funda_bila"], shaders["LabShader"], modelMatrix, e->getDetailColors(), e->getLifes());
    RenderSimpleMesh(meshes["funda_picioare"], shaders["LabShader"], modelMatrix, e->getDetailColors(), e->getLifes());
    

    RenderSimpleMesh(meshes["tun"], shaders["LabShader"], modelMatrix, e->getColors(), e->getLifes());
    RenderSimpleMesh(meshes["ornament_tun"], shaders["LabShader"], modelMatrix, e->getDetailColors(), e->getLifes());
}

void Tema2::RenderTanks(float deltaTime) {
    int i = 0;
    for (Tank* e : allTanks) {
        if (e != NULL) {
            if (e->getLifes() > 0) {
                // it's alive
                ShowTank(e, deltaTime);
            } else {
                // died
                if (i == 0) {
                    // my tank died
                    break;
                }
                else {
                    enemies.erase(enemies.begin() + i - 1);
                    allTanks.erase(allTanks.begin() + i);
                    numberEnemies--;
                    score++;
                }
            }
            i++;
        }
    }
}

void Tema2::RenderProjectiles(float deltaTimeSeconds) {
    int i = 0;
    for (Projectile* p : projectiles) {
        if (p != NULL) {
            if (time(0) <= p->getTime()) {
                glm::mat4 matrix = glm::mat4(1);
                p->setPosition(p->getPosition() + p->getForward() * glm::vec3(deltaTimeSeconds * 10));
                matrix = glm::translate(matrix, p->getPosition());
                matrix = glm::scale(matrix, glm::vec3(0.2));
                RenderSimpleMesh(meshes["projectile"], shaders["LabShader"], matrix, glm::vec3(0.69, 0.239, 0.18));
            }
            else {
                projectiles.erase(projectiles.begin() + i);
                i--;
               
            }
            i++;
        }
    }
}

void Tema2::RenderBuildings() {
    for (Building* b : buildings) {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, b->getPosition());
        modelMatrix = glm::scale(modelMatrix, b->getScale());
        RenderSimpleMesh(meshes["building"], shaders["LabShader"], modelMatrix, b->getColor());
    }
}

// COLLISION

void Tema2::TankTankCollision(float deltaTime) {
    if (enemies.size() > 0) {
        for (Tank* t1 : allTanks) {
            if (t1 != NULL) {
                for (Tank* t2 : allTanks) {
                    if (t2 != NULL && t1 != t2) {
                        float distance = glm::distance(t1->getPosition(), t2->getPosition());
                        float sum = 2 * radius;
                        float absP = sum - distance;

                        if (distance <= sum) {
                            // they collide
                            glm::vec3 dif = t1->getPosition() - t2->getPosition();
                            glm::vec3 P = absP * glm::normalize(dif);
                            t1->setPosition(t1->getPosition() + P * (0.5f) * deltaTime * 2.0f);
                            t2->setPosition(t2->getPosition() + P * (-0.5f) * deltaTime * 2.0f);
                        }
                    }
                }
            }
        }
    }
}

void Tema2::ProjectileTankCollision(float deltaTime) {
    int i = 0;
    for (Tank* e : allTanks) {
        i = 0;
        for (Projectile* p : projectiles) {
            float distance = glm::distance(p->getPosition(), e->getPosition());
            float sum = radius + 0.1;
            if (distance <= sum) {
                // tank was shot
                e->setLifes();
                projectiles.erase(projectiles.begin() + i);
                i--;
            }

            i++;
        }
    }
}

void Tema2::ProjectileBuildingCollision(float deltaTime) {
    int i = 0;
    for (Building* b : buildings) {
        if (b != NULL) {
            i = 0;
            for (Projectile* p : projectiles) {
                if (p != NULL) {
                    bool collisionX = p->getPosition().x + 0.2f >= b->getPosition().x - b->getScale().x / 2 && p->getPosition().x - 0.2f <= b->getPosition().x + b->getScale().x / 2;
                    bool collisionY = p->getPosition().y + 0.2f >= b->getPosition().y - b->getScale().y / 2  && p->getPosition().y - 0.2f <= b->getPosition().y + b->getScale().y / 2;
                    bool collisionZ = p->getPosition().z + 0.2f >= b->getPosition().z - b->getScale().z / 2  && p->getPosition().z - 0.2f <= b->getPosition().z + b->getScale().z / 2;
                       
                    if (collisionX && collisionY && collisionZ) {
                        // they collide
                        projectiles.erase(projectiles.begin() + i);
                    }
                }

                i++;
            }
        }
    }
}

void Tema2::TankBuildingCollision(float deltaTime) {
    int i = 0;
    for (Building* b : buildings) {
        if (b != NULL) {
            i = 0;
            for (Tank* t : allTanks) {
                if (t != NULL) {
                    bool collisionX = t->getPosition().x + radius >= b->getPosition().x - b->getScale().x / 2 && t->getPosition().x - radius <= b->getPosition().x + b->getScale().x / 2;
                    bool collisionY = t->getPosition().y + radius >= b->getPosition().y - b->getScale().y / 2 && t->getPosition().y - radius <= b->getPosition().y + b->getScale().y / 2;
                    bool collisionZ = t->getPosition().z + radius >= b->getPosition().z - b->getScale().z / 2 && t->getPosition().z - radius <= b->getPosition().z + b->getScale().z / 2;

                    if (collisionX && collisionY && collisionZ) {
                        // they collide
                        float distance = glm::distance(t->getPosition(), b->getPosition());
                        float sum = radius + b->getScale().x * sqrt(2);
                        float absP = sum - distance;

                        glm::vec3 dif = t->getPosition() - b->getPosition();
                        glm::vec3 P = absP * glm::normalize(dif);
                        t->setPosition(t->getPosition() + P * deltaTime * 0.4f);
                    }
                }

                i++;
            }
        }
    }
}

// SPAWNING

bool Tema2::SpawningInTheBuilding(glm::vec3 possiblePosition) {
    for (Building* b : buildings) {
        if (b != NULL) {
            bool collisionX = possiblePosition.x + radius >= b->getPosition().x - b->getScale().x / 2 && possiblePosition.x - radius <= b->getPosition().x + b->getScale().x / 2;
            bool collisionZ = possiblePosition.z + radius >= b->getPosition().z - b->getScale().z / 2 && possiblePosition.z - radius <= b->getPosition().z + b->getScale().z / 2;

            if (collisionX && collisionZ) {
                // they collide
                return true;
            }
        }
    }

    return false;
}

void Tema2::RandomEnemySpawning() {
    if (time(0) >= spawningEnemyTime && numberEnemies <= 15) {
        spawningEnemyTime = time(0) + 5;

        int randX = (rand() % (int(abs(planeX) * 2))) + planeX;
        int randZ = (rand() % (int(abs(planeZ) * 2))) + planeZ;
        for (int i = 0; i < allTanks.size(); i++) {
            float distance = glm::distance(glm::vec3(randX, 0, randZ), allTanks[i]->getPosition());
            float sum = 2 * radius;
            if (distance <= sum || SpawningInTheBuilding(glm::vec3(randX, 0, randZ))) {
                // they intersect
                randX = (rand() % (int(abs(planeX) * 2))) + planeX;
                randZ = (rand() % (int(abs(planeZ) * 2))) + planeZ;
                
                i = -1;
            }
        }

        float red = (rand() % 100) / 100.0f;
        float green = (rand() % 100) / 100.0f;
        float blue = (rand() % 100) / 100.0f;

        Tank* enemy = new Tank(glm::vec3(red, green, blue), glm::vec3(red, green, blue) + glm::vec3(0.5), glm::vec3(randX, 0, randZ));
        enemies.push_back(enemy);
        allTanks.push_back(enemy);
        numberEnemies++;
    }
}

void Tema2::RandomBuildingSpawning() {
    for (int i = 0; i < 10; i++) {
        int randX = ((rand() % 31) + 20) * (rand() % 2 == 0? 1 : -1);
        int randZ = ((rand() % 31) + 20) * (rand() % 2 == 0 ? 1 : -1);

        int scaleX = (rand() % 10) + 10;
        int scaleY = (rand() % 10) + 10;

        Building* b = new Building(glm::vec3(randX, 0, randZ), glm::vec3(0.71, 0.898, 0.812), glm::vec3(scaleX, scaleY, scaleX));
        buildings.push_back(b);
    }
}

// MOVEMENT

void Tema2::MoveEnemies(float deltaTime) {
    for (Tank* e : enemies) {
        if (e != NULL) {
            float distance = glm::distance(e->getPosition(), myTank->getPosition());
            float sum = 6 * radius;
            float absP = sum - distance;

            if (time(0) >= e->getTimeToMove()) {
                e->setTimeToMove(time(0) + (rand() % 2) + 1);
                e->move->setCurrentState(e->move->GetNextMovementState(e->move->getCurrentState()));
            }

            if (distance <= sum) {
                glm::vec3 dif = myTank->getPosition() - e->getPosition();
                float cs = glm::dot(glm::normalize(e->getCannonForward()), glm::normalize(dif));
                glm::vec3 left_right = glm::cross(glm::normalize(e->getCannonForward()), glm::normalize(dif));
                float angle = acos(cs);
                if (left_right.y < 0) {
                    angle = -angle;
                }

                e->setAngleTurret(e->getAngleTurret() + RADIANS(angle));
                e->setCannonCenter(glm::vec3(glm::rotate(glm::mat4(1), RADIANS(angle), glm::vec3(0, 1, 0)) * glm::vec4(e->getCannonCenter(), 1)));
                e->setCannonForward(glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), RADIANS(angle), glm::vec3(0, 1, 0)) * glm::vec4(e->getCannonForward(), 1))));
                glm::vec3 aux = glm::vec3(glm::rotate(glm::mat4(1), e->getAngle(), glm::vec3(0, 1, 0)) * glm::vec4(e->getTurretCenter(), 1)) - e->getCannonCenter();

                uint64_t ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
                if (ms >= e->getTimeToShoot()) {
                    glm::vec3 auxTurretCenter = glm::vec3(glm::rotate(glm::mat4(1), e->getAngle(), glm::vec3(0, 1, 0)) * glm::vec4(e->getTurretCenter(), 1));
                    Projectile* p = new Projectile(e->getPosition() + e->getCannonCenter() + auxTurretCenter, e->getCannonForward(), time(0) + 1);
                    projectiles.push_back(p);
                    e->setTimeToShoot(ms + 1000);
                }
            }
            else if (e->move->getCurrentState() == MovementState::GoingForward) {
                e->moveW(deltaTime);
            }
            else if (e->move->getCurrentState() == MovementState::GoingBackward) {
                e->moveS(deltaTime);
            }
            else if (e->move->getCurrentState() == MovementState::InPlaceRotationRight) {
                e->moveD(deltaTime);
            }
            else if (e->move->getCurrentState() == MovementState::InPlaceRotationLeft) {
                e->moveA(deltaTime);
            }
        }
    }
}

void Tema2::Update(float deltaTimeSeconds)
{
    if (Engine::GetElapsedTime() >= 150.0f || myTank->getLifes() <= 0) {
        // game ended
        return;
    }

    RenderBuildings();
    RandomEnemySpawning();
    RenderTanks(deltaTimeSeconds);
    RenderProjectiles(deltaTimeSeconds);

    ProjectileTankCollision(deltaTimeSeconds);
    TankTankCollision(deltaTimeSeconds);
    ProjectileBuildingCollision(deltaTimeSeconds);
    TankBuildingCollision(deltaTimeSeconds);

    MoveEnemies(deltaTimeSeconds);

    for (Tank* e : allTanks) {
        glm::vec3 pos = e->getPosition();

        if (pos.x < -50) {
            pos.x = -50;
        }
        if (pos.z < -50) {
            pos.z = -50;
        }
        if (pos.x > 50) {
            pos.x = 50;
        }
        if (pos.z > 50) {
            pos.z = 50;
        }

        e->setPosition(pos);
    }

    // Render ground
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -0.1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(3.0f));
        RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, glm::vec3(0.239, 0.357, 0.349));
    }

    // Render the point light in the scene
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, lightPosition);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
        RenderMesh(meshes["sphere"], shaders["Simple"], modelMatrix);
    }

}

void Tema2::FrameEnd()
{
    glm::ivec2 resolution = window->GetResolution() / 2;

    if (myTank->getLifes() <= 0) {
        textRenderer->RenderText("You DIED!", resolution.x - 200 , resolution.y - 50, 1, glm::vec3(0));
    }
    else if (Engine::GetElapsedTime() >= 150.0f) {
        textRenderer->RenderText("Game Over!", resolution.x - 200, resolution.y - 50, 1, glm::vec3(0));
        textRenderer->RenderText("Score: " + to_string(score * 100), resolution.x - 200, resolution.y + 20, 1, glm::vec3(0));
    }
    //DrawCoordinateSystem(camera->GetViewMatrix(), GetSceneCamera()->GetProjectionMatrix());
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, const int hp)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Set shader uniforms for light properties
    int light_position = glGetUniformLocation(shader->program, "light_position");
    glUniform3f(light_position, lightPosition.x, lightPosition.y, lightPosition.z);

    int light_direction = glGetUniformLocation(shader->program, "light_direction");
    glUniform3f(light_direction, lightDirection.x, lightDirection.y, lightDirection.z);

    // Set material property uniforms (shininess, kd, ks, object color) 
    int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(material_shininess, materialShininess);

    int material_kd = glGetUniformLocation(shader->program, "material_kd");
    glUniform1f(material_kd, materialKd);

    int material_ks = glGetUniformLocation(shader->program, "material_ks");
    glUniform1f(material_ks, materialKs);

    int object_color = glGetUniformLocation(shader->program, "object_color");
    glUniform3f(object_color, color.r, color.g, color.b);

    int HP = glGetUniformLocation(shader->program, "hp");
    glUniform1i(HP, hp);

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = camera->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    if (window->KeyHold(GLFW_KEY_W)) {
        myTank->moveW(deltaTime);
    }

    if (window->KeyHold(GLFW_KEY_A)) {
        myTank->moveA(deltaTime);
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        myTank->moveS(deltaTime);
    }

    if (window->KeyHold(GLFW_KEY_D)) {
        myTank->moveD(deltaTime);
    }

    if (window->KeyHold(GLFW_KEY_Q)) {
        camera->RotateThirdPerson_OY(RADIANS(1));
    }
    else if (window->KeyHold(GLFW_KEY_E)) {
        camera->RotateThirdPerson_OY(-RADIANS(1));
    }
    else {
        camera->Set(myTank->getPosition() + glm::vec3(0, 5, -distanceToTarget), myTank->getPosition() + glm::vec3(0, 2, 0), glm::vec3(0, 1, 0));
        camera->RotateThirdPerson_OY(myTank->getAngle());
    }
}

void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
}

void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensitivity = 0.1f;
        myTank->setAngleTurret(myTank->getAngleTurret() + RADIANS(deltaX * sensitivity));
        myTank->setCannonCenter(glm::vec3(glm::rotate(glm::mat4(1), RADIANS(deltaX * sensitivity), glm::vec3(0, 1, 0)) * glm::vec4(myTank->getCannonCenter(), 1)));
        myTank->setCannonForward(glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), RADIANS(deltaX * sensitivity), glm::vec3(0, 1, 0)) * glm::vec4(myTank->getCannonForward(), 1))));
    }
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    
    // shoot projectile
    if(IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
        uint64_t ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        if (ms >= myTank->getTimeToShoot()) {
            glm::vec3 auxTurretCenter = glm::vec3(glm::rotate(glm::mat4(1), myTank->getAngle(), glm::vec3(0, 1, 0)) * glm::vec4(myTank->getTurretCenter(), 1));
            Projectile* p = new Projectile(myTank->getPosition() + myTank->getCannonCenter() + auxTurretCenter, myTank->getCannonForward(), time(0) + 3);
            projectiles.push_back(p);
            myTank->setTimeToShoot(ms + 1000);
        }
    }
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}
