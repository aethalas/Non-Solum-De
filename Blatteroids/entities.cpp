#include "entities.h"
#include "gamecode.h"
#include "myinputs.h"

const float MAXSTAT = 876.0f ;
const float TURNSPEED = 3.0f ;
const float ACCELERATION = 875.0f ;
const float FRICTION = 0.75f ;
const float BULLETSPEED = 15.0f ;
const float DELAY = 0.5f ;
const float FUELCOST = 0.5f ;
const float HEALTHCOST = 25.0f ;
const float AMMOCOST = 50.0f ;
const Vector2D GRAVITY (0, 135) ;
const float SCOREBOARDTIMER = 1000.0f ;

SoundFX::SoundFX() : GameObject(SOUNDFX)
{
	m_nextExplosion = 0 ; // Not loaded yet
	m_nextShoot = 0 ; // Not loaded yet
	m_thrust = 0 ; // Not loaded yet
 m_refuel = 0 ;  // Not loaded yet
 m_itemPickup = 0 ; // Not loaded yet
 m_rocketLaunch = 0 ; // Not loaded yet
 m_rocketExplode = 0 ; // Not loaded yet

	for (int i = 0; i < NUMEXPLOSIONSOUNDS; i++)
	{
		m_explosions[i] = 0 ;	// Not loaded yet
	}

	for (int i = 0 ; i < NUMSHOOTSOUNDS; i++)
	{
		m_bullets[i] = 0 ;	// Not loaded yet
	}
}


void SoundFX::Initialise()
{
 // Not used.
}

void SoundFX::Draw()
{
 // No draw function. It doesn't need one.
}

void SoundFX::Update(float frametime)
{
 // Not used.
}

IShape2D& SoundFX::GetCollisionShape()
{
	return collisionShape ;
}

void SoundFX::ProcessCollision(GameObject& other)
{
 // No collisions.
}

void SoundFX::HandleEvent(Event evt)
{
 // No handle events.
}

void SoundFX::LoadSounds()
{
	MySoundEngine* pSoundEngine = MySoundEngine::GetInstance();

 // Load the thrust sound
	if (m_thrust == 0)
	{
		m_thrust = pSoundEngine->LoadWav(L"thrustloop1.wav") ;
	}

 // Load the shooting sound
	for (int i = 0; i < NUMSHOOTSOUNDS; i++)
	{
		// If sounds are currently loaded, no need to load them again
		if (m_bullets[i] == 0)
		{
			m_bullets[i] = pSoundEngine->LoadWav(L"shoot.wav");
		}
	}

	// Load the explosions sounds
	for (int i = 0; i < NUMEXPLOSIONSOUNDS; i++)
	{
		// If sounds are currently loaded, no need to load them again
		if (m_explosions[i] == 0)
		{
			switch (i % 5)	// Only 5 wave sounds
			{
			case 0:
				m_explosions[i] = pSoundEngine->LoadWav(L"explosion1.wav");
				break;
			case 1:
				m_explosions[i] = pSoundEngine->LoadWav(L"explosion2.wav");
				break;
			case 2:
				m_explosions[i] = pSoundEngine->LoadWav(L"explosion3.wav");
				break;
			case 3:
				m_explosions[i] = pSoundEngine->LoadWav(L"explosion4.wav");
				break;
			case 4:
				m_explosions[i] = pSoundEngine->LoadWav(L"explosion5.wav");
				break;
			}
		}
	}

 // Load the refuel sound
	if (m_refuel == 0)
	{
		m_refuel = pSoundEngine->LoadWav(L"refuel.wav") ;
	}

 // Load the item pickup sound
 if (m_itemPickup == 0)
 {
  m_itemPickup = pSoundEngine->LoadWav(L"itempickup.wav") ;
 }

 // Load the missle/rocket launch sound
 if (m_rocketLaunch == 0)
 {
  m_rocketLaunch = pSoundEngine->LoadWav(L"rocketlaunching.wav") ; 
 }

 // Load the missle/rocket explode sound
 if (m_rocketExplode == 0)
 {
  m_rocketExplode = pSoundEngine->LoadWav(L"rocketexplode.wav") ;
 }
}

void SoundFX::StartThrust(int volume)
{ // Play thrusting sound
 MySoundEngine::GetInstance()->SetVolume(m_thrust, volume) ;
	MySoundEngine::GetInstance()->Play(m_thrust, true) ;
}

void SoundFX::StopThrust()
{ // Stop thrusting sound
	MySoundEngine::GetInstance()->Stop(m_thrust) ;
}

void SoundFX::PlayShoot()
{ // Play shoot sound
	MySoundEngine::GetInstance()->Play(m_bullets[m_nextShoot]) ;

	++m_nextShoot ;

	if (m_nextShoot >= NUMSHOOTSOUNDS)
 {
		m_nextShoot = 0 ;
 }
}

void SoundFX::PlayExplosion()
{ // Play explosion sound
	MySoundEngine::GetInstance()->Play(m_explosions[m_nextExplosion]) ;

	m_nextExplosion += rand() % 3 ;	

	if (m_nextExplosion >= NUMEXPLOSIONSOUNDS)
 {
	 m_nextExplosion = 0 ;
 }
}

void SoundFX::PlayRefuel()
{ // Play refuel sound
	MySoundEngine::GetInstance()->Play(m_refuel, true) ;
}

void SoundFX::StopRefuel()
{ // Stop refuel sound
	MySoundEngine::GetInstance()->Stop(m_refuel) ;
}

void SoundFX::PlayItemPickUp()
{ // Play the item pickup sound
 MySoundEngine::GetInstance()->Play(m_itemPickup) ;
}

void SoundFX::PlayRocketLaunch()
{ // Play the missle/rocket launch sound
 MySoundEngine::GetInstance()->Play(m_rocketLaunch) ;
}

void SoundFX::PlayRocketExplode()
{ // Stop the missle/rocket launch sound
 MySoundEngine::GetInstance()->Play(m_rocketExplode) ;
}







Ground::Ground() : GameObject(GROUND)
{
 // No-op
}

void Ground::Initialise(Vector2D startPos)
{
	m_position = startPos ;
	LoadImage(L"ground.bmp") ;
 m_drawDepth = 11 ;
}

void Ground::ProcessCollision(GameObject& other)
{
 // No-op
}

void Ground::Update(float frametime)
{
 // No-op
}

IShape2D& Ground::GetCollisionShape()
{
 collisionShape.PlaceAt(m_position.YValue+50,m_position.XValue+900, m_position.YValue-50, m_position.XValue-900) ;
	return collisionShape ;
}

Rectangle2D Ground::GetRectangle()
{
 return collisionShape ;
}

void Ground::HandleEvent(Event evt)
{
 // No-op
}

float Ground::GetCurrentPosition()
{
 return m_position.XValue ;
}






Building::Building() : GameObject(BUILDING)
{
 // No-op
}

void Building::Initialise(Vector2D startPos)
{
	m_position = startPos ;
 m_drawDepth = 10 ;

 int random = rand() % 10 + 1 ;

 if (random == 1) 
 { // 1 in 10 chance of the hotel building
	 LoadImage(L"building.bmp") ;
 }
 else if (random == 2)
 { // 1 in 10 chance of the hospital building
 	LoadImage(L"building2.bmp") ;
 }
 else
 { // Spawn the regular, plain buildings
 	LoadImage(L"building3.bmp") ;
 }

}

void Building::ProcessCollision(GameObject& other)
{
 // No-op
}

void Building::Update(float frametime)
{
 // No-op
}

IShape2D& Building::GetCollisionShape()
{
 collisionShape.PlaceAt(m_position.YValue+487,m_position.XValue+320, m_position.YValue-487, m_position.XValue-320) ;
	return collisionShape ;
}

Rectangle2D Building::GetRectangle()
{
 return collisionShape ;
}

void Building::HandleEvent(Event evt)
{
 // No-op
}

float Building::GetCurrentPosition()
{
 return m_position.XValue ;
}








RefuelBuilding::RefuelBuilding()
{
 // No-op
}

void RefuelBuilding::Initialise(Vector2D startPos)
{
 m_position = startPos ;
 m_animationSpeed = 3.0f ;
 m_currentAnimation = 0.0f ;
 m_refuel = 1 ; // This building refuels the player
 m_drawDepth = 10 ;

 LoadImage(L"refuel_building.bmp") ;
 LoadImage(L"refuel_building2.bmp") ;
 LoadImage(L"refuel_building3.bmp") ;
 LoadImage(L"refuel_building4.bmp") ; 
 LoadImage(L"refuel_building3.bmp") ;
 LoadImage(L"refuel_building2.bmp") ;
}

void RefuelBuilding::Update(float frametime)
{
  // Code for animating the refuel buildings
  m_currentAnimation += m_animationSpeed * frametime ;

  if (m_currentAnimation >= 6.0f)
  {
   m_currentAnimation = 0 ;
  }

  m_imageNumber = int(m_currentAnimation) ;
}







