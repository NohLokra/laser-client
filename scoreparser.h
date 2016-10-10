#ifndef SCOREPARSER_H
#define SCOREPARSER_H

#include <vector>
#include <QString>
#include <QStringList>
#include <QJsonArray>
#include <QMessageBox>
#include <QJsonDocument>

#ifdef QT_DEBUG
#include <QDebug>
#endif

#include "jsonencodable.h"

using namespace std;

enum RowType {
    SHOT, //Touches données
    HIT   //Touches reçues
};

enum TeamColor {
    RED,
    BLUE,
    PURPLE,
    MIXED
};

typedef enum RowType RowType;
typedef enum TeamColor TeamColor;

class Row : public JsonEncodable
{
public:
    Row(QString line);
    RowType getType();
    int getTotal();
    QJsonObject toJson();
    QString getTypeString();

private:
    QString _line;
    QString _playerName;
    TeamColor _playerTeam;
    QString _playerTeamLetter;
    int _frontCount;
    int _laserCount;
    int _rearCount;
    int _shoulderCount;
    int _total;
    RowType _type;
};

class Player : public JsonEncodable
{
public:
    Player(QString infos);
    void addRow(Row);
    void setRatio(int ratio);
    TeamColor getTeamColor();
    QString getName();
    QJsonObject toJson();

private:
    QString _name;
    TeamColor _teamColor;
    vector<Row> _shots;
    vector<Row> _hits;
    int _score;
    int _ratio;
    int _packNumber;
    int _nbShots;
    int _ranking;
};

class Team : public JsonEncodable
{
public:
    Team(TeamColor color, int score = 0);
    void addPlayer(Player);
    TeamColor getColor();
    int size();
    vector<Player> getPlayers();
    int getScore();
    QString getColorString();
    QJsonObject toJson();
    int getPlayersCount();

private:
    TeamColor _color;
    vector<Player> _players;
    int _score;
};

class Game : public JsonEncodable
{
public:
    Game(QString gameDetails);
    void addTeam(Team);
    bool hasTeam(TeamColor color);
    Team* getTeam(TeamColor color);
    vector<Team> getTeams();
    QJsonObject toJson();

private:
    vector<Team> _teams;
    int _timestamp;
    QString _name;
    int _numPlayers;
    int _redScore;
    int _blueScore;
    int _purpleScore;
    int _mixedScore;
};

class ScoreParser
{
public:
    ScoreParser(QString fileContent);
    ~ScoreParser();
    vector<QString> listPlayers();
    Game parse();
    QJsonObject jsonParse();

private:
    QString _text;
    Game* _game;
};

#endif // SCOREPARSER_H
