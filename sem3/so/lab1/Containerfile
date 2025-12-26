FROM ubuntu:latest

RUN apt-get update && \
  apt-get install -y gcc && \
  apt-get clean

WORKDIR /app

COPY hello.c .

RUN gcc hello.c -o hello

CMD ["./hello"]