Bullet::Bullet() : GameObject(BULLET)
{
 // No-op
}

void Bullet::Initialise(Vector2D startPos, Vector2D velocity, float angle, 
                        SoundFX* pSound)
{
 m_position = startPos ;
 m_velocity = velocity ;
 m_timer = 10000.0f ;
 m_angle = angle ;
 m_pSound = pSound ;
 LoadImage(L"bullet.bmp") ;
}

void Bullet::ProcessCollision(GameObject& other)
{
  if (other.GetType() == BUILDING || other.GetType() == ALIEN)
  {
   // Deactivate the bullet
   Deactivate() ;
 
   // Play explosion sound
   m_pSound->PlayExplosion() ;
   
   // Create explosion at the point of impact
   Explosion *pExplosion = new Explosion() ;
   pExplosion->Initialise(m_position, Vector2D(0,0), 6.0f, 0.5f) ;
   Game::instance.m_objects.AddItem(pExplosion, false) ;
   
   // Send event to the GameManager class
   Event evt ;
   evt.type = EVENT_OBJECTDESTROYED ;
   evt.position = m_position ;
   evt.pSource = this ;
   Game::instance.NotifyEvent(evt) ;
  }
}

void Bullet::Update(float frametime)
{
 m_timer -= frametime ; // Countdown

 // Used to determine the movement of the bullet
 Vector2D acceleration ;
 acceleration.setBearing(m_angle + 1.60f, ACCELERATION) ;
 m_velocity = m_velocity + acceleration * frametime ;
 m_position = m_position + m_velocity * frametime ;

 if (m_timer <= 0)
 { // Deactivate the bullet if its been created too long
  Deactivate();
 }
}

IShape2D& Bullet::GetCollisionShape()
{
 collisionShape.PlaceAt(m_position, 20) ;
 return collisionShape ;
}






Missle::Missle() : GameObject(MISSLE)
{
 // No-op
}

void Missle::Initialise(Vector2D startPos, Vector2D velocity, SoundFX* pSound,
                        GameManager* pGameManager)
{
 m_position = startPos ;
 m_velocity = velocity ;
 m_launchTimer = 0.7f ;
 m_timer = 10000.0f ;
 m_pSound = pSound ;
 m_drawDepth = 4 ;
 m_pGameManager = pGameManager ;
 LoadImage(L"missle.bmp") ;
}

void Missle::ProcessCollision(GameObject& other)
{
  if (other.GetType() == BUILDING || other.GetType() == ALIEN)
  { // If the missle collides with either a building, or an alien
   Deactivate() ;

   // Play the missle/rocket explosion sound
   m_pSound->PlayRocketExplode() ;

   // Create an explosion at the point of impact
   Explosion *pExplosion = new Explosion() ;
   pExplosion->Initialise(m_position, Vector2D(0,0), 6.0f, 1.5f) ;
   Game::instance.m_objects.AddItem(pExplosion, false) ;
  
   // Send event to the GameManager class
   Event evt ;
   evt.type = EVENT_OBJECTDESTROYED ;
   evt.position = m_position ;
   evt.pSource = this ;
   Game::instance.NotifyEvent(evt) ;
  }
}

void Missle::Update(float frametime)
{
 // Count down the relevant timers
 m_timer -= frametime ;
 m_launchTimer -= frametime ;

	Vector2D acceleration;
	acceleration.setBearing(m_angle, ACCELERATION) ;
	m_velocity = m_velocity + acceleration * frametime ;

 
 if (m_launchTimer > 0)
 { // Pushes the missle/rocket backwards/upwards, bit of an affect
   // to add realisim to the movement of the trajectory
  m_position.YValue = m_position.YValue + 250.0f * frametime ;
  m_position.XValue = m_position.XValue - 250.0f * frametime ;
 }

 if (m_launchTimer < 0)
 { // Moves the rocket toward the alien's position until a collision occurs
  if (m_position.XValue < m_pGameManager->AlienXPosition())
  {
   acceleration.setBearing(m_angle, ACCELERATION) ;
   m_position.XValue = m_position.XValue + 1000.0f * frametime ;
  }
  if(m_position.XValue > m_pGameManager->AlienXPosition())
  {
   m_position.XValue = m_position.XValue - 1000.0f * frametime ;
  }  

  if (m_position.YValue < m_pGameManager->AlienYPosition())
  {
   m_position.YValue = m_position.YValue + 1000.0f * frametime ;
  }
  if (m_position.YValue > m_pGameManager->AlienYPosition())
  {
   m_position.YValue = m_position.YValue - 1000.0f * frametime ;
  }
 }

 // Create smoke behind the missle/rocket's position
	Smoke *pSmoke = new Smoke ;
	Vector2D flameDirection ;
	flameDirection.setBearing(m_angle - 1.5f, 600) ;
	pSmoke->Initialise(m_position, flameDirection, 20.0f, 0.8f) ;
	Game::instance.m_objects.AddItem(pSmoke, false) ;

 if (m_timer <= 0)
 { // If the timer of the missle/rocket reaches zero, remove it
  Deactivate();
 }
}

IShape2D& Missle::GetCollisionShape()
{
 collisionShape.PlaceAt(m_position, 20) ;
 return collisionShape ;
}








AlienBullet::AlienBullet() : GameObject(ALIENBULLET)
{
 // No-op
}

void AlienBullet::Initialise(Vector2D startPos, Vector2D velocity, float angle,
                             SoundFX* pSound)
{
	m_position = startPos ;
	m_velocity = velocity ;
	m_timer = 10000.0f ;
 m_angle = angle ;
 m_pSound = pSound ;
	LoadImage(L"bullet2.bmp") ;
}

void AlienBullet::ProcessCollision(GameObject& other)
{
  if (other.GetType() == BUILDING || other.GetType() == SHIP)
  { // If the missle collides with either a building, or the player
   Deactivate();

   // Play the explosion sound
   m_pSound->PlayExplosion() ;

   // Create an explosion at the correct position
   Explosion *pExplosion = new Explosion() ;
   pExplosion->Initialise(m_position, Vector2D(0,0), 6.0f, 0.5f) ;
   Game::instance.m_objects.AddItem(pExplosion, false) ;

   // Send event to the GameManager class
	  Event evt ;
	  evt.type = EVENT_OBJECTDESTROYED ;
	  evt.position = m_position ;
	  evt.pSource = this ;
	  Game::instance.NotifyEvent(evt) ;
  }
}

void AlienBullet::Update(float frametime)
{
 // Countdown the timer 
	m_timer -= frametime ;

	Vector2D acceleration ; 
	acceleration.setBearing(m_angle + 1.60f, ACCELERATION) ;
	m_velocity = m_velocity + acceleration * frametime ;
	m_position = m_position + m_velocity * frametime ;

	if (m_timer <= 0)
	{ // If the bullet has been around too long, remove it
		Deactivate() ;
	}
}

IShape2D& AlienBullet::GetCollisionShape()
{
 collisionShape.PlaceAt(m_position, 20) ;
	return collisionShape ;
}

Circle2D AlienBullet::GetCircle() const
{
 return collisionShape ;
}








Flame::Flame() : GameObject(FLAME)
{
 // No-op
}

void Flame::Initialise(Vector2D startPos, Vector2D velocity,
                       float animationSpeed, float scale)
{
  m_velocity = velocity ;
  m_position = startPos ;
  m_animationSpeed = animationSpeed ;
  m_currentAnimation = 0.0f ;
  m_imageScale = scale ;
  m_drawDepth = 4 ;

  LoadImage(L"flame1.bmp");
  LoadImage(L"flame2.bmp");
  LoadImage(L"flame3.bmp");
  LoadImage(L"flame4.bmp");
  LoadImage(L"flame5.bmp");
  LoadImage(L"flame6.bmp");
  LoadImage(L"flame7.bmp");
  LoadImage(L"flame8.bmp");
  LoadImage(L"flame9.bmp");
  LoadImage(L"flame10.bmp");
};
 
void Flame::ProcessCollision(GameObject& other)
{
 // No-op
}

void Flame::Update(float frametime)
{
  // Used to animate the flame so that it cycles through
  // the loaded images
  m_currentAnimation += m_animationSpeed * frametime ;

  if (m_currentAnimation >= 10.0f)
  {
    Deactivate();
    m_currentAnimation = 0 ;
  }

  m_position = m_position + m_velocity * frametime ;

  m_imageNumber = int(m_currentAnimation) ;
}

IShape2D& Flame::GetCollisionShape()
{
 	return collisionShape ;
}

void Flame::HandleEvent(Event evt)
{
 // No-op
}






Smoke::Smoke()
{
 // No-op
}

