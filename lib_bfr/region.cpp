#include "lib_bfr/region.h"
#include "lib_bfr/province.h"
#include <QDebug>

BattleForRokugan::Region::Region(const BattleForRokugan::Region::Type type, QObject *parent)
    : QObject(parent), m_type(type), m_firstCard(std::rand()%2)
{
    // init provinces
    switch (type) {
    case Type::Crab:       addProvinces({ 1, 3, 2, 2 }, 3); break;
    case Type::Crane:      addProvinces({ 2, 2, 3    }, 0); break;
    case Type::Dragon:     addProvinces({ 1, 2, 3    }, 1); break;
    case Type::Lion:       addProvinces({ 2, 2, 2    }, 1 ); break;
    case Type::Phoenix:    addProvinces({ 2, 2, 1    }, 0); break;
    case Type::Scorpion:   addProvinces({ 3, 2, 1    }, 1); break;
    case Type::Unicorn:    addProvinces({ 2, 3, 1    }, 0); break;
    case Type::Archipelago:addProvinces({ 2, 1, 1 }); break;
    case Type::Dune:       addProvinces({ 3, 2, 3 }); break;
    case Type::LandOfShadowDown:
    case Type::LandOfShadowUp: addProvinces();
    default:;
    }
}

std::optional<BattleForRokugan::Clan::Type> BattleForRokugan::Region::daimyoRegion() const
{
    auto clan = Clan::Type::None;
    for (const auto &it : m_provinceList){
        if (auto clanIt = it->clanOwner(); it.get()== m_provinceList.begin()->get()){
            if (clanIt != Clan::Type::None){
                clan = clanIt;
                continue;
            }
            else
                return std::nullopt;
        }
        else if (clanIt != clan)
            return std::nullopt;
    }
    return clan;
}

BattleForRokugan::Region::Type BattleForRokugan::Region::type() const
{
    return m_type;
}

std::optional<QString> BattleForRokugan::Region::cardRegionName() const
{
    switch (m_type) {
    case Type::Crab: return m_firstCard ?
                    tr("Sea Access")
                  : tr("Castling");

    case Type::Archipelago:return m_firstCard ?
                    tr("Pirate Raids")
                  : tr("Prosperity");

    case Type::Crane: return m_firstCard ?
                    tr("Code of Honor")
                  : tr("Diplomatic Mission");

    case Type::Dragon: return m_firstCard ?
                    tr("Objective Movement")
                  : tr("Blessed Land");

    case Type::Dune: return m_firstCard ?
                    tr("Bountiful Harvest")
                  : tr("Ashigaru Militia");

    case Type::Lion: return m_firstCard ?
                    tr("Bushido")
                  : tr("Glorious Battle");

    case Type::Phoenix: return m_firstCard ?
                    tr("Kami Support")
                  : tr("Purge");

    case Type::Scorpion: return m_firstCard ?
                    tr("Spy Network")
                  : tr("Fires of Rebellion");

    case Type::Unicorn: return m_firstCard ?
                    tr("Reinforcement")
                  : tr("Cultural Exchange");

    case Type::LandOfShadowDown: return m_firstCard ?
                    tr("Raise Dead")
                  : tr("Dominion of Terror");

    case Type::LandOfShadowUp: return m_firstCard ?
                    tr("Deal with Evil")
                  : tr("Killing the Weak");
    default:;
    }
    return std::nullopt;
}

