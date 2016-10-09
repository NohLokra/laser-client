#ifndef SCOREPARSER_H
#define SCOREPARSER_H

#include <vector>
#include <QString>
#include <QStringList>
#ifdef QT_DEBUG
#include <QDebug>
#endif
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

class Row
{
public:
    Row(QString line);
    RowType getType();
    int getTotal();

private:
    QString _line;
    QString _playerName;
    TeamColor _playerTeam;
    int _frontCount;
    int _laserCount;
    int _rearCount;
    int _shoulderCount;
    int _total;
    RowType _type;
};

class Player
{
public:
    Player(QString name);
    void addRow(Row);
    void setRatio(int ratio);
private:
    QString _name;
    vector<Row> _shots;
    vector<Row> _hits;
    int _score;
    int _ratio;
};

class Team
{
    Team(TeamColor color, int score = 0);
    Team(TeamColor color, vector<Player> players, int score = 0);
    void addPlayer(Player);

private:
    TeamColor _color;
    vector<Player> _players;
    int _score;
};

class Game
{
public:
    Game(int timestamp);
    Game(vector<Team> teams, int timestamp);
    void addTeam(Team);

private:
    vector<Team> _teams;
    int _timestamp;
};

class ScoreParser
{
public:
    ScoreParser(QString fileContent);
    ~ScoreParser();
    vector<QString> listPlayers();
    Game parse();

private:
    QString _text;
};

#endif // SCOREPARSER_H
