package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

const PHILOSOPHER_COUNT = 5
const MEAL_COUNT = 3

var logMutex sync.Mutex

func Log(msg string) {
	logMutex.Lock()
	fmt.Println(msg)
	logMutex.Unlock()
}

var Forks [PHILOSOPHER_COUNT]sync.Mutex

func Philosopher(id int, wg *sync.WaitGroup) {
	defer wg.Done()

	MealsEaten := 0
	Fails := 0

	LeftFork := id
	RightFork := (id + 1) % PHILOSOPHER_COUNT

	displayId := id + 1

	r := rand.New(rand.NewSource(time.Now().UnixNano() + int64(id)))

	RandomWait := func() {
		time.Sleep(time.Duration(r.Intn(500)) * time.Millisecond)
	}

	for MealsEaten < MEAL_COUNT {
		Log(fmt.Sprintf("Philosopher %d thinks...", displayId))
		RandomWait()

		if Forks[LeftFork].TryLock() {
			if Forks[RightFork].TryLock() {
				MealsEaten++
				Log(fmt.Sprintf("--- Philosopher %d eats (meal %d)", displayId, MealsEaten))
				RandomWait()

				Forks[RightFork].Unlock()
				Forks[LeftFork].Unlock()
				Log(fmt.Sprintf("Philosopher %d dropped both forks", displayId))
			} else {
				Forks[LeftFork].Unlock() 
				Fails++
				Log(fmt.Sprintf("[!] Philosopher %d couldn't get right fork, drops left one", displayId))
				RandomWait()
			}
		} else {
			Fails++
			Log(fmt.Sprintf("[!] Philosopher %d couldn't get left fork", displayId))
			RandomWait()
		}
	}

	Log(fmt.Sprintf("\n[SUCCESS] Philosopher %d finished eating, failures: %d\n", displayId, Fails))
}

func main() {
	var wg sync.WaitGroup

	wg.Add(PHILOSOPHER_COUNT)

	for i := 0; i < PHILOSOPHER_COUNT; i++ {
		go Philosopher(i, &wg)
	}

	wg.Wait()
}
