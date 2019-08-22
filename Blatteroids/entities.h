#pragma once

#include "GameObject.h"
#include "mysoundengine.h"
#include "GameObject.h"

// Manages the sound effects
class SoundFX : public GameObject
{
private:
	Rectangle2D collisionShape ;
	static const int NUMSHOOTSOUNDS = 3 ;
	static const int NUMEXPLOSIONSOUNDS = 5 ;
 SoundIndex m_title ;	
	SoundIndex m_thrust ;
	SoundIndex m_bullets[NUMSHOOTSOUNDS] ;
	SoundIndex m_explosions[NUMEXPLOSIONSOUNDS] ;
 SoundIndex m_refuel ;
 SoundIndex m_itemPickup ;
 SoundIndex m_rocketLaunch ;
 SoundIndex m_rocketExplode ;
	int m_nextShoot ;
	int m_nextExplosion ;

public:
	SoundFX() ;
 void Initialise() ;
 void Draw() ;
 void Update(float frametime) ;
 IShape2D& GetCollisionShape() ; 
 void ProcessCollision(GameObject& other) ;
 void HandleEvent(Event evt) ;
	void LoadSounds() ;
	void StartThrust(int volume) ;
	void StopThrust() ;
 void PlayShoot() ;
	void PlayExplosion() ;
 void PlayRefuel() ;
 void StopRefuel() ;
 void PlayItemPickUp() ;
 void PlayRocketLaunch() ;
 void PlayRocketExplode() ;
};

// Class to handle the ground
class Ground : public GameObject
{
private:
	Rectangle2D collisionShape ;

public:
	Ground() ;
	void Initialise(Vector2D startPos) ;
	void ProcessCollision(GameObject& other) ;
	void Update(float frametime) ;
	IShape2D& GetCollisionShape() ;
 Rectangle2D GetRectangle() ;
	void HandleEvent(Event evt) ;
 float GetCurrentPosition() ;
};

// Class to handle the building
class Building : public GameObject
{
private:
	Rectangle2D collisionShape ;

public:
	Building() ;
	virtual void Initialise(Vector2D startPos) ;
	void ProcessCollision(GameObject& other) ;
	virtual void Update(float frametime) ;
	IShape2D& GetCollisionShape() ;
 Rectangle2D GetRectangle() ;
	void HandleEvent(Event evt) ;
 float GetCurrentPosition() ;
 bool RefuelCheck() ;
};

// Class to handle the refuel building
class RefuelBuilding : public Building
{
private:
 float m_animationSpeed ;
 float m_currentAnimation ;

public:
	RefuelBuilding() ;
	void Initialise(Vector2D startPos) ;
	void Update(float frametime) ;
};

// Class to handle player bullets
class Bullet : public GameObject
{
private:
	Circle2D collisionShape ;
	Vector2D m_velocity ;
	float m_timer ;
 SoundFX* m_pSound ;

public:
	Bullet();
	virtual void Initialise(Vector2D startPos, Vector2D velocity, float angle, SoundFX* m_pSound) ;
	virtual void ProcessCollision(GameObject& other) ;
	virtual void Update(float frametime) ;
	IShape2D& GetCollisionShape() ;
};

class GameManager ; // Forward declaration
// Class to handle player missles
class Missle : public GameObject
{
private:
	Circle2D collisionShape ;
	Vector2D m_velocity ;
	float m_timer ;
 SoundFX* m_pSound ;
 float m_launchTimer ;
 GameManager* m_pGameManager ;

public:
	Missle();
	void Initialise(Vector2D startPos, Vector2D velocity, SoundFX* m_pSound, GameManager* pGameManager) ;
 void ProcessCollision(GameObject& other) ;
	void Update(float frametime) ;
	IShape2D& GetCollisionShape() ;
};

// Class to handle alien bullets
class AlienBullet : public GameObject
{
private:
	Circle2D collisionShape ;
	Vector2D m_velocity ;
	float m_timer ;
 SoundFX* m_pSound ;

public:
	AlienBullet();
	void Initialise(Vector2D startPos, Vector2D velocity, float angle, SoundFX* m_pSound) ;
	void ProcessCollision(GameObject& other) ;
	void Update(float frametime) ;
	IShape2D& GetCollisionShape() ;
 Circle2D GetCircle() const ;
};

// Class to handle flame from the ship
class Flame : public GameObject
{
protected:
	Rectangle2D collisionShape ;
 Vector2D m_velocity ;  
 float m_animationSpeed ;
 float m_currentAnimation ;

public:
	Flame() ;
	virtual void Initialise(Vector2D startPos, Vector2D velocity, float animationSpeed, float scale) ;
	void ProcessCollision(GameObject &other) ;
	void Update(float frametime) ;
	IShape2D& GetCollisionShape() ;
	void HandleEvent(Event evt) ;
};

// Class to handle missle smoke
class Smoke : public Flame
{
public:
 Smoke() ;
 void Initialise(Vector2D startPos, Vector2D velocity, float animationSpeed, float scale) ;
};

