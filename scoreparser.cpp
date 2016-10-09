#include "scoreparser.h"

Row::Row(QString line) : _line(line)
{
    QStringList parts = line.split("|");

    QStringList subParts = parts[0].split(":"); // HIT:R par exemple, si on a été touché par un rouge
    _type = subParts[0] == "HIT" ? HIT : SHOT;

    //On teste la couleur pour déterminer la team
    if ( subParts[1] == "R" )
        _playerTeam = RED;
    else if ( subParts[1] == "B" )
        _playerTeam = BLUE;
    else if ( subParts[1] == "P" )
        _playerTeam = PURPLE;
    else if ( subParts[1] == "M" )
        _playerTeam = MIXED;
    else throw "Unsupported team color";

    _playerName = parts[1].trimmed();
    _frontCount = parts[2].toInt();
    _rearCount = parts[3].toInt();
    _shoulderCount = parts[4].toInt();
    _laserCount = parts[5].toInt();
    _total = parts[6].toInt();
}

RowType Row::getType() {
    return _type;
}

int Row::getTotal() {
    return _total;
}

Player::Player(QString name) : _name(name), _shots(), _hits(), _score(0), _ratio(0) {

}

void Player::addRow(Row r) {
    if ( r.getType() == SHOT ) {
        _shots.push_back(r);
        _score += r.getTotal();
    } else {
        _hits.push_back(r);
        _score -= r.getTotal();
    }

    qDebug() << "Current score for " << _name << ": " << _score;
}

void Player::setRatio(int ratio) {
    _ratio = ratio;
    int bonus = ratio * 10;
    if ( bonus > 100 )
        _score += 100;
    else
        _score += bonus;
}

ScoreParser::ScoreParser(QString fileContent) : _text(fileContent)
{
    QStringList parts = fileContent.split("score_players[playerIndex].alias");
    qDebug() << parts;

    QString text = "HIT:R|DDPINCH   | 2|  | 1|  |  13|\n            SHOT:R|DDPINCH   | 1| 2| 6|  |  90|\n            HIT:R|BARDA     | 1|  | 8| 2|  35|\n            SHOT:R|BARDA     | 1| 1|12|11| 250|\n            HIT:R|JUJU      |  | 1|  | 2|  10|\n            SHOT:R|JUJU      | 3| 1| 2| 4| 100|\n            HIT:R|JULIEN    | 1| 1| 2| 1|  18|\n            SHOT:R|JULIEN    | 3|  | 2| 4|  90|\n            HIT:R|SUIJIN    | 2|  | 2| 1|  19|\n            SHOT:R|SUIJIN    | 4| 5| 8| 8| 250|\n            HIT:R|DIAMKAPPA | 1| 1|  | 1|  12|\n            SHOT:R|DIAMKAPPA | 1| 1| 5|  |  70|\n            HIT:R|ZOZO      | 1|  |  | 2|  11|\n            SHOT:R|ZOZO      | 2|  | 3| 2|  70|\n            HIT:B|KARIKOU   |  |  | 1|  |   3|\n            SHOT:B|KARIKOU   | 2| 1| 3|  |  60|\n            HIT:B|AOLYN     |  | 1|  | 1|   7|\n            SHOT:B|AOLYN     | 5| 1| 7| 2| 150|\n            HIT:B|EL DOUCHE | 2| 1| 4| 1|  29|\n            SHOT:B|EL DOUCHE | 6| 2| 8| 4| 200|\n            HIT:B|THECHOSENS| 1|  |  | 1|   8|\n            SHOT:B|THECHOSENS| 1| 1| 3| 2|  70|\n            HIT:B|MANU      |  |  | 2|  |   6|\n            SHOT:B|MANU      | 1| 3| 5| 1| 100|\n            HIT:B|EL MACHO  |  | 1|  |  |   4|\n            SHOT:B|EL MACHO  | 2| 1| 5| 1|  90|\n            HIT:B|LE MAESTRO|  | 2| 1|  |  11|\n            SHOT:B|LE MAESTRO| 1|  | 3| 5|  90|\n            HIT:B|DRAK      | 3|  | 2|13|  60|\n            SHOT:B|DRAK      | 5| 3| 8| 4| 200|";
    QStringList rows = text.split("\n");

    Player p("Zozo");
    p.setRatio(7);
    for ( int i = 0 ; i < rows.length() ; i++ ) {
        qDebug() << rows[i].trimmed();
        p.addRow(Row(rows[i].trimmed()));
    }
}

ScoreParser::~ScoreParser()
{

}

