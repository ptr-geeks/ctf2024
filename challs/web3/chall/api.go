package main

import (
	"encoding/json"
	"net/http"
)

func apiGetServers(w http.ResponseWriter, r *http.Request) {
	servers := sqlGetServers()
	json, err := json.Marshal(servers)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	w.Header().Set("Content-Type", "application/json")
	w.Write(json)
}

func apiGetServer(w http.ResponseWriter, r *http.Request) {
	id := r.PathValue("id")
	server := sqlGetServer(id)
	if server == nil {
		http.NotFound(w, r)
		return
	}

	json, err := json.Marshal(server)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	w.Header().Set("Content-Type", "application/json")
	w.Write(json)
}

func apiGetGames(w http.ResponseWriter, r *http.Request) {
	games := sqlGetGames()
	json, err := json.Marshal(games)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	w.Header().Set("Content-Type", "application/json")
	w.Write(json)
}

func apiGetGame(w http.ResponseWriter, r *http.Request) {
	id := r.PathValue("id")
	g := sqlGetGame(id)
	if g == nil {
		http.NotFound(w, r)
		return
	}

	json, err := json.Marshal(g)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	w.Header().Set("Content-Type", "application/json")
	w.Write(json)
}

func apiSearch(w http.ResponseWriter, r *http.Request) {
	query := r.FormValue("q")
	if query == "" {
		http.Error(w, "Missing query", http.StatusBadRequest)
		return
	}

	servers := sqlSearch(query)
	json, err := json.Marshal(servers)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	w.Header().Set("Content-Type", "application/json")
	w.Write(json)
}
