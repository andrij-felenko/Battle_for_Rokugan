#include "lib_bfr/player.h"

BattleForRokugan::Player::Player(QString name, Clan::Type type, QObject* parent)
    : QObject(parent), m_clan(new Clan(type,this)), m_name(name), m_mission(nullptr)
{
    m_tokenAssetsList.push_back(new TurnToken(TurnToken::Type::Empty, this));

    // add all token to start reserve pocket
    addTokenToReserve(TurnToken::Type::Army, 6 , 1);
    addTokenToReserve(TurnToken::Type::Army, 4 , 2);
    addTokenToReserve(TurnToken::Type::Army, 3 , 3);
    addTokenToReserve(TurnToken::Type::Army, 2 , 4);
    addTokenToReserve(TurnToken::Type::Army, 1 , 5);
    addTokenToReserve(TurnToken::Type::Navy, 2 , 1);
    addTokenToReserve(TurnToken::Type::Navy, 1 , 2);
    addTokenToReserve(TurnToken::Type::Shinobi, 1 , 1);
    addTokenToReserve(TurnToken::Type::Shinobi, 2 , 2);
    addTokenToReserve(TurnToken::Type::Blessing, 2 , 2);
    addTokenToReserve(TurnToken::Type::Diplomacy);
    addTokenToReserve(TurnToken::Type::Sabotage);

    // add special clan turn token
    auto specClanToken = m_clan->specialClanToken();
    addTokenToReserve(specClanToken.type(), 1, specClanToken.value());

    // add base cards
    m_cardList.push_back(new Card(Card::Type::Shugendja, this));
    m_cardList.push_back(new Card(Card::Type::Intelligence, this));
    m_cardList.push_back(new Card(Card::Type::Intelligence, this));
}

QString BattleForRokugan::Player::name() const
{
    return m_name;
}

const BattleForRokugan::Clan* BattleForRokugan::Player::clan() const
{
    return m_clan;
}

void BattleForRokugan::Player::setMission(BattleForRokugan::Mission::Type mission)
{
    if (m_mission == nullptr)
        return;
    m_mission = new Mission(mission, this);
}

unsigned BattleForRokugan::Player::regionCardCount() const
{
    unsigned ret = 0;
    for (auto it : m_cardList)
        if (Card::isInitiative(it->type()))
            ret++;
    return ret;
}

unsigned BattleForRokugan::Player::provinceCount() const
{
    return m_provinceList.size();
}

unsigned BattleForRokugan::Player::controlTokenCount() const
{
    unsigned ret = provinceCount();
    for (const auto &it : m_provinceList)
        ret += it.get()->controlUp();
    return ret;
}

const BattleForRokugan::Mission* BattleForRokugan::Player::mission() const
{
    return m_mission;
}

void BattleForRokugan::Player::addTokenToReserve(BattleForRokugan::TurnToken::Type type,
                                                 unsigned char count, unsigned char value)
{
    for (unsigned char i = 0; i < count; i++)
        m_tokenReserveList.push_back(new TurnToken(type, value, this));
}
