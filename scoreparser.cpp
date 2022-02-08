#include "scoreparser.h"

Row::Row(QString line) : _line(line)
{

    QStringList parts = line.split("|");

    QStringList subParts = parts[0].split(":"); // HIT:R par exemple, si on a été touché par un rouge
    _type = subParts[0] == "HIT" ? HIT : SHOT;

    //On teste la couleur pour déterminer la team
    _playerTeamLetter = subParts[1];
    if ( subParts[1] == "R" )
        _playerTeam = RED;
    else if ( subParts[1] == "B" )
        _playerTeam = BLUE;
    else if ( subParts[1] == "P" )
        _playerTeam = PURPLE;
    else if ( subParts[1] == "M" )
        _playerTeam = MIXED;

    _playerName = parts[1].trimmed();
    _frontCount = parts[2].trimmed().toInt();
    _rearCount = parts[3].trimmed().toInt();
    _shoulderCount = parts[4].trimmed().toInt();
    _laserCount = parts[5].trimmed().toInt();
    _total = parts[6].trimmed().toInt();
}

RowType Row::getType() {
    return _type;
}

QString Row::getTypeString()
{
    return _type == SHOT ? "shot" : "hit";
}

int Row::getTotal() {
    return _total;
}

QJsonObject Row::toJson()
{
    QJsonObject row
    {
        {"front", _frontCount},
        {"rear", _rearCount},
        {"shoulder", _shoulderCount},
        {"laser", _laserCount},
        {"total", _total},
        {"player_name", _playerName},
        {"player_team", _playerTeamLetter}
    };

    return row;
}

Player::Player(QString infos) : _name(), _shots(), _hits(), _score(0), _ratio(0) {
    QStringList lines = infos.split("\n");
    lines.removeAll("");

    _name = lines[0].trimmed();
    _packNumber = lines[2].toInt();
    _score = lines[lines.indexOf("SCORE")+1].trimmed().toInt();

    QStringList shotParts = lines[lines.indexOf("Centre Shots")+1].split("|");
    _nbShots = shotParts[0].toInt();
    _ratio = shotParts[1].toInt();
    _ranking = shotParts[2].toInt();

    QString color = lines[lines.indexOf("Colour")+1].replace(QRegExp("[\\d]"), "").trimmed();
    if ( color.toUpper() == "RED" )
        _teamColor = RED;
    else if ( color.toUpper() == "BLUE" )
        _teamColor = BLUE;
    else if ( color.toUpper() == "MIXED" )
        _teamColor = MIXED;
    else if ( color.toUpper() == "PURPLE" )
        _teamColor = PURPLE;


    int startHitList = lines.indexOf("START HIT LIST");
    for ( int i = startHitList+1 ; lines[i] != "END HIT LIST" ; i++ ) // On boucle sur les listes de tirs donnés/reçus
    {
        QString line = lines[i];
        addRow(line);
    }
}

QString Player::getName() {
    return _name;
}

void Player::addRow(Row r) {
    if ( r.getType() == SHOT ) {
        _shots.push_back(r);
    } else {
        _hits.push_back(r);
    }
}

TeamColor Player::getTeamColor() {
    return _teamColor;
}

QJsonObject Player::toJson()
{
    QJsonObject player
    {
        {"score", _score},
        {"name", _name},
        {"ratio", _ratio},
        {"pack_number", _packNumber},
        {"nb_shots", _nbShots},
        {"ranking", _ranking}
    };

    QJsonArray shots;
    for ( unsigned int i = 0 ; i < _shots.size() ; i++ )
        shots.append(_shots[i].toJson());

    QJsonArray hits;
    for ( unsigned int i = 0 ; i < _hits.size() ; i++ )
        hits.append(_hits[i].toJson());

    player.insert("shots", shots);
    player.insert("hits", hits);

    return player;
}

Team::Team(TeamColor color, int score) : _color(color), _players(), _score(score)
{

}

void Team::addPlayer(Player* p) {
    _players.push_back(p);
}

TeamColor Team::getColor() {
    return _color;
}

int Team::size() {
    return _players.size();
}

vector<Player*> Team::getPlayers() {
    return _players;
}

