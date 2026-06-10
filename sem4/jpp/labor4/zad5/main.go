package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

const USER_COUNT = 20
const MESSAGE_COUNT = 100

type Message struct {
	Target int
	Sender int
}

var logMutex sync.Mutex

func Log(msg string) {
	logMutex.Lock()
	fmt.Println(msg)
	logMutex.Unlock()
}

func Server(serverChan chan Message, userChans []chan Message, wg *sync.WaitGroup) {
	defer wg.Done() 

	for i := 0; i < USER_COUNT * MESSAGE_COUNT; i++ {
		msg := <-serverChan
		userChans[msg.Target] <- msg
	}
}

func UserTask(id int, serverChan chan Message, inbox chan Message, wg *sync.WaitGroup, stats []int) {
	defer wg.Done()
	
	displayId := id + 1

	r := rand.New(rand.NewSource(time.Now().UnixNano() + int64(id)))
	Sent := 0
	ReceivedCount := 0

	for {
		if Sent < MESSAGE_COUNT {
			Target := r.Intn(USER_COUNT)
			msg := Message{Target: Target, Sender: id}

			select {
				case inMsg, ok := <-inbox: 
					if !ok {
						stats[id] = ReceivedCount
						return
					}

					ReceivedCount++
					Log(fmt.Sprintf("[<-] User %d received from %d", displayId, inMsg.Sender + 1))
			
				case serverChan <- msg:
					Sent++
					Log(fmt.Sprintf("[->] User %d sent to %d", displayId, Target + 1))
			}
		} else {
			inMsg, ok := <-inbox
			if !ok {
				stats[id] = ReceivedCount
				return
			}

			ReceivedCount++
			Log(fmt.Sprintf("[<-] User %d received from %d", displayId, inMsg.Sender + 1))
		}
	}
}

func main() {
	Log("SERVER READY")

	serverChan := make(chan Message)
	userChans := make([]chan Message, USER_COUNT)
	for i := 0; i < USER_COUNT; i++ {
		userChans[i] = make(chan Message)
	}
	
	stats := make([]int, USER_COUNT)

	var serverWg sync.WaitGroup
	serverWg.Add(1)
	go Server(serverChan, userChans, &serverWg)

	var usersWg sync.WaitGroup
	usersWg.Add(USER_COUNT)
	for i := 0; i < USER_COUNT; i++ {
		go UserTask(i, serverChan, userChans[i], &usersWg, stats)
	}

	serverWg.Wait()

	for i := 0; i < USER_COUNT; i++ {
		close(userChans[i])
	}
	usersWg.Wait() 
	
	total := 0;

	Log("\nSUMMARY")
	for i := 0; i < USER_COUNT; i++ {
		Log(fmt.Sprintf("User %d received %d messages", i + 1, stats[i]))
		total = total + stats[i]
	}

	Log(fmt.Sprintf("Total: %d messages", total))
}
