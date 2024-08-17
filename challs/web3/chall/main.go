package main

import (
	"net/http"
)

func main() {
	sqlInit()

	http.HandleFunc("/api/servers", apiGetServers)
	http.HandleFunc("/api/servers/{id}", apiGetServer)
	http.HandleFunc("/api/games", apiGetGames)
	http.HandleFunc("/api/games/{id}", apiGetGame)
	http.HandleFunc("/api/search", apiSearch)

	http.Handle("/", http.FileServer(http.Dir("./static")))

	http.ListenAndServe(":8080", nil)
}
