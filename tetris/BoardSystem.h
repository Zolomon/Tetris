#pragma once

#include "entityx/entityx.h"
#include "MoveLeftEvent.h"
#include "MoveRightEvent.h"
#include "InstanDownEvent.h"
#include "RotateEvent.h"
#include "MoveDownEvent.h"
#include "Game.h"
#include <unordered_set>

struct Piece;

// Updates a body's position and rotation.
struct BoardSystem : public entityx::System<BoardSystem>, public entityx::Receiver<BoardSystem> {
public:
	void configure(entityx::EventManager &events) override;

	explicit BoardSystem(std::shared_ptr<Game> target);
	
	bool isMergable(Piece& piece);

	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
	int distanceToTopPieceEdge(Piece* p);
	int distanceToBottomPieceEdge(Piece* p);
	int distanceToLeftPieceEdge(Piece* p);
	int distanceToRightPieceEdge(Piece* p);
	void receive(const MoveLeftEvent &moveLeft);

	void receive(const MoveRightEvent &moveRight);

	void receive(const MoveDownEvent &moveDownEvent);

	void receive(const RotateEvent &rotateEvent);

	void receive(const InstantDownEvent &instantDownEvent);

	void merge(Piece& piece);

	std::shared_ptr<Game> target;
	entityx::Entity piece;
	entityx::Entity board;
};
