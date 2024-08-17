package main

type Server struct {
	Id    int    `json:"id"`
	Name  string `json:"name"`
	Desc  string `json:"desc"`
	IP    string `json:"ip"`
	Game  string `json:"game"`
	Stars int    `json:"stars"`
}

type Game struct {
	Id       int    `json:"id"`
	Name     string `json:"name"`
	Desc     string `json:"desc"`
	Category string `json:"category"`
}
