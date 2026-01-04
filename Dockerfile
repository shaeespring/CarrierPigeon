FROM ubuntu:24.04

WORKDIR /app

COPY backend backend
COPY lists lists

RUN apt-get update
RUN apt-get install -y build-essential
RUN apt-get install -y make

WORKDIR /app/backend

RUN make all

WORKDIR /app

ENV PATH="/app/backend:$PATH"
