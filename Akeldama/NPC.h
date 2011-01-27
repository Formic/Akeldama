/**
 * NPC class - isA Character
 *
 * NPC's are set to govern themselves by patrolling a path. The player will be hostile to the player 
 * when the player enters the NPC's cone of vision. 
 */
#ifndef NPC_H
#define NPC_H

#include "Character.h"
#include "Vision.h"

class NPC : public Character {
	private:
		//-= Member variables =-
		vector<pair<float, Direction>*>* path;
		vector<pair<float, Direction>*>::iterator currentPathVector;
		int nextIterator;
		float distanceOnCurrentPathVector;
		float distanceOffPath;
		float visionRadius;
		
		//-= Static member variables =-
		static const float visionAngle;
		static const float maxAllottedDistanceFromPath;

		//-= Methods =-
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