// Class to handle explosions
class Explosion : public GameObject
{
private:
 Rectangle2D collisionShape ;
 Vector2D m_velocity ;
 float m_animationSpeed ;
 float m_currentAnimation ;

public:
 Explosion() ;
 void Initialise(Vector2D startPos, Vector2D velocity, float animationSpeed, float scale) ;
 void ProcessCollision(GameObject &other) ;
 void Update(float frametime) ;
 IShape2D& GetCollisionShape() ;
 void HandleEvent(Event evt) ;
};

// Class to handle damage to ship
class Damage : public GameObject
{
private:
 Rectangle2D collisionShape ;
 Vector2D m_velocity ;
 float m_animationSpeed ;
 float m_currentAnimation ;

public:
 Damage() ;
 void Initialise(Vector2D startPos, Vector2D velocity, float animationSpeed, float scale) ;
 void ProcessCollision(GameObject &other) ;
 void Update(float frametime) ;
 IShape2D& GetCollisionShape() ;
 void HandleEvent(Event evt) ;
};

// Class to handle the health bar
class Health : public GameObject
{
private:
	Rectangle2D collisionShape ;
 Vector2D m_size ;
 float m_healthAmount ;

public:
	Health();
	void Initialise(Vector2D startPos, float size) ;
	void ProcessCollision(GameObject& other) ;
 void Draw() ;
	void Update(float frametime) ;
 float GetHealth() const ;
 void Heal(float amount) ;
 void TakeDamage(float amount) ;
	IShape2D& GetCollisionShape() ;
	void HandleEvent(Event evt) ;
};

// Class to handle the fuel bar
class Fuel : public GameObject
{
private:
	Rectangle2D collisionShape ;
 Vector2D m_size ;
 float m_fuelAmount ;
 SoundFX* m_pSound ;

public:
	Fuel();
	void Initialise(Vector2D startPos, float size, SoundFX* pSound) ;
	void ProcessCollision(GameObject& other) ;
 void Draw() ;
	void Update(float frametime) ;
 float GetFuel() const ;
 void Use(float amount) ;
 void Refuel(float amount) ;
	IShape2D& GetCollisionShape() ;
	void HandleEvent(Event evt) ;
};

// Class to handle ammunition
class Ammunition : public GameObject
{
private:
	Rectangle2D collisionShape ;
 Vector2D m_size ;
 float m_ammoAmount ;
 int m_missleAmount ;

public:
	Ammunition();
	void Initialise(Vector2D startPos, float size) ;
	void ProcessCollision(GameObject& other) ;
 void Draw() ;
	void Update(float frametime) ;
 float GetAmmo() const ;
 void Use(float amount) ;
 void Resupply(float amount) ;
	IShape2D& GetCollisionShape() ;
	void HandleEvent(Event evt) ;
 void LoadMissle() ;
 void SpendMissle() ;
 int GetMissle() const ;
};

// Class to handle the background
class Background : public GameObject
{
private:
	Rectangle2D collisionShape ;
 float m_animationSpeed ;
 float m_currentAnimation ;

public:
	Background() ;
	void Initialise(Vector2D startPos, float animationSpeed) ;
	void ProcessCollision(GameObject& other) ;
	void Update(float frametime) ;
	IShape2D& GetCollisionShape() ;
	void HandleEvent(Event evt) ;
 float GetCurrentPosition() ;
};

// Class to handle the planets in the background
class FloraFauna : public GameObject
{
private:
	Rectangle2D collisionShape ;
 float m_animationSpeed ;
 float m_currentAnimation ;

public:
	FloraFauna() ;
	void Initialise(float startPos, int floraFauna) ;
	void ProcessCollision(GameObject& other) ;
	void Update(float frametime) ;
	IShape2D& GetCollisionShape() ;
	void HandleEvent(Event evt) ;
 float GetCurrentPosition() ;
};

// Class to handle fragments in the game
class Fragments : public GameObject
{
private:
	static const int MAXFRAGMENTS = 200 ;
	Vector2D m_positions[MAXFRAGMENTS] ;		// Position of each fragment
	Vector2D m_velocities[MAXFRAGMENTS] ;	// Velocity of each fragment	
	unsigned int m_colours[MAXFRAGMENTS] ;	// Colour of each fragment
	Point2D m_collider ;
	int m_nextFragment ;			// The next fragment to add

public:
	Fragments() ;
	void AddFragment(Vector2D position, Vector2D velocity, unsigned int colour) ;
	void Update(float frametime) ;
	IShape2D& GetCollisionShape() ;
	void ProcessCollision(GameObject& other) ;
	void Draw() ;
	void HandleEvent(Event evt) ;
};

