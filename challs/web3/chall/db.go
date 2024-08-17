package main

import (
	"database/sql"
	"os"
	"strings"

	_ "github.com/mattn/go-sqlite3"
)

var sqlDb *sql.DB

func sqlInit() {
	var err error
	sqlDb, err = sql.Open("sqlite3", "database.sqlite3")
	if err != nil {
		panic(err)
	}

	rows := 0
	err = sqlDb.QueryRow("SELECT COUNT(*) FROM flags").Scan(&rows)
	if err != nil {
		panic(err)
	}

	if rows == 0 {
		sqlDb.Exec("INSERT INTO flags(flag) VALUES('" + sqlEscapeArg(os.Getenv("FLAG")) + "')")
	}
}

func sqlEscapeArg(arg string) string {
	return strings.Replace(arg, "'", "''", 1)
}

func sqlGetServers() []Server {
	servers := make([]Server, 0)

	rows, err := sqlDb.Query("SELECT * FROM servers")
	if err != nil {
		return servers
	}
	defer rows.Close()

	for rows.Next() {
		var server Server
		rows.Scan(&server.Id, &server.Name, &server.Desc, &server.IP, &server.Game, &server.Stars)
		servers = append(servers, server)
	}

	return servers
}

func sqlGetServer(id string) *Server {
	var server Server

	err := sqlDb.QueryRow("SELECT * FROM servers WHERE id = "+sqlEscapeArg(id)).Scan(&server.Id, &server.Name, &server.Desc, &server.IP, &server.Game, &server.Stars)
	if err != nil {
		return nil
	}

	return &server
}

func sqlGetGames() []Game {
	games := make([]Game, 0)

	rows, err := sqlDb.Query("SELECT * FROM games")
	if err != nil {
		return games
	}
	defer rows.Close()

	for rows.Next() {
		var game Game
		rows.Scan(&game.Id, &game.Name, &game.Desc, &game.Category)
		games = append(games, game)
	}

	return games
}

func sqlGetGame(id string) *Game {
	var g Game

	err := sqlDb.QueryRow("SELECT * FROM games WHERE id = "+sqlEscapeArg(id)).Scan(&g.Id, &g.Name, &g.Desc, &g.Category)
	if err != nil {
		return nil
	}

	return &g
}

func sqlSearch(query string) []Server {
	servers := make([]Server, 0)

	rows, err := sqlDb.Query("SELECT * FROM servers WHERE name LIKE '%" + sqlEscapeArg(query) + "%'")
	if err != nil {
		return servers
	}
	defer rows.Close()

	for rows.Next() {
		var server Server
		rows.Scan(&server.Id, &server.Name, &server.Desc, &server.IP, &server.Game, &server.Stars)
		servers = append(servers, server)
	}

	return servers
}