int Team::getScore() {
    return _score;
}

QString Team::getColorString()
{
    if ( _color == RED )
        return "red";
    else if ( _color == BLUE )
        return "blue";
    else if ( _color == MIXED )
        return "mixed";
    else
        return "purple";
}

QJsonObject Team::toJson()
{
    QJsonObject team
    {
        {"color", getColorString()},
        {"score", getScore()}
    };

    QJsonArray players;
    for ( unsigned int i = 0 ; i < _players.size() ; i++ )
    {
        players.append(_players[i]->toJson());
    }

    team.insert("players", players);

    return team;
}

int Team::getPlayersCount()
{
    return _players.size();
}

Game::Game(QString gameDetails) {
    QStringList details = gameDetails.trimmed().split("\n");
    for ( int i = 0 ; i < details.size() ; i += 2 ) {
        QString key = details[i].trimmed();
        QString value = details[i+1].trimmed();

        if ( key == "score_game.game_name" )
        {
            _name = value.trimmed();
        }
        else if ( key == "score_game.num_players" )
        {
            _numPlayers = value.toInt();
        }
        else if ( key == "score_game.start_time" )
        {
            _timestamp = details[i+1].toInt();
        }
        else if ( key == "score_game.redScore" )
        {
            _redScore = details[i+1].toInt();
            if ( !hasTeam(RED) )
                addTeam(Team(RED, _redScore));
        }
        else if ( key == "score_game.greenScore" ) //Je suppute que green ça soit les bleus
        {
            _blueScore = details[i+1].toInt();
            if ( !hasTeam(BLUE) )
                addTeam(Team(BLUE, _blueScore));
        }
        else if ( key == "score_game.mixedScore" )
        {
            _mixedScore = details[i+1].toInt();
            if ( !hasTeam(MIXED) )
                addTeam(Team(MIXED, _mixedScore));
        }
        else if ( key == "score_game.purpleScore" )
        {
            _purpleScore = details[i+1].toInt();
            if ( !hasTeam(PURPLE) )
                addTeam(Team(PURPLE, _purpleScore));
        }
    }
}

bool Game::hasTeam(TeamColor color) {
    bool result = false;
    for ( unsigned int i = 0 ; i < _teams.size() ; i++ ) {
        if ( _teams[i].getColor() == color )
            result = true;
    }

    return result;
}

void Game::addTeam(Team t)
{
    _teams.push_back(t);
}

Team* Game::getTeam(TeamColor color) {
    for ( unsigned int i = 0 ; i < _teams.size() ; i++ ) {
        if ( _teams[i].getColor() == color )
            return &_teams[i];
    }

    return NULL;
}

vector<Team> Game::getTeams() {
    return _teams;
}

QJsonObject Game::toJson()
{
    QJsonObject object
    {
        {"numPlayers", _numPlayers},
        {"timestamp", _timestamp},
        {"name", _name}
    };


    QJsonArray teams;
    for ( unsigned int i = 0 ; i < _teams.size() ; i++ )
    {
        Team teamToEncode = _teams[i];
        if ( teamToEncode.getPlayersCount() > 0 )
        {
            QJsonObject encodedTeam = _teams[i].toJson();
            teams.append(encodedTeam);
        }
    }

    object.insert("teams", teams);

    return object;
}

ScoreParser::ScoreParser(QString fileContent) : _text(fileContent)
{
    QStringList parts = _text.split("score_players[playerIndex].alias");

    QString gameDetails = parts[0]; //On initialise notre instance de Game avec les détails dans parts[0]
    Game* game = new Game(gameDetails);

    for ( int i = 1 ; i < parts.size() ; i++ ) { //On part de 1 car parts[0] contient ls détails de la game
        Player *p = new Player(parts[i]);

        Team* playerTeam = game->getTeam(p->getTeamColor()); //On récup l'équipe du joueur et on l'ajoute dedans
        playerTeam->addPlayer(p);
    }

    _game = game;
}

Game ScoreParser::parse() {
    return *_game;
}

QJsonObject ScoreParser::jsonParse()
{
    QJsonObject game = _game->toJson();

    return game;
}

ScoreParser::~ScoreParser()
{

}

