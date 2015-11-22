#ifndef STATECONSTELLATION_H
#define STATECONSTELLATION_H

#include "GameState.h"
#include "Character.h"
#include "Planet.h"
#include "Controller.h"
#include "Arrow.h"
#include "StaticParticles.h"
#include "DynamicParticles.h"
#include <list>
#include <vector>

class StateConstellation;
typedef std::shared_ptr<StateConstellation> SharedStateConstellation;
typedef void (StateConstellation::*UpdateFunc)(float); //Ptr on method update, conform to all method with same signature
typedef void (StateConstellation::*EventFunc)(const sf::Event& e); //Ptr on event handler method
/**
 * @brief The main state of the game where the gameplay happends
 */
class StateConstellation : public GameState
{
public:
    StateConstellation();

    /**
     * @brief //Struct representing internal state. One update method and one event method
     *
     * Used to make a tiny-statemachine inside the ConstellationState
     */
    struct InternalState
    {
        UpdateFunc uf;
        EventFunc ef;
    };

    /**
     * @brief Setups the scene and add game actors (planets and characters)..
     */
    void onBegin();
    void onEnd();
    void onResume();
    void onPause();
    void draw(sf::RenderTarget& target);
    void update(float delta_s);
    void pushEvent(const sf::Event& e);

    //Updates methods
    void rotUpdate(float delta_s);
    void defaultUpdate(float delta_s);

    //Events methods
    void rotEvent(const sf::Event& e);
    void waitingEvent(const sf::Event &e);
    void defaultEvent(const sf::Event& e);

    /**
     * @brief get vectorial gravitational field at given point p
     * @param p point to sample grav field
     * @return grav field
     */
    sf::Vector2f getGravFieldAt(const sf::Vector2f &p) const;

    /**
     * @brief check wether a given point is in a planet
     * @param p point
     * @return nullptr or the first planet colliding with point
     */
    SharedPlanet collideWithPlanet(const sf::Vector2f &p) const;

    /**
     * @brief check wether a given point is in a character
     * @param p point
     * @return nullptr or the first intersected character
     */
    SharedCharacter collideWithCharacter(const sf::Vector2f &p) const;

    void pushArrow(SharedArrow a);

    void onNewRound();

    void onWin();

    //Seems very improbable to be called
    void onEquality();

    void nextPlayer();

    bool isCurrentPlayer(const PlayerID& id)  const;

    void onArrowDecayed();

    std::vector<sf::Vector2f> pathForInitials(sf::Vector2f pos, sf::Vector2f speed, int precision) const;

    sf::FloatRect getBounds(float margin = 0) const;

    float zoomFactor() const;

    sf::Vector2f clampRect(const sf::FloatRect& rect, float margin = 0) const;
private:
    void correctViews(float vx, float vy);
    typedef std::list<SharedController> Players;
    typedef std::list<SharedArrow> Arrows;

    InternalState mIState;
    sf::Vector2i mOldMousePos;
    sf::Vector2i mMousePos;
    float mYaw;
    float mPitch;

    std::list<SharedPlanet> mPlanets;
    Players mPlayers;
    Players::iterator mCurrentPlayer;
    Arrows mArrows;
    StaticParticles mBackground;
    DynamicParticles mExpl;
    sf::View mView;
    sf::View mBackView;
};

#endif // STATECONSTELLATION_H
