#ifndef NPC_H
#define NPC_H

#include "Unit.h"
#include "Vision.h"


class NPC : public Unit {
	private:
		vector<pair<float, Direction>*>* path;
		vector<pair<float, Direction>*>::iterator currentPathVector;
		int nextIterator;
		float distanceOnCurrentPathVector;
		float distanceOffPath;
		float visionRadius;
		
		static const float visionAngle;
		static const float maxAllottedDistanceFromPath;

		void UpdateVision(float dt);
		void HandleIntelligence(float dt);
		bool IsPlayerInSight();
		void Patrol(float dt);
		bool IsPlayerInRange();
		void MoveToPlayer();
		bool IsOffPath();
		bool HasChasedTooFar();
		void ReturnToPat();
		void InvertPath();
		float GetLeftVisionAngle();
		float GetRightVisionAngle();
	public:
		NPC();
		~NPC();
		float UpdatePos(float dt);
		float GetVisionRadius() { return visionRadius; }
};

#endif