std::optional<QString> BattleForRokugan::Region::cardRegionDescription() const
{
    switch (m_type) {
    case Type::Crab: return m_firstCard ?
                    tr("Select a continental province and place a harbor token in it. "
                       "This province is now considered a coastal province.")

                  : tr("Select 1 Army, Fleet, or Shinobi token from your discard "
                       "and return it to your asset. Then choose 1 battle token from "
                       "your asset and either discard it or mix it into your personal supply.");

    case Type::Archipelago:return m_firstCard ?
                    tr("Select a province and place a scorched earth token on it. "
                       "If you control that province, place 3 control tokens faceup "
                       "and another province you control.")

                  : tr("Select a province (other than Shadowlands) and place "
                       "a +2 Honor Bonus token there.");

    case Type::Crane: return m_firstCard ?
                    tr("Select 2 provinces (excluding shadow lands) and place "
                       "a +1 Honor Bonus token in each.")

                  : tr("Select a province and place a peace token in it. "
                       "If another player controls the province, place 2 control tokens "
                       "faceup on any province you control.");

    case Type::Dragon: return m_firstCard ?
                    tr("Choose 2 provinces you control and place 1 control token "
                       "face up on each province.")

                  : tr("Select a province and place a shrine token on it. "
                       "This province cannot be attacked, but the player "
                       "who controls the province can attack neighboring provinces from it.");

    case Type::Dune: return m_firstCard ?
                    tr("Choose a province you control and place 2 control tokens there face up.")

                  : tr("Select 3 provinces (excluding Shadowlands) "
                       "and place a +1 Defense Bonus token on each province.");

    case Type::Lion: return m_firstCard ?
                    tr("Select a province (except the Shadowlands) and place "
                       "a 4-flower token in it, covering the flower printed on the board. "
                       "The honor value of this province becomes 4.")

                  : tr("Select a province and place a Glory token on it. "
                       "Diplomacy and mayhem tokens cannot be placed in this province.");

    case Type::Phoenix: return m_firstCard ?
                    tr("Select a province (except Shadowlands) "
                       "and place a +2 Defense Bonus token there.")

                  : tr("Remove the Scorched Earth token from any province. Then, place 2 "
                       "of your control tokens in that province and turn one of them face up.");

    case Type::Scorpion: return m_firstCard ?
                    tr("Choose another player and see the tokens in his asset. "
                       "This player cannot use an empty token for this round.")

                  : tr("Remove a peace token from any province. If you control this province, "
                       "place 2 control tokens faceup on it.");

    case Type::Unicorn: return m_firstCard ?
                    tr("Choose 2 Army tokens from your discard and return them to your asset. "
                       "Then choose 2 battle tokens from your asset and either discard them "
                       "or mix them into your personal supply.")

                  : tr("Choose a province under your control and a province under enemy control. "
                       "Swap all control tokens in your province with all control tokens "
                       "in the enemy province (do not flip them).");

    case Type::LandOfShadowDown: return m_firstCard ?
                    tr("Remove your control token from any province other than the Shadowlands. "
                       "Then, choose a battle token from your discard and place it "
                       "face up on the board, observing the rest of the placement rules. "
                       "After that, place a battle token from your asset as usual.")

                  : tr("Remove your control token from any province other than the Shadowlands. "
                       "Then remove 2 or fewer Special Tokens from the board.");

    case Type::LandOfShadowUp: return m_firstCard ?
                    tr("Remove your control token from any province other than the Shadowlands. "
                       "Then select 4 or fewer battle tokens on the board and look "
                       "at their faces without showing the others. "
                       "Reveal one of these tokens and send it to its clan's discard.")

                  : tr("Discard a Battle token from your asset. You do not place "
                       "a battle token this turn. Then reveal any 2 battle tokens on the board "
                       "and send them to their clans' discard.");
    default:;
    }
    return std::nullopt;
}

void BattleForRokugan::Region::addProvinces(std::vector <char> list, char capital)
{
    if (list.size() <= 0)
        return;

    for (char i = 0; i < char(list.size()); i++)
        m_provinceList.push_back(std::make_shared <Province> (m_type, i == capital, i, list[i]));
}

std::optional<std::shared_ptr<BattleForRokugan::Province>>
BattleForRokugan::Region::findProvince(unsigned char number)
{
    for (auto it : m_provinceList)
        if (it.get()->number() == number)
            return it;
    return std::nullopt;
}
