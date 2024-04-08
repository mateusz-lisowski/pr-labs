package main

import (
	"fmt"
	"io"
	"net/http"

	"golang.org/x/net/websocket"
)

type Server struct {
	connections map[*websocket.Conn]bool
}

func newServer() *Server {
	return &Server{
		connections: make(map[*websocket.Conn]bool),
	}
}

func (s *Server) handleWebsocket(conn *websocket.Conn) {
	fmt.Println("New incoming connection from: ", conn.RemoteAddr())
	s.connections[conn] = true
	s.readLoop(conn)
}

func (s *Server) readLoop(conn *websocket.Conn) {
	buffer := make([]byte, 1024)
	for {
		n, err := conn.Read(buffer)
		if err != nil {
			if err == io.EOF {
				break
			}
			fmt.Println("Error reading socket: ", err)
			continue
		}
		msg := buffer[:n]
		s.broadcast(msg)
	}
}

func (s *Server) broadcast(msg []byte) {
	for conn := range s.connections {
		go func(conn *websocket.Conn) {
			if _, err := conn.Write(msg); err != nil {
			}
		}(conn)
	}
}

func main() {
	const port int = 8080

	server := newServer()

	http.Handle("/ws", websocket.Handler(server.handleWebsocket))

	fmt.Printf("Listening on port %d\n", port)
	http.ListenAndServe(fmt.Sprintf(":%d", port), nil)
}