// Class to handle the ship
class Ship : public GameObject
{
private:
 GameManager* m_pManager ;
 Health *m_health ; // Handles the ships health
 Fuel *m_fuel ; // Handles the ships fuel
	Circle2D collisionShape ;
	Vector2D m_velocity ;
 Ammunition *m_ammoAmount ; // Creates & handles the ammo bar
 SoundFX *m_soundFX ;
	float m_shootingDelay ; // Cooldown on shooting current weapon
 int m_shootingVolume ;
 bool m_landedOnRefuel ;
 bool m_landedOnBuilding ;
 bool m_thrusting ; // Determines whether the ship is thrusting or not.
 bool m_rotate ; // Used to rotate the ship during a collision.
 float m_timer ; // Used for the bounce when colliding with a building

public:
	Ship() ;
	void Initialise(Vector2D startPos, Health* pHealth, Fuel* pFuel, Ammunition* pAmmo, SoundFX *pSound, GameManager* pGameManager) ;
	void ProcessCollision(GameObject& other) ;
	void Update(float frametime) ;
	IShape2D& GetCollisionShape() ;
	void HandleEvent(Event evt) ;
 float GetCurrentXPosition() const ;
 float GetCurrentYPosition() const ; 
 bool GetState() const ;
 void LoadMissle() ;
};

// Class to handle the aliens in the game
class Aliens : public GameObject
{
protected:
	Circle2D collisionShape ;
	Vector2D m_velocity ;
 SoundFX *m_soundFX ;
 Ship* m_pShip ;
 bool m_isDead ;
 int m_healthAmount ;

public:
	Aliens() ;
	virtual void Initialise(Vector2D startPos, SoundFX* pSound, Ship* pShip) ;
	void ProcessCollision(GameObject& other) ;
	virtual void Update(float frametime) ;
	IShape2D& GetCollisionShape() ;
	void HandleEvent(Event evt) ;
 bool IsDead() const ;
 float GetXPosition() const ;
 float GetYPosition() const ;
};

// Class to handle the aliens that shoot in the game
class AlienShooter : public Aliens
{
private:
	float m_shootingDelay ; // Cooldown on shooting current weapon

public:
 AlienShooter() ;
	void Initialise(Vector2D startPos, SoundFX* pSound, Ship* pShip) ;
	void Update(float frametime) ;
};

// Class to handle the rare aliens in the game
class AlienShooterRare : public Aliens
{
private:
 float m_shootingDelay ; // Cooldown on shooting current weapon

public:
 AlienShooterRare() ;
	void Initialise(Vector2D startPos, SoundFX* pSound, Ship* pShip) ;
	void Update(float frametime) ;
};

// Class to handle the item drops
class MissleDrop : public GameObject
{
private:
	Circle2D collisionShape ;
 float m_animationSpeed ;
 float m_currentAnimation ;

public:
	MissleDrop() ;
	virtual void Initialise(Vector2D startPos) ;
	virtual void ProcessCollision(GameObject& other) ;
	void Update(float frametime) ;
	IShape2D& GetCollisionShape() ;
	void HandleEvent(Event evt) ;
};

// Manages game assets, such as the ground and buildings
class GameManager : public GameObject
{
private:
 Rectangle2D collisionShape ;
 int m_score ; // Player score
 float m_gap[4] ;
 bool m_notOver ;
 static const int MAXASSETS = 20 ;
 Ground* m_pGround[MAXASSETS] ;
 Building* m_pBuilding[MAXASSETS] ;
 FloraFauna* m_pFloraFauna[MAXASSETS] ; 
 Background* m_pBackground[MAXASSETS] ;
 SoundFX *m_pSound ;
 Ship* m_pShip ;
 Aliens* m_pAliens[MAXASSETS] ;
 int MAXALIENS ;

public:
 GameManager() ;
 void Initialise(Ship* pShip, SoundFX* pSound) ;
 void Draw() ;
 void Update(float frametime) ;
 IShape2D& GetCollisionShape() ; 
 void ProcessCollision(GameObject& other) ;
 void HandleEvent(Event evt) ;
 int GetScore() const ;
 Ground* CreateGround() ;
 void RemoveGround(Ground* pGround) ;
 Building* CreateBuilding() ;
 void RemoveBuilding(Building* pBuilding) ;
 FloraFauna* CreateFloraFauna() ;
 void RemoveFloraFauna(FloraFauna* pFloraFauna) ;
 Background* CreateBackground() ;
 void RemoveBackground(Background* pBackground) ;
 void GameOver() ;
 Aliens* CreateAlien() ;
 void RemoveAlien(Aliens* pAlien) ;
 float AlienXPosition() ;
 float AlienYPosition() ;
};

// Manages the scoreboard
class ScoreBoard : public GameObject
{
private:
	Rectangle2D collisionShape ;
 int latestScore ;
	float m_scoreboardTimer ;

public:
 ScoreBoard() ;
 void Initialise() ;
 void Draw() ;
 void Update(float frametime) ;
 IShape2D& GetCollisionShape() ; 
 void ProcessCollision(GameObject& other) ;
 void HandleEvent(Event evt) ;
 void NewGame() ;
};