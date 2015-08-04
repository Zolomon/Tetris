#pragma once

#include <Windows.h>
#include <algorithm>
#include <iterator>
#include <tchar.h>
#include <cassert>
#include <sstream>
#include <vector>
#include <memory>
#include <map>

#include "Bitmap.h"
#include "Command.h"
#include "Resource.h"
#include "Settings.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "GDIBitmap.h"
#include "entityx/entityx.h"
#include "glm/glm.hpp"
#include <unordered_set>

namespace ex = entityx;

class RenderComponent;
class PhysicsComponent;

float r(int a, float b = 0) {
    return static_cast<float>(std::rand() % (a * 1000) + b * 1000) / 1000.0;
}


struct Body {
    Body(const glm::vec2 &position, const glm::vec2 &direction, float rotationd = 0.0)
        : position(position), direction(direction), rotationd(rotationd) {}

    glm::vec2 position;
    glm::vec2 direction;
    float rotation = 0.0, rotationd;
};


struct Renderable {
    explicit Renderable(Bitmap shape) : shape(shape) {}

    Bitmap shape;
};


struct Particle {
    explicit Particle(float radius, float duration)
        : radius(radius), d(1.0f) {}

    float radius, alpha, d;
};


struct Collideable {
    explicit Collideable(float radius) : radius(radius) {}

    float radius;
};


// Emitted when two entities collide.
struct CollisionEvent {
    CollisionEvent(ex::Entity left, ex::Entity right) : left(left), right(right) {}

    ex::Entity left, right;
};


class SpawnSystem : public ex::System<SpawnSystem> {
public:
    explicit SpawnSystem(int count) : size(Settings::Window::Size), count(count) {}

    void update(ex::EntityManager &es, ex::EventManager &events, ex::TimeDelta dt) override {
        int c = 0;
        ex::ComponentHandle<Collideable> collideable;
        es.each<Collideable>([&](ex::Entity entity, Collideable&) { ++c; });

        for (int i = 0; i < count - c; i++) {
            ex::Entity entity = es.create();

            // Mark as collideable (explosion particles will not be collideable).
            collideable = entity.assign<Collideable>(r(10, 5));

            // "Physical" attributes.
            entity.assign<Body>(
                glm::vec2(r(size.x), r(size.y)),
                glm::vec2(r(100, -50), r(100, -50)));

            // Shape to apply to entity.
            entity.assign<Renderable>(0);
        }
    }

private:
    glm::vec2 size;
    int count;
};


// Updates a body's position and rotation.
struct BodySystem : public ex::System<BodySystem> {
    void update(ex::EntityManager &es, ex::EventManager &events, ex::TimeDelta dt) override {
        es.each<Body>([dt](ex::Entity entity, Body &body) {
            body.position += body.direction * static_cast<float>(dt);
            body.rotation += body.rotationd * dt;
        });
    };
};


// Bounce bodies off the edge of the screen.
class BounceSystem : public ex::System<BounceSystem> {
public:
    explicit BounceSystem() : size(Settings::Window::Size) {}

    void update(ex::EntityManager &es, ex::EventManager &events, ex::TimeDelta dt) override {
        es.each<Body>([this](ex::Entity entity, Body &body) {
            if (body.position.x + body.direction.x < 0 ||
                body.position.x + body.direction.x >= size.x)
                body.direction.x = -body.direction.x;
            if (body.position.y + body.direction.y < 0 ||
                body.position.y + body.direction.y >= size.y)
                body.direction.y = -body.direction.y;
        });
    }

private:
    glm::vec2 size;
};


// Determines if two Collideable bodies have collided. If they have it emits a
// CollisionEvent. This is used by ExplosionSystem to create explosion
// particles, but it could be used by a SoundSystem to play an explosion
// sound, etc..
//
// Uses a fairly rudimentary 2D partition system, but performs reasonably well.
class CollisionSystem : public ex::System<CollisionSystem> {
    static const int PARTITIONS = 200;

    struct Candidate {
        glm::vec2 position;
        float radius;
        ex::Entity entity;
    };

public:
    explicit CollisionSystem() : size(Settings::Window::Size) {
        size.x = size.x / PARTITIONS + 1;
        size.y = size.y / PARTITIONS + 1;
    }

