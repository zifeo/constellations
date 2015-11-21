#include "StateTitleScreen.h"
#include "Core.h"
#include "StateConstellation.h"
#include "Button.h"
#include "SpinBox.h"
#include <functional>

StateTitleScreen::StateTitleScreen() : mMainWidget(new Widget())
{
}

void StateTitleScreen::onBegin()
{
    using namespace std::placeholders;
    sf::Texture* titleTex = Core::get().textureCache().get("data/constellations.png");
    mTitle.setOrigin(titleTex->getSize().x/2.f,titleTex->getSize().y/2.f);
    mTitle.setTexture(*titleTex);
    mTitle.setScale(2.5f,2.5f);
    Core::get().textureCache().get("data/constellations.png")->setSmooth(false);
    //mTitle.setString("Constellations");
    sf::Text text;
    text.setFont(*Core::get().fontCache().get("default"));
    text.setString("Start!");
    text.setCharacterSize(50);

    mTitle.setPosition(1280/2,200);
    //mTitle.setCharacterSize(156);
    text.setPosition(1280/2-150,720/2);

    mMainWidget->add(new Button(text,std::bind(&StateTitleScreen::launchStateConstellation,this)));
    text.move(0,60);
    text.setString("Players :");
    mMainWidget->add(new SpinBox(text,2,2,4,std::bind(&StateTitleScreen::setPlayerCount,this,_1)));
    text.move(0,60);
    text.setString("Life points :");
    mMainWidget->add(new SpinBox(text,1,1,10,std::bind(&StateTitleScreen::setPlayerPv,this,_1)));
    text.move(0,60);
    text.setString(L"Quit");
    mMainWidget->add(new Button(text,[]{Core::get().endGame();}));
    mMainWidget->show();

    mBackground.setTexture(Core::get().textureCache().get("data/stars_w_4.png"),4);
    mBackground.uniformDistribution({0,0,1280,720}, 150);
    mView = Core::get().renderWindow().getDefaultView();
}

void StateTitleScreen::update(float delta_s)
{
    //NA
}

void StateTitleScreen::onResume()
{
    mView = Core::get().renderWindow().getDefaultView();
}

void StateTitleScreen::onEnd()
{

}

void StateTitleScreen::onPause()
{

}

void StateTitleScreen::launchStateConstellation()
{
    setVisible(false);
    Core::get().pushState(SharedState(new StateConstellation()));
}

void StateTitleScreen::draw(sf::RenderTarget &target)
{
    target.setView(mView);
    target.draw(mBackground);
    target.draw(*mMainWidget.get());
    target.draw(mTitle);
}

void StateTitleScreen::pushEvent(const sf::Event &e)
{
    mMainWidget->pushEvent(e);
    switch(e.type)
    {
        case sf::Event::KeyReleased:
            if(e.key.code == sf::Keyboard::Return)
                launchStateConstellation();
            if(e.key.code == sf::Keyboard::Escape)
                Core::get().endGame();
            break;
    }
}

void StateTitleScreen::setPlayerCount(int count)
{
    Core::get().globalDict()["player_count"] = count;
}

void StateTitleScreen::setPlayerPv(int pv)
{
    Core::get().globalDict()["player_pv"] = pv;
}