void Smoke::Initialise(Vector2D startPos, Vector2D velocity,
                       float animationSpeed, float scale)
{
  m_velocity = velocity ;
  m_position = startPos ;
  m_animationSpeed = animationSpeed ;
  m_currentAnimation = 0.0f ;
  m_imageScale = scale ;
  m_drawDepth = 4 ;

  LoadImage(L"smoke1.bmp");
  LoadImage(L"smoke2.bmp");
  LoadImage(L"smoke3.bmp");
  LoadImage(L"smoke4.bmp");
  LoadImage(L"smoke5.bmp");
  LoadImage(L"smoke6.bmp");
  LoadImage(L"smoke7.bmp");
  LoadImage(L"smoke8.bmp");
  LoadImage(L"smoke9.bmp");
  LoadImage(L"smoke10.bmp");
}




Explosion::Explosion() : GameObject(EXPLOSION)
{
 // No-op
}

void Explosion::Initialise(Vector2D startPos, Vector2D velocity,
                           float animationSpeed, float scale)
{
  m_velocity = velocity ;
  m_position = startPos ;
  m_animationSpeed = animationSpeed ;
  m_currentAnimation = 0.0f ;
  m_imageScale = scale ;
  m_drawDepth = 11 ;

  LoadImage(L"explosion1.bmp");
  LoadImage(L"explosion2.bmp");
  LoadImage(L"explosion3.bmp");
  LoadImage(L"explosion4.bmp");
  LoadImage(L"explosion5.bmp");
  LoadImage(L"explosion6.bmp");
  LoadImage(L"explosion7.bmp");
}

void Explosion::ProcessCollision(GameObject& other)
{
 // No-op
}

void Explosion::Update(float frametime)
{
  // Used to animate the explosion so that it cycles through
  // the loaded images
  m_currentAnimation += m_animationSpeed * frametime ;

  if (m_currentAnimation >= 7.0f)
  {
    Deactivate();
    m_currentAnimation = 0 ;
  }

  m_position = m_position + m_velocity * frametime ;

  m_imageNumber = int(m_currentAnimation) ;
}

IShape2D& Explosion::GetCollisionShape()
{
 	return collisionShape ;
}

void Explosion::HandleEvent(Event evt)
{
 // No-op
}





Damage::Damage() : GameObject(DAMAGE)
{
 // No-op
}

void Damage::Initialise(Vector2D startPos, Vector2D velocity,
                        float animationSpeed, float scale)
{
  m_velocity = velocity ;
  m_position = startPos ;
  m_animationSpeed = animationSpeed ;
  m_currentAnimation = 0.0f ;
  m_imageScale = scale ;
  m_drawDepth = 6 ;

  LoadImage(L"explosion1.bmp");
  LoadImage(L"explosion2.bmp");
  LoadImage(L"explosion3.bmp");
}

void Damage::ProcessCollision(GameObject& other)
{
 // No-op
}

void Damage::Update(float frametime)
{
  // Used to animate damage so that it cycles through
  // the loaded images
  m_currentAnimation += m_animationSpeed * frametime ;

  if (m_currentAnimation >= 3.0f)
  {
    Deactivate();
    m_currentAnimation = 0 ;
  }

  m_position = m_position + m_velocity * frametime ;

  m_imageNumber = int(m_currentAnimation) ;
}

IShape2D& Damage::GetCollisionShape()
{
 	return collisionShape ;
}

void Damage::HandleEvent(Event evt)
{
 // No-op
}








Health::Health() : GameObject(HEALTHBAR)
{
 // No-op
}

void Health::Initialise(Vector2D startPos, float value)
{
 m_position = startPos ;
 m_healthAmount = value ;
 m_drawDepth = 11 ;
}

void Health::ProcessCollision(GameObject& other)
{
 // No-op
}

void Health::Draw()
{
 // Create the UI element for Health
 MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance() ;
 Rectangle2D dot ;
 pDrawEngine->DrawAt(Vector2D(m_position.XValue+385, m_position.YValue-105), pDrawEngine->LoadPicture(L"healthbackdrop.bmp"), 1.0f, 0.0f, 0.0f);
 dot.PlaceAt(m_position.YValue+38, m_position.XValue+10, m_position.YValue+7, m_position.XValue+m_healthAmount) ;
 pDrawEngine->FillRect(dot, _XRGB(119, 66, 66)) ;
}

void Health::Update(float frametime)
{
 // Allows the class to remain in the upper left portion of the screen
 m_position = MyDrawEngine::GetInstance()->theCamera.ReverseTransform(Vector2D(80, 44)) ;
}

float Health::GetHealth() const
{
 return m_healthAmount ;
}

void Health::Heal(float amount)
{
 // Heals the player ship, being careful to ensure
 // the health does not exceed the maximum
 if (m_healthAmount < MAXSTAT)
 {
  if ((m_healthAmount + amount) > MAXSTAT)
  {
   m_healthAmount = MAXSTAT ;
  }
  else
  {
   m_healthAmount += amount ;
  }
 }
}

void Health::TakeDamage(float amount)
{
 // Allows the player ship to take damage, as long as the health is over the
 // minimum
 if (amount > MAXSTAT)
 {
  m_healthAmount = 11.0f ;
 }
 else
 {
  m_healthAmount -= amount ;
 }
}

IShape2D& Health::GetCollisionShape()
{
	return collisionShape;
}

void Health::HandleEvent(Event evt)
{
 // No-op
}







Fuel::Fuel() : GameObject(FUELBAR)
{
 // No-op
}

void Fuel::Initialise(Vector2D startPos, float value, SoundFX* pSound)
{
 m_position = startPos ;
 m_fuelAmount = value ;
 m_pSound = pSound ;
 m_drawDepth = 11 ;
}

void Fuel::ProcessCollision(GameObject& other)
{
 // No-op
}

void Fuel::Draw()
{
 // Create the UI element for Fuel
 MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance() ;
 Rectangle2D dot ;
 pDrawEngine->DrawAt(Vector2D(m_position.XValue+385, m_position.YValue-105), pDrawEngine->LoadPicture(L"fuelbackdrop.bmp"), 1.0f, 0.0f, 0.0f);
 dot.PlaceAt(m_position.YValue+38, m_position.XValue+10, m_position.YValue+7, m_position.XValue+m_fuelAmount) ;
 pDrawEngine->FillRect(dot, _XRGB(123, 119, 94)) ;
}

void Fuel::Update(float frametime)
{
 // Allows the class to remain in the upper portion of the screen
 m_position = MyDrawEngine::GetInstance()->theCamera.ReverseTransform(Vector2D(639, 44)) ;
}

void Fuel::Use(float amount)
{
 m_fuelAmount -= amount ;
}

void Fuel::Refuel(float amount)
{
 // Refuels the player ship
 if (m_fuelAmount < 875.0f)
 {
  m_fuelAmount += amount ;
 }
}

float Fuel::GetFuel() const
{
 return m_fuelAmount ; // Return fuel amount
}

IShape2D& Fuel::GetCollisionShape()
{
	return collisionShape ;
}

void Fuel::HandleEvent(Event evt)
{
 // No-op
}






Ammunition::Ammunition() : GameObject(AMMO)
{
 // No-op
}

void Ammunition::Initialise(Vector2D startPos, float value)
{
 m_position = startPos ;
 m_ammoAmount = value ;
 m_drawDepth = 11 ;
 m_missleAmount = 0 ;
}

void Ammunition::ProcessCollision(GameObject& other)
{
 // No-op
}

void Ammunition::Draw()
{
 // Create the UI element for Ammunition
 MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance() ;
 Rectangle2D dot ;
 pDrawEngine->DrawAt(Vector2D(m_position.XValue+385, m_position.YValue-105), pDrawEngine->LoadPicture(L"ammobackdrop.bmp"), 1.0f, 0.0f, 0.0f);
 dot.PlaceAt(m_position.YValue+38, m_position.XValue+10, m_position.YValue+7, m_position.XValue+m_ammoAmount) ;
 pDrawEngine->FillRect(dot, _XRGB(51, 102, 153)) ;

 if (m_missleAmount > 0)
 {
  pDrawEngine->DrawAt(Vector2D(m_position.XValue-90, m_position.YValue-50), pDrawEngine->LoadPicture(L"missleui.bmp"), 1.0f, 0.0f, 0.0f);
 }
 if (m_missleAmount > 1)
 {
  pDrawEngine->DrawAt(Vector2D(m_position.XValue-20, m_position.YValue-50), pDrawEngine->LoadPicture(L"missleui.bmp"), 1.0f, 0.0f, 0.0f);
 }
 if (m_missleAmount > 2)
 {
  pDrawEngine->DrawAt(Vector2D(m_position.XValue+50, m_position.YValue-50), pDrawEngine->LoadPicture(L"missleui.bmp"), 1.0f, 0.0f, 0.0f);
 }
}

void Ammunition::Update(float frametime)
{
 // Allows the class to remain in the upper portion of the screen
 m_position = MyDrawEngine::GetInstance()->theCamera.ReverseTransform(Vector2D(1200, 44)) ;
}

