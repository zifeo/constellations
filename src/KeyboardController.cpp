#include "KeyboardController.h"
#include <iostream>
using namespace std;


KeyboardController::KeyboardController(SharedCharacter c) : Controller(c)
{
    KeyboardController::mState = MOVE;
}

bool KeyboardController::onEvent(const sf::Event& e)
{
    Action a;
    a.type = Action::NONE;

    //Suicide shortcut for tests :
    if(e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::S)
        character()->hit(999);

    switch(mState)
    {
        case STATE::MOVE:
        {
            if(e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left)
            {
                mOldMousePos = {e.mouseButton.x,e.mouseButton.y};
                releaseKey(sf::Keyboard::Left);
                releaseKey(sf::Keyboard::Right);
                mState = AIM;
                break;
            }
            constexpr float vr = 4;
            if (e.type == sf::Event::KeyPressed)
            {
                if (e.key.code == sf::Keyboard::Left && pressKey(e.key.code))
                {
                    a.move.distance = -vr;
                    a.type = Action::MOVE_X;
                }
                if (e.key.code == sf::Keyboard::Right && pressKey(e.key.code))
                {
                    a.move.distance = vr;
                    a.type = Action::MOVE_X;
                }
            }
            if (e.type == sf::Event::KeyReleased)
            {
                if (e.key.code == sf::Keyboard::Left && releaseKey(e.key.code))
                {
                    a.move.distance = +vr;
                    a.type = Action::MOVE_X;
                }
                if (e.key.code == sf::Keyboard::Right && releaseKey(e.key.code))
                {
                    a.move.distance = -vr;
                    a.type = Action::MOVE_X;
                }
            }
            break;
        }
        case STATE::AIM:
        {
            if (e.type == sf::Event::KeyPressed && (e.key.code == sf::Keyboard::Left || e.key.code == sf::Keyboard::Right))
            {
                character()->queueAction(a);
                a.type = Action::CANCEL;
                mState = MOVE;
                break;
            }
            if(e.type == sf::Event::MouseMoved)
                //TODO tweak smoothing
                mMousePos = (mMousePos*0.1f+sf::Vector2f{e.mouseMove.x,e.mouseMove.y}*0.9f);
                a.aim.direction = (mMousePos - mOldMousePos)*0.25f;
            if(e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Right)
            {
                a.type = Action::CANCEL;
                mState = MOVE;
                break;
            }
            if(e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left)
            {
                if(mOldMousePos != sf::Vector2f{e.mouseButton.x,e.mouseButton.y}){
                    a.type = Action::THROW;
                }
                mState = MOVE;
                break;
            }

            a.type = Action::AIM;
            break;
        }
    }

    if(a.type != Action::NONE)
        character()->queueAction(a);
    return a.type == Action::THROW;
}

bool KeyboardController::pressKey(sf::Keyboard::Key key)
{
    KeysState::iterator it = mKeysState.find(key);
    if(it == mKeysState.end()){
        mKeysState.emplace(KeysState::value_type(key,true));
        return true;
    }
    if(!it->second){
        it->second = true;
        return true;
    }
    return false;
}

bool KeyboardController::releaseKey(sf::Keyboard::Key key)
{
    KeysState::iterator it = mKeysState.find(key);
    if(it != mKeysState.end() && it->second){
        it->second = false;
        return true;
    }
    return false;
}