    void update(ex::EntityManager &es, ex::EventManager &events, ex::TimeDelta dt) override {
        reset();
        collect(es);
        collide(events);
    };

private:
    std::vector<std::vector<Candidate>> grid;
    glm::vec2 size;

    void reset() {
        grid.clear();
        grid.resize(size.x * size.y);
    }

    void collect(ex::EntityManager &entities) {
        entities.each<Body, Collideable>([this](ex::Entity entity, Body &body, Collideable &collideable) {
            unsigned int
                left = static_cast<int>(body.position.x - collideable.radius) / PARTITIONS,
                top = static_cast<int>(body.position.y - collideable.radius) / PARTITIONS,
                right = static_cast<int>(body.position.x + collideable.radius) / PARTITIONS,
                bottom = static_cast<int>(body.position.y + collideable.radius) / PARTITIONS;
            Candidate candidate{ body.position, collideable.radius, entity };
            unsigned int slots[4] = {
                left + top * size.x,
                right + top * size.x,
                left + bottom * size.x,
                right + bottom * size.x,
            };
            grid[slots[0]].push_back(candidate);
            if (slots[0] != slots[1]) grid[slots[1]].push_back(candidate);
            if (slots[1] != slots[2]) grid[slots[2]].push_back(candidate);
            if (slots[2] != slots[3]) grid[slots[3]].push_back(candidate);
        });
    }

    void collide(ex::EventManager &events) {
        for (const std::vector<Candidate> &candidates : grid) {
            for (const Candidate &left : candidates) {
                for (const Candidate &right : candidates) {
                    if (left.entity == right.entity) continue;
                    if (collided(left, right))
                        events.emit<CollisionEvent>(left.entity, right.entity);
                }
            }
        }
    }

    float length(const glm::vec2 &v) {
        return std::sqrt(v.x * v.x + v.y * v.y);
    }

    bool collided(const Candidate &left, const Candidate &right) {
        return length(left.position - right.position) < left.radius + right.radius;
    }
};


class ParticleSystem : public ex::System<ParticleSystem> {
public:
    void update(ex::EntityManager &es, ex::EventManager &events, ex::TimeDelta dt) override {
        es.each<Particle>([dt](ex::Entity entity, Particle &particle) {
            particle.alpha -= particle.d * dt;
            if (particle.alpha <= 0) {
                entity.destroy();
            }
        });
    }
};


class ParticleRenderSystem : public ex::System<ParticleRenderSystem> {
public:
    explicit ParticleRenderSystem(Game &target) : target(target) {}

    void update(ex::EntityManager &es, ex::EventManager &events, ex::TimeDelta dt) override {
        Game &target = this->target;
        es.each<Particle, Body>([&](ex::Entity entity, Particle &particle, Body &body) {
            const float r = particle.radius;
            /*vertices.append(sf::Vertex(body.position + glm::vec2(-r, -r), particle.colour));
            vertices.append(sf::Vertex(body.position + glm::vec2(r, -r), particle.colour));
            vertices.append(sf::Vertex(body.position + glm::vec2(r, r), particle.colour));
            vertices.append(sf::Vertex(body.position + glm::vec2(-r, r), particle.colour));*/
            this->target.DrawBitmap(this->target.bitmapDictionary[Resource::RedBlock], body.position.x, body.position.y);
        });
        //target.Draw(vertices);
    }
private:
    Game &target;
};


// For any two colliding bodies, destroys the bodies and emits a bunch of bodgy explosion particles.
class ExplosionSystem : public ex::System<ExplosionSystem>, public ex::Receiver<ExplosionSystem> {
public:
    void configure(ex::EventManager &events) override {
        events.subscribe<CollisionEvent>(*this);
    }

    void update(ex::EntityManager &es, ex::EventManager &events, ex::TimeDelta dt) override {
        for (ex::Entity entity : collided) {
            emit_particles(es, entity);
            entity.destroy();
        }
        collided.clear();
    }