float Ammunition::GetAmmo() const
{
 return m_ammoAmount ;
}

void Ammunition::Use(float amount)
{
 // Allows the player to fire shots, as long as there is sufficient ammo
 if (amount > m_ammoAmount)
 {
  m_ammoAmount = 11.0f ;
 }
 else
 {
  m_ammoAmount -= amount ;
 }
}

void Ammunition::Resupply(float amount)
{
 // Resupplies the player ship
 if (m_ammoAmount < 875.0f)
 {
  m_ammoAmount += amount ;
 }
}

IShape2D& Ammunition::GetCollisionShape()
{
	return collisionShape;
}

void Ammunition::HandleEvent(Event evt)
{
 // No-op
}

void Ammunition::LoadMissle()
{
 // Upon collecting a missle, allows the player to use one
 // This is limited to 3
 if (m_missleAmount <= 3)
 {
  m_missleAmount++ ;
 }
 else
 {
  m_missleAmount = m_missleAmount ;
 }
}

int Ammunition::GetMissle() const
{
 return m_missleAmount ; // Return missle amount
}

void Ammunition::SpendMissle()
{
 // Used to fire missles by the player, as long as they are able to
 if (m_missleAmount > 1)
 {
  m_missleAmount-= 1 ;
 }
 else
 {
 m_missleAmount = 0 ;
 }
}






Background::Background() : GameObject(BACKGROUND)
{
 // No-op
}

void Background::Initialise(Vector2D startPos, float animationSpeed)
{
	m_position = startPos ;
 m_drawDepth = -1 ;

	LoadImage(L"background.bmp") ;
}

void Background::ProcessCollision(GameObject& other)
{
 // No-op
}

void Background::Update(float frametime)
{
 // No-op
}

IShape2D& Background::GetCollisionShape()
{
	return collisionShape ;
}

void Background::HandleEvent(Event evt)
{
 // No-op
}

float Background::GetCurrentPosition()
{
 return m_position.XValue ; // Return X position of the background
}






FloraFauna::FloraFauna() : GameObject(FLORAFAUNA)
{
 // No-op
}

void FloraFauna::Initialise(float startPos, int floraFauna)
{
 m_drawDepth = 20 ;

 if (floraFauna == 1)
 {
	 LoadImage(L"grass.bmp") ;
  m_position = Vector2D(-100.0f+startPos, -885) ;
 }
 else if (floraFauna == 2)
 {
	 LoadImage(L"grass2.bmp") ;
  m_position = Vector2D(-100.0f+startPos, -885) ;
 }
 else if (floraFauna == 3)
 {
	 LoadImage(L"bush.bmp") ;
  m_position = Vector2D(-100.0f+startPos, -885) ;
 }
 else if (floraFauna == 4)
 {
	 LoadImage(L"tree.bmp") ;
  m_position = Vector2D(-100.0f+startPos, -787) ;
 }
 else if (floraFauna == 5)
 {
	 LoadImage(L"tree2.bmp") ;
  m_position = Vector2D(-100.0f+startPos, -787) ;
 }
 else if (floraFauna == 6)
 {
	 LoadImage(L"tree3.bmp") ;
  m_position = Vector2D(-100.0f+startPos, -787) ;
 }
 else if (floraFauna == 7)
 {
	 LoadImage(L"tree4.bmp") ;
  m_position = Vector2D(-100.0f+startPos, -787) ;
 }
 else if (floraFauna == 8)
 {
	 LoadImage(L"rock.bmp") ;
  m_position = Vector2D(-100.0f+startPos, -885) ;
 }
 else if (floraFauna == 9)
 {
	 LoadImage(L"rock2.bmp") ;
  m_position = Vector2D(-100.0f+startPos, -898) ;
 }
 else if (floraFauna == 10)
 {
	 LoadImage(L"rock3.bmp") ;
  m_position = Vector2D(-100.0f+startPos, -885) ;
 }
}

void FloraFauna::ProcessCollision(GameObject& other)
{
 // No-op
}

void FloraFauna::Update(float frametime)
{
 // No-op
}

IShape2D& FloraFauna::GetCollisionShape()
{
	return collisionShape ;
}

void FloraFauna::HandleEvent(Event evt)
{
 // No-op
}

float FloraFauna::GetCurrentPosition()
{
 return m_position.XValue ; // Return X position of the Flora/Fauna
}







Fragments::Fragments() : GameObject(FRAGMENT)
{
	for (int i = 0; i < MAXFRAGMENTS; i++)
	{
		m_positions[i].set(16600.0f+i, 16600.0f) ;
		m_velocities[i].set(0, 0) ;
		m_colours[i] = 0 ;
	}
	m_nextFragment = 0 ;	
	m_handleEvents = true ;	
}

void Fragments::HandleEvent(Event evt)
{
 // Send an event
	if (evt.type == EVENT_OBJECTDESTROYED)
	{
		if (evt.pSource->GetType() == BULLET)
		{
			for (int i = 0; i < 4; i++)
			{
				float direction = rand() % 628 / 100.0f ;	
				float speed = rand() % 100 + 100.0f ;		
				Vector2D dir ;
				dir.setBearing(direction, speed) ;
				AddFragment(evt.position, dir, MyDrawEngine::WHITE) ;
			}
		}
	}
}

void Fragments::AddFragment(Vector2D position, Vector2D velocity,
                            unsigned int colour)
{
	m_positions[m_nextFragment] = position ;
	m_velocities[m_nextFragment] = velocity ;
	m_colours[m_nextFragment] = colour ;
	m_nextFragment++ ;

	if (m_nextFragment >= MAXFRAGMENTS)
	{
		m_nextFragment = 0 ;
	}
}

void Fragments::Update(float frametime)
{
	for (int i = 0; i < MAXFRAGMENTS; i++)
	{
		m_positions[i] = m_positions[i] + m_velocities[i] * frametime ;
	}
}

IShape2D& Fragments::GetCollisionShape()
{
	return m_collider ;
}

void Fragments::ProcessCollision(GameObject& other)
{
 // No-op
}

void Fragments::Draw()
{
	MyDrawEngine::GetInstance()->DrawPointList(m_positions, m_colours, MAXFRAGMENTS) ;
}











Ship::Ship() : GameObject(SHIP)
{
 // Constructor. Needs to be empty.
}

void Ship::Initialise(Vector2D startPos, Health* pHealth, Fuel* pFuel,
                      Ammunition* pAmmo, SoundFX* pSound,
                      GameManager* pGameManager)
{
	m_position = startPos ;
	m_angle = 0.0f ;
	m_velocity.set(0, 0) ;
	m_shootingDelay = 0.0f ;
 m_shootingVolume = -3000 ;
	LoadImage(L"ship.bmp") ;
 m_health = pHealth ;
 m_fuel = pFuel ;
 m_ammoAmount = pAmmo ;
 m_soundFX = pSound ;
 m_landedOnRefuel = false ;
 m_landedOnBuilding = false ;
 m_thrusting = false ;
 m_drawDepth = 5 ;
 m_rotate = false ;
 m_pManager = pGameManager ;
}


