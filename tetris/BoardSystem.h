#pragma once

#include "entityx/entityx.h"
#include "MoveLeftEvent.h"
#include "MoveRightEvent.h"
#include "InstantDownEvent.h"
#include "RotateEvent.h"
#include "MoveDownEvent.h"
#include "Game.h"
#include "PieceSpawnEvent.h"
#include "RestartEvent.h"

struct ScoreEvent;
struct Piece;

// Updates a body's position and rotation.
struct BoardSystem : entityx::System<BoardSystem>, entityx::Receiver<BoardSystem> {
	void configure(entityx::EventManager &events) override;

	explicit BoardSystem(std::shared_ptr<Game> target);
	
	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
	
	bool isMergable(Piece& piece);
	void checkForGameOver();
	void updateScoreScreen(int newRows);
	void scoreAndShiftRowsDown(std::vector<int> fullRows, entityx::EventManager &events);
	std::vector<int> getFullRows();
	void merge(Piece& piece);

	int distanceToTopPieceEdge(Piece* p);	
	int distanceToBottomPieceEdge(Piece* p);	
	int distanceToLeftPieceEdge(Piece* p);	
	int distanceToRightPieceEdge(Piece* p);
	
	void receive(const MoveLeftEvent &moveLeft);
	void receive(const MoveRightEvent &moveRight);
	void receive(const MoveDownEvent &moveDownEvent);
	void receive(const RotateEvent &rotateEvent);
	void receive(const InstantDownEvent &instantDownEvent);
	void receive(const PieceSpawnEvent &pieceSpawnEvent);
	void receive(const ScoreEvent &scoreEvent);
	void receive(const RestartEvent &restartEvent);

	std::shared_ptr<Game> target;
	entityx::Entity piece;
	entityx::Entity board;
	entityx::Entity scoreScreen;
	entityx::EventManager *events;

	double pieceMoveDownStartTime;
	double horizontalMovePieceStartTime;
	double currentTime;
	long score;
	long filledRows;
	long maxFilledRows;
	bool gameOver;
	bool restart;
	
};