    void emit_particles(ex::EntityManager &es, ex::Entity entity) {
        ex::ComponentHandle<Body> body = entity.component<Body>();
        ex::ComponentHandle<Renderable> renderable = entity.component<Renderable>();
        ex::ComponentHandle<Collideable> collideable = entity.component<Collideable>();
        
        float area = (3.1459 * collideable->radius * collideable->radius) / 3.0;
        for (int i = 0; i < area; i++) {
            ex::Entity particle = es.create();

            float rotationd = r(720, 180);
            if (std::rand() % 2 == 0) rotationd = -rotationd;

            float offset = r(collideable->radius, 1);
            float angle = r(360) * 3.1459 / 180.0;
            particle.assign<Body>(
                body->position + glm::vec2(offset * cos(angle), offset * sin(angle)),
                body->direction + glm::vec2(offset * 2 * cos(angle), offset * 2 * sin(angle)),
                rotationd);

            float radius = r(3, 1);
            particle.assign<Particle>(radius, radius / 2);
        }
    }

    void receive(const CollisionEvent &collision) {
        // Events are immutable, so we can't destroy the entities here. We defer
        // the work until the update loop.
        collided.insert(collision.left);
        collided.insert(collision.right);
    }

private:
    std::unordered_set<ex::Entity> collided;
};


// Render all Renderable entities and draw some informational text.
class RenderSystem :public ex::System<RenderSystem> {
public:
    explicit RenderSystem(Game &target) : target(target) {
        
    }

    void update(ex::EntityManager &es, ex::EventManager &events, ex::TimeDelta dt) override {
        es.each<Body, Renderable>([this](ex::Entity entity, Body &body, Renderable &renderable) {
            renderable.shape->setPosition(body.position);
            renderable.shape->setRotation(body.rotation);
            target.draw(*renderable.shape.get());
        });
        last_update += dt;
        frame_count++;
        if (last_update >= 0.5) {
            std::ostringstream out;
            const double fps = frame_count / last_update;
            out << es.size() << " entities (" << static_cast<int>(fps) << " fps)";
            text.setString(out.str());
            last_update = 0.0;
            frame_count = 0.0;
        }
        this->target.DrawString(text);
    }

private:
    double last_update = 0.0;
    double frame_count = 0.0;
    Game &target;
};


class Application : public ex::EntityX {
public:
    explicit Application(sf::RenderTarget &target, sf::Font &font) {
        systems.add<SpawnSystem>(target, 500);
        systems.add<BodySystem>();
        systems.add<BounceSystem>(target);
        systems.add<CollisionSystem>(target);
        systems.add<ExplosionSystem>();
        systems.add<ParticleSystem>();
        systems.add<RenderSystem>(target, font);
        systems.add<ParticleRenderSystem>(target);
        systems.configure();
    }

    void update(ex::TimeDelta dt) {
        systems.update<SpawnSystem>(dt);
        systems.update<BodySystem>(dt);
        systems.update<BounceSystem>(dt);
        systems.update<CollisionSystem>(dt);
        systems.update<ExplosionSystem>(dt);
        systems.update<ParticleSystem>(dt);
        systems.update<RenderSystem>(dt);
        systems.update<ParticleRenderSystem>(dt);
    }
};


class Game {
public:
    Game() {};
    ~Game() {};

    bool LoadBitmapFromFile(const std::wstring filename, Resource resource);
    void InitializeGraphics(HWND window);
    void BeginGraphics();
    void DrawBitmap(Bitmap bitmap, int x, int y)  const;
    void DrawString(const std::wstring text, COLORREF color, int x, int y) const;
    void Render(const double interpolation);
    void Update(const double deltaTime);
    void EndGraphics();
    void FreeBitmap(Bitmap bitmap);
    void ShutdownGraphics();

    void Start();
    void ProcessInput(Command command);

    // GDI-related stuff
    HWND window;
    HDC backbufferDC;
    HBITMAP backbufferBitmap;
    HDC bitmapDC;
    HGDIOBJ oldObject;

    
    // EOF GDI


    //std::vector<std::shared_ptr<Entity>> entities;
    std::vector<std::shared_ptr<RenderComponent>> renderComponents;
    std::vector<std::shared_ptr<PhysicsComponent>> physicsComponents;
    //std::vector<std::shared_ptr<>

    std::map<Resource, Bitmap> bitmapDictionary;
    std::map<Resource, std::wstring> fileDictionary;
    std::vector<GDIBitmap> gdiBitmaps;
    std::vector<Bitmap> bitmaps;
    //Bitmap playerBitmap;
    //int score;
private:
};