void Ship::ProcessCollision(GameObject& other)
{
 // float angle = (m_position - other.GetPosition()).angle() ;

 // Creates a dot under the sprite of the ship. This is used
 // for landing purposes only.
 Point2D landingCheck ;
 Vector2D dotExt(0,-50) ;
 dotExt = dotExt.rotatedBy(-m_angle) ;
 landingCheck.PlaceAt(m_position+dotExt) ;

 // Creates a segment along the top of the ship. Used for damage detection.
 Segment2D firstCheck ;
 Vector2D ext(-115,0);
 ext = ext.rotatedBy(-m_angle) ;
 Vector2D ext2(-75,50) ;
 ext2 = ext2.rotatedBy(-m_angle) ;
 firstCheck.PlaceAt(m_position-ext, m_position+ext2) ;

 // Creates a segment along the front of the ship. Used for damage detection.
 Segment2D secondCheck ;
 Vector2D ext3(-115,0);
 ext3 = ext3.rotatedBy(-m_angle) ;
 Vector2D ext4(75,-50) ;
 ext4 = ext4.rotatedBy(-m_angle) ;
 secondCheck.PlaceAt(m_position-ext3, m_position+ext4) ;

 // Creates a segment along the bottom of the ship. Used for damage detection.
 Segment2D thirdCheck ;
 Vector2D ext5(125,55);
 ext5 = ext5.rotatedBy(-m_angle) ;
 Vector2D ext6(75,-50) ;
 ext6 = ext6.rotatedBy(-m_angle) ;
 thirdCheck.PlaceAt(m_position-ext5, m_position+ext6) ;

 // Creates a segment along the back of the ship. Used for damage detection.
 Segment2D fourthCheck ;
 Vector2D ext7(75,-50);
 ext7 = ext7.rotatedBy(-m_angle) ;
 Vector2D ext8(-125,-56) ;
 ext8 = ext8.rotatedBy(-m_angle) ;
 fourthCheck.PlaceAt(m_position-ext7, m_position+ext8) ;

 if (other.GetType() == ALIENBULLET)
 { // Deals with enemy bullets hiting the player ship
   m_health->TakeDamage(HEALTHCOST) ; // Take damage
   Damage *pDamage = new Damage() ; // Create a new damage notifier
   pDamage->Initialise(m_position, Vector2D(0,0), 15.0f, 1.0f) ;
   Game::instance.m_objects.AddItem(pDamage, false) ; 
 }
 
 if (other.GetType() == ALIEN)
 { // Deals with an alien ship hitting into the player ship
		m_soundFX->StopThrust() ;	// Stop the thrust sound
  m_soundFX->PlayExplosion() ; // Play the explosion sound
  Explosion *pExplosion = new Explosion() ; // Create new explosion
  pExplosion->Initialise(m_position, Vector2D(0,0), 4.0f, 1.5f) ;
  Game::instance.m_objects.AddItem(pExplosion, false) ;
  m_active = false ; // Remove the ship.
 }

 if (other.GetType() == BUILDING)
 { // Deals with collisions with a building
  Building *pOtherBuilding = dynamic_cast<Building*> (&other) ;
  Rectangle2D r = pOtherBuilding->GetRectangle() ;
  // MyDrawEngine::GetInstance()->FillRect(r, _XRGB(123, 119, 94)) ;

  if (m_velocity.magnitude() <= 300.0f && r.Intersects(landingCheck) && other.RefuelCheck() == 1)
  { // If the ship lands on a refuel building, allow the ship to refuel.
   m_landedOnRefuel = true ;
  } 
  else if (m_velocity.magnitude() <= 300.0f && (r.Intersects(landingCheck)))
  { // Otherwise, just land the ship on a regular building top.
   m_landedOnBuilding = true ;
  }
  else if (m_velocity.magnitude() >= 600.0f && r.Intersects(landingCheck))
  { // If the ship is flying too quickly, ensure the ship is immediately destroyed
		 m_soundFX->StopThrust() ;	// Stop the thrust sound
   m_soundFX->PlayExplosion() ; // Play the explosion sound
   m_health->TakeDamage(1000) ; // blown up from the impact.
 	 Damage *pDamage = new Damage() ;
   pDamage->Initialise(m_position, Vector2D(0,0), 15.0f, 1.0f) ;
   Game::instance.m_objects.AddItem(pDamage, false) ;
  }
  else if ((m_velocity.magnitude() > 300.0f && m_velocity.magnitude() < 600) && r.Intersects(landingCheck))
  { // Any other interaction with a building will damage the ship slightly.
		 m_soundFX->StopThrust() ;	// Stop the thrust sound
   m_soundFX->PlayExplosion() ; // Play the explosion sound
   m_health->TakeDamage(HEALTHCOST) ;
   Damage *pDamage = new Damage() ;
   pDamage->Initialise(m_position, Vector2D(0,0), 15.0f, 1.0f) ;
   Game::instance.m_objects.AddItem(pDamage, false) ;
   m_velocity = -m_velocity ;
   m_rotate = true ;
  }
 }


 if (other.GetType() == GROUND)
 { // Deals with collisions with the ground
  Ground *pOtherGround = dynamic_cast<Ground*> (&other) ;
  Rectangle2D r = pOtherGround->GetRectangle() ;
  MyDrawEngine::GetInstance()->FillRect(r, _XRGB(123, 119, 94)) ;

  if (m_velocity.magnitude() <= 300.0f && r.Intersects(landingCheck))
  { // Land on the ground.
   m_landedOnBuilding = true ;
  }
  else if (m_velocity.magnitude() >= 600.0f && r.Intersects(landingCheck))
  { // If the ship is flying too quickly, ensure the ship is immediately
		 m_soundFX->StopThrust() ;	// Stop the thrust sound
   m_soundFX->PlayExplosion() ; // Play the explosion sound
   m_health->TakeDamage(1000) ; // blown up from the impact.
 	 Damage *pDamage = new Damage() ;
   pDamage->Initialise(m_position, Vector2D(0,0), 15.0f, 1.0f) ;
   Game::instance.m_objects.AddItem(pDamage, false) ;
  }
  else if ((m_velocity.magnitude() > 300.0f && m_velocity.magnitude() < 600) && r.Intersects(landingCheck))
  { // Any other interaction with the ground will damage the ship slightly.
		 m_soundFX->StopThrust() ;	// Stop the thrust sound
   m_soundFX->PlayExplosion() ;
   m_health->TakeDamage(HEALTHCOST) ;
   Damage *pDamage = new Damage() ;
   pDamage->Initialise(m_position, Vector2D(0,0), 15.0f, 1.0f) ;
   Game::instance.m_objects.AddItem(pDamage, false) ;
   m_velocity = -m_velocity ;
  }
 }

 if (m_health->GetHealth() <= 15.0f || m_fuel->GetFuel() <= 15.0f)
 { // If the ship has less than 15.0f health or fuel, blow it up.
		m_soundFX->StopThrust() ;	// Stop the thrust sound
  m_soundFX->PlayExplosion() ; // Play the explosion sound
  Explosion *pExplosion = new Explosion() ; // Create new explosion
  pExplosion->Initialise(m_position, Vector2D(0,0), 4.0f, 1.5f) ;
  Game::instance.m_objects.AddItem(pExplosion, false) ;
  m_active = false ; // Remove the ship.
 }
}


void Ship::Update(float frametime)
{
 // Sample the keyboard
	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();

 // Places the camera on the player ship
	MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D(m_position.XValue+1250, -m_position.YValue));

	if ((pInputs->KeyPressed(DIK_LEFT) || pInputs->KeyPressed(DIK_A)) && (!m_landedOnBuilding && !m_landedOnRefuel))
	{ // Used to rotate left
		m_angle -= TURNSPEED * frametime ;
	}

	if ((pInputs->KeyPressed(DIK_RIGHT) || pInputs->KeyPressed(DIK_D)) && (!m_landedOnBuilding && !m_landedOnRefuel))
	{ // Used to rotate right
		m_angle += TURNSPEED * frametime ;
	}

	if ((pInputs->KeyPressed(DIK_UP) || pInputs->KeyPressed(DIK_W)) && m_fuel->GetFuel() > 11.0f && m_position.YValue < 600.0f) // Thrusting
	{
  // If thrusting, the ship cannot be landed
  m_landedOnBuilding = false ;
  m_landedOnRefuel = false ;
  m_thrusting = true ;

		if (m_thrusting == true)	
		{ // If the player is thrusting, turn up the volume
   m_shootingVolume += frametime * 3000 ; // Increase volume
			m_soundFX->StartThrust(m_shootingVolume) ; // Play thrusting sound
		}

  // Reduce the amount of fuel
  m_fuel->Use(FUELCOST) ;
  
		Vector2D acceleration;
		acceleration.setBearing(m_angle, ACCELERATION) ;
		m_velocity = m_velocity + acceleration * frametime ;
 
  // Create flame object below the ship
		Flame *pFlame = new Flame ;
		Vector2D flameDirection ;
		flameDirection.setBearing(m_angle + 3.141f, 600) ;
		pFlame->Initialise(m_position, flameDirection, 68.0f, 1.0f) ;
		Game::instance.m_objects.AddItem(pFlame, false) ;
	}
 else // Not thrusting
 {
 	if (m_thrusting)		// If  thrusting last frame
		{
			m_soundFX->StopThrust() ;	// Stop the thrust sound
   m_shootingVolume = -3000 ;
		}
		m_thrusting = false ;			// Remember we are thrusting
 }

	if ((pInputs->KeyPressed(DIK_DOWN) || pInputs->KeyPressed(DIK_S)) && m_position.YValue < 600.0f)
	{
		Vector2D acceleration;
		acceleration.setBearing(m_angle, -ACCELERATION);
		m_velocity = m_velocity + acceleration * frametime;
	}

 if (pInputs->KeyPressed(DIK_LSHIFT) && m_ammoAmount->GetMissle() > 0 && m_shootingDelay < 0)
 { // Used for firing the guided missles
  m_shootingDelay = DELAY * 6 ;

  Vector2D position ;
		position.setBearing(m_angle, 1) ;
		position = position + m_position ;

		Vector2D velocity ;
		velocity.setBearing(m_angle + 1.65f, BULLETSPEED) ;
		velocity = velocity + m_velocity ;

  float angle ;
  angle = m_angle ;

		Missle* pMissle = new Missle;
		pMissle->Initialise(position, velocity, m_soundFX, m_pManager) ;
		Game::instance.m_objects.AddItem(pMissle, true) ;

			m_soundFX->PlayRocketLaunch() ;	// Play the shoot sound
   m_ammoAmount->SpendMissle() ; // Reduce the missle count
 }

	if (pInputs->KeyPressed(DIK_SPACE) && m_shootingDelay < 0 && m_ammoAmount->GetAmmo()> 11.0f)
	{ // Used to shoot regular bullets
  m_shootingDelay = DELAY ;
  m_ammoAmount->Use(AMMOCOST) ;

		Vector2D position ;
		position.setBearing(m_angle, 1) ;
		position = position + m_position ;

		Vector2D velocity ;
		velocity.setBearing(m_angle + 1.65f, BULLETSPEED) ;
		velocity = velocity + m_velocity ;

  float angle ;
  angle = m_angle ;

		Bullet* pBullet = new Bullet;
		pBullet->Initialise(position, velocity, angle, m_soundFX) ;
		Game::instance.m_objects.AddItem(pBullet, true) ;

			m_soundFX->PlayShoot() ;	// Play the shoot sound
	}

 // Reduce shooting delay
 m_shootingDelay -= frametime ;

 // Update the ships velocity
	m_velocity = m_velocity - FRICTION * frametime * m_velocity - GRAVITY * frametime ;


 if (m_rotate == true)
 { // Rotate the ship for a second or so upon collision.
  m_timer += 1.0f * frametime ;
  m_angle += 3 * frametime ;

  if (m_timer >= 1.0f)
  {
   m_rotate = false ;
   m_timer = 0 ;
  }
 }

 if (m_landedOnRefuel == true)
 { // If the player has landed on a Refuel building type, then
   // refill the players fuel bar as long as they remain landed.
  float amount = 70 * frametime ;
  m_fuel->Refuel(amount) ;
  m_ammoAmount->Resupply(amount) ;
  m_soundFX->PlayRefuel() ;
 }
 else
 {
  m_soundFX->StopRefuel() ;
 }

 if (m_landedOnBuilding || m_landedOnRefuel)
 {
   // If landed, set the velocity to zero.
   m_velocity.set(0,0) ; 

  if (m_angle != 0)
  {
   if (m_angle > 0)
   { // Angle higher than 0 will reduce the angle.
    m_angle -= 3 * frametime ;
   }
   if (m_angle < 0)
   { // Angle lower than 0 will increase the angle.
    m_angle += 3 * frametime ;
   }
  }
 }

 // Update the ships position
	m_position = m_position + m_velocity * frametime ;
}

