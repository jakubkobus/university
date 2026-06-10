import java.util.concurrent.SynchronousQueue;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.TimeUnit;

public class Main {
  static final int USER_COUNT = 20;
  static final int MESSAGE_COUNT = 50;

  static volatile boolean isRunning = true;

  static class Message {
    int target;
    int sender;

    Message(int target, int sender) {
      this.target = target;
      this.sender = sender;
    }
  }

  static synchronized void Log(String msg) {
    System.out.println(msg);
  }

  static SynchronousQueue<Message> serverQueue = new SynchronousQueue<>();
  static SynchronousQueue<Message>[] userQueues = new SynchronousQueue[USER_COUNT];

  static class ServerTask extends Thread {
    @Override
    public void run() {
      try {
        for(int i = 0; i < USER_COUNT * MESSAGE_COUNT; i++) {
          Message msg = serverQueue.take();    
          userQueues[msg.target].put(msg);
        }
      } catch(InterruptedException e) {}
    }
  }

  static class UserTask extends Thread {
    int id;
    int ReceivedCount = 0;

    UserTask(int id) {
        this.id = id;
    }

    @Override
    public void run() {
      int Sent = 0;
      int displayId = id + 1; 

      while(true) {
          try {
            Message inMsg = userQueues[id].poll();
            
            if(inMsg != null) {
              ReceivedCount++;
              Log("[<-] User " + displayId + " received from " + (inMsg.sender + 1));
            } else {
              if(Sent < MESSAGE_COUNT) {
                int target = ThreadLocalRandom.current().nextInt(USER_COUNT);
                Message outMsg = new Message(target, id);

                boolean sentOk = serverQueue.offer(outMsg);

                if(sentOk) {
                  Sent++;
                  Log("[->] User " + displayId + " sent to " + (target + 1));
                } else {
                  Thread.sleep(50);
                }
              } else {
                if(!isRunning) {
                  break;
                }
                
                inMsg = userQueues[id].poll(50, TimeUnit.MILLISECONDS);
                if(inMsg != null) {
                  ReceivedCount++;
                  Log("[<-] User " + displayId + " received from " + (inMsg.sender + 1));
                }
              }
            }
          } catch(InterruptedException e) {
            break;
          }
      }
    }
  }

  public static void main(String[] args) throws InterruptedException {
    Log("SERVER READY");

    for(int i = 0; i < USER_COUNT; i++) {
      userQueues[i] = new SynchronousQueue<>();
    }

    ServerTask server = new ServerTask();
    server.start();

    UserTask[] users = new UserTask[USER_COUNT];
    for(int i = 0; i < USER_COUNT; i++) {
      users[i] = new UserTask(i);
      users[i].start();
    }

    server.join();

    isRunning = false;
    for(int i = 0; i < USER_COUNT; i++) {
      users[i].join();
    }

    Log("\nSUMMARY");
    for(int i = 0; i < USER_COUNT; i++) {
      Log("User " + (i + 1) + " received " + users[i].ReceivedCount + " messages");
    }
  }
}