IShape2D& Ship::GetCollisionShape()
{ // Determines the shape of the ship. Currently set to
  // a circle with a radius of 10. Problem is, the ship is
  // a rectangle. Oops. Seems to work OK though.
  collisionShape.PlaceAt(m_position, 110) ;
  MyDrawEngine::GetInstance()->FillCircle(m_position, 110, MyDrawEngine::WHITE) ;
	 return collisionShape ;
}

void Ship::HandleEvent(Event evt)
{ // Empty for the time being.  
}

float Ship::GetCurrentXPosition() const
{
 return m_position.XValue ;
}

float Ship::GetCurrentYPosition() const
{
 return m_position.YValue ;
}

bool Ship::GetState() const
{
 return m_active ;
}

void Ship::LoadMissle()
{
 m_ammoAmount->LoadMissle() ;
}











Aliens::Aliens() : GameObject(ALIEN)
{
 // No-op
}

void Aliens::Initialise(Vector2D startPos, SoundFX* pSound, Ship* pShip)
{
	LoadImage(L"alien.bmp") ;
	m_angle = 0.0f ;
 m_position = startPos ;
 m_drawDepth = 5 ;
 m_isDead = false ;
	m_velocity.set(0, 0) ;
 m_soundFX = pSound ;
 m_pShip = pShip ;
 m_healthAmount = 3 ;
}

void Aliens::ProcessCollision(GameObject& other)
{
 if (other.GetType() == BULLET)
 { // If the alien collides with the player's bullets
  m_healthAmount -= 1 ;

  if (m_healthAmount <= 0)
  {
   m_isDead = true ;
 	 Damage *pDamage = new Damage() ;
   pDamage->Initialise(m_position, Vector2D(0,0), 15.0f, 1.0f) ;
   Game::instance.m_objects.AddItem(pDamage, false) ;
		 // Send message that the alien has died
		 Event evt ;
		 evt.position = m_position ;
		 evt.pSource = this ;
		 evt.type = EVENT_OBJECTDESTROYED ;
		 Game::instance.NotifyEvent(evt) ;
   m_soundFX->PlayExplosion() ; // Play the explosion sound

   int chance = rand() % 10 + 1 ;

   if (chance > 5)
   {
    // Spawn an item drop
    MissleDrop* pMissleDrop = new MissleDrop ;
    pMissleDrop->Initialise(m_position) ;
    Game::instance.m_objects.AddItem(pMissleDrop, true) ;
   }
  }
 }

 if (other.GetType() == MISSLE)
 { // If the alien collides with the player's bullets
   m_isDead = true ;
 	 Damage *pDamage = new Damage() ;
   pDamage->Initialise(m_position, Vector2D(0,0), 15.0f, 1.0f) ;
   Game::instance.m_objects.AddItem(pDamage, false) ;
		 // Send message that the alien has died
		 Event evt ;
		 evt.position = m_position ;
		 evt.pSource = this ;
		 evt.type = EVENT_OBJECTDESTROYED ;
		 Game::instance.NotifyEvent(evt) ;
   m_soundFX->PlayExplosion() ; // Play the explosion sound

   int chance = rand() % 10 + 1 ;

   if (chance > 5)
   {
    // Spawn an item drop
    MissleDrop* pMissleDrop = new MissleDrop ;
    pMissleDrop->Initialise(m_position) ;
    Game::instance.m_objects.AddItem(pMissleDrop, true) ;
   }
 }

 if (other.GetType() == BUILDING)
 { // If the alien collides with a building
   m_isDead = true ;
 	 Damage *pDamage = new Damage() ;
   pDamage->Initialise(m_position, Vector2D(0,0), 15.0f, 1.0f) ;
   Game::instance.m_objects.AddItem(pDamage, false) ;
		 // Send message that the alien has died
		 Event evt ;
		 evt.position = m_position ;
		 evt.pSource = this ;
		 evt.type = EVENT_OBJECTDESTROYED ;
		 Game::instance.NotifyEvent(evt) ;
   m_soundFX->PlayExplosion() ; // Play the explosion sound
 }
}

void Aliens::Update(float frametime)
{
 // Allows the alien to focus their attention on the player's ship
 m_angle = ((m_position - m_pShip->GetPosition()).angle()) - 1.6f ;

 MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance() ;

 // The alien ship will only act if the alien is on screen at the time
 // It will then move toward the player in an attempt to collide with them
 if (pDrawEngine->IsOnCamera(collisionShape))
 {
  if (m_position.YValue < m_pShip->GetCurrentYPosition())
  {
  	m_position.YValue = m_position.YValue + 400.0f * frametime ;
  }

  if (m_position.YValue > m_pShip->GetCurrentYPosition())
  {
  	m_position.YValue = m_position.YValue - 400.0f * frametime ;
  }

  if (m_position.XValue < m_pShip->GetCurrentXPosition())
  {
  	m_position.XValue = m_position.XValue + 400.0f * frametime ;
  }

  if (m_position.XValue > m_pShip->GetCurrentXPosition())
  {
  	m_position.XValue = m_position.XValue - 400.0f * frametime ;
  }
 }
}

IShape2D& Aliens::GetCollisionShape()
{
  collisionShape.PlaceAt(m_position, 110) ;
	 return collisionShape ;
}

void Aliens::HandleEvent(Event evt)
{
 // No-op
}

bool Aliens::IsDead() const
{
 return m_isDead ; // Return whether it is dead or not
}

float Aliens::GetXPosition() const
{
 return m_position.XValue ; // Return X position of the alien
}

float Aliens::GetYPosition() const
{
 return m_position.YValue ; // Return Y position of the alien
}









AlienShooter::AlienShooter()
{
 // No-op
}

void AlienShooter::Initialise(Vector2D startPos, SoundFX* pSound, Ship* pShip)
{
	LoadImage(L"alien2.bmp") ;
	m_angle = 0.0f ;
 m_position = startPos ;
 m_drawDepth = 5 ;
 m_isDead = false ;
	m_velocity.set(0, 0) ;
 m_soundFX = pSound ;
 m_pShip = pShip ;
 m_healthAmount = 2 ;
}

void AlienShooter::Update(float frametime)
{
 // Used to allow the alien to focus its attention on the player
 m_angle = ((m_position - m_pShip->GetPosition()).angle()) - 1.6f ;

  MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance() ;

 if (m_shootingDelay < 0 && pDrawEngine->IsOnCamera(collisionShape))
 { // If the alien is on screen, and able to shoot
  m_shootingDelay = DELAY * 3 ;

		Vector2D position ;
		position.setBearing(m_angle, 1) ;
		position = position + m_position+Vector2D(0,0) ;

		Vector2D velocity ;
		velocity.setBearing(m_angle, BULLETSPEED) ;
		velocity = velocity + m_velocity ;

  float angle ;
  angle = m_angle+3.1f ;

  // Fires a bullet toward the player
		AlienBullet* pBullet = new AlienBullet;
		pBullet->Initialise(position, velocity, angle, m_soundFX) ;
		Game::instance.m_objects.AddItem(pBullet, true) ;

  m_soundFX->PlayShoot() ;	// Play the shoot sound
 }

 m_shootingDelay -= frametime ; // Cool's down the aliens weapon
}









AlienShooterRare::AlienShooterRare()
{
 
}

void AlienShooterRare::Initialise(Vector2D startPos, SoundFX* pSound,
                                  Ship* pShip)
{
 LoadImage(L"alien3.bmp") ;
 m_angle = 0.0f ;
 m_position = startPos ;
 m_drawDepth = 5 ;
 m_isDead = false ;
 m_velocity.set(0, 0) ;
 m_soundFX = pSound ;
 m_pShip = pShip ;
 m_healthAmount = 4 ;
}

void AlienShooterRare::Update(float frametime)
{
 // Used to allow the alien to focus its attention on the player
 m_angle = ((m_position - m_pShip->GetPosition()).angle()) - 1.6f ;

 MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance() ;

 if (m_shootingDelay < 0 && pDrawEngine->IsOnCamera(collisionShape))
 { // If the alien is on screen, and able to shoot
  m_shootingDelay = DELAY * 2 ;

  Vector2D position ;
  position.setBearing(m_angle, 1) ;
  position = position + m_position - Vector2D(0, 100);

  Vector2D velocity ;
  velocity.setBearing(m_angle, BULLETSPEED) ;
  velocity = velocity + m_velocity ;

  Vector2D position2 ;
  position2.setBearing(m_angle, 1) ;
  position2 = position2 + m_position + Vector2D(0, 100) ;

  Vector2D velocity2 ;
  velocity2.setBearing(m_angle, BULLETSPEED) ;
  velocity2 = velocity2 + m_velocity;

  float angle ;
  angle = m_angle+3.1f ;

  AlienBullet* pBullet = new AlienBullet ;
  pBullet->Initialise(position, velocity, angle, m_soundFX) ;
  Game::instance.m_objects.AddItem(pBullet, true) ;

  AlienBullet* pBullet2 = new AlienBullet ;
  pBullet2->Initialise(position2, velocity2, angle, m_soundFX) ;
  Game::instance.m_objects.AddItem(pBullet2, true) ;

  m_soundFX->PlayShoot() ;	// Play the shoot sound
 }

 m_shootingDelay -= frametime ;
}







MissleDrop::MissleDrop() : GameObject(ITEM)
{
 // No-op
}

void MissleDrop::Initialise(Vector2D startPos)
{
	m_position = startPos ;
 m_animationSpeed = 3.0f ;
 m_currentAnimation = 0.0f ;
 m_drawDepth = 10 ;
 LoadImage(L"missledrop.bmp") ;
 LoadImage(L"missledrop2.bmp") ;
 LoadImage(L"missledrop3.bmp") ;
 LoadImage(L"missledrop2.bmp") ;
 LoadImage(L"missledrop.bmp") ;
}

void MissleDrop::ProcessCollision(GameObject& other)
{
 if (other.GetType() == SHIP)
 { // Send an event that the player has picked up the missle
  Deactivate() ;
  Event evt ;
  evt.type = EVENT_ITEMPICKUP ;
  evt.position = m_position ;
  evt.pSource = this ;
  Game::instance.NotifyEvent(evt) ;
 }
}

void MissleDrop::Update(float frametime)
{
  // Animates the missle icon on screen, to make it more visible to the player
  // that it can be picked up
  m_currentAnimation += m_animationSpeed * frametime ;

  if (m_currentAnimation >= 5.0f)
  {
   m_currentAnimation = 0 ;
  }

  m_imageNumber = int(m_currentAnimation) ;
}

IShape2D& MissleDrop::GetCollisionShape()
{
 collisionShape.PlaceAt(m_position, 10) ;
 MyDrawEngine::GetInstance()->FillCircle(m_position, 10, MyDrawEngine::WHITE) ;
	return collisionShape ;
}

void MissleDrop::HandleEvent(Event evt)
{
 // No-op
}








GameManager::GameManager() : GameObject(GAMEMANAGER)
{ // Set all of our pointers to null pointers.
 for (int i = 0; i < MAXASSETS; i++)
 {
  m_pBackground[i] = nullptr ;
  m_pBuilding[i] = nullptr ;
  m_pGround[i] = nullptr ;
  m_pFloraFauna[i] = nullptr ;
  m_pAliens[i] = nullptr ;
 }
}


void GameManager::Initialise(Ship* pShip, SoundFX* pSound)
{
 m_drawDepth = 50 ; // Depth is to ensure gameover screen is on top
 m_pShip = pShip ; // Grab our player's ship so we can check where it is
 m_pSound = pSound ; // Grab the sound object so we can control it
 m_pSound->LoadSounds() ; // Load the sounds for the game
 m_notOver = false ; // The game is not over 
 m_handleEvents = true;		// This object will receive events
}

void GameManager::Draw()
{
 if (m_notOver != true)
 {
  MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance() ;
  pDrawEngine->DrawAt(Vector2D(m_position.XValue+485, m_position.YValue-105), pDrawEngine->LoadPicture(L"scorebackdrop.bmp"), 1.0f, 0.0f, 0.0f);
  pDrawEngine->WriteInt(Vector2D(m_position.XValue+333, m_position.YValue-125), m_score, _XRGB(181, 183, 136), 0) ;
 }
}

void GameManager::Update(float frametime)
{
 if (m_score < 7500)
 {  // Used to determine the amount of aliens on screen depending on the score
  MAXALIENS = 1 ;
 }
 else if (m_score > 7500 && m_score < 15000)
 {
  MAXALIENS = 2 ;
 }
 else if (m_score > 15000)
 {
  MAXALIENS = 3 ;
 }

 if (m_pShip->GetState() != true)
 { // If the game ends, run the GameOver function
  m_notOver = true ;
  GameOver() ;  
 }

 // Draws the score in the appropriate location
 m_position = MyDrawEngine::GetInstance()->theCamera.ReverseTransform(Vector2D(1535, -33)) ;

 // Run our functions for handling the objects in-game
 CreateBackground() ;
 CreateFloraFauna() ;
 CreateBuilding() ;
 CreateGround() ;
 CreateAlien() ;
}

IShape2D& GameManager::GetCollisionShape()
{
	return collisionShape ;
}

void GameManager::ProcessCollision(GameObject& other)
{
 // No collisions.
}

void GameManager::HandleEvent(Event evt)
{
	if (evt.type == EVENT_OBJECTDESTROYED)
	{
  if (evt.pSource->GetType() == ALIEN)
		{ // If an alien ship has died, award the player
    // with 1250 points.
    m_score = m_score + 1250 ;
  }
 }

	if (evt.type == EVENT_ITEMPICKUP)
	{ // If the player picks up the potion, heal the ship.
  m_pSound->PlayItemPickUp() ;	// Play item pickup noise
  m_pShip->LoadMissle() ; // Load the missle into the UI
 }
}

int GameManager::GetScore() const
{
 return m_score ;
}

Ground* GameManager::CreateGround()
{
 for (int i = 0; i < MAXASSETS; i++)
 {
  if (m_pGround[i] == nullptr)
  {
   m_pGround[i] = new Ground() ; 
   m_pGround[i]->Initialise(Vector2D(m_gap[0]+-500, -960)) ;
   Game::instance.m_objects.AddItem(m_pGround[i], true) ;
   m_gap[0] = m_gap[0] + 1800.0f ;
   return m_pGround[i] ;
  }
  if (m_pShip->GetCurrentXPosition() > (m_pGround[i]->GetCurrentPosition()+3000))
  { // Check whether we should remove the asset before creating any new ones
   RemoveGround(m_pGround[i]) ;
  }
 }
 return 0 ;
}

void GameManager::RemoveGround(Ground* pGround)
{ // Removes ground from the game and sets it back to null pointer
 for (int i = 0; i < MAXASSETS; i++)
 {
  if (m_pGround[i] == pGround)
  {
   m_pGround[i]->Deactivate() ;
   m_pGround[i] = nullptr ;
  }
 }
}

Building* GameManager::CreateBuilding()
{
 for (int i = 0; i < MAXASSETS; i++)
 {
  if (m_pBuilding[i] == nullptr)
  {
   float height = (float)rand()/(float)(RAND_MAX/400.0f);
   float random = (float)rand()/(float)(RAND_MAX/10.0f)+1.0f;
   float randomNumber2 = (float)rand()/(float)(RAND_MAX/200.0f)+650.0f;
   int refuelSpawn = rand() % 10 + 1 ;
  
   if (refuelSpawn <= 2)
   { // Create a 1/10 chance of a refuel building spawning
    m_pBuilding[i] = new RefuelBuilding() ;
    m_pBuilding[i]->Initialise(Vector2D(m_gap[1]+650.0f, -500.0f-height)) ;
    Game::instance.m_objects.AddItem(m_pBuilding[i], true) ;
   }
   else
   { // Otherwise create a normal building
    m_pBuilding[i] = new Building() ;
    m_pBuilding[i]->Initialise(Vector2D(m_gap[1]+650.0f, -500.0f-height)) ;
    Game::instance.m_objects.AddItem(m_pBuilding[i], true) ;
   }

   m_gap[1] += (float)rand()/(float)(RAND_MAX/1.0f) + randomNumber2 ;
   return m_pBuilding[i] ;
  }
  if (m_pShip->GetCurrentXPosition() > (m_pBuilding[i]->GetCurrentPosition()+3000))
  { // Check whether we should remove the asset before creating any new ones
   RemoveBuilding(m_pBuilding[i]) ;
  }
 }
 return 0 ;
}

void GameManager::RemoveBuilding(Building* pBuilding)
{ // Removes buildings from the game and sets it back to null pointer
 for (int i = 0; i < MAXASSETS; i++)
 {
  if (m_pBuilding[i] == pBuilding)
  {
   m_pBuilding[i]->Deactivate() ;
   m_pBuilding[i] = nullptr ; 
  }
 }
}

FloraFauna* GameManager::CreateFloraFauna()
{
 for (int i = 0; i < MAXASSETS; i++)
 {
  if (m_pFloraFauna[i] == nullptr)
  {
   int randomNumber = rand() % 10 + 1 ;
   float randomNumber2 = (float)rand()/(float)(RAND_MAX/500.0f)+200.0f;
   m_pFloraFauna[i] = new FloraFauna() ;
   m_pFloraFauna[i]->Initialise(m_gap[2], randomNumber) ;
   Game::instance.m_objects.AddItem(m_pFloraFauna[i], true) ;
   m_gap[2] += (float)rand()/(float)(RAND_MAX/1.0f) + randomNumber2 ;
   return m_pFloraFauna[i] ;
  }
  if (m_pShip->GetCurrentXPosition() > (m_pFloraFauna[i]->GetCurrentPosition()+1500))
  { // Check whether we should remove the asset before creating any new ones
   RemoveFloraFauna(m_pFloraFauna[i]) ;
  }
 }
 return 0 ;
}

void GameManager::RemoveFloraFauna(FloraFauna* pFloraFauna)
{ // Removes flora/fauna from the game and sets it back to null pointer
 for (int i = 0; i < MAXASSETS; i++)
 {
  if (m_pFloraFauna[i] == pFloraFauna)
  {
   m_pFloraFauna[i]->Deactivate() ;
   m_pFloraFauna[i] = nullptr ;
  }
 }
}

Background* GameManager::CreateBackground()
{
 for (int i = 0; i < MAXASSETS; i++)
 {
  if (m_pBackground[i] == nullptr)
  {
   m_pBackground[i] = new Background() ; 
   m_pBackground[i]->Initialise(Vector2D(m_gap[3]+-500, 1100), 0.0f) ;
   Game::instance.m_objects.AddItem(m_pBackground[i], true) ;
   m_gap[3] = m_gap[3] + 2650.0f ;
   return m_pBackground[i] ;
  }
  if (m_pShip->GetCurrentXPosition() > (m_pBackground[i]->GetCurrentPosition()+3000))
  { // Check whether we should remove the asset before creating any new ones.
   RemoveBackground(m_pBackground[i]) ;
  }
 }
 return 0 ;
}

void GameManager::RemoveBackground(Background* pBackground)
{ // Removes background from the game and sets it back to null pointer
 for (int i = 0; i < MAXASSETS; i++)
 {
  if (m_pBackground[i] == pBackground)
  {
   m_pBackground[i]->Deactivate() ;
   m_pBackground[i] = nullptr ;
  }
 }
}

void GameManager::GameOver()
{ // Creates the scoreboard overlay when the game has reached a conclusion
 ScoreBoard* pScoreBoard = new ScoreBoard ;
 pScoreBoard->Initialise() ;
 Game::instance.m_objects.AddItem(pScoreBoard, false) ;
 Game::instance.SetLatestScore(m_score) ;
}

Aliens* GameManager::CreateAlien()   
{
 for (int i = 0; i < MAXALIENS; i++)
 {
  if (m_pAliens[i] == nullptr)
  {
   float randomWidth = (float)rand()/(float)(RAND_MAX/500.0f)+200.0f;
   float randomHeight = (float)rand()/(float)(RAND_MAX/500.0f)+200.0f;
   int alienSpawn = rand() % 10 + 1 ;

   if (alienSpawn > 0 && alienSpawn <= 2)
   {
    m_pAliens[i] = new AlienShooterRare() ; 
    m_pAliens[i]->Initialise(Vector2D(m_pShip->GetCurrentXPosition()+5000+randomWidth, randomHeight), m_pSound, m_pShip) ;
    Game::instance.m_objects.AddItem(m_pAliens[i], true) ;
   }
   else if (alienSpawn > 2 && alienSpawn <= 6)
   {
    m_pAliens[i] = new AlienShooter() ; 
    m_pAliens[i]->Initialise(Vector2D(m_pShip->GetCurrentXPosition()+5000+randomWidth, randomHeight), m_pSound, m_pShip) ;
    Game::instance.m_objects.AddItem(m_pAliens[i], true) ;
   }
   else
   {
    m_pAliens[i] = new Aliens() ; 
    m_pAliens[i]->Initialise(Vector2D(m_pShip->GetCurrentXPosition()+5000+randomWidth, randomHeight), m_pSound, m_pShip) ;
    Game::instance.m_objects.AddItem(m_pAliens[i], true) ;
   }

   return m_pAliens[i] ;
  }

  if (m_pAliens[i]->IsDead())
  { // Check whether we should remove the asset before creating any new ones
   RemoveAlien(m_pAliens[i]) ;
  }

 }
 return 0 ;
}

void GameManager::RemoveAlien(Aliens* pAlien)
{ // Removes aliens from the game and sets it back to null pointer
 for (int i = 0; i < MAXASSETS; i++)
 {
  if (m_pAliens[i] == pAlien)
  {
   m_pAliens[i]->Deactivate() ;
   m_pAliens[i] = nullptr ;
  }
 }
}

float GameManager::AlienXPosition()
{ // Returns the X position of the created alien
 for (int i = 0; i < MAXASSETS; i++)
 {
  if (m_pAliens[i])
  {
   return m_pAliens[i]->GetXPosition() ;
  }
 }
 return 0 ;
}

float GameManager::AlienYPosition()
{ // Returns the Y position of the created alien
 for (int i = 0; i < MAXASSETS; i++)
 {
  if (m_pAliens[i])
  {
   return m_pAliens[i]->GetYPosition() ;
  }
 }
 return 0 ;
}






ScoreBoard::ScoreBoard() : GameObject(GROUND)
{
 m_scoreboardTimer = 10.0f ; // Timer until game returns to the main menu
}

void ScoreBoard::Initialise()
{
 Game::instance.m_objects.DeactivateAll();
}

void ScoreBoard::Draw()
{
 // No-op
}

void ScoreBoard::ProcessCollision(GameObject& other)
{
 // No-op
}

void ScoreBoard::Update(float frametime)
{
 // Sample the keyboard
	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();

 // Draw at the appropriate location
 MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance() ;
 pDrawEngine->theCamera.PlaceAt(Vector2D(0,0)) ;
 pDrawEngine->DrawAt(Vector2D(0,0), 2, 1.0f, 0.0f, 0.0f) ;
 pDrawEngine->WriteInt(Vector2D(-180,-36), Game::instance.GetLatestScore(), _XRGB(150, 167, 167), 2) ;

 // Probably a bit hacky at the minute. If the size of the linked list is less than
 // 5, just print out the exact list. Otherwise, print out 5 results.
 int maxsize = 0 ;
 if (Game::instance.GetSize() <= 5)
 {
  maxsize = Game::instance.GetSize() ;
 }
 else
 { 
  maxsize = 5 ;
 }

 // List the scores
 Game::instance.ListBeginning() ;

 m_scoreboardTimer -= frametime ;
 if(pInputs->NewKeyPressed(DIK_RETURN) || m_scoreboardTimer <= 0)
 { // Return to the main menu if the player hits enter or the timer runs out
  NewGame() ;
 }
}

IShape2D& ScoreBoard::GetCollisionShape()
{
	return collisionShape ;
}

void ScoreBoard::HandleEvent(Event evt)
{
 // No-op
}

void ScoreBoard::NewGame()
{ // Create a new game environment
 m_active = false ;
 Game::instance.ScoreEnd(true) ;
